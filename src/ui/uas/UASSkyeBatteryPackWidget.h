#ifndef UASSKYEBATTERYPACKWIDGET_H
#define UASSKYEBATTERYPACKWIDGET_H

#include <QWidget>
#include "QGCMAVLink.h"
#include <QtGui>

namespace Ui {
    class UASSkyeBatteryPackWidget;
}

class UASSkyeBatteryPackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeBatteryPackWidget(QWidget *parent = 0, MAV_SKYE_BATTERY_PACK_ID pack = MAV_SKYE_BATTERY_PACK_ID_NONE);
    ~UASSkyeBatteryPackWidget();
    void changeBatteryStatus(double voltage1, double voltage2, double voltage3, double voltage4, double voltage5, double voltage6, double current, int remaining);
    void updateVoltageVisibility(double voltage, QLCDNumber *lcdNumber);

private:
    Ui::UASSkyeBatteryPackWidget *ui;

    int batteryCells;           ///< Number of cells in LiPo Accu (4 = 14.8V, 6 = 22.2V)

protected:

};

#endif // UASSKYEBATTERYPACKWIDGET_H
