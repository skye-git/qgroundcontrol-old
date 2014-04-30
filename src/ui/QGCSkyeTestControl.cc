#include "QGCSkyeTestControl.h"
#include "ui_QGCSkyeTestControl.h"
#include "UASManager.h"

// dynamic style for arm button
#define STYLE_RED "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); color: yellow;"
#define STYLE_GREEN "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); color: yellow;"

// dynamic style for mode button
#define STYLE_GRAYMODE "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #999999, stop: 1 #444444);"
#define STYLE_WHITEMODE "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DDDDDD, stop: 1 #999999);"
#define STYLE_GREENMODE "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #004433, stop: 1 #228822);"


QGCSkyeTestControl::QGCSkyeTestControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestControl),
    uas(NULL),
    engineOn(false)
{
    ui->setupUi(this);

    ui->manPushButton->setObjectName("manControlButtonGray");
    ui->ratePushButton->setObjectName("rateControlButtonGray");
    ui->attPushButton->setObjectName("attControlButtonGray");

    // rate control is not supported on current IMU anymore
    ui->ratePushButton->hide();

    ui->manPushButton->setStyleSheet("");
    ui->ratePushButton->setStyleSheet("");
    ui->attPushButton->setStyleSheet("");

    ui->controlButton->setObjectName("controlButtonGreen");
    ui->controlButton->setStyleSheet("");

    //connect UAS activation
    connect( UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    //connect uas
    setUAS( UASManager::instance()->getActiveUAS() );


    //connect Pushbuttons
    connect(ui->stopAllButton, SIGNAL(clicked()),this, SLOT(stopAll()));
    connect(ui->setZeroButton, SIGNAL(clicked()),this, SLOT(setZero()));
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
        uas->setModeCommand(mode);
        //uas->setInputMode(SkyeMAV::QGC_INPUT_MODE_NONE);
        //emit emitValues();
    }
}

void QGCSkyeTestControl::setManualMode()
{
    if (this->uas) {
        if (engineOn) {
            ui->manPushButton->setObjectName("manControlButtonWhite");
            ui->manPushButton->setStyleSheet("");
            changeMode(MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
        }
    }
}

void QGCSkyeTestControl::setRateMode()
{
    if (this->uas) {
        if (engineOn) {
            ui->ratePushButton->setObjectName("rateControlButtonWhite");
            ui->ratePushButton->setStyleSheet("");
            changeMode(MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
        }
    }
}

void QGCSkyeTestControl::setAttMode()
{
    if (this->uas) {
        if (engineOn) {
            ui->attPushButton->setObjectName("attControlButtonWhite");
            ui->attPushButton->setStyleSheet("");
            changeMode( MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
        }
    }
}

void QGCSkyeTestControl::cycleContextButton()
{
    if (this->uas)
    {
        if (!engineOn)
        {
            engineOn=true;
            if (tab == QGC_SKYE_CONFIG_TAB_MOTOR || QGC_SKYE_CONFIG_TAB_MOTOR_PPM)
            {
                uas->setModeCommand(MAV_MODE_FLAG_TEST_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);
            } else {
                uas->armSystem();
            }

        } else {
            //emit valueDirectControlChanged( 0, 0, 0, 0, 0, 0 );
            stopAll();
            uas->setMode(MAV_MODE_PREFLIGHT, 0);
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
        //ui->controlButton->setObjectName("controlButtonRed");
        ui->controlButton->setStyleSheet(STYLE_RED);
        break;
    case (int)MAV_STATE_STANDBY:
        engineOn = false;
        stopAll();
        ui->controlButton->setText(tr("ARM SYSTEM"));
        ui->controlButton->setObjectName("controlButtonGreen");
        //ui->controlButton->setStyleSheet("");
        ui->controlButton->setStyleSheet(STYLE_GREEN);
        break;
    }
}

void QGCSkyeTestControl::updateMode(int uas, int baseMode)
{
    //qDebug() << "QGCSkyeTestControl: update mode:" << baseMode ;
    if (baseMode == MAV_MODE_PREFLIGHT)
    {
        //qDebug() << "PREFLIGHT";
        //ui->manPushButton->setObjectName("manControlButtonGray");
        //ui->ratePushButton->setObjectName("rateControlButtonGray");
        //ui->attPushButton->setObjectName("attControlButtonGray");
        ui->manPushButton->setStyleSheet(STYLE_GRAYMODE);
        ui->ratePushButton->setStyleSheet(STYLE_GRAYMODE);
        ui->attPushButton->setStyleSheet(STYLE_GRAYMODE);
    }

    if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL)
    {
        //qDebug() << "MANUAL_MODE";
        //ui->manPushButton->setObjectName("manControlButtonGreen");
        //ui->ratePushButton->setObjectName("rateControlButtonGray");
        //ui->attPushButton->setObjectName("attControlButtonGray");
        ui->manPushButton->setStyleSheet(STYLE_GREENMODE);
        ui->ratePushButton->setStyleSheet(STYLE_GRAYMODE);
        ui->attPushButton->setStyleSheet(STYLE_GRAYMODE);
    }

    if ((baseMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE) && (baseMode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE))
    {
        //qDebug() << "RATE_MODE";
        //ui->manPushButton->setObjectName("manControlButtonGray");
        //ui->ratePushButton->setObjectName("rateControlButtonGreen");
        //ui->attPushButton->setObjectName("attControlButtonGray");
        ui->manPushButton->setStyleSheet(STYLE_GRAYMODE);
        ui->ratePushButton->setStyleSheet(STYLE_GREENMODE);
        ui->attPushButton->setStyleSheet(STYLE_GRAYMODE);
    }

    if ((baseMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE) && !(baseMode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE))
    {
        //qDebug() << "ATT_MODE";
        //ui->manPushButton->setObjectName("manControlButtonGray");
        //ui->ratePushButton->setObjectName("rateControlButtonGray");
        //ui->attPushButton->setObjectName("attControlButtonGreen");
        ui->manPushButton->setStyleSheet(STYLE_GRAYMODE);
        ui->ratePushButton->setStyleSheet(STYLE_GRAYMODE);
        ui->attPushButton->setStyleSheet(STYLE_GREENMODE);
    }

//    ui->manPushButton->setStyleSheet("");
//    ui->ratePushButton->setStyleSheet("");
//    ui->attPushButton->setStyleSheet("");

}

void QGCSkyeTestControl::tabChanged(int tab)
{
    this->tab = tab;

    /* disarm system at every tab change */
    if (this->uas)
    {
        uas->disarmSystem();
    }

    /* adjust buttons according to current tab */
    switch (tab) {
    case QGC_SKYE_CONFIG_TAB_MOTOR:
    case QGC_SKYE_CONFIG_TAB_MOTOR_PPM:
        ui->manPushButton->hide();
        ui->ratePushButton->hide();
        ui->attPushButton->hide();
        ui->setZeroButton->show();
        break;
    case QGC_SKYE_CONFIG_TAB_FORCE:
        ui->setZeroButton->hide();
        ui->manPushButton->show();
        //ui->ratePushButton->show();
        ui->attPushButton->show();
        break;
    default:
        // this should not be the case.
        break;
    }
}
