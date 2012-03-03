#ifndef SKYEMAV_H
#define SKYEMAV_H


#include "UAS.h"

class SkyeMAV : public UAS
{
    Q_OBJECT
    Q_INTERFACES(UASInterface)
public:
    SkyeMAV(MAVLinkProtocol* mavlink, int id);
    ~SkyeMAV();
public slots:
    /** @brief Receive a MAVLink message from this MAV */
    void receiveMessage(LinkInterface* link, mavlink_message_t message);
    /** @brief Send the 6 DOF command (from 3d Mouse) to MAV */
    void setManualControlCommandsByMouse(double x , double y , double z , double a , double b , double c );

protected:
    /** @brief Send a Direct Control Command to MAV: */
    void sendDirectControlCommands(double xThrust, double yThrust, double zThrust, double xMoment, double yMoment, double zMoment);
    /** @brief Send a Assisted Control Command to MAV: */
    void sendAssistedControlCommands(double xVel, double yVel, double zVel, double xRot, double yRot, double zRot);

    double manualXThrust;      ///< X Thrust set by human pilot
    double manualYThrust;      ///< Y Thrust set by human pilot
    double manualZThrust;      ///< Z Thrust set by human pilot
    double manualXMoment;      ///< Moment around X axis set by human pilot
    double manualYMoment;      ///< Moment around Y axis set by human pilot
    double manualZMoment;      ///< Moment around Z axis set by human pilot

    double manualXVel;          ///< X velocity set by human pilot
    double manualYVel;          ///< Y velocity set by human pilot
    double manualZVel;          ///< Z velocity set by human pilot
    double manualXRot;          ///< Roll (x axis) set by human pilot
    double manualYRot;          ///< Pitch (y axis) set by human pilot
    double manualZRot;          ///< Yaw (z axis) set by human pilot

};

#endif // SKYEMAV_H
