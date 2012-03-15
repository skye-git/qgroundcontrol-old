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

    batteryPacks.insert(QGC_SKYE_BATTERY_PACK_1, new UASSkyeBatteryPackWidget(this, QGC_SKYE_BATTERY_PACK_1));
    listLayout->addWidget(batteryPacks.value(QGC_SKYE_BATTERY_PACK_1));

    batteryPacks.insert(QGC_SKYE_BATTERY_PACK_1, new UASSkyeBatteryPackWidget(this, QGC_SKYE_BATTERY_PACK_2));
    listLayout->addWidget(batteryPacks.value(QGC_SKYE_BATTERY_PACK_1));

    batteryPacks.insert(QGC_SKYE_BATTERY_PACK_1, new UASSkyeBatteryPackWidget(this, QGC_SKYE_BATTERY_PACK_3));
    listLayout->addWidget(batteryPacks.value(QGC_SKYE_BATTERY_PACK_1));
}

UASSkyeBatteryInfoWidget::~UASSkyeBatteryInfoWidget()
{
    delete ui;
}
