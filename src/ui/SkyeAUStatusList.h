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

private:
    Ui::SkyeAUStatusList *ui;
    int uasId;                          ///< Reference to the current uas

    QMap<int, SkyeAUStatus*> auList;    ///< Actuation unit info widget list


};

#endif // SKYEAUSTATUSLIST_H
