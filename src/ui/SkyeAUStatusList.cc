#include "SkyeAUStatusList.h"
#include "ui_SkyeAUStatusList.h"
#include "UASManager.h"
#include "SkyeMAV.h"

#include <QDebug>

SkyeAUStatusList::SkyeAUStatusList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkyeAUStatusList),
    uasId(0),
    allocationCase(0)
{
    ui->setupUi(this);
    auList = QMap<int, SkyeAUStatus*>();

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

}

SkyeAUStatusList::~SkyeAUStatusList()
{
    delete ui;
}


void SkyeAUStatusList::setUAS(UASInterface *uas)
{
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        this->uasId = 0;
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(oldUAS);
        if (mav)
        {
            // disconnect
            disconnect(mav, SIGNAL(batteryStatusChanged(mavlink_battery_status_t*)), this, SLOT(checkBatteryStatusId(mavlink_battery_status_t*)));
            disconnect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocationCase(int)));
            disconnect(this, SIGNAL(requestAllocationCase(int)), mav, SLOT(sendAUConfiguration(int)));
        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        // connect
        connect(mav, SIGNAL(batteryStatusChanged(mavlink_battery_status_t*)), this, SLOT(checkBatteryStatusId(mavlink_battery_status_t*)));
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocationCase(int)));
        connect(this, SIGNAL(requestAllocationCase(int)), mav, SLOT(sendAUConfiguration(int)));

    }
}

void SkyeAUStatusList::checkBatteryStatusId(mavlink_battery_status_t *battery)
{
    //qDebug() << "battery status of id " << battery->accu_id;
    if (auList.contains(battery->accu_id))
    {
        // widget already exists
    } else {
        auList.insert(battery->accu_id, new SkyeAUStatus(battery->accu_id, this));
        ui->horizontalLayout->insertWidget(battery->accu_id, auList.value(battery->accu_id));
        auList.value(battery->accu_id)->updateBatteryStatus(battery);
        connect(auList.value(battery->accu_id), SIGNAL(requestAllocationCase(uint,bool)), this, SLOT(changeAllocationCase(uint,bool)));
    }

}

void SkyeAUStatusList::changeAllocationCase(uint au, bool status)
{
    if (status == false && au <= 4)
    {
        emit requestAllocationCase(au);
    }
    if (status == true)
    {
        // AU was only disabled if allocationCase == au
        if (allocationCase == au)
        {
            emit requestAllocationCase(0);
        }
    }
}

void SkyeAUStatusList::updateAllocationCase(int allocCase)
{
    allocationCase = allocCase;
}
