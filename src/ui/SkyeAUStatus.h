#ifndef SKYEAUSTATUS_H
#define SKYEAUSTATUS_H

#include <QWidget>
#include "UASInterface.h"

namespace Ui {
class SkyeAUStatus;
}

class SkyeAUStatus : public QWidget
{
    Q_OBJECT

public:
    explicit SkyeAUStatus(int id, QWidget *parent = 0);
    ~SkyeAUStatus();

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);
    /** @brief Set the actuation unit id */
    void setAU(int id);
    /** @brief update battery status of this actuation unit */
    void updateBatteryStatus(mavlink_battery_status_t *battery);
    /** @brief update battery cells status of this actuation unit */
    void updateBatteryCellsStatus(mavlink_battery_cells_status_t *battery);
    /** @brief update thruster value of this actuation unit */
    void updateThrustValue(mavlink_allocation_controller_raw_t *alloc);
    /** @brief rewrite tooltip */
    void updateToolTipText();

private slots:
    /** enable/disable actuation unit for allocation */
    //void toggledCheckBox(bool activated);

private:
    Ui::SkyeAUStatus *ui;
    int uasId;                          ///< Reference to the current uas
    int auId;                           ///< ID of this actuation unit

    mavlink_battery_status_t *batt;             ///< battery status of this actuation unit
    mavlink_battery_cells_status_t *cells;      ///< battery cells status of this actuation unit
    uint8_t thrust;                             ///< thrust of this actuation unit in percent [%]

    QString getStringForAccuStatus(int status);

};

#endif // SKYEAUSTATUS_H
