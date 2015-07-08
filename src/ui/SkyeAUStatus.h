#ifndef SKYEAUSTATUS_H
#define SKYEAUSTATUS_H

#include <QWidget>
#include <QMenu>
#include <QTimer>
#include "UASInterface.h"
#include "UASManager.h"
#include "SkyeMAV.h"


namespace Ui {
class SkyeAUStatus;
}

class SkyeAUStatus : public QWidget
{
    Q_OBJECT

public:
    explicit SkyeAUStatus(int id, QWidget *parent);
    ~SkyeAUStatus();
    bool isAUReady() {return status == MAV_ACTUATION_UNIT_STATUS_READY;}
    bool isAUEnabled() {return enabled;}

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);
    /** @brief Set the actuation unit id */
    void setAU(int id);
    /** @brief update battery status of this actuation unit */
    void updateBatteryStatus(mavlink_battery_status_t *battery);
//    /** @brief update battery cells status of this actuation unit */
//    void updateBatteryCellsStatus(mavlink_battery_cells_status_t *battery);
    /** @brief update thruster value of this actuation unit */
    void updateThrustValue(mavlink_allocation_output_raw_t *alloc);
    /** @brief rewrite tooltip */
    void updateToolTipText();
    /** @brief Regularely check whether data is up-to-date */
    void checkUpToDate();
    /** @brief Update stylesheets according to values */
    void updateStyleSheets();
    /** @brief Update GUI to Allocation Case of Skye */
    void updateAllocationCase(int allocCase);
    /** @brief Update to actuation unit status */
    void updateActuationStatus(mavlink_actuation_status_t *au_status);
    /** @brief Clicked reset button. Emit reset command */
    void clickedResetButton();
    /** @brief Request redefining of allocation case depending on status and enabled checkbox */
    void emitEnabled();

    void reduceWidget();
    void expandWidget();


signals:
    /** @brief Status has changed  */
    void AUStatusChanged(uint au, bool ready, bool activated);
    /** @brief Reset actuation unit */
    void requestAUReset(int au);

private slots:
    /** @brief enable/disable actuation unit for allocation */
    void clickedCheckBox(bool checked);


private:
    Ui::SkyeAUStatus *ui;

    int uasId;                          ///< Reference to the current uas
    int auId;                           ///< ID of this actuation unit
    bool enabled;                       ///< User flag to enable/disable this actuation unit

    mavlink_battery_status_t *batt;             ///< battery status of this actuation unit
    double voltage;                             ///< total voltage of battery cells
//    mavlink_battery_cells_status_t *cells;      ///< battery cells status of this actuation unit
    MAV_ACTUATION_UNIT_STATUS status;           ///< actuation status
    uint8_t thrust;                             ///< thrust of this actuation unit in percent [%]

    QString getStringForAccuStatus(int status);
    QString getShortStringForAccuStatus(int status);
    QString getStringForAUStatus(int status);   ///< See MAV_ACTUATION_STATUS enum

    QTimer timer;                               ///< Timer to check novelity of data
    QTime lastUpdate;                           ///< Timestamp of last AU or battery info
};

#endif // SKYEAUSTATUS_H
