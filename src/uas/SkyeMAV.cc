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
//    currentTrajectoryStamp(0),
    inputMode(QGC_INPUT_MODE_TOUCH)
{
    imagePacketsArrived = 0;
    this->setUASName("SKYE");
//    connect(&trajectoryTimer, SIGNAL(timeout()), this, SLOT(followTrajectory()));
//    trajectoryTimer.start(100);
}

SkyeMAV::~SkyeMAV(void)
{
}

void SkyeMAV::receiveMessage(LinkInterface *link, mavlink_message_t message)
{
    if (message.sysid == uasId)  // make sure the message is for the right UAV
    {
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
    if (base_mode & MAV_MODE_FLAG_GUIDED_ENABLED)
    {
        manualXRot = a * (double)sensitivityFactorRot;
        manualYRot = b * (double)sensitivityFactorRot;
        manualZRot = c * (double)sensitivityFactorRot;
        qDebug() << "Set manual rotation for FAC" << a << b << c;

    }else if (base_mode & MAV_MODE_FLAG_AUTO_ENABLED)
    {
        manualZVel = z * (double)sensitivityFactorTrans;
        manualXRot = a * (double)sensitivityFactorRot;
        manualYRot = b * (double)sensitivityFactorRot;
        manualZRot = c * (double)sensitivityFactorRot;
        qDebug() << "Set lift and manual rotation for HAC" << z << a << b << c;

    }else if (base_mode & MAV_MODE_FLAG_MANUAL_INPUT_ENABLED)
    {
        manualXVel = x * (double)sensitivityFactorTrans;
        manualYVel = y * (double)sensitivityFactorTrans;
        manualZVel = z * (double)sensitivityFactorTrans - (double)liftFactor;
        manualZVel = qMin((double)sensitivityFactorTrans, qMax(-(double)sensitivityFactorTrans, manualZVel));
        manualXRot = a * (double)sensitivityFactorRot;
        manualYRot = b * (double)sensitivityFactorRot;
        manualZRot = c * (double)sensitivityFactorRot;
        sendManualControlCommands6DoF(manualXVel, manualYVel, manualZVel, manualXRot, manualYRot, manualZRot);
        //    qDebug() << ": SENT 6DOF CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
    }
}

void SkyeMAV::set6DOFCommandsByWidget(double x, double y, double z, double a, double b, double c)
{
    sendManualControlCommands6DoF(x, y, z, a, b, c);
}

void SkyeMAV::sendManualControlCommands6DoF(double x, double y, double z, double phi, double theta, double psi)
{
    if (this->base_mode & MAV_MODE_FLAG_SAFETY_ARMED)
    {
        mavlink_message_t message;
        mavlink_msg_setpoint_6dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)x, (float)y, (float)z, (float)phi, (float)theta, (float)psi);
        sendMessage(message);
        //qDebug() << SENT 6DOF CONTROL MESSAGE:" << x << y << z << phi << theta << psi;
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


/*
void SkyeMAV::followTrajectory()
{
    if (base_mode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED) // Half or Full Automatic Control
    {
        qDebug() << "SkyeMAV::followTrajectory";
        QVector<double> trajX;
        QVector<double> trajY;
        QVector<double> trajZ;
        waypointManager.getEditableTrajectory()->getVector(trajX, trajY, trajZ);
//if (!(waypointManager.getEditableTrajectory()->getVector(trajX, trajY, trajZ)));
//        {
//            qDebug() << "SkyeMAV: Trajectory empty or not valid";
//            return;
//        }
        if (trajX.isEmpty()){
            return;
        }
        if (trajX.size() <= currentTrajectoryStamp && currentTrajectoryStamp > 0)
        {
            currentTrajectoryStamp = trajX.size() - 1;
        }

        deltaLatLngAlt[0] = trajX.value(currentTrajectoryStamp) - latitude;
        deltaLatLngAlt[1] = trajY.value(currentTrajectoryStamp) - longitude;
        deltaLatLngAlt[2] = trajZ.value(currentTrajectoryStamp) - altitude;

        // Translate to local coordinates
        deltaXYZ[0] = deltaLatLngAlt[0] * 3.141592 / 180.0 * QGC_EARTH_RADIUS * QGC_COS_LATITUDE;
        deltaXYZ[1] = deltaLatLngAlt[1] * 3.141592 / 180.0 * QGC_EARTH_RADIUS;
        deltaXYZ[2] = deltaLatLngAlt[2];

        deltaNorm = qSqrt(deltaXYZ[0]*deltaXYZ[0] + deltaXYZ[1]*deltaXYZ[1] + deltaXYZ[2]+deltaXYZ[2]);
        deltaNorm2D = qSqrt(deltaXYZ[0]*deltaXYZ[0] + deltaXYZ[1]*deltaXYZ[1]);
        //        qDebug() << "Follows point" << currentTrajectoryStamp << "deltaLat" << deltaLatLngAlt[0] << "deltaLng" << deltaLatLngAlt[1] << "deltaAlt" << deltaLatLngAlt[2]<< "altitude" << altitude;
        qDebug() << "deltaX" << deltaXYZ[0] << "deltaY" << deltaXYZ[1] << "deltaZ" << deltaXYZ[2] << "deltaNorm" << deltaNorm;

        InertialToCamera(deltaXYZ, deltaCam);
        qDebug() << "DeltaCam" << deltaCam[0] << deltaCam[1] << deltaCam[2];

        if (base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY ) //&& !qIsNaN(deltaCam[0]) && !qIsNaN(deltaCam[1]) && !qIsNaN(deltaCam[2])
        {
            if (base_mode & MAV_MODE_FLAG_DECODE_POSITION_AUTO) // FULL AUTOMATIC CONTROL
            {
                if (deltaNorm < QGC_SKYE_MAX_VEL_NORM / sensitivityFactorTrans)
                {
                    qDebug() << "Send original 6DOF manual control command for FAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * deltaCam[0],
                                                sensitivityFactorTrans * deltaCam[1],
                                                sensitivityFactorTrans * deltaCam[2],
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                } else {
                    qDebug() << "Send original 6DOF manual control command for FAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[0],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[1],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[2],
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                }
                if ( deltaNorm < QGC_SKYE_LOOKAHEAD )
                {
                    qDebug() << "REACHED POINT" << currentTrajectoryStamp << "OF TRAJECTORY";
                    if (trajX.size() > currentTrajectoryStamp + 1)
                        currentTrajectoryStamp++;
                }
            }
            else        // HALF AUTOMATIC CONTROL
            {
                if (deltaNorm2D < QGC_SKYE_MAX_VEL_NORM / sensitivityFactorTrans)
                {
                    qDebug() << "Send original 6DOF manual control command for HAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * deltaCam[0],
                                                sensitivityFactorTrans * deltaCam[1],
                                                manualZVel,
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                } else {
                    qDebug() << "Send reduced 6DOF manual control command for HAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm2D * deltaCam[0],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm2D * deltaCam[1],
                                                manualZVel,
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                }
                if ( deltaNorm2D < QGC_SKYE_LOOKAHEAD )
                {
                    qDebug() << "REACHED POINT" << currentTrajectoryStamp << "OF TRAJECTORY";
                    if (trajX.size() > currentTrajectoryStamp + 1)
                        currentTrajectoryStamp++;
                }
            }
        }
    }
}

void SkyeMAV::InertialToCamera(const double inertFrame[3], double camFrame[3])
{
    updateTrigonometry();
    int i = 0;
    int k = 0;
    for (i = 0; i<3; i++)
    {
        camFrame[i] = 0;
        for (k = 0; k<3; k++)
        {
            camFrame[i] += fromItoC[i*3 + k] * inertFrame[k];
        }
    }
}

void SkyeMAV::updateTrigonometry()
{
    cosPhi = qCos(roll);
    sinPhi = qSin(roll);
    cosTheta = qCos(pitch);
    sinTheta = qSin(pitch);
    cosPsi = qCos(yaw);
    sinPsi = qSin(yaw);
    fromItoC[0] = cosTheta*cosPsi;
    fromItoC[1] = cosTheta*sinPsi;
    fromItoC[2] = -sinTheta;
    fromItoC[3] = sinPhi*sinTheta*cosPsi - cosPhi*sinPsi;
    fromItoC[4] = sinPhi*sinTheta*sinPsi + cosPhi*cosPsi;;
    fromItoC[5] = sinPhi*cosTheta;
    fromItoC[6] = cosPhi*sinTheta*cosPsi + sinPhi*sinPsi;
    fromItoC[7] = cosPhi*sinTheta*sinPsi - sinPhi*cosPsi;
    fromItoC[8] = cosPhi*cosTheta;
//    qDebug() << "I to C" << fromItoC[0] << fromItoC[1] << fromItoC[2] << fromItoC[3] << fromItoC[4] << fromItoC[5] << fromItoC[6] << fromItoC[7] << fromItoC[8];
}
*/
