#include "UASSkyeBatteryInfoWidget.h"
#include "ui_UASSkyeBatteryInfoWidget.h"
#include "UASManager.h"
#include "SkyeMAV.h"

UASSkyeBatteryInfoWidget::UASSkyeBatteryInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryInfoWidget),
    uasId(0)
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

    batteryPacks.insert(MAV_SKYE_BATTERY_PACK_ID_2, new UASSkyeBatteryPackWidget(this, MAV_SKYE_BATTERY_PACK_ID_2));
    listLayout->addWidget(batteryPacks.value(MAV_SKYE_BATTERY_PACK_ID_2));

    batteryPacks.insert(MAV_SKYE_BATTERY_PACK_ID_3, new UASSkyeBatteryPackWidget(this, MAV_SKYE_BATTERY_PACK_ID_3));
    listLayout->addWidget(batteryPacks.value(MAV_SKYE_BATTERY_PACK_ID_3));

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
        // Disconnect old UAS
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
    MAV_SKYE_BATTERY_PACK_ID packId = (MAV_SKYE_BATTERY_PACK_ID)battery->accu_id;
    double voltage1 = (double)battery->voltage_cell_1/1000;
    double voltage2 = (double)battery->voltage_cell_2/1000;
    double voltage3 = (double)battery->voltage_cell_3/1000;
    double voltage4 = (double)battery->voltage_cell_4/1000;
    double current = (double)battery->current_battery/100;
    int remaining = battery->battery_remaining;
    if( batteryPacks.value(packId))
        batteryPacks.value(packId)->changeBatteryStatus( voltage1, voltage2, voltage3, voltage4, current, remaining);
}
