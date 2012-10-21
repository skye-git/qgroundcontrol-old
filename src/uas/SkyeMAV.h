#ifndef SKYEMAV_H
#define SKYEMAV_H

#include <QPolygonF>
#include <QTimer>
#include <QVector>
#include "UAS.h"
#include "BluefoxReconfigure.h"

class SkyeMAV : public UAS
{
    Q_OBJECT
    Q_INTERFACES(UASInterface)
public:
    SkyeMAV(MAVLinkProtocol* mavlink, int id);
    ~SkyeMAV();


    /** @brief Get the airframe */
    int getAirframe() const
    {
        return airframe;
    }
    /** @brief Provide encapsulated mavlink image */
    QImage getImage();
    /** @brief Get mode */
    uint8_t getMode();
    /** @brief */
    int getCurrentTrajectoryStamp() { return currentTrajectoryStamp; }

private:
    /** @brief Transforms a Vector from inertial to uas coordinates */
    void InertialToCamera(const double inertFrame[3], double camFrame[3]);
    void updateTrigonometry();

public slots:
    /** @brief Set the specific airframe type */
    void setAirframe(int airframe)
    {
        this->airframe = airframe;
        emit systemSpecsChanged(uasId);
    }
    /** @brief Receive a MAVLink message from this MAV */
    void receiveMessage(LinkInterface* link, mavlink_message_t message);
    /** @brief Send the 6 DOF command (from 3d Mouse or Touch Input) to MAV */
    void setManualControlCommands6DoF(double x , double y , double z , double a , double b, double c);
    /** @brief Send the 8 DOF command (from Testphase Widget) to MAV */
    void setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 ); //AL (06.03.12)
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorTrans(float val) {sensitivityFactorTrans = val;}
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorRot(float val) {sensitivityFactorRot = val;}

    void followTrajectory();

signals:
    /** @brief Emit new detailed accu info for one accu pack
     *  @param packID see ENUM MAV_SKYE_BATTERY_PACK_ID
     *          voltCell1 Voltage of cell 1 in volt
     *          voltCell2 Voltage of cell 2 in volt
     *          voltCell3 Voltage of cell 3 in volt
     *          voltCell4 Voltage of cell 4 in volt
     *          current Recent current of accu pack in ampere
     *          percent Estimated remaining battery, -1 when not estimated
    **/
    void batteryPackChanged(mavlink_skye_battery_status_t* battery);
    void reportUDPLinkFailed(QString errorStr);


protected:
    /** Send a Manual 6DoF Control Command to MAV */
    void sendManualControlCommands6DoF(double x, double y, double z, double phi, double theta, double psi);
    /** @brief Send a Testphase Control Command to MAV: */
    void sendManualControlCommands8DoF(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 );

    int airframe;                   ///< The airframe type

    int manual1Thrust;          ///< Thrust for Motor 1 set by human pilot
    int manual2Thrust;          ///< Thrust for Motor 2 set by human pilot
    int manual3Thrust;          ///< Thrust for Motor 3 set by human pilot
    int manual4Thrust;          ///< Thrust for Motor 4 set by human pilot
    int manual1Orientation;     ///< Orientation for Motor 1 set by human pilot
    int manual2Orientation;     ///< Orientation for Motor 2 set by human pilot
    int manual3Orientation;     ///< Orientation for Motor 3 set by human pilot
    int manual4Orientation;     ///< Orientation for Motor 4 set by human pilot

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

    float sensitivityFactorTrans;    ///< Translational factor for manual control [remark: abs(deviceInput) <= 1 ]
    float sensitivityFactorRot;      ///< Rotational factor for manual control [remark: abs(deviceInput) <= 1 ]

    int currentTrajectoryStamp;
    QTimer trajectoryTimer;

    double deltaLatLngAlt[3];
    double deltaXYZ[3];
    double deltaCam[3];
    double deltaNorm;
    double deltaNorm2D;

    double cosPhi;
    double sinPhi;
    double cosTheta;
    double sinTheta;
    double cosPsi;
    double sinPsi;
    double fromItoC[9];
};

#endif // SKYEMAV_H
