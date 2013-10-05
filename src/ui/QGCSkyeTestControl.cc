#include "QGCSkyeTestControl.h"
#include "ui_QGCSkyeTestControl.h"
#include "UASManager.h"

QGCSkyeTestControl::QGCSkyeTestControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestControl),
    uas(NULL),
    engineOn(false)
{
    ui->setupUi(this);

    //connect UAS activation
    connect( UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    //connect uas
    setUAS( UASManager::instance()->getActiveUAS() );


    //connect Pushbuttons
    connect(ui->stopAllButton, SIGNAL(clicked()),this, SLOT(stopAll()));
    connect(ui->SetZeroButton, SIGNAL(clicked()),this, SLOT(setZero()));
    connect(ui->controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));

    connect(ui->manPushButton, SIGNAL(clicked()), this, SLOT(setManualMode()));
    connect(ui->ratePushButton, SIGNAL(clicked()), this, SLOT(setRateMode()));
    connect(ui->attPushButton, SIGNAL(clicked()), this, SLOT(setAttMode()));

}

QGCSkyeTestControl::~QGCSkyeTestControl()
{
    if (this->uas)
    {
        uas->setMode(MAV_MODE_PREFLIGHT, 0);
    }
    delete ui;
}

void QGCSkyeTestControl::setUAS(UASInterface *mav)
{
    if (uas != 0)
    {
        disconnect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        disconnect(uas, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
    }

    uas = dynamic_cast<SkyeMAV*>(mav);
    if (this->uas)
    {
        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        connect(uas, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        updateState(uas->getState());
        uas->setMode(MAV_MODE_PREFLIGHT, 0);
        uas->setInputMode(SkyeMAV::QGC_INPUT_MODE_NONE);
    }
}

void QGCSkyeTestControl::stopAll()
{
    emit stopAllRequested();
}

void QGCSkyeTestControl::setZero()
{
    emit setZeroRequested();
}

void QGCSkyeTestControl::changeMode(int mode)
{
    if (this->uas)
    {
        uas->setMode(mode, 0);
        uas->setInputMode(SkyeMAV::QGC_INPUT_MODE_NONE);
        //emit emitValues();
    }
}

void QGCSkyeTestControl::setManualMode()
{
    if (this->uas) {
        if (engineOn) {
            changeMode(MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
        }
    }
}

void QGCSkyeTestControl::setRateMode()
{
    if (this->uas) {
        if (engineOn) {
            changeMode(MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
        }
    }
}

void QGCSkyeTestControl::setAttMode()
{
    if (this->uas) {
        if (engineOn) {
            changeMode(MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
        }
    }
}

void QGCSkyeTestControl::cycleContextButton()
{
    if (this->uas)
    {
        if (!engineOn)
        {
            uas->armSystem();
            engineOn=true;
            if (tab == QGC_SKYE_CONFIG_TAB_MOTOR)
            {
                uas->setModeCommand(MAV_MODE_FLAG_TEST_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
            }

        } else {
            //emit valueDirectControlChanged( 0, 0, 0, 0, 0, 0 );
            stopAll();
            uas->disarmSystem();
            engineOn=false;
        }
    }
}

void QGCSkyeTestControl::updateState(int state)
{
    switch (state)
    {
    case (int)MAV_STATE_ACTIVE:
        engineOn = true;
        ui->controlButton->setText(tr("DISARM SYSTEM"));
        ui->controlButton->setStyleSheet("* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); border-color: yellow; color: yellow }");
        break;
    case (int)MAV_STATE_STANDBY:
        engineOn = false;
        stopAll();
        ui->controlButton->setText(tr("ARM SYSTEM"));
        ui->controlButton->setStyleSheet("* { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); }");
        break;
    }
}

void QGCSkyeTestControl::updateMode(int uas, int baseMode)
{
    QString green = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #004433, stop: 1 #228822)}";
    QString gray  = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #999999, stop: 1 #444444)}";

    if (baseMode == MAV_MODE_PREFLIGHT)
    {
        ui->manPushButton->setStyleSheet(gray);
        ui->ratePushButton->setStyleSheet(gray);
        ui->attPushButton->setStyleSheet(gray);
    }

    if ((baseMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL) || (baseMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE))
    {
        ui->manPushButton->setStyleSheet(green);
    } else {
        ui->manPushButton->setStyleSheet(gray);
    }

    if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE)
    {
        if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE)
        {
            ui->ratePushButton->setStyleSheet(green);
            ui->attPushButton->setStyleSheet(gray);
        } else {
            ui->ratePushButton->setStyleSheet(green);
            ui->attPushButton->setStyleSheet(green);
        }
    } else {
        ui->ratePushButton->setStyleSheet(gray);
        ui->attPushButton->setStyleSheet(gray);
    }
}

void QGCSkyeTestControl::tabChanged(int tab)
{
    if (this->uas)
    {
        uas->disarmSystem();
    }

    this->tab = tab;

    if (tab == QGC_SKYE_CONFIG_TAB_MOTOR)
    {
        ui->manPushButton->hide();
        ui->ratePushButton->hide();
        ui->attPushButton->hide();

        ui->SetZeroButton->show();
    }

    if (tab == QGC_SKYE_CONFIG_TAB_FORCE)
    {
        ui->SetZeroButton->hide();

        ui->manPushButton->show();
        ui->ratePushButton->show();
        ui->attPushButton->show();
    }
}
