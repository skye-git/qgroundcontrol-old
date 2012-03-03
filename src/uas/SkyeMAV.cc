#include <QDebug>
#include "SkyeMAV.h"

SkyeMAV::SkyeMAV(MAVLinkProtocol* mavlink, int id) :
UAS(mavlink, id),
manualXThrust(0),
manualYThrust(0),
manualZThrust(0),
manualXMoment(0),
manualYMoment(0),
manualZMoment(0)
{
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
            case MAVLINK_MSG_ID_DIRECT_CONTROL:
            {
                // TO DO: This is no receiving message, but one to send!!!
                break;
            }
            case MAVLINK_MSG_ID_ASSISTED_CONTROL:
            {
                // TO DO: This is no receiving message, but one to send!!!
                break;
            }
                
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

void SkyeMAV::setManualControlCommandsByMouse(double x , double y , double z , double a , double b, double c)
{
#ifdef MAVLINK_ENABLED_SKYE
    
    qDebug() << "Recent Mode: " << mode;
    qDebug() << "Direct is " << MAV_MODE_DIRECT_CONTROL_ARMED;
    switch (mode)
    {
        case (MAV_MODE_DIRECT_CONTROL_ARMED -1):        // FIXME, remove -1
        {
            sendDirectControlCommands(x, y, z, a, b, c);
        }
            break;
        case (MAV_MODE_ASSISTED_CONTROL_ARMED -1):      // FIXME, remove -1
        {
            sendAssistedControlCommands(x, y, z, a, b, c);
        }
            break;
        default:
        {
            qDebug() << "3DMOUSE/MANUAL CONTROL: IGNORING COMMANDS: Set mode to MANUAL to send 3DMouse commands first";
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
    
    mavlink_msg_direct_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)manualXThrust, (float)manualYThrust, (float)manualZThrust, (float)manualXMoment, (float)manualYMoment, (float)manualZMoment);
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
    
    mavlink_msg_assisted_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)manualXVel, (float)manualYVel, (float)manualZVel, (float)manualXRot, (float)manualYRot, (float)manualZRot);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT ASSISTED CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
    
    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());
    
#endif // MAVLINK_ENABLED_SKYE
}

