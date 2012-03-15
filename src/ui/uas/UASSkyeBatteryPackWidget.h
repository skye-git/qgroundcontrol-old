#ifndef UASSKYEBATTERYPACKWIDGET_H
#define UASSKYEBATTERYPACKWIDGET_H

#include <QWidget>

namespace Ui {
    class UASSkyeBatteryPackWidget;
}

enum QGC_SKYE_BATTERY_PACK
{
    QGC_SKYE_BATTERY_PACK_NONE,
    QGC_SKYE_BATTERY_PACK_1,
    QGC_SKYE_BATTERY_PACK_2,
    QGC_SKYE_BATTERY_PACK_3
};

class UASSkyeBatteryPackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeBatteryPackWidget(QWidget *parent = 0, QGC_SKYE_BATTERY_PACK pack = QGC_SKYE_BATTERY_PACK_NONE);
    ~UASSkyeBatteryPackWidget();

private:
    Ui::UASSkyeBatteryPackWidget *ui;
};

#endif // UASSKYEBATTERYPACKWIDGET_H
