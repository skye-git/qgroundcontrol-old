#ifndef SkyeUAS_H
#define SkyeUAS_H

#define QGC_SKYE_DEBUG 0

#define SKYE_ALARM_VOLTAGE 22.0f
#define SKYE_CRITICAL_VOLTAGE 23.0f

#define QGC_SENSITIVITY_TRANS_DEFAULT 0.5f
#define QGC_SENSITIVITY_ROT_DEFAULT 0.5f
#define QGC_LIFT_VALUE_DEFAULT 0.0f

#include <QPolygonF>
#include <QTimer>
#include <QVector>
#include "UAS.h"
#include "QGCInputs.h"

#define MAX_LIFT_VALUE 0.2
#define LIFT_RESOLUTION 999     //values from 0 to LIFT_RESOLUTION are possible


class SkyeUAS : public UAS
{
    Q_OBJECT
    Q_INTERFACES(UASInterface)
public:
    SkyeUAS(MAVLinkProtocol* mavlink, int id);
    ~SkyeUAS();


    /** @brief Get the airframe */
    int getAirframe() const
    {
        return airframe;
    }

    /** @brief Get the current state of active UAS */
    int getState() const
    {
        return status;
    }

    /** @brief Get mode */
    uint8_t getMode();



public slots:
    /** @brief Set the specific airframe type */
    void setAirframe(int airframe)
    {
        this->airframe = airframe;
        emit systemSpecsChanged(uasId);
    }
    /** @brief Receive a MAVLink message from this MAV */
    void receiveMessage(LinkInterface* link, mavlink_message_t message);
    /** @brief Send the 6 DOF command (from 3d Mouse or Touch Input) to MAV
     *  @note  The values are scaled by the sensitivity factors
     *         The additive slider values are added without scaling */
    void setManual6DOFControlCommands(double x , double y , double z , double a , double b, double c);
    /** @brief Enable device input overwrite. Set this to true, when input is given by test widget */
    void setInputOverwrite(bool enable);
    /** @brief Send the 6 DOF command (from test config window) to MAV */
    void set6DOFCommandsByWidget(double x , double y , double z , double a , double b, double c);
    /** @brief Send the 8 DOF command (from Testphase Widget) to MAV */
    void setTestphaseCommandsByWidget(double Thrust1 , double Thrust2 , double Thrust3 , double Thrust4 , double Orientation1 , double Orientation2, double Orientation3, double Orientation4, bool usePpm);
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorTrans(float val);
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorRot(float val);
    /** @brief Send mode via mavlink command */
    void setModeCommand(int mode);
    /** @brief Set additive value for z manual control */
    void setLiftValue(int val);
    /** @brief Set additive value for roll manual control */
    void setAddRollValue(double val) {addRollValue = val;}
    /** @brief Set additive value for pitch manual control */
    void setAddPitchValue(double val) {addPitchValue = val;}
    /** @brief Set additive value for yaw manual control */
    void setAddYawValue(double val) {addYawValue = val;}

	/** @brief Some onboard parameter changes need special actions. Handle them here! */
	void onboardParameterChanged(int uas, int component, QString parameterName, int parameterCount, int parameterId, int type, QVariant value);

    /** @brief Send color information */
    void sendLedColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency);
    /** @brief Send parameter for actuation unit configuration (SKYE_AL_CASE) */
    void sendAllocationCase(int);
    /** @brief Send parameter (float) */
    void sendParameterFloat(QString param_id_name, float value);
    /** @brief Send parameter (float) */
    void sendParameterInt32(QString param_id_name, const void *val);
    /** @brief Send AU reset command */
    void sendAUReset(int auId);
    /** @brief Send new motor position configuration to Skye */
    void sendSkyeConfiguration(double *quaternions); // [4][6]
    /** @brief Send control mode*/
    void sendControlModeCommand(SKYE_CONTROL_MODE ctrlMode);

signals:
    void batteryStatusChanged(mavlink_battery_status_t* battery);
    void allocationValueChanged(mavlink_allocation_output_t* allocation);
    void actuationStatusChanged(mavlink_actuation_status_t* au_status);
    void reportUDPLinkFailed(QString errorStr);
    /** @brief Battery is low. Shutdown required */
    void batteryLow(double voltage);
    /** @brief Battery is low. Shutdown required */
    void batteryLow(double voltage, bool isLow, unsigned int ms);
    void allocCaseChanged(int allocCase);
    void skyeControlModeChanged(SKYE_CONTROL_MODE ctrlMode);
    void sensitivityTransChanged(double);
    void sensitivityRotChanged(double);
    void liftValueChanged(int);

protected:
    /** Send a Manual 6DoF Control Command to MAV */
    void sendManualControlCommands6DoF(float x, float y, float z, float phi, float theta, float psi);
    /** @brief Send a Testphase Control Command to MAV: */
    void sendManualControlCommands12DoF(float Thrust1 , float Thrust2 , float Thrust3 , float Thrust4 , float Thrust5 , float Thrust6 , float Orientation1 , float Orientation2, float Orientation3, float Orientation4, float Orientation5, float Orientation6 );

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

    float sensitivityFactorTrans;   ///< Translational factor for manual control [remark: abs(deviceInput) <= 1 ]
    float sensitivityFactorRot;     ///< Rotational factor for manual control [remark: abs(deviceInput) <= 1 ]

    int liftValue;                  ///< Additive term for manual control: int from controller and slider
    float liftValueFloat;           ///< liftvalue normalized from 0 to 1
    double addRollValue;            ///< Additive term for manual control
    double addPitchValue;           ///< Additive term for manual control
    double addYawValue;             ///< Additive term for manual control

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

    bool inputOverwrite;        ///< True when device inputs are overwritten by test widget
};

#endif // SkyeUAS_H

