#include "UASSkyeBatteryInfoWidget.h"
#include "ui_UASSkyeBatteryInfoWidget.h"
#include <UASManager.h>
#include "SkyeMAV.h"

UASSkyeBatteryInfoWidget::UASSkyeBatteryInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryInfoWidget),
    uasId(0),
    batteryPacksNumber(1),
    uasUsesZeroBatteryId(false)
{
    ui->setupUi(this);

    listLayout = new QVBoxLayout(this);
    listLayout->setMargin(0);
    listLayout->setSpacing(3);
    listLayout->setAlignment(Qt::AlignTop);
    this->setLayout(listLayout);

    batteryPacks = QMap<int, UASSkyeBatteryPackWidget*>();

    batteryPacks.insert(MAV_SKYE_BATTERY_PACK_ID_1, new UASSkyeBatteryPackWidget(this, MAV_SKYE_BATTERY_PACK_ID_1));
    listLayout->addWidget(batteryPacks.value(MAV_SKYE_BATTERY_PACK_ID_1));

    setActiveUAS(UASManager::instance()->getActiveUAS());
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));
}

UASSkyeBatteryInfoWidget::~UASSkyeBatteryInfoWidget()
{
    delete ui;
}

void UASSkyeBatteryInfoWidget::setActiveUAS(UASInterface *uas)
{
    if (this->uasId != 0)
    {
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(UASManager::instance()->getUASForId(uasId));
        if (mav)
        {
            disconnect(mav, SIGNAL(batteryPackChanged(mavlink_battery_status_t*)), this, SLOT(changeBatteryPack(mavlink_battery_status_t*)));
            batteryPacksNumber = 1;
            uasUsesZeroBatteryId = false;
        }
    }

    // Connect UAS
    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        uasId = mav->getUASID();
        connect(mav, SIGNAL(batteryPackChanged(mavlink_battery_status_t*)), this, SLOT(changeBatteryPack(mavlink_battery_status_t*)));
    }
}

void UASSkyeBatteryInfoWidget::changeBatteryPack(mavlink_battery_status_t* battery)
{
//    qDebug()<<"Message battery_status received";
    MAV_SKYE_BATTERY_PACK_ID packId = (MAV_SKYE_BATTERY_PACK_ID)(battery->accu_id);
    if (packId == 0) uasUsesZeroBatteryId = true;
    double voltage1 = (double)battery->voltage_cell_1/1000.0;
    double voltage2 = (double)battery->voltage_cell_2/1000.0;
    double voltage3 = (double)battery->voltage_cell_3/1000.0;
    double voltage4 = (double)battery->voltage_cell_4/1000.0;
    double voltage5 = (double)battery->voltage_cell_5/1000.0;
    double voltage6 = (double)battery->voltage_cell_6/1000.0;
    double current = (double)battery->current_battery/100.0;
    int remaining = battery->battery_remaining;

    if (packId == batteryPacksNumber+1)
    {
        // Add battery pack widget
        batteryPacks.insert(packId, new UASSkyeBatteryPackWidget(this, packId));
        listLayout->addWidget(batteryPacks.value(packId));
        batteryPacksNumber++;
     }

    // Shift id if UAS starts id with ID 0
    if (uasUsesZeroBatteryId == true)
    {
        packId = (MAV_SKYE_BATTERY_PACK_ID)((int)packId + 1);
    }
    // Update battery pack widget
    if (batteryPacks.value(packId))
    {
        batteryPacks.value(packId)->changeBatteryStatus( voltage1, voltage2, voltage3, voltage4, voltage5, voltage6, current, remaining);
    }

}
