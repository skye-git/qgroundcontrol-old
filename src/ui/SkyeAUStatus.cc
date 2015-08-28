#include "SkyeAUStatus.h"
#include "ui_SkyeAUStatus.h"

#define SKYE_AU_STATUS_INTERVAL 10000

SkyeAUStatus::SkyeAUStatus(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkyeAUStatus),
    uasId(0),
    enabled(true),
    status(MAV_ACTUATION_UNIT_STATUS_UNKNOWN),
    thrust(0)
{
    ui->setupUi(this);
    setAU(id);

    ui->labelName->setStyleSheet("QLabel { font-size: 12pt;}");
    ui->labelBatteryStatus->setText("");
    ui->labelBatteryStatus->setToolTip("Battery status");
    ui->labelAUStatus->setText("");
    ui->labelAUStatus->setToolTip("Actuation unit status");
    ui->progressBarThrust->setValue(0);
    ui->lcdNumberCurrent->setToolTip("Battery current [A]");
    ui->lcdNumberVoltage->setToolTip("Battery voltage [V]");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(clickedResetButton()));
    connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(clickedCheckBox(bool)));

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

    batt = new mavlink_battery_status_t;
    memset(batt, 0, sizeof(*batt));

    // update AU status list a first time
    emitEnabled();

    // start timer to check whether info is up-to-date
    lastUpdate.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkUpToDate()));
    timer.start(SKYE_AU_STATUS_INTERVAL);
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
        SkyeUAS* mav = dynamic_cast<SkyeUAS*>(oldUAS);
        if (mav)
        {
            // Disconnect
            disconnect(mav, SIGNAL(batteryStatusChanged(mavlink_battery_status_t*)), this, SLOT(updateBatteryStatus(mavlink_battery_status_t*)));
            disconnect(mav, SIGNAL(allocationValueChanged(mavlink_allocation_controller_raw_t*)), this, SLOT(updateThrustValue(mavlink_allocation_controller_raw_t*)));
            disconnect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocationCase(uint)));
            disconnect(mav, SIGNAL(actuationStatusChanged(mavlink_actuation_status_t*)), this, SLOT(updateActuationStatus(mavlink_actuation_status_t*)));
            disconnect(this, SIGNAL(requestAUReset(int)), mav, SLOT(sendAUReset(int)));
        }
    }


    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        // connect
        connect(mav, SIGNAL(batteryStatusChanged(mavlink_battery_status_t*)), this, SLOT(updateBatteryStatus(mavlink_battery_status_t*)));
        connect(mav, SIGNAL(allocationValueChanged(mavlink_allocation_controller_raw_t*)), this, SLOT(updateThrustValue(mavlink_allocation_controller_raw_t*)));
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocationCase(int)));
        connect(mav, SIGNAL(actuationStatusChanged(mavlink_actuation_status_t*)), this, SLOT(updateActuationStatus(mavlink_actuation_status_t*)));
        connect(this, SIGNAL(requestAUReset(int)), mav, SLOT(sendAUReset(int)));

    }
}

void SkyeAUStatus::setAU(int id)
{
    this->auId = id;
    ui->labelName->setText(QString("AU %1").arg(id+1));
}

void SkyeAUStatus::updateBatteryStatus(mavlink_battery_status_t *battery)
{
    if (this->auId == battery->id)
    {
        memcpy(batt, battery, sizeof(*battery));

        /* sum up cell voltages */
        voltage = 0.0;
        for (int i=0; i<10; i++) {
            if (batt->voltages[i] > 0) {
                voltage += (double)battery->voltages[i];
            }

//            qDebug() << "BAT ID" << batt->id << "cellvoltage = " <<
//                        batt->voltages[0] <<
//                        batt->voltages[1] <<
//                        batt->voltages[2];
        }

        ui->lcdNumberVoltage->display(voltage/1000.0);
        ui->lcdNumberCurrent->display(battery->current_battery/1000.0);
        ui->labelBatteryStatus->setText(getShortStringForAccuStatus((int)battery->battery_function));
        ui->labelBatteryStatus->setToolTip(getStringForAccuStatus((int)battery->battery_function));

        updateToolTipText();
        updateStyleSheets();
    }
}

void SkyeAUStatus::updateThrustValue(mavlink_allocation_output_t *alloc)
{
    thrust = alloc->thrust[this->auId]*100/1000;
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
                     .arg(batt->id)
                     .arg(batt->voltages[0]/1000.0)
                     .arg(batt->voltages[1]/1000.0)
                     .arg(batt->voltages[2]/1000.0)
                     .arg(batt->voltages[3]/1000.0)
                     .arg(batt->voltages[4]/1000.0)
                     .arg(batt->voltages[5]/1000.0)
                     .arg(batt->current_battery/1000.0)
                     .arg(batt->current_consumed)
                     .arg(batt->current_charged)
                     .arg(batt->time_charged/60)
                     .arg(batt->time_charged-(batt->time_charged/60)*60));
}

void SkyeAUStatus::checkUpToDate()
{
    // check whether data is outdated
    if (lastUpdate.elapsed() > SKYE_AU_STATUS_INTERVAL)
    {
        ui->widgetTop->setStyleSheet("QWidget#widgetTop {background-color: rgba(200, 200, 200, 100);}");
        ui->widgetBottom->setStyleSheet("QWidget#widgetBottom {background-color: rgba(200, 200, 200, 100);}");
        ui->labelBatteryStatus->setText("Outdated!");
        this->update();
    }
}

void SkyeAUStatus::updateStyleSheets()
{
    lastUpdate.restart();

    // style for voltage display
    if (voltage > SKYE_CRITICAL_VOLTAGE) {
        ui->lcdNumberVoltage->setPalette(QColor(50, 205, 50));  // GREEN
    } else if (voltage > SKYE_ALARM_VOLTAGE) {
        ui->lcdNumberVoltage->setPalette(QColor(255, 165, 0));  // ORANGE
    } else {
        ui->lcdNumberVoltage->setPalette(QColor(255, 0, 0));    // RED
    }
    // TODO: check here why color does not always display properly
    ui->lcdNumberVoltage->update();

    QString str;

    switch (status) {
    case MAV_ACTUATION_UNIT_STATUS_ERROR:
    case MAV_ACTUATION_UNIT_STATUS_DETACHED:
    case MAV_ACTUATION_UNIT_STATUS_DISABLED:
        str = "QWidget#widgetTop {background-color: rgba(255, 0, 0, 170);}";
        break;
    case MAV_ACTUATION_UNIT_STATUS_READY:
        str = "QWidget#widgetTop {background-color: rgba(0, 200, 0, 170);}";
        break;
    case MAV_ACTUATION_UNIT_STATUS_INITIALIZING:
        str = "QWidget#widgetTop {background-color: rgba(255, 140, 0, 170);}";
        break;
    case MAV_ACTUATION_UNIT_STATUS_HOMING:
        str = "QWidget#widgetTop {background-color: rgba(255, 255, 0, 170);}";
        break;
    default:
        str = "QWidget#widgetTop {background-color: rgba(0, 0, 0, 0);}";
        break;
    }
    ui->widgetTop->setStyleSheet(str);


    // battery status color (increasing importance)
    QPalette pal(palette());
    if (batt->battery_function & BATTERY_STATUS_BIT_ATTACHED) {
        str = "QWidget#widgetBottom {background-color: rgba(0, 0, 0, 255); }";
    } else {
        str = "QWidget#widgetBottom {background-color: rgba(160, 160, 160, 255); }";
    }

    if (batt->battery_function & BATTERY_STATUS_BIT_UNDERVOLTAGE) {
        str = "QWidget#widgetBottom {background-color: rgba(255, 100, 0, 255); }";
    }
    if (batt->battery_function & BATTERY_STATUS_BIT_ERROR) {
        str = "QWidget#widgetBottom {background-color: rgba(200, 0, 0, 255); }";
    }
    ui->widgetBottom->setStyleSheet(str);
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

QString SkyeAUStatus::getShortStringForAccuStatus(int status)
{
    QString str = "";

    if (status & BATTERY_STATUS_BIT_ATTACHED)
    {
        str.append("AT");
    }
    if (status & BATTERY_STATUS_BIT_BALANCING)
    {
        if (str.length()) str.append("|");
        str.append("BAL");
    }
    if (status & BATTERY_STATUS_BIT_CHARGING)
    {
        if (str.length()) str.append("|");
        str.append("CH");
    }
    if (status & BATTERY_STATUS_BIT_DISABLED)
    {
        if (str.length()) str.append("|");
        str.append("DIS");
    }
    if (status & BATTERY_STATUS_BIT_ERROR)
    {
        if (str.length()) str.append("|");
        str.append("ERR");
    }
    if (status & BATTERY_STATUS_BIT_FULL)
    {
        if (str.length()) str.append("|");
        str.append("FULL");
    }
    if (status & BATTERY_STATUS_BIT_UNDERVOLTAGE)
    {
        if (str.length()) str.append("|");
        str.append("UV");
    }

    return str;
}

QString SkyeAUStatus::getStringForAUStatus(int status)
{
    QString str = "";
    switch (status)
    {
    case MAV_ACTUATION_UNIT_STATUS_DETACHED:
    {
        str.append("detached");
    } break;
    case MAV_ACTUATION_UNIT_STATUS_DISABLED:
    {
        if (str.length()) str.append(", ");
        str.append("disabled");
    } break;
    case MAV_ACTUATION_UNIT_STATUS_ERROR:
    {
        if (str.length()) str.append(", ");
        str.append("ERROR");
    } break;
    case MAV_ACTUATION_UNIT_STATUS_HOMING:
    {
        if (str.length()) str.append(", ");
        str.append("homing");
    } break;
    case MAV_ACTUATION_UNIT_STATUS_INITIALIZING:
    {
        if (str.length()) str.append(", ");
        str.append("init");
    } break;
    case MAV_ACTUATION_UNIT_STATUS_READY:
    {
        if (str.length()) str.append(", ");
        str.append("ready");
    } break;
    case MAV_ACTUATION_UNIT_STATUS_UNKNOWN:
    {
        if (str.length()) str.append(", ");
        str.append("unknown");
    } break;
    default: break;
    }
    return str;
}

void SkyeAUStatus::clickedCheckBox(bool checked)
{
    enabled = checked;
    emitEnabled();
}

void SkyeAUStatus::emitEnabled()
{
    emit AUStatusChanged(this->auId+1, status == MAV_ACTUATION_UNIT_STATUS_READY, enabled);
}

void SkyeAUStatus::updateAllocationCase(int allocCase)
{
    // Is this actuation unit excluded?
    // ui->checkBox->setChecked(allocCase != (auId+1));
    // qDebug() << "THIS IS AU+1" << this->auId+1 << "and allocCase is" << allocCase;
}

void SkyeAUStatus::updateActuationStatus(mavlink_actuation_status_t *au_status)
{
    if (au_status->au_id == this->auId)
    {
        if (status != (MAV_ACTUATION_UNIT_STATUS)au_status->status)
        {
            status = (MAV_ACTUATION_UNIT_STATUS)au_status->status;
            emitEnabled();
        }
        ui->labelAUStatus->setText(getStringForAUStatus((int)au_status->status));
        updateStyleSheets();
    }
}

void SkyeAUStatus::clickedResetButton()
{
    emit requestAUReset(this->auId);
}

void SkyeAUStatus::reduceWidget()
{
    ui->labelBatteryStatus->hide();
    ui->lcdNumberCurrent->hide();
    ui->widgetTop->hide();
}

void SkyeAUStatus::expandWidget()
{
    ui->labelBatteryStatus->show();
    ui->lcdNumberCurrent->show();
    ui->widgetTop->show();
}
