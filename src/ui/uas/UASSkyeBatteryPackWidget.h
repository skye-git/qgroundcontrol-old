#ifndef UASSKYEBATTERYPACKWIDGET_H
#define UASSKYEBATTERYPACKWIDGET_H

#include <QWidget>
#include "QGCMAVLink.h"

namespace Ui {
    class UASSkyeBatteryPackWidget;
}

class UASSkyeBatteryPackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeBatteryPackWidget(QWidget *parent = 0, MAV_SKYE_BATTERY_PACK_ID pack = MAV_SKYE_BATTERY_PACK_ID_NONE);
    ~UASSkyeBatteryPackWidget();

private:
    Ui::UASSkyeBatteryPackWidget *ui;

protected:

};

#endif // UASSKYEBATTERYPACKWIDGET_H
