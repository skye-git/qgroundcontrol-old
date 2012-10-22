#ifndef UASSKYEBATTERYINFOWIDGET_H
#define UASSKYEBATTERYINFOWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include "UASSkyeBatteryPackWidget.h"
#include "UASInterface.h"

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
    /** @brief Set the system this widget controls */
    void setActiveUAS(UASInterface* uas);
    /** @brief New values for battery pack **/
    void changeBatteryPack(mavlink_battery_status_t* battery);

private:
    Ui::UASSkyeBatteryInfoWidget *ui;

protected:
    QMap<int, UASSkyeBatteryPackWidget*> batteryPacks;
    QVBoxLayout* listLayout;
    int uasId;
};

#endif // UASSKYEBATTERYINFOWIDGET_H
