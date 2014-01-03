#include "SkyeAUStatus.h"
#include "ui_SkyeAUStatus.h"
#include "UASManager.h"
#include "SkyeMAV.h"

SkyeAUStatus::SkyeAUStatus(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkyeAUStatus),
    uasId(0),
    thrust(0)
{
    ui->setupUi(this);
    setAU(id);

    ui->labelName->setStyleSheet("QLabel { font-size: 12pt;}");
    ui->lcdNumberCurrent->setToolTip("Battery current [A]");
    ui->lcdNumberVoltage->setToolTip("Battery voltage [V]");
    ui->pushButton->setDisabled(true);
    ui->checkBox->setDisabled(true);
    //connect(ui->checkBox, SIGNAL(toggled(bool)), this,


    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

    batt = new mavlink_battery_status_t;
    cells = new mavlink_battery_cells_status_t;
    memset(batt, 0, sizeof(*batt));
    memset(cells, 0, sizeof(*cells));

}

SkyeAUStatus::~SkyeAUStatus()
{
    delete ui;
}

void SkyeAUStatus::setUAS(UASInterface *uas)
{
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        this->uasId = 0;
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(oldUAS);
        if (mav)
        {
            // Disconnect
            disconnect(mav, SIGNAL(batteryCellsStatusChanged(mavlink_battery_cells_status_t*)), this, SLOT(updateBatteryCellsStatus(mavlink_battery_cells_status_t*)));
            disconnect(mav, SIGNAL(batteryStatusChanged(mavlink_battery_status_t*)), this, SLOT(updateBatteryStatus(mavlink_battery_status_t*)));
            disconnect(mav, SIGNAL(allocationValueChanged(mavlink_allocation_controller_raw_t*)), this, SLOT(updateThrustValue(mavlink_allocation_controller_raw_t*)));
        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        // connect
        connect(mav, SIGNAL(batteryCellsStatusChanged(mavlink_battery_cells_status_t*)), this, SLOT(updateBatteryCellsStatus(mavlink_battery_cells_status_t*)));
        connect(mav, SIGNAL(batteryStatusChanged(mavlink_battery_status_t*)), this, SLOT(updateBatteryStatus(mavlink_battery_status_t*)));
        connect(mav, SIGNAL(allocationValueChanged(mavlink_allocation_controller_raw_t*)), this, SLOT(updateThrustValue(mavlink_allocation_controller_raw_t*)));

    }
}

void SkyeAUStatus::setAU(int id)
{
    this->auId = id;
    ui->labelName->setText(QString("AU %1").arg(id));
}

void SkyeAUStatus::updateBatteryCellsStatus(mavlink_battery_cells_status_t *battery_cells)
{
    if (this->auId == battery_cells->accu_id)
    {
        memcpy(cells, battery_cells, sizeof(*battery_cells));

        updateToolTipText();
        updateStyleSheets();
    }
}

void SkyeAUStatus::updateBatteryStatus(mavlink_battery_status_t *battery)
{
    if (this->auId == battery->accu_id)
    {
        memcpy(batt, battery, sizeof(*battery));

        ui->lcdNumberVoltage->display(battery->voltage/1000.0);
        ui->lcdNumberCurrent->display(battery->current/1000.0);
        ui->labelMessage->setText(getStringForAccuStatus((int)battery->status));
        ui->labelMessage->setToolTip(getStringForAccuStatus((int)battery->status));

        updateToolTipText();
        updateStyleSheets();
    }
}

void SkyeAUStatus::updateThrustValue(mavlink_allocation_controller_raw_t *alloc)
{
    switch (this->auId)
    {
    case 0: thrust = alloc->thrust_1*100/1000; break;
    case 1: thrust = alloc->thrust_2*100/1000; break;
    case 2: thrust = alloc->thrust_3*100/1000; break;
    case 3: thrust = alloc->thrust_4*100/1000; break;
    }

    ui->progressBarThrust->setValue(thrust);

}

void SkyeAUStatus::updateToolTipText()
{

    this->setToolTip(QString("Actuation unit ID: %1 \n"
                             "Cell voltages [V]: \n"
                             "%2 \t %3 \t %4 \t %5 \t %6 \t %7 \n"
                             "Current [A]:\t %8 \n"
                             "Energy since last reset [mAh]: %9 \n"
                             "Charged energy [mAh]: %10 (%11min %12sec)")
                     .arg(cells->accu_id)
                     .arg(cells->voltage_cell_1/1000.0)
                     .arg(cells->voltage_cell_2/1000.0)
                     .arg(cells->voltage_cell_3/1000.0)
                     .arg(cells->voltage_cell_4/1000.0)
                     .arg(cells->voltage_cell_5/1000.0)
                     .arg(cells->voltage_cell_6/1000.0)
                     .arg(batt->current/1000.0)
                     .arg(batt->energy)
                     .arg(batt->charge)
                     .arg(batt->time/60)
                     .arg(batt->time-(batt->time/60)*60));
}

void SkyeAUStatus::updateStyleSheets()
{
    // style for voltage display
    if (batt->voltage > SKYE_CRITICAL_VOLTAGE*1000)
    {
        ui->lcdNumberVoltage->setPalette(QColor(50, 205, 50));
    }
    else if (batt->voltage > SKYE_ALARM_VOLTAGE*1000)
    {
        ui->lcdNumberVoltage->setPalette(QColor(255, 165, 0));
    }
    else
    {
        ui->lcdNumberVoltage->setPalette(QColor(255, 0, 0));
    }

    // status color (increasing importance)
    QPalette pal(palette());
    if (batt->status & BATTERY_STATUS_BIT_ATTACHED)
    {
        this->setAutoFillBackground(false);
        pal.setColor(QPalette::Background, Qt::black);
    } else {
        this->setAutoFillBackground(true);
        pal.setColor(QPalette::Background, Qt::gray);
    }
    if (batt->status & BATTERY_STATUS_BIT_UNDERVOLTAGE)
    {
        this->setAutoFillBackground(true);
        pal.setColor(QPalette::Background, Qt::red);
    }
    if (batt->status & BATTERY_STATUS_BIT_ERROR)
    {
        this->setAutoFillBackground(true);
        pal.setColor(QPalette::Background, Qt::darkRed);
    }
    this->setPalette(pal);
}

QString SkyeAUStatus::getStringForAccuStatus(int status)
{
    QString str = "";

    if (status & BATTERY_STATUS_BIT_ATTACHED)
    {
        str.append("attached");
    }
    if (status & BATTERY_STATUS_BIT_BALANCING)
    {
        if (str.length()) str.append(", ");
        str.append("balancing");
    }
    if (status & BATTERY_STATUS_BIT_CHARGING)
    {
        if (str.length()) str.append(", ");
        str.append("charging");
    }
    if (status & BATTERY_STATUS_BIT_DISABLED)
    {
        if (str.length()) str.append(", ");
        str.append("disabled");
    }
    if (status & BATTERY_STATUS_BIT_ERROR)
    {
        if (str.length()) str.append(", ");
        str.append("ERROR");
    }
    if (status & BATTERY_STATUS_BIT_FULL)
    {
        if (str.length()) str.append(", ");
        str.append("full");
    }
    if (status & BATTERY_STATUS_BIT_UNDERVOLTAGE)
    {
        if (str.length()) str.append(", ");
        str.append("undervoltage");
    }

    return str;
}
