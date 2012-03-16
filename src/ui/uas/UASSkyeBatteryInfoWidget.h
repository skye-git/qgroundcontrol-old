#ifndef UASSKYEBATTERYINFOWIDGET_H
#define UASSKYEBATTERYINFOWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include "UASSkyeBatteryPackWidget.h"

namespace Ui {
    class UASSkyeBatteryInfoWidget;
}

class UASSkyeBatteryInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeBatteryInfoWidget(QWidget *parent = 0);
    ~UASSkyeBatteryInfoWidget();

public slots:
    /** @brief New values for battery pack **/
    //changeBatteryPack(mavlink_skye_battery_status_t* battery);

private:
    Ui::UASSkyeBatteryInfoWidget *ui;

protected:
    QMap<int, UASSkyeBatteryPackWidget*> batteryPacks;
    QVBoxLayout* listLayout;
//    UASSkyeBatteryPackWidget* uWidget;
};

#endif // UASSKYEBATTERYINFOWIDGET_H
