#include <QDebug>
#include "UASSkyeBatteryPackWidget.h"
#include "ui_UASSkyeBatteryPackWidget.h"


UASSkyeBatteryPackWidget::UASSkyeBatteryPackWidget(QWidget *parent, MAV_SKYE_BATTERY_PACK_ID pack) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryPackWidget),
    batteryCells(-1),
    measuringCurrent(true),
    estimatingRemaining(true)
{
    ui->setupUi(this);

    this->setStyleSheet("QProgressBar {height: 35;}");
    this->setStyleSheet("QProgressBar::chunk {background-color: green;}");

//    toolBarBatteryVoltageLabel->setStyleSheet(QString("QLabel { margin: 0px 0px 0px 4px; font: 14px; color: %1; }").arg(QColor(Qt::green).name()));
    ui->lcdNumberVoltage1->setToolTip("Voltage 1");
    ui->lcdNumberVoltage2->setToolTip("Voltage 2");
    ui->lcdNumberVoltage3->setToolTip("Voltage 3");
    ui->lcdNumberVoltage4->setToolTip("Voltage 4");
    ui->lcdNumberVoltage5->setToolTip("Voltage 5");
    ui->lcdNumberVoltage6->setToolTip("Voltage 6");
    ui->lcdNumberCurrent->setToolTip("Total current");
    ui->progressBarRemaining->setToolTip("Estimated remaining battery");

    ui->lcdNumberCurrent->setStyleSheet("* { background-color: gray; color: darkblue; }");

    QString labelText;
    switch (pack)
    {
        case MAV_SKYE_BATTERY_PACK_ID_1:
        {
            labelText = "Skye Battery Info";
            this->setToolTip("Battery info for of Skye");
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
            labelText = "Battery Id higher than 3";
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
        batteryCells = 1;
        batteryCells = 2;
        batteryCells = 3;
        // Display at least 4 "cells" (even if they are zero)
        batteryCells = 4;
    if (voltage5 > 0)
        batteryCells = 5;
    if (voltage6 > 0)
        batteryCells = 6;
    if (priorVoltage != batteryCells)
        updateVoltageVisibility();

//    updateCurrentVisibility(current); // Always show current
    updateRemainingVisibility(remaining);


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
        ui->lcdNumberVoltage6->show();
    case 5:
        ui->lcdNumberVoltage5->show();
    case 4:
        ui->lcdNumberVoltage4->show();
    case 3:
        ui->lcdNumberVoltage3->show();
    case 2:
        ui->lcdNumberVoltage2->show();
    case 1:
        ui->lcdNumberVoltage1->show();
        break;
    default:
        break;
    }
}

void UASSkyeBatteryPackWidget::updateCurrentVisibility(double current)
{
    if (current < 0.0 && measuringCurrent)
    {
        ui->lcdNumberCurrent->hide();
        measuringCurrent = false;
    }
    else if (current >= 0.0 && !measuringCurrent)
    {
        ui->lcdNumberCurrent->show();
        measuringCurrent = true;
    }
}

void UASSkyeBatteryPackWidget::updateRemainingVisibility(int remaining)
{
    if (remaining == -1 && estimatingRemaining)
    {
        ui->progressBarRemaining->hide();
        estimatingRemaining = false;
    }
    else if (remaining >= 0 && !estimatingRemaining)
    {
        ui->progressBarRemaining->show();
        estimatingRemaining = true;
    }
}
