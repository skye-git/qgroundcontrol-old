#include "UASSkyeBatteryPackWidget.h"
#include "ui_UASSkyeBatteryPackWidget.h"

UASSkyeBatteryPackWidget::UASSkyeBatteryPackWidget(QWidget *parent, QGC_SKYE_BATTERY_PACK pack) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryPackWidget)
{
    ui->setupUi(this);

    this->setStyleSheet("QProgressBar {height: 35;}");
    this->setStyleSheet("QProgressBar::chunk {background-color: green;}");

    ui->progressBarVoltageCell1->setToolTip("Voltage of Cell 1");
    ui->progressBarVoltageCell2->setToolTip("Voltage of Cell 2");
    ui->progressBarVoltageCell3->setToolTip("Voltage of Cell 3");
    ui->progressBarVoltageCell4->setToolTip("Voltage of Cell 4");

    QString labelText;
    switch (pack)
    {
        case QGC_SKYE_BATTERY_PACK_1:
        {
            labelText = "Battery pack 1";
        }
        break;
        case QGC_SKYE_BATTERY_PACK_2:
        {
            labelText = "Battery pack 2";
        }
        break;
        case QGC_SKYE_BATTERY_PACK_3:
        {
            labelText = "Battery pack 3";
        }
        break;
        default:
            labelText = "no pack";
            break;
    }
    ui->labelBatteryPack->setText(labelText);
}

UASSkyeBatteryPackWidget::~UASSkyeBatteryPackWidget()
{
    delete ui;
}
