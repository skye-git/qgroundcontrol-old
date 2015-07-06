#include <QDebug>
#include <qmath.h>
#include "SkyeMAV.h"
//#include "UDPLink.h"

SkyeMAV::SkyeMAV(MAVLinkProtocol* mavlink, int id) :
    UAS(mavlink, id),
    airframe(QGC_AIRFRAME_SKYE),
    manualXThrust(0.0),
    manualYThrust(0.0),
    manualZThrust(0.0),
    manualXMoment(0.0),
    manualYMoment(0.0),
    manualZMoment(0.0),
    manualXVel(0.0),
    manualYVel(0.0),
    manualZVel(0.0),
    manualXRot(0.0),
    manualYRot(0.0),
    manualZRot(0.0),
    sensitivityFactorTrans(QGC_SENSITIVITY_TRANS_DEFAULT),
    sensitivityFactorRot(QGC_SENSITIVITY_ROT_DEFAULT),
    liftValue(QGC_LIFT_VALUE_DEFAULT*LIFT_RESOLUTION),
    liftValueFloat(QGC_LIFT_VALUE_DEFAULT),
    addRollValue(0.0),
    addPitchValue(0.0),
    addYawValue(0.0),
    inputMode(QGC_INPUT_MODE_NONE)
{
    imagePacketsArrived = 0;
    this->setUASName("SKYE");

//    this->connect(this, SIGNAL(parameterChanged(int,int,QString,QVariant)), this, SLOT(onboardParameterChanged(int,int,QString,QVariant)));
}

SkyeMAV::~SkyeMAV(void)
{
}

void SkyeMAV::receiveMessage(LinkInterface *link, mavlink_message_t message)
{
    if (message.sysid == uasId)  // make sure the message is for the right UAV
    {
        //qDebug() << "[SKYE_MAV] RECEIVED MESSAGE NUMBER" << message.msgid;
        if (!link) return;
        switch (message.msgid)
        {
        case MAVLINK_MSG_ID_BATTERY_STATUS:
        {
            mavlink_battery_status_t battery;
            mavlink_msg_battery_status_decode(&message, &battery);

            emit batteryStatusChanged(&battery);

        }
        break;
        case MAVLINK_MSG_ID_ALLOCATION_OUTPUT_RAW:
        {
            mavlink_allocation_output_raw_t allocation;
            mavlink_msg_allocation_output_raw_decode(&message, &allocation);

            emit allocationValueChanged(&allocation);
        }
        break;
        case MAVLINK_MSG_ID_ACTUATION_STATUS:
        {
            mavlink_actuation_status_t au_status;
            mavlink_msg_actuation_status_decode(&message, &au_status);

            emit actuationStatusChanged(&au_status);
        }
        break;


        // Ignore these messages
        case MAVLINK_MSG_ID_SETPOINT_6DOF:
        case MAVLINK_MSG_ID_SETPOINT_12DOF:
        case MAVLINK_MSG_ID_RANGE_SENSOR_RAW:
        case MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED:
        case MAVLINK_MSG_ID_ATTITUDE_CTRL_OUTPUT_RAW:
        case MAVLINK_MSG_ID_POSITION_CTRL_OUTPUT_RAW:
            break;

        default:
        {
            // Let UAS handle the default message set
            UAS::receiveMessage(link, message);
        }
        break;
        }
    } else {
        qDebug() << "[SkyeMAV] Got Message with wrong sysid" << message.sysid;
    }
}

void SkyeMAV::onboardParameterChanged(int uas, int component, QString parameterName, QVariant value) {
	if (parameterName ==  QString("SKYE_ALOC_CASE"))
	{
		//qDebug() << "[SkyeMAV] GOT PARAM" << rawValue.param_value;
		emit allocCaseChanged(value.toInt());
	}
}

void SkyeMAV::setManual6DOFControlCommands(double x , double y , double z , double a , double b, double c)
{
    // make sure input device is defined
    if (inputMode != QGC_INPUT_MODE_NONE)
    {
        manualXVel = x * (double)sensitivityFactorTrans;
        manualYVel = y * (double)sensitivityFactorTrans;
        manualZVel = z * (double)sensitivityFactorTrans - (double)liftValueFloat;
        manualZVel = qMin((double)sensitivityFactorTrans, qMax(-(double)sensitivityFactorTrans, manualZVel));
        manualXRot = a * (double)sensitivityFactorRot + addRollValue;
        manualYRot = b * (double)sensitivityFactorRot + addPitchValue;
        manualZRot = c * (double)sensitivityFactorRot + addYawValue;
        //    qDebug() << ": SENT 6DOF CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
        sendManualControlCommands6DoF(manualXVel, manualYVel, manualZVel, manualXRot, manualYRot, manualZRot);
    } else {
        manualXVel = 0.0;
        manualYVel = 0.0;
        manualZVel = 0.0;
        manualXRot = 0.0;
        manualYRot = 0.0;
        manualZRot = 0.0;
    }
}

void SkyeMAV::set6DOFCommandsByWidget(double x, double y, double z, double a, double b, double c)
{
    // only accept widget inputs when no input device defined
    if (inputMode == QGC_INPUT_MODE_NONE)
    {
        sendManualControlCommands6DoF(x, y, z, a, b, c);
    }
}

void SkyeMAV::sendManualControlCommands6DoF(float x, float y, float z, float phi, float theta, float psi)
{
    if (this->base_mode & MAV_MODE_FLAG_SAFETY_ARMED)
    {
        // saturate values to [-1,1]
        x = x > 1.0 ? 1.0 : x;
        y = y > 1.0 ? 1.0 : y;
        z = z > 1.0 ? 1.0 : z;
        phi   = phi   > 1.0 ? 1.0 : phi;
        theta = theta > 1.0 ? 1.0 : theta;
        psi   = psi   > 1.0 ? 1.0 : psi;

        x = x < -1.0 ? -1.0 : x;
        y = y < -1.0 ? -1.0 : y;
        z = z < -1.0 ? -1.0 : z;
        phi   = phi   < -1.0 ? -1.0 : phi;
        theta = theta < -1.0 ? -1.0 : theta;
        psi   = psi   < -1.0 ? -1.0 : psi;

        mavlink_message_t message;
        mavlink_msg_setpoint_6dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId,
                                       x,
                                       y,
                                       z,
                                       phi,
                                       theta,
                                       psi);
        sendMessage(message);
        // qDebug() << "SENT 6DOF CONTROL MESSAGE:" << x << y << z << phi << theta << psi;
    }
}

void SkyeMAV::setTestphaseCommandsByWidget(double Thrust1 , double Thrust2 , double Thrust3 , double Thrust4 , double Orientation1 , double Orientation2, double Orientation3, double Orientation4, bool usePpm)
{
    if (usePpm) {
        // Negative thrust values are interpreted as PPM value (since skye2.1)
        sendManualControlCommands12DoF(-(float)Thrust1,
                                      -(float)Thrust2,
                                      -(float)Thrust3,
                                      -(float)Thrust4,
                                       0,
                                       0,
                                      (float)Orientation1,
                                      (float)Orientation2,
                                      (float)Orientation3,
                                      (float)Orientation4,
                                       0,
                                       0);
    } else {
        // Positive thrust values are interpreted as Newton (since skye2.1)
        sendManualControlCommands12DoF((float)Thrust1,
                                      (float)Thrust2,
                                      (float)Thrust3,
                                      (float)Thrust4,
                                       0,
                                       0,
                                      (float)Orientation1,
                                      (float)Orientation2,
                                      (float)Orientation3,
                                      (float)Orientation4,
                                       0,
                                       0);
    }
}

void SkyeMAV::sendManualControlCommands12DoF(float Thrust1 , float Thrust2 , float Thrust3 , float Thrust4 , float Thrust5 , float Thrust6 , float Orientation1 , float Orientation2, float Orientation3, float Orientation4, float Orientation5, float Orientation6 )
{
    if ((base_mode & MAV_MODE_FLAG_SAFETY_ARMED) && (base_mode & MAV_MODE_FLAG_TEST_ENABLED))
    {
        mavlink_message_t message;

        float inputValues[12];
        inputValues[0] = Thrust1;
        inputValues[6] = Orientation1;
        inputValues[1] = Thrust2;
        inputValues[7] = Orientation2;
        inputValues[2] = Thrust3;
        inputValues[8] = Orientation3;
        inputValues[3] = Thrust4;
        inputValues[9] = Orientation4;
        inputValues[4] = Thrust5;
        inputValues[10] = Orientation5;
        inputValues[5] = Thrust6;
        inputValues[11] = Orientation6;

        mavlink_msg_setpoint_12dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId,
                                                    inputValues);
        sendMessage(message);
        //qDebug() << ": SENT 8DOF CONTROL MESSAGE: 1Thrust" << Thrust1 << " 2Thrust: " << Thrust2 << " 3Thrust: " << Thrust3 << " 4Thrust: " << Thrust4 << " 1Orientation: " << Orientation1 << " 2Orientation: " << Orientation2 << " 3Orientation: " << Orientation3 << " 4Orientation: " << Orientation4;
    }

}

void SkyeMAV::setModeCommand(int mode)
{
	mavlink_message_t message;

	mavlink_msg_command_long_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId,
								  (uint8_t)MAV_COMP_ID_ALL, MAV_CMD_DO_SET_MODE, 1, mode, 0, 0, 0, 0, 0, 0);

    sendMessage(message);
}


uint8_t SkyeMAV::getMode()
{
    return this->base_mode;
}

void SkyeMAV::setInputMode(SkyeMAV::QGC_INPUT_MODE input, bool active)
{
    bool oldInputState = inputMode & input;
    qDebug() << "[SkyeMAV] setInputMode: request flag" << input << "set from" << oldInputState << "to" << active;

    // check whether input mode has changed
    if (oldInputState != active)
    {
        qDebug() << "[SkyeMAV] Set input" << input << "to" << active;
        if (active)
        {
			// Activate this input
			inputMode += input;
        } else {
			// Deactivate this input
            inputMode -= input;
        }

        emit inputModeChanged(inputMode);
    } else {
        // do nothing
        qDebug() << "[SkyeMAV] Input" << input << "was already" << active;
    }
}

void SkyeMAV::setInputMode(SkyeMAV::QGC_INPUT_MODE input)
{
    // check if input mode changes
    if (inputMode != input) {
        inputMode = input;
        emit inputModeChanged(inputMode);
    } else {
        // do nothing
        qDebug() << "[SkyeMAV] Input was already" << inputMode;
    }
}

void SkyeMAV::updateMouseInputStatus(bool active)
{
    if (active == false)
    {
        // 3dMouse starting not succeded. User must press button again
        if ((inputMode & QGC_INPUT_MODE_MOUSE) == true)
        {
            inputMode -= QGC_INPUT_MODE_MOUSE;
        }
        emit resetMouseInput(false);
    } else {
        // 3dMouse starting succeded,
        if ((inputMode & QGC_INPUT_MODE_MOUSE) == false)
        {
            inputMode += QGC_INPUT_MODE_MOUSE;
        }
        emit resetMouseInput(true);
    }


}

void SkyeMAV::sendLedColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency)
{
    mavlink_message_t msg;
    mavlink_msg_led_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, ledId, red, green, blue, mode, frequency);
    sendMessage(msg);
    qDebug() << "[SkyeMAV] Sent LED Color Message. ledId:" << ledId << "red: " << red << "green: " << green << "blue: " << blue << "mode: " << mode << "frequency" << frequency;
}

void SkyeMAV::sendAllocationCase(int disabledAU)
{
	//mavlink_message_t msg;
	//mavlink_msg_param_set_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, this->uasId, (uint8_t)MAV_COMP_ID_ALL, "SKYE_ALOC_CASE", (int32_t)disabledAU, (uint8_t)MAV_PARAM_TYPE_INT32);
	//sendMessage(msg);
    //setParameter(mavlink->getComponentId(), QString("SKYE_ALOC_CASE"), QVariant((int32_t)disabledAU));
    qDebug() << "[SkyeMAV] Sent SKYE_ALOC_CASE" << disabledAU;
}

void SkyeMAV::sendAUReset(int auId)
{
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, this->uasId, (uint8_t)MAV_COMP_ID_ALL, MAV_CMD_SKYE_RESET_AU, 0, (float)auId, 1.0f, 0, 0, 0, 0, 0);
    sendMessage(msg);
    qDebug() << "[SkyeMAV] Sent reset command for AU id" << auId;
}

void SkyeMAV::sendSkyeConfiguration(double *quaternions) // [4][6]
{
    // reshape multidimensional array
    double q[4][6];
    memcpy(q, quaternions, sizeof(q));

    mavlink_message_t msg;
    mavlink_actuation_configuration_t au_config;
    for (int i = 0; i<4; i++)
    {
        au_config.quat_au1[i] = q[i][0];
        au_config.quat_au2[i] = q[i][1];
        au_config.quat_au3[i] = q[i][2];
        au_config.quat_au4[i] = q[i][3];
        au_config.quat_au5[i] = q[i][4];
        au_config.quat_au6[i] = q[i][5];
    }
    mavlink_msg_actuation_configuration_encode(mavlink->getSystemId(), mavlink->getComponentId(), &msg, &au_config);
    sendMessage(msg);
    qDebug() << "[SkyeMAV] Sent actuation configuration for Skye";
}

void SkyeMAV::setLiftValue(int val)
{
    if (val != liftValue and val >= 0 and val <= LIFT_RESOLUTION)
    {
        liftValue = val;
        qDebug() << "[SkyeMAV] lift factor" << val;
        emit liftValueChanged(liftValue);
        liftValueFloat = liftValue / (float)LIFT_RESOLUTION;
    }

}

void SkyeMAV::setSensitivityFactorTrans(float val)
{
    if (sensitivityFactorTrans!= val)
    {
        sensitivityFactorTrans = val;
        qDebug() << "[SkyeMAV] sensitivity translation" << val;
        emit sensitivityTransChanged((double)sensitivityFactorTrans);
    }
}

void SkyeMAV::setSensitivityFactorRot(float val)
{
    if (sensitivityFactorRot!= val)
    {
        sensitivityFactorRot = val;
        qDebug() << "[SkyeMAV] sensitivity rotation" << val;
        emit sensitivityRotChanged((double)sensitivityFactorRot);
    }
}




