#ifndef UASVOLTAGEINFOWIDGET_H
#define UASVOLTAGEINFOWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include "UASInterface.h"
#include "UASManager.h"
#include "SkyeMAV.h"

#define N_VOLT 4

namespace Ui {
class UASVoltageInfoWidget;
}

class UASVoltageInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit UASVoltageInfoWidget(QWidget *parent = 0);
    ~UASVoltageInfoWidget();
    
private:
    Ui::UASVoltageInfoWidget *ui;
    int uasId;
    QHBoxLayout *boxLayout;
    QLabel labelVoltage[N_VOLT];
    float voltage[N_VOLT];

public slots:
    void setActiveUAS(UASInterface *uas);
    void changeVoltageInfo(mavlink_battery_voltage_t *info);
};

#endif // UASVOLTAGEINFOWIDGET_H
