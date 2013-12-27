#include "SkyeAUStatus.h"
#include "ui_SkyeAUStatus.h"
#include "UASManager.h"
#include "SkyeMAV.h"

SkyeAUStatus::SkyeAUStatus(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkyeAUStatus),
    uasId(0)
{
    ui->setupUi(this);
    setAU(id);

    ui->pushButton->setDisabled(true);
    ui->checkBox->setDisabled(true);
    //connect(ui->checkBox, SIGNAL(toggled(bool)), this,

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

    bat = new mavlink_battery_status_t;
    bat->accu_id = 0;
    bat->battery_remaining = -1;
    bat->current_battery = 0;
    bat->voltage_cell_1 = 0;
    bat->voltage_cell_2 = 0;
    bat->voltage_cell_3 = 0;
    bat->voltage_cell_4 = 0;
    bat->voltage_cell_5 = 0;
    bat->voltage_cell_6 = 0;

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
            disconnect(mav, SIGNAL(batteryPackChanged(mavlink_battery_status_t*)), this, SLOT(updateBatteryStatus(mavlink_battery_status_t*)));
        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        // connect
        connect(mav, SIGNAL(batteryPackChanged(mavlink_battery_status_t*)), this, SLOT(updateBatteryStatus(mavlink_battery_status_t*)));

    }
}

void SkyeAUStatus::setAU(int id)
{
    this->auId = id;
    ui->labelName->setText(QString("AU %1").arg(id));
}

void SkyeAUStatus::updateBatteryStatus(mavlink_battery_status_t *battery)
{
    if (this->auId == battery->accu_id)
    {
        memcpy(bat, battery, sizeof(*battery));
        ui->lcdNumberVoltage->display(( battery->voltage_cell_1 +
                                        battery->voltage_cell_2 +
                                        battery->voltage_cell_3 +
                                        battery->voltage_cell_4 +
                                        battery->voltage_cell_5 +
                                        battery->voltage_cell_6 ) / 1000.0);

        updateToolTipText();
    }
}

void SkyeAUStatus::updateToolTipText()
{
    qDebug() << "BATTERY"
                << bat->voltage_cell_1
                << bat->voltage_cell_2
                << bat->voltage_cell_3
                << bat->voltage_cell_4
                << bat->voltage_cell_5
                << bat->voltage_cell_6;

    this->setToolTip(QString("Actuation unit ID: %1 \n"
                             "Cell voltages [V]: \n"
                             "%2 \t %3 \t %4 \t %5 \t %6 \t %7 \n"
                             "Current [A]: %8")
                     .arg(bat->accu_id)
                     .arg(bat->voltage_cell_1/1000.0)
                     .arg(bat->voltage_cell_2/1000.0)
                     .arg(bat->voltage_cell_3/1000.0)
                     .arg(bat->voltage_cell_4/1000.0)
                     .arg(bat->voltage_cell_5/1000.0)
                     .arg(bat->voltage_cell_6/1000.0)
                     .arg(bat->current_battery/100.0));
}

