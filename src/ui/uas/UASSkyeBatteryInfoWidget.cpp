#include "UASSkyeBatteryInfoWidget.h"
#include "ui_UASSkyeBatteryInfoWidget.h"

UASSkyeBatteryInfoWidget::UASSkyeBatteryInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSkyeBatteryInfoWidget)
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

//    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
}

UASSkyeBatteryInfoWidget::~UASSkyeBatteryInfoWidget()
{
    delete ui;
}
