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

    // right-click menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    menu.addAction("Minimize");
    menu.actions().first()->setCheckable(true);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));
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
            disconnect(mav, SIGNAL(batteryCellsStatusChanged(mavlink_battery_cells_status_t*)), this, SLOT(checkBatteryCellsStatusId(mavlink_battery_cells_status_t*)));
            disconnect(mav, SIGNAL(actuationStatusChanged(mavlink_actuation_status_t*)), this, SLOT(checkActuationStatusId(mavlink_actuation_status_t*)));
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
        connect(mav, SIGNAL(batteryCellsStatusChanged(mavlink_battery_cells_status_t*)), this, SLOT(checkBatteryCellsStatusId(mavlink_battery_cells_status_t*)));
        connect(mav, SIGNAL(actuationStatusChanged(mavlink_actuation_status_t*)), this, SLOT(checkActuationStatusId(mavlink_actuation_status_t*)));
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocationCase(int)));
        connect(this, SIGNAL(requestAllocationCase(int)), mav, SLOT(sendAUConfiguration(int)));

    }
}

void SkyeAUStatusList::checkBatteryStatusId(mavlink_battery_status_t *battery)
{
    if ( createAUStatusWidget(battery->accu_id) )
    {
        // Widget has been newly created. Forward data.
        auList.value(battery->accu_id)->updateBatteryStatus(battery);
    }
}

void SkyeAUStatusList::checkBatteryCellsStatusId(mavlink_battery_cells_status_t *cells)
{
    if ( createAUStatusWidget(cells->accu_id) )
    {
        // Widget has been newly created. Forward data.
        auList.value(cells->accu_id)->updateBatteryCellsStatus(cells);
    }
}

void SkyeAUStatusList::checkActuationStatusId(mavlink_actuation_status_t *au_status)
{
    if ( createAUStatusWidget(au_status->au_id) )
    {
        // Widget has been newly created. Forward data.
        auList.value(au_status->au_id)->updateActuationStatus(au_status);
    }
}

bool SkyeAUStatusList::createAUStatusWidget(int id)
{
    if (auList.contains(id))
    {
        // widget already exists
        return false;
    } else {
        auList.insert(id, new SkyeAUStatus(id, this));
        ui->horizontalLayout->insertWidget(id, auList.value(id));
        connect(auList.value(id), SIGNAL(requestAllocationCase(uint,bool)), this, SLOT(changeAllocationCase(uint,bool)));
        return true;
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


void SkyeAUStatusList::showContextMenu(const QPoint& pos)
{
    QPoint globalPos = this->mapToGlobal(pos);
    QAction* selectedItem = menu.exec(globalPos);

    if (selectedItem)
    {
        if (selectedItem->isChecked())
        {
            QMap<int, SkyeAUStatus*>::iterator i;
            for (i = auList.begin(); i != auList.end(); ++i)
                i.value()->reduceWidget();
        }
        else
        {
            QMap<int, SkyeAUStatus*>::iterator i;
            for (i = auList.begin(); i != auList.end(); ++i)
                i.value()->expandWidget();
        }
    }
}
