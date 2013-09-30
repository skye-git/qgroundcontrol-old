#ifndef UASSKYEBATTERYPACKWIDGET_H
#define UASSKYEBATTERYPACKWIDGET_H

#include <QWidget>
#include "QGCMAVLink.h"
#include <QtGui>
#include <QMap>
#include <QLCDNumber>

namespace Ui {
    class UASSkyeBatteryPackWidget;
}

class UASSkyeBatteryPackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeBatteryPackWidget(QWidget *parent = 0, MAV_SKYE_BATTERY_PACK_ID pack = MAV_SKYE_BATTERY_PACK_ID_NONE);
    ~UASSkyeBatteryPackWidget();
    void changeBatteryStatus(const double *voltages, int size, double current, int remaining);
    void updateCurrentVisibility(double current);
    void updateRemainingVisibility(int remaining);

private:
    Ui::UASSkyeBatteryPackWidget *ui;

    int batteries;              ///< Number batteries
    bool measuringCurrent;      ///< true if autopilot measures current
    bool estimatingRemaining;   ///< true if autopilot estimates remaining battery

    QMap<int, QLCDNumber*> voltageMap;      ///< Container for voltage displays
    QMap<int, QLCDNumber*> currentMap;      ///< Containter for current display(s)



};

#endif // UASSKYEBATTERYPACKWIDGET_H
