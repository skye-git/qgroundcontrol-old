#include "UASSkyeBatteryPackWidget.h"
#include "ui_UASSkyeBatteryPackWidget.h"

UASSkyeBatteryPackWidget::UASSkyeBatteryPackWidget(QWidget *parent, MAV_SKYE_BATTERY_PACK_ID pack) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryPackWidget)
{
    ui->setupUi(this);

    this->setStyleSheet("QProgressBar {height: 35;}");
    this->setStyleSheet("QProgressBar::chunk {background-color: green;}");

    ui->progressBarVoltageCell1->setToolTip("Voltage of cell 1");
    ui->progressBarVoltageCell2->setToolTip("Voltage of cell 2");
    ui->progressBarVoltageCell3->setToolTip("Voltage of cell 3");
    ui->progressBarVoltageCell4->setToolTip("Voltage of cell 4");

    QString labelText;
    switch (pack)
    {
        case MAV_SKYE_BATTERY_PACK_ID_1:
        {
            labelText = "Battery pack 1";
            this->setToolTip("Battery info for accu pack 1");
        }
        break;
        case MAV_SKYE_BATTERY_PACK_ID_2:
        {
            labelText = "Battery pack 2";
            this->setToolTip("Battery info for accu pack 2");
        }
        break;
        case MAV_SKYE_BATTERY_PACK_ID_3:
        {
            labelText = "Battery pack 3";
            this->setToolTip("Battery info for accu pack 3");
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
