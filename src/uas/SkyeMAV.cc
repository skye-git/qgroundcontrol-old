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

#define QGC_SKYE_MAX_VEL_NORM 1.0
#define QGC_SKYE_LOOKAHEAD 2.0

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
        qDebug() << "[SKYE_MAV] RECEIVED MESSAGE NUMBER" << message.msgid;
        if (!link) return;
        switch (message.msgid)
        {
        case MAVLINK_MSG_ID_BATTERY_STATUS:
        {
            mavlink_battery_status_t battery;
            mavlink_msg_battery_status_decode(&message, &battery);

            emit batteryPackChanged(&battery);
            uint16_t lowestVolt = 99999;
            lowestVolt = (battery.voltage_cell_1 < lowestVolt && battery.voltage_cell_1 > 0) ? battery.voltage_cell_1 : lowestVolt;
            lowestVolt = (battery.voltage_cell_2 < lowestVolt && battery.voltage_cell_2 > 0) ? battery.voltage_cell_2 : lowestVolt;
            lowestVolt = (battery.voltage_cell_3 < lowestVolt && battery.voltage_cell_3 > 0) ? battery.voltage_cell_3 : lowestVolt;
            lowestVolt = (battery.voltage_cell_4 < lowestVolt && battery.voltage_cell_4 > 0) ? battery.voltage_cell_4 : lowestVolt;
            lowestVolt = (battery.voltage_cell_5 < lowestVolt && battery.voltage_cell_5 > 0) ? battery.voltage_cell_5 : lowestVolt;
            lowestVolt = (battery.voltage_cell_6 < lowestVolt && battery.voltage_cell_6 > 0) ? battery.voltage_cell_6 : lowestVolt;

            // check low voltage -> alert required
            if (lowestVolt < 22000)
            {
                emit batteryLow(0.001*(double)lowestVolt);
            }
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

    manualXVel = x * (double)sensitivityFactorTrans;
    manualYVel = y * (double)sensitivityFactorTrans;
    manualZVel = z * (double)sensitivityFactorTrans - (double)liftFactor;
    manualXRot = a * (double)sensitivityFactorRot + addRollValue;
    manualYRot = b * (double)sensitivityFactorRot + addPitchValue;
    manualZRot = c * (double)sensitivityFactorRot + addYawValue;
//    qDebug() << ": SENT 6DOF CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
    sendManualControlCommands6DoF(manualXVel, manualYVel, manualZVel, manualXRot, manualYRot, manualZRot);
}

void SkyeMAV::set6DOFCommandsByWidget(double x, double y, double z, double a, double b, double c)
{
    sendManualControlCommands6DoF(x, y, z, a, b, c);
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
        qDebug() << "SENT 6DOF CONTROL MESSAGE:" << x << y << z << phi << theta << psi;
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
    qDebug("Sent LED Color Message");
}

