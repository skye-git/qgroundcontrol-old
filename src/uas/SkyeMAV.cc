#include <QDebug>
#include <qmath.h>
#include "SkyeMAV.h"
#include "UDPLink.h"

#ifndef QGC_EARTH_RADIUS
#define QGC_EARTH_RADIUS 6367449.0
#endif

#ifndef QGC_COS_LATITUDE
#define QGC_COS_LATITUDE 0.67716
#endif

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
    sensitivityFactorTrans(0.0f),
    sensitivityFactorRot(0.0f),
    liftFactor(0.0f),
    addRollValue(0.0),
    addPitchValue(0.0),
    addYawValue(0.0),
//    currentTrajectoryStamp(0),
    inputMode(QGC_INPUT_MODE_TOUCH)
//    lowBatteryFront(false),
//    lowBatteryAU(false),
//    lowBattery(false),
//    lowBatteryMs(0)
{
    imagePacketsArrived = 0;
    this->setUASName("SKYE");
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

//            // LOW BATTERY ALARM
//            if (battery.status & BATTERY_STATUS_BIT_ATTACHED)
//            {
//                if (battery.voltage < (uint16_t)(SKYE_ALARM_VOLTAGE * 1000))
//                {
//                    lowBatteryAU = battery.accu_id;
//                    if (!lowBattery)
//                    {
//                        lowBatteryMs = QGC::groundTimeMilliseconds();
//                        lowBattery = true;
//                    }
//                    //emit batteryLow(0.001*(double)lowestVolt);
//                    emit batteryLow(0.001*(double)battery.voltage, true, QGC::groundTimeMilliseconds() - lowBatteryMs);
//                } else {
//                    if (lowBatteryAU == battery.accu_id)
//                    {
//                        lowBatteryAU = -1;
//                    }
//                    lowBattery = lowBatteryFront;
//                    if (!lowBattery)
//                    {
//                        emit batteryLow(0.0, false, 0);
//                    }
//                }
//            }
        }
        break;
        case MAVLINK_MSG_ID_BATTERY_CELLS_STATUS:
        {
            mavlink_battery_cells_status_t battery;
            mavlink_msg_battery_cells_status_decode(&message, &battery);

            emit batteryCellsStatusChanged(&battery);
        }
        break;
        case MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW:
        {
            mavlink_allocation_controller_raw_t allocation;
            mavlink_msg_allocation_controller_raw_decode(&message, &allocation);

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

        case MAVLINK_MSG_ID_SYS_STATUS:
        {
            mavlink_sys_status_t state;
            mavlink_msg_sys_status_decode(&message, &state);

            // Prepare for sending data to the realtime plotter, which is every field excluding onboard_control_sensors_present.
            quint64 time = getUnixTime();
            QString name = QString("M%1:SYS_STATUS.%2").arg(message.sysid);

            // Process CPU load.
            emit loadChanged(this,state.load/10.0f);
            emit valueChanged(uasId, name.arg("load"), "%", state.load/10.0f, time);

            // Battery charge/time remaining/voltage calculations
            currentVoltage = state.voltage_battery/1000.0f;
            lpVoltage = filterVoltage(currentVoltage);

            chargeLevel = state.battery_remaining;

            emit batteryChanged(this, currentVoltage, currentCurrent, getChargeLevel(), timeRemaining);
            emit valueChanged(uasId, name.arg("battery_remaining"), "%", getChargeLevel(), time);
            // emit voltageChanged(message.sysid, currentVoltage);
            emit valueChanged(uasId, name.arg("battery_voltage"), "V", currentVoltage, time);

            // And if the battery current draw is measured, log that also.
            if (state.current_battery != -1)
            {
                currentCurrent = ((double)state.current_battery)/100.0f;
                emit valueChanged(uasId, name.arg("battery_current"), "A", currentCurrent, time);
            }

//            // LOW BATTERY ALARM
//            if (currentVoltage < SKYE_ALARM_VOLTAGE)
//            {
//                lowBatteryFront = true;
//                if (!lowBattery)
//                {
//                    lowBatteryMs = QGC::groundTimeMilliseconds();
//                    lowBattery = true;
//                }
//                //emit batteryLow((double)lpVoltage);
//                emit batteryLow(currentVoltage, true, QGC::groundTimeMilliseconds() - lowBatteryMs);
//            } else {
//                lowBatteryFront = false;
//                lowBattery = (lowBatteryAU != -1);
//                if (!lowBattery)
//                {
//                    emit batteryLow(0.0, false, 0);
//                }
//            }

            // Trigger drop rate updates as needed. Here we convert the incoming
            // drop_rate_comm value from 1/100 of a percent in a uint16 to a true
            // percentage as a float. We also cap the incoming value at 100% as defined
            // by the MAVLink specifications.
            if (state.drop_rate_comm > 10000)
            {
                state.drop_rate_comm = 10000;
            }
            emit dropRateChanged(this->getUASID(), state.drop_rate_comm/100.0f);
            emit valueChanged(uasId, name.arg("drop_rate_comm"), "%", state.drop_rate_comm/100.0f, time);
        }
            break;

        case MAVLINK_MSG_ID_PARAM_VALUE:
        {
            mavlink_param_value_t rawValue;
            mavlink_msg_param_value_decode(&message, &rawValue);

            // check for value of SKYE_ALOC_CASE parameter
            if (strcmp(rawValue.param_id , "SKYE_ALOC_CASE") == 0)
            {
                //qDebug() << "[SkyeMAV] GOT PARAM" << rawValue.param_value;
                emit allocCaseChanged((int)rawValue.param_value);
            }

            // Let UAS handle this message additionally
            UAS::receiveMessage(link, message);

         }
         break;

        // Ignore these messages
        case MAVLINK_MSG_ID_SETPOINT_6DOF:
        case MAVLINK_MSG_ID_SETPOINT_8DOF:
        case MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_1_RAW:
        case MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_2_RAW:
        case MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_3_RAW:
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

void SkyeMAV::setManual6DOFControlCommands(double x , double y , double z , double a , double b, double c)
{
    // make sure input device is defined
    if (inputMode != QGC_INPUT_MODE_NONE)
    {
        manualXVel = x * (double)sensitivityFactorTrans;
        manualYVel = y * (double)sensitivityFactorTrans;
        manualZVel = z * (double)sensitivityFactorTrans - (double)liftFactor;
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

void SkyeMAV::sendManualControlCommands6DoF(double x, double y, double z, double phi, double theta, double psi)
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
        mavlink_msg_setpoint_6dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)x, (float)y, (float)z, (float)phi, (float)theta, (float)psi);
        sendMessage(message);
        //qDebug() << "SENT 6DOF CONTROL MESSAGE:" << x << y << z << phi << theta << psi;
    }
}

void SkyeMAV::setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4)
{
        sendManualControlCommands8DoF(Thrust1, Thrust2, Thrust3, Thrust4, Orientation1, Orientation2, Orientation3, Orientation4);

    //qDebug() << "sendTestphaseControlCommands aufgerufen " << Thrust1 << Thrust2 << Thrust3 << Thrust4;
}

void SkyeMAV::sendManualControlCommands8DoF(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 )
{
    if ((base_mode & MAV_MODE_FLAG_SAFETY_ARMED) && (base_mode & MAV_MODE_FLAG_TEST_ENABLED))
    {
        mavlink_message_t message;

        mavlink_msg_setpoint_8dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId,
                                             (float)Thrust1,
                                             (float)Thrust2,
                                             (float)Thrust3,
                                             (float)Thrust4,
                                             (float)Orientation1,
                                             (float)Orientation2,
                                             (float)Orientation3,
                                             (float)Orientation4);
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


void SkyeMAV::setInputMode(SkyeMAV::QGC_INPUT_MODE input)
{
    qDebug() << "[SkyeMAV] Set new input mode" << input;
    inputMode = input;
    emit inputModeChanged(inputMode);
}

void SkyeMAV::sendLedColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency)
{
    mavlink_message_t msg;
    mavlink_msg_led_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, ledId, red, green, blue, mode, frequency);
    sendMessage(msg);
    qDebug() << "[SkyeMAV] Sent LED Color Message. ledId:" << ledId << "red: " << red << "green: " << green << "blue: " << blue << "mode: " << mode << "frequency" << frequency;
}

void SkyeMAV::sendAUConfiguration(int disabledAU)
{
    mavlink_message_t msg;
    mavlink_msg_param_set_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, this->uasId, (uint8_t)MAV_COMP_ID_ALL, "SKYE_ALOC_CASE", (float)disabledAU, (uint8_t)MAV_PARAM_TYPE_REAL32);
    sendMessage(msg);
    qDebug() << "[SkyeMAV] Sent SKYE_ALOC_CASE" << disabledAU;
}

void SkyeMAV::sendAUReset(int auId)
{
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, this->uasId, (uint8_t)MAV_COMP_ID_ALL, MAV_CMD_RESET_SKYE_AU, 0, (float)auId, 1.0f, 0, 0, 0, 0, 0);
    sendMessage(msg);
    qDebug() << "[SkyeMAV] Sent reset command for AU id" << auId;
}
