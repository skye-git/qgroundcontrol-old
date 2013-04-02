#include "UASVoltageInfoWidget.h"
#include "ui_UASVoltageInfoWidget.h"

UASVoltageInfoWidget::UASVoltageInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASVoltageInfoWidget)
{
    ui->setupUi(this);

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));

    boxLayout = new QHBoxLayout;
    setLayout(boxLayout);

    for (int i=0; i<N_VOLT; i++)
    {
        boxLayout->addWidget(&labelVoltage[i]);
        labelVoltage[i].setText("--V");
        labelVoltage[i].setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }

}

UASVoltageInfoWidget::~UASVoltageInfoWidget()
{
    delete ui;
}


void UASVoltageInfoWidget::setActiveUAS(UASInterface *uas)
{
    // Disconnect old Skye UAS
    if (this->uasId != 0)
    {
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(UASManager::instance()->getUASForId(uasId));
        if (mav)
        {
            disconnect(mav, SIGNAL(voltageInfoChanged(mavlink_battery_voltage_t*)), this, SLOT(changeVoltageInfo(mavlink_battery_voltage_t*)));
        }
    }

    // Connect Skye UAS
    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        uasId = mav->getUASID();
        connect(mav, SIGNAL(voltageInfoChanged(mavlink_battery_voltage_t*)), this, SLOT(changeVoltageInfo(mavlink_battery_voltage_t*)));
    }
}

void UASVoltageInfoWidget::changeVoltageInfo(mavlink_battery_voltage_t *info)
{
    QString voltageText;
    for (int i=0; i<N_VOLT; i++)
    {
        switch (i)
        {
        case 0: voltage[i] = info->voltage_1 / 1000.0f;
            break;
        case 1: voltage[i] = info->voltage_2 / 1000.0f;
            break;
        case 2: voltage[i] = info->voltage_3 / 1000.0f;
            break;
        case 3: voltage[i] = info->voltage_4 / 1000.0f;
            break;
        }
        if (voltage[i] > 0.0f)
        {
            voltageText.setNum(voltage[i], 'g', 3);
            voltageText.append(" V");
            labelVoltage[i].setText(voltageText);
        } else {
            labelVoltage[i].hide();
        }
    }
}
