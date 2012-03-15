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

private:
    Ui::UASSkyeBatteryInfoWidget *ui;

protected:
    QMap<int, UASSkyeBatteryPackWidget*> batteryPacks;
    QVBoxLayout* listLayout;
//    UASSkyeBatteryPackWidget* uWidget;
};

#endif // UASSKYEBATTERYINFOWIDGET_H
