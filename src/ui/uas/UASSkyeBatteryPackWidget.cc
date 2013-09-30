#include <QDebug>
#include "UASSkyeBatteryPackWidget.h"
#include "ui_UASSkyeBatteryPackWidget.h"

#define CELLS 6
#define CELL_VOLTAGE_CRITICAL 3.666666666666
#define CELL_VOLTAGE_EMERGENCY 3.3


UASSkyeBatteryPackWidget::UASSkyeBatteryPackWidget(QWidget *parent, MAV_SKYE_BATTERY_PACK_ID pack) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryPackWidget),
    batteries(0),
    measuringCurrent(true),
    estimatingRemaining(true)
{
    ui->setupUi(this);

//    this->setStyleSheet("QProgressBar {height: 35;}");
//    this->setStyleSheet("QProgressBar::chunk {background-color: green;}");

    QLabel* voltageLabel = new QLabel("Voltages [V]:");
    ui->horizontalLayoutLeft->addWidget(voltageLabel);

    QLabel* currentLabel = new QLabel("Current [A]:");
    ui->horizontalLayoutRight->addWidget(currentLabel);

    currentMap[0] = new QLCDNumber;
    ui->horizontalLayoutRight->addWidget(currentMap[0]);
    currentMap[0]->setToolTip("Total current [A]");
    currentMap[0]->setPalette(Qt::cyan);

    // initial call of battery update
    double volt[4] = {0.0, 0.0, 0.0, 0.0};
    changeBatteryStatus(volt, sizeof(volt)/sizeof(double), 0.0, 0.0);
}

UASSkyeBatteryPackWidget::~UASSkyeBatteryPackWidget()
{
    delete ui;
}

void UASSkyeBatteryPackWidget::changeBatteryStatus(const double *voltages, int size, double current, int remaining)
{
    // Update number of cells/batteries
    batteries = size;

    for (int i=0; i<batteries; i++)
    {
        // Create number displays
        if (i >= voltageMap.size())
        {
            voltageMap[i] = new QLCDNumber;
            ui->horizontalLayoutLeft->addWidget(voltageMap[i]);
            voltageMap[i]->setToolTip(QString("Voltage of AU %1 [V]").arg(i+1));
        }

        // Update display value
        if (i < size)
        {
            voltageMap[i]->display(voltages[i]);

            if (voltages[i] > CELLS*CELL_VOLTAGE_CRITICAL)
            {
                // high voltage
                voltageMap[i]->setPalette(QColor(50, 205, 50));
            }
            else if (voltages[i] > CELLS*CELL_VOLTAGE_EMERGENCY)
            {
                // medium voltage
                voltageMap[i]->setPalette(QColor(255, 165, 0));
            }
            else
            {
                // low voltage
                voltageMap[i]->setPalette(QColor(255, 0, 0));
                // TODO: raise emergency
            }
        } else {
            voltageMap[i]->display(0.0);
        }
    }
}

void UASSkyeBatteryPackWidget::updateCurrentVisibility(double current)
{
    if (current < 0.0 && measuringCurrent)
    {
        currentMap[0]->hide();
        measuringCurrent = false;
    }
    else if (current >= 0.0 && !measuringCurrent)
    {
        currentMap[0]->show();
        measuringCurrent = true;
    }
}

void UASSkyeBatteryPackWidget::updateRemainingVisibility(int remaining)
{
    if (remaining == -1 && estimatingRemaining)
    {
//        ui->progressBarRemaining->hide();
        estimatingRemaining = false;
    }
    else if (remaining >= 0 && !estimatingRemaining)
    {
//        ui->progressBarRemaining->show();
        estimatingRemaining = true;
    }
}
