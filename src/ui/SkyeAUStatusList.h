#ifndef SKYEAUSTATUSLIST_H
#define SKYEAUSTATUSLIST_H

#include <QWidget>
#include <QMap>
#include "SkyeAUStatus.h"
#include "UASInterface.h"
#include "SkyeAUStatusSettingsDialog.h"

namespace Ui {
class SkyeAUStatusList;
}

class SkyeAUStatusList : public QWidget
{
    Q_OBJECT

public:
    explicit SkyeAUStatusList(QWidget *parent = 0);
    ~SkyeAUStatusList();

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);
    /** @brief Create new widget for every id */
    void checkBatteryStatusId(mavlink_battery_status_t *battery);
//    /** @brief Create new widget for every id */
//    void checkBatteryCellsStatusId(mavlink_battery_cells_status_t *cells);
    /** @brief Create new widget for every id */
    void checkActuationStatusId(mavlink_actuation_status_t *au_status);
    /** @brief Create new widget. Returns true when newly created. Returns false when already existing. */
    bool createAUStatusWidget(int id);
    /** @brief Allocation case request of an single AU that changed enabled flag */
    void changeAUStatus(uint auId, bool ready, bool enabled);
    /** @brief Update Allocation Case for Skye */
    void updateAllocationCase();
    /** @brief Right-click menu */
    void showContextMenu(const QPoint& pos);
    /** @brief setAllocationAutoMode */
    void setAllocationAutoMode(bool allocAuto);
    /** @brief send new motor position configuration to Skye */
    void setSkyeConfiguration(double*); // [SKYE_AU_PARAM_MAX][SKYE_AU_COUNT_MAX]

signals:
    /** @brief Send a new allocation case to Skye */
    void requestAllocationCase(int alloc);
    /** @brief Send new Skye AU orientations for new allocation matrix */
    void sendSkyeConfiguration(double*); // [SKYE_AU_PARAM_MAX][SKYE_AU_COUNT_MAX]

private:
    Ui::SkyeAUStatusList *ui;
    int uasId;                          ///< Reference to the current uas

    QMap<int, SkyeAUStatus*> auList;    ///< Actuation unit info widget list
    QMap<int, bool> auActiveList;       ///< Active AU: auto: ready & enabled, manual: enabled

    bool allocationAuto;                ///< If true, allocation considers state of actuation units
    int allocationCase;                 ///< Allocation case. 0: all AUs, 1: w/o AU1, 2: w/o AU2, 3: w/o AU3, 4: w/o AU4

    QMenu menu;

    SkyeAUStatusSettingsDialog *settingsDialog; ///< Dialog widget for actuation config settings
};

#endif // SKYEAUSTATUSLIST_H
