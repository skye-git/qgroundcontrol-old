#include "SkyeAUStatusList.h"
#include "ui_SkyeAUStatusList.h"
#include "UASManager.h"
#include "SkyeMAV.h"

#include <QDebug>

#define AU_ID_MAX 3

SkyeAUStatusList::SkyeAUStatusList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkyeAUStatusList),
    uasId(0),
    allocationAuto(true),
    allocationCase(0)
{
    ui->setupUi(this);
    auList = QMap<int, SkyeAUStatus*>();
    auActiveList = QMap<int, bool>();

    ui->pushButtonAutomaticAllocation->setCheckable(true);
    ui->pushButtonAutomaticAllocation->setChecked(allocationAuto);
    connect(ui->pushButtonAutomaticAllocation, SIGNAL(toggled(bool)), this, SLOT(setAllocationAutoMode(bool)));
    setAllocationAutoMode(allocationAuto);

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
    if (id > AU_ID_MAX || id < 0)
    {
        qDebug() << "AU id" << id << "ignored because of id restriction to" << AU_ID_MAX;
        return false;
    }
    if (auList.contains(id))
    {
        // widget already exists
        return false;
    } else {
        auList.insert(id, new SkyeAUStatus(id, this));
        ui->layoutAUStatus->insertWidget(id, auList.value(id));
        connect(auList.value(id), SIGNAL(AUStatusChanged(uint,bool,bool)), this, SLOT(changeAUStatus(uint,bool,bool)));
        return true;
    }
}

void SkyeAUStatusList::changeAUStatus(uint auId, bool ready, bool enabled)
{
    updateAllocationCase();
}

void SkyeAUStatusList::updateAllocationCase()
{

    int numberOfActiveAUs = 0;

    // update au status maps
    QMap<int, SkyeAUStatus*>::iterator i;
    for (i = auList.begin(); i != auList.end(); ++i)
    {
        if (allocationAuto == true)
        {
            // AUTO ALLOACTION: AU must be ready and enabled
            auActiveList[i.key()] = (i.value()->isAUReady() && i.value()->isAUEnabled());
        } else {
            // MANUAL ALLOCATIOIN: AU must be enabled
            auActiveList[i.key()] = i.value()->isAUEnabled();
        }
        numberOfActiveAUs += auActiveList[i.key()];
    }


    if (numberOfActiveAUs == auActiveList.size())
    {
        // all AUs are enabled. AllocationCase 0
        emit requestAllocationCase( 0 );
    }
    else if (numberOfActiveAUs == auActiveList.size() - 1)
    {
        // one AU is disabled. Submit AlloctionCase = au_id + 1
        emit requestAllocationCase( auActiveList.key(false)+1 );
    }
    else
    {
        // invalid allocationCase
        emit requestAllocationCase( -1 );
    }
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

void SkyeAUStatusList::setAllocationAutoMode(bool allocAuto)
{
    allocationAuto = allocAuto;
    if (allocAuto)
    {
        ui->pushButtonAutomaticAllocation->setText("AUTO");
        ui->pushButtonAutomaticAllocation->setToolTip("Automatic Allocation");
    }
    else
    {
        ui->pushButtonAutomaticAllocation->setText("MANUAL");
        ui->pushButtonAutomaticAllocation->setToolTip("Manual Allocation");
    }

    updateAllocationCase();
}
