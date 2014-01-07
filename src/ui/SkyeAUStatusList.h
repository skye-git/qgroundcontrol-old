#ifndef SKYEAUSTATUSLIST_H
#define SKYEAUSTATUSLIST_H

#include <QWidget>
#include <QMap>
#include "SkyeAUStatus.h"
#include "UASInterface.h"

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
    /** @brief Create new widget for every id */
    void checkBatteryCellsStatusId(mavlink_battery_cells_status_t *cells);
    /** @brief Create new widget for every id */
    void checkActuationStatusId(mavlink_actuation_status_t *au_status);
    /** @brief Create new widget. Returns true when newly created. Returns false when already existing. */
    bool createAUStatusWidget(int id);
    /** @brief Change allocation case */
    void changeAllocationCase(uint au, bool status);
    /** @brief Update GUI to Allocation Case of Skye */
    void updateAllocationCase(int allocCase);
    /** @brief Right-click menu */
    void showContextMenu(const QPoint& pos);

signals:
    /** @brief Send a new allocation case to Skye */
    void requestAllocationCase(int alloc);

private:
    Ui::SkyeAUStatusList *ui;
    int uasId;                          ///< Reference to the current uas

    QMap<int, SkyeAUStatus*> auList;    ///< Actuation unit info widget list

    int allocationCase;                 ///< Allocation case. 0: all AUs, 1: w/o AU1, 2: w/o AU2, 3: w/o AU3, 4: w/o AU4

    QMenu menu;
};

#endif // SKYEAUSTATUSLIST_H
