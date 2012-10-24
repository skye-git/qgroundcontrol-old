#include <QDebug>
#include "UASSkyeBatteryPackWidget.h"
#include "ui_UASSkyeBatteryPackWidget.h"

UASSkyeBatteryPackWidget::UASSkyeBatteryPackWidget(QWidget *parent, MAV_SKYE_BATTERY_PACK_ID pack) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryPackWidget),
    batteryCells(-1)
{
    ui->setupUi(this);

    this->setStyleSheet("QProgressBar {height: 35;}");
    this->setStyleSheet("QProgressBar::chunk {background-color: green;}");

//    toolBarBatteryVoltageLabel->setStyleSheet(QString("QLabel { margin: 0px 0px 0px 4px; font: 14px; color: %1; }").arg(QColor(Qt::green).name()));
    ui->lcdNumberVoltage1->setToolTip("Voltage of cell 1");
    ui->lcdNumberVoltage2->setToolTip("Voltage of cell 2");
    ui->lcdNumberVoltage3->setToolTip("Voltage of cell 3");
    ui->lcdNumberVoltage4->setToolTip("Voltage of cell 4");
    ui->lcdNumberCurrent->setToolTip("Current of this accu pack");
    ui->progressBarRemaining->setToolTip("Estimated remaining battery");

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

void UASSkyeBatteryPackWidget::changeBatteryStatus(double voltage1, double voltage2, double voltage3, double voltage4, double voltage5, double voltage6, double current, int remaining)
{
    ui->lcdNumberVoltage1->display(voltage1);
    ui->lcdNumberVoltage2->display(voltage2);
    ui->lcdNumberVoltage3->display(voltage3);
    ui->lcdNumberVoltage4->display(voltage4);
    ui->lcdNumberVoltage5->display(voltage5);
    ui->lcdNumberVoltage6->display(voltage6);
    ui->lcdNumberCurrent->display(current);
    ui->progressBarRemaining->setValue(remaining);


    int priorVoltage;
    priorVoltage = batteryCells;
    if (voltage1 > 0)
        batteryCells = 1;
    if (voltage2 > 0)
        batteryCells = 2;
    if (voltage3 > 0)
        batteryCells = 3;
    if (voltage4 > 0)
        batteryCells = 4;
    if (voltage5 > 0)
        batteryCells = 5;
    if (voltage6 > 0)
        batteryCells = 6;
    if (priorVoltage != batteryCells)
        updateVoltageVisibility();


    // TODO: change styleSheet if value is low
}

void UASSkyeBatteryPackWidget::updateVoltageVisibility()
{
    ui->lcdNumberVoltage1->hide();
    ui->lcdNumberVoltage2->hide();
    ui->lcdNumberVoltage3->hide();
    ui->lcdNumberVoltage4->hide();
    ui->lcdNumberVoltage5->hide();
    ui->lcdNumberVoltage6->hide();

    switch (batteryCells)
    {
    case 6:
    {
        ui->lcdNumberVoltage6->show();
    }
    case 5:
    {
        ui->lcdNumberVoltage5->show();
    }
    case 4:
    {
        ui->lcdNumberVoltage4->show();
    }
    case 3:
    {
        ui->lcdNumberVoltage3->show();
    }
    case 2:
    {
        ui->lcdNumberVoltage2->show();
    }
    case 1:
    {
        ui->lcdNumberVoltage1->show();
        break;
    }
    default:
        break;
    }
}
