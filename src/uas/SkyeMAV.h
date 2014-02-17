#ifndef SKYEMAV_H
#define SKYEMAV_H

#define SKYE_ALARM_VOLTAGE 22.0f
#define SKYE_CRITICAL_VOLTAGE 23.0f

#include <QPolygonF>
#include <QTimer>
#include <QVector>
#include "UAS.h"


#define MAX_LIFT_VALUE 0.2
#define LIFT_RESOLUTION 999     //values from 0 to LIFT_RESOLUTION are possible

//#include "BluefoxReconfigure.h"

class SkyeMAV : public UAS
{
    Q_OBJECT
    Q_INTERFACES(UASInterface)
public:
    SkyeMAV(MAVLinkProtocol* mavlink, int id);
    ~SkyeMAV();

    enum QGC_INPUT_MODE {
        QGC_INPUT_MODE_NONE=0,
        QGC_INPUT_MODE_MOUSE=1,
        QGC_INPUT_MODE_TOUCH=2,
        QGC_INPUT_MODE_KEYBOARD=4,
        QGC_INPUT_MODE_XBOX=8
    };

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

    /** @brief Get activated input mode flags for this uas */
    int getInputMode()
    {
        return inputMode;
    }



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
    /** @brief Send the 6 DOF command (from test config window) to MAV */
    void set6DOFCommandsByWidget(double x , double y , double z , double a , double b, double c);
    /** @brief Send the 8 DOF command (from Testphase Widget) to MAV */
    void setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 ); //AL (06.03.12)
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorTrans(float val) {sensitivityFactorTrans = val;}
    /** @brief Set multiplication factor for manual control */
    void setSensitivityFactorRot(float val) {sensitivityFactorRot = val;}
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

    /** @brief Set active input flag for this UAS */
    void setInputMode(SkyeMAV::QGC_INPUT_MODE input, bool active);
    /** @brief Report de-/activation of rotative 3DMouse input */
    void changeMouseRotationActive(bool active){emit mouseButtonRotationChanged(active);}
    /** @brief Report de-/activation of translative 3DMouse input */
    void changeMouseTranslationActive(bool active){emit mouseButtonTranslationChanged(active);}

    void sendLedColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency);

    /** @brief Send parameter for actuation unit configuration (SKYE_ALOC_CASE) */
    void sendAUConfiguration(int);
    /** @brief Send AU reset command */
    void sendAUReset(int auId);

signals:
    /** @brief Emit new detailed accu info for one accu pack
     *  @param  voltage_cell_1 Voltage of cell 1 in volt
     *          voltage_cell_2 Voltage of cell 2 in volt
     *          voltage_cell_3 Voltage of cell 3 in volt
     *          voltage_cell_4 Voltage of cell 4 in volt
     *          voltage_cell_5 Voltage of cell 5 in volt
     *          voltage_cell_6 Voltage of cell 6 in volt
    **/
    void batteryCellsStatusChanged(mavlink_battery_cells_status_t* cells);
    void batteryStatusChanged(mavlink_battery_status_t* battery);
    void allocationValueChanged(mavlink_allocation_controller_raw_t* allocation);
    void actuationStatusChanged(mavlink_actuation_status_t* au_status);
    void reportUDPLinkFailed(QString errorStr);
    void mouseButtonRotationChanged(bool active);
    void mouseButtonTranslationChanged(bool active);
    void inputModeChanged(int inputMode);
    /** @brief Battery is low. Shutdown required */
    void batteryLow(double voltage);
    /** @brief Battery is low. Shutdown required */
    void batteryLow(double voltage, bool isLow, unsigned int ms);
    void allocCaseChanged(int allocCase);
    void liftValueChanged(int);

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

    int inputMode;                          // input device bit flags (see QGC_INPUT_MODE)

    //bool lowBatteryFront;                   ///< true if electronics platform battery is low
    //int lowBatteryAU;                       ///< id of actuation units that battery is low; -1 otherwise
    //bool lowBattery;                        ///< true if any battery is low
    //unsigned int lowBatteryMs;              ///< QGC Groundtime Millisecond when battery droped below critical value

};

#endif // SKYEMAV_H

