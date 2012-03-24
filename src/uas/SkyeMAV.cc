#include <QDebug>
#include "SkyeMAV.h"

SkyeMAV::SkyeMAV(MAVLinkProtocol* mavlink, int id) :
UAS(mavlink, id),
airframe(QGC_AIRFRAME_SKYE),
manualXThrust(0),
manualYThrust(0),
manualZThrust(0),
manualXMoment(0),
manualYMoment(0),
manualZMoment(0),
manual1Thrust(0),
manual2Thrust(0),
manual3Thrust(0),
manual4Thrust(0),
manual1Orientation(0),
manual2Orientation(0),
manual3Orientation(0),
manual4Orientation(0)
{

    this->setUASName("SKYE");
}

SkyeMAV::~SkyeMAV(void)
{
}

void SkyeMAV::receiveMessage(LinkInterface *link, mavlink_message_t message)
{
#ifdef MAVLINK_ENABLED_SKYE
    if (message.sysid == uasId)  // make sure the message is for the right UAV
    {
        if (!link) return;
        switch (message.msgid)
        {
        case MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL:
        {
            // TO DO: This is no receiving message, but one to send!!!
            break;
        }
        case MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL:
        {
            // TO DO: This is no receiving message, but one to send!!!
            break;
        }
        case MAVLINK_MSG_ID_SKYE_TEST_MOTORS:
        {
            // TO DO: This is no receiving message, but one to send!!!
            break;
        }

        case MAVLINK_MSG_ID_SKYE_BATTERY_STATUS:
        {
            mavlink_skye_battery_status_t battery;
            mavlink_msg_skye_battery_status_decode(&message, &battery);

            emit batteryPackChanged(&battery);

        }
        break;
        case MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED:
        {
        // Copied from PxQuadMAV.cc
            // FIXME Kind of a hack to load data from disk
            mavlink_skye_cam_image_triggered_t img;
            mavlink_msg_skye_cam_image_triggered_decode(&message, &img);
            emit imageStarted(img.timestamp);
        }
        break;
        case MAVLINK_MSG_ID_SKYE_HOME_MAXON:
        {
            // This message is only for sending...
        }
        break;
        default:
        {
            // Let UAS handle the default message set
            UAS::receiveMessage(link, message);
            break;
            }
        }
    }
#else
    // Let UAS handle the default message set
    UAS::receiveMessage(link, message);
    Q_UNUSED(link);
    Q_UNUSED(message);
#endif // MAVLINK_ENABLED_SKYE
}


void SkyeMAV::setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4)
{
#ifdef MAVLINK_ENABLED_SKYE

    sendTestphaseControlCommands(Thrust1, Thrust2, Thrust3, Thrust4, Orientation1, Orientation2, Orientation3, Orientation4);
    qDebug() << "sendTestphaseControlCommands aufgerufen " << Thrust1;

#else
    Q_UNUSED(Thrust1);
    Q_UNUSED(Thrust2);
    Q_UNUSED(Thrust3);
    Q_UNUSED(Thrust4);
    Q_UNUSED(Orientation1);
    Q_UNUSED(Orientation2);
    Q_UNUSED(Orientation3);
    Q_UNUSED(Orientation4);

#endif // MAVLINK_ENABLED_SKYE
}

void SkyeMAV::setManualControlCommands6DoF(double x , double y , double z , double a , double b, double c)
{
#ifdef MAVLINK_ENABLED_SKYE
    qDebug() << "Recent Mode: " << mode << ": " << getShortModeTextFor(mode);

    //if (mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY)
    {
        if ((mode == MAV_MODE_DIRECT_CONTROL_DISARMED) || (mode == MAV_MODE_DIRECT_CONTROL_ARMED))
        {
            sendDirectControlCommands(x, y, z, a, b, c);
        }else if ((mode == MAV_MODE_ASSISTED_CONTROL_DISARMED) || (mode == MAV_MODE_ASSISTED_CONTROL_ARMED))
        {
            sendAssistedControlCommands(x, y, z, a, b, c);
        }else{
            qDebug() << "3DMOUSE/MANUAL CONTROL: IGNORING COMMANDS: Set mode to MANUAL and CUSTOM to send 3DMouse commands!";
        }
    }

#else
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);
    Q_UNUSED(a);
    Q_UNUSED(b);
    Q_UNUSED(c);
#endif // MAVLINK_ENABLED_SKYE
}

//AL (06.03.12)
void SkyeMAV::sendTestphaseControlCommands(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 )
{
#ifdef MAVLINK_ENABLED_SKYE
    // Scale values (The Testphase widget is designed that no scaling is needed from UI to the machine the value shouldn't change)
    //double thrustScaling = 1.0f;
    //double orientationScaling = 1.0f;

    manual1Thrust = Thrust1;//*thrustScaling;
    manual2Thrust = Thrust2;//*thrustScaling;
    manual3Thrust = Thrust3;//*thrustScaling;
    manual4Thrust = Thrust4;//*thrustScaling;
    manual1Orientation = Orientation1;//*orientationScaling;
    manual2Orientation = Orientation2;//*orientationScaling;
    manual3Orientation = Orientation3;//*orientationScaling;
    manual4Orientation = Orientation4;//*orientationScaling;

    mavlink_message_t message;

    mavlink_msg_skye_test_motors_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (int)manual1Thrust, (int)manual2Thrust, (int)manual3Thrust,(int)manual4Thrust, (int)manual1Orientation, (int)manual2Orientation, (int)manual3Orientation,(int)manual4Orientation);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT TESTPHASE CONTROL MESSAGE: 1Thrust" << manual1Thrust << " 2Thrust: " << manual2Thrust << " 3Thrust: " << manual3Thrust << " 4Thrust: " << manual4Thrust << " 1Orientation: " << manual1Orientation << " 2Orientation: " << manual2Orientation << " 3Orientation: " << manual3Orientation << " 4Orientation: " << manual4Orientation;

    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());


#endif // MAVLINK_ENABLED_SKYE
}

//AL (06.03.12)

void SkyeMAV::sendDirectControlCommands(double xThrust, double yThrust, double zThrust, double xMoment, double yMoment, double zMoment)
{
#ifdef MAVLINK_ENABLED_SKYE
    // Scale values
    double thrustScaling = 1.0f;
    double momentScaling = 1.0f;
    
    manualXThrust = xThrust * thrustScaling;
    manualYThrust = yThrust * thrustScaling;
    manualZThrust = zThrust * thrustScaling;
    manualXMoment = xMoment * momentScaling;
    manualYMoment = yMoment * momentScaling;
    manualZMoment = zMoment * momentScaling;
    
    mavlink_message_t message;
    
    mavlink_msg_skye_direct_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)manualXThrust, (float)manualYThrust, (float)manualZThrust, (float)manualXMoment, (float)manualYMoment, (float)manualZMoment);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT DIRECT CONTROL MESSAGE: xThrust" << manualXThrust << " yThrust: " << manualYThrust << " zThrust: " << manualZThrust << " xMoment: " << manualXMoment << " yMoment: " << manualYMoment << " zMoment: " << manualZMoment;
    
    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());
    
#endif // MAVLINK_ENABLED_SKYE
}


void SkyeMAV::sendAssistedControlCommands(double xVel, double yVel, double zVel, double xRot, double yRot, double zRot)
{
#ifdef MAVLINK_ENABLED_SKYE
    // Scale values
    double velScaling = 1.0f;
    double yawScaling = 1.0f;
    double pitchScaling = 1.0f;
    double rollScaling = 1.0f;
    
    manualXVel = xVel * velScaling;
    manualYVel = yVel * velScaling;
    manualZVel = zVel * velScaling;
    manualXRot = xRot * rollScaling;
    manualYRot = yRot * pitchScaling;
    manualZRot = zRot * yawScaling;
    
    mavlink_message_t message;
    
    mavlink_msg_skye_assisted_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)manualXVel, (float)manualYVel, (float)manualZVel, (float)manualXRot, (float)manualYRot, (float)manualZRot);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT ASSISTED CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
    
    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());
    
#endif // MAVLINK_ENABLED_SKYE
}

void SkyeMAV::takeImageShot(MAV_CAM_ID cam)
{
#ifdef MAVLINK_ENABLED_SKYE
    mavlink_message_t message;
    mavlink_msg_skye_cam_take_shot_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, cam, true);
    sendMessage(message);
#endif // MAVLINK_ENABLED_SKYE
}

void SkyeMAV::sendHomingCommand()
{
#ifdef MAVLINK_ENABLED_SKYE
    mavlink_message_t message;
    uint8_t homing = 1;

    mavlink_msg_skye_home_maxon_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, homing);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT HOMING COMMAND MESSAGE";
#endif // MAVLINK_ENABLED_SKYE
}