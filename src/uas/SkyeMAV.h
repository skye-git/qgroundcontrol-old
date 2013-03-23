#ifndef SKYEMAV_H
#define SKYEMAV_H

#include <QPolygonF>
#include <QTimer>
#include <QVector>
#include "UAS.h"
//#include "BluefoxReconfigure.h"

class SkyeMAV : public UAS
{
    Q_OBJECT
    Q_INTERFACES(UASInterface)
public:
    SkyeMAV(MAVLinkProtocol* mavlink, int id);
    ~SkyeMAV();

    enum QGC_INPUT_MODE {
        QGC_INPUT_MODE_NONE,
        QGC_INPUT_MODE_MOUSE,
        QGC_INPUT_MODE_TOUCH,
        QGC_INPUT_MODE_KEYBOARD
    };

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
    int getCurrentTrajectoryStamp()
    {
        return currentTrajectoryStamp;
    }
    /** @brief Get activated input mode for this uas */
    QGC_INPUT_MODE getInputMode()
    {
        return inputMode;
    }

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
    void setManual6DOFControlCommands(double x , double y , double z , double a , double b, double c);
    /** @brief Send the 8 DOF command (from Testphase Widget) to MAV */
    void setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 ); //AL (06.03.12)
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorTrans(float val) {sensitivityFactorTrans = val;}
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorRot(float val) {sensitivityFactorRot = val;}
    /** @brief Send mode via mavlink command */
    void setModeCommand(int mode);

    void followTrajectory();
    /** @brief Set active Input Mode for this UAS */
    void setInputMode(SkyeMAV::QGC_INPUT_MODE input);
    /** @brief Report de-/activation of rotative 3DMouse input */
    void changeMouseRotationActive(bool active){emit mouseButtonRotationChanged(active);}
    /** @brief Report de-/activation of translative 3DMouse input */
    void changeMouseTranslationActive(bool active){emit mouseButtonTranslationChanged(active);}

    void sendLedColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency);

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
    void batteryPackChanged(mavlink_battery_status_t* battery);
    void reportUDPLinkFailed(QString errorStr);
    void mouseButtonRotationChanged(bool active);
    void mouseButtonTranslationChanged(bool active);
    void inputModeChanged(SkyeMAV::QGC_INPUT_MODE);


protected:
    /** Send a Manual 6DoF Control Command to MAV */
    void sendManualControlCommands6DoF(double x, double y, double z, double phi, double theta, double psi);
    /** @brief Send a Testphase Control Command to MAV: */
    void sendManualControlCommands8DoF(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 );

    int airframe;                   ///< The airframe type

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

    QGC_INPUT_MODE inputMode;
};

#endif // SKYEMAV_H
