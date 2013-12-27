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
    batt->accu_id = 0;
    batt->status = 0;
    batt->voltage = 0;
    batt->current = 0;
    batt->energy = 0;

    cells = new mavlink_battery_cells_status_t;
    cells->accu_id = 0;
    cells->voltage_cell_1 = 0;
    cells->voltage_cell_2 = 0;
    cells->voltage_cell_3 = 0;
    cells->voltage_cell_4 = 0;
    cells->voltage_cell_5 = 0;
    cells->voltage_cell_6 = 0;

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

void SkyeAUStatus::updateBatteryCellsStatus(mavlink_battery_cells_status_t *battery)
{
    if (this->auId == battery->accu_id)
    {
        memcpy(cells, battery, sizeof(*battery));

        updateToolTipText();
    }
}

void SkyeAUStatus::updateBatteryStatus(mavlink_battery_status_t *battery)
{
    if (this->auId == battery->accu_id)
    {
        ui->lcdNumberVoltage->display(battery->voltage/1000.0);
        ui->lcdNumberCurrent->display(battery->current/1000.0);
        ui->labelMessage->setText(getStringForAccuStatus((int)battery->status));
        ui->labelMessage->setToolTip(getStringForAccuStatus((int)battery->status));

        updateToolTipText();
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
