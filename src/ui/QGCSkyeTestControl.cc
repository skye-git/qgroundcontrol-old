#include "QGCSkyeTestControl.h"
#include "UASManager.h"
#include "QGCInputs.h"

// dynamic style for arm button
#define STYLE_RED "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); color: yellow; border-radius: 2px; min-height: 35px; max-height: 50px; min-width: 260px; max-width: 260px; border: 3px solid yellow; font-size: 15pt;"
#define STYLE_GREEN "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); color: yellow; border-radius: 2px; min-height: 35px; max-height: 50px; min-width: 260px; max-width: 260px; border: 3px solid yellow; font-size: 15pt;"

// dynamic style for stopAll and setZero buttons
#define STYLE_GRAY_RESET "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #999999, stop: 1 #444444); border-radius: 2px; min-height: 35px; max-height: 50px; min-width: 80px; max-width: 80px; border: 3px solid; font-size: 15pt;"

// dynamic style for mode buttons
#define STYLE_GRAYMODE "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #999999, stop: 1 #444444); border-radius: 2px; min-height: 35px; max-height: 50px; min-width: 80px; max-width: 80px; border: 3px solid; font-size: 15pt;"
#define STYLE_WHITEMODE "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DDDDDD, stop: 1 #999999); border-radius: 2px; min-height: 35px; max-height: 50px; min-width: 80px; max-width: 80px; border: 3px solid; font-size: 15pt;"
#define STYLE_GREENMODE "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #004433, stop: 1 #228822); border-radius: 2px; min-height: 35px; max-height: 50px; min-width: 80px; max-width: 80px; border: 3px solid; font-size: 15pt;"


QGCSkyeTestControl::QGCSkyeTestControl(QWidget *parent) : QWidget(parent),
    uas(NULL),
    engineOn(false),
    controlMode(SKYE_CONTROL_MODE_MAX)
{
    ui.setupUi(this);

    ui.pushButtonMan->setStyleSheet(STYLE_GRAYMODE);
    ui.pushButton5dof->setStyleSheet(STYLE_GRAYMODE);
    ui.pushButton6dof->setStyleSheet(STYLE_GRAYMODE);
    ui.pushButtonControl->setStyleSheet(STYLE_GREEN);

    ui.pushButtonStopAll->setStyleSheet(STYLE_GRAY_RESET);
    ui.pushButtonSetZero->setStyleSheet(STYLE_GRAY_RESET);

    // connect UAS activation
    connect( UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    // connect uas
    setUAS( UASManager::instance()->getActiveUAS() );


    //connect Pushbuttons
    connect(ui.pushButtonStopAll, SIGNAL(clicked()), this, SLOT(stopAll()));
    connect(ui.pushButtonSetZero, SIGNAL(clicked()), this, SLOT(setZero()));
    connect(ui.pushButtonControl, SIGNAL(clicked()), this, SLOT(cycleContextButton()));

    connect(ui.pushButtonMan, SIGNAL(clicked()), this, SLOT(setManualMode()));
    connect(ui.pushButton5dof, SIGNAL(clicked()), this, SLOT(set5dofMode()));
    connect(ui.pushButton6dof, SIGNAL(clicked()), this, SLOT(set6dofMode()));

}

QGCSkyeTestControl::~QGCSkyeTestControl()
{
    if (this->uas)
    {
        uas->setMode(MAV_MODE_PREFLIGHT, 0);
    }
}

void QGCSkyeTestControl::setUAS(UASInterface *mav)
{
    qDebug() << "TestControl: setUAS" << mav;
    if (mav != NULL) {
        if (uas != 0)
        {
            disconnect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
            disconnect(uas, SIGNAL(skyeControlModeChanged(SKYE_CONTROL_MODE)), this, SLOT(updateMode(SKYE_CONTROL_MODE)));
        }

        uas = dynamic_cast<SkyeUAS*>(mav);
        if (this->uas)
        {
            connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
            connect(uas, SIGNAL(skyeControlModeChanged(SKYE_CONTROL_MODE)), this, SLOT(updateMode(SKYE_CONTROL_MODE)));
            updateState(uas->getState());
        }
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

void QGCSkyeTestControl::changeMode(SKYE_CONTROL_MODE mode)
{
    if (this->uas)
    {
        this->uas->sendControlModeCommand(mode);
    }
}

void QGCSkyeTestControl::setManualMode()
{
    if (this->uas) {
        if (controlMode != SKYE_CONTROL_MODE_MANUAL) {
            changeMode(SKYE_CONTROL_MODE_MANUAL);
            ui.pushButtonMan->setStyleSheet(STYLE_WHITEMODE);
        }
    }
}

void QGCSkyeTestControl::set5dofMode()
{
    if (this->uas) {
        if (controlMode != SKYE_CONTROL_MODE_5DOF) {
            changeMode(SKYE_CONTROL_MODE_5DOF);
            ui.pushButton5dof->setStyleSheet(STYLE_WHITEMODE);
        }
    }
}

void QGCSkyeTestControl::set6dofMode()
{
    if (this->uas) {
        if (controlMode != SKYE_CONTROL_MODE_6DOF) {
            changeMode(SKYE_CONTROL_MODE_6DOF);
            ui.pushButton6dof->setStyleSheet(STYLE_WHITEMODE);
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
			if (tab == QGC_SKYE_CONFIG_TAB_MOTOR || tab == QGC_SKYE_CONFIG_TAB_MOTOR_PPM)
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
        ui.pushButtonControl->setText(tr("DISARM SYSTEM"));
        ui.pushButtonControl->setStyleSheet(STYLE_RED);
        break;
    case (int)MAV_STATE_STANDBY:
        engineOn = false;
        stopAll();
        ui.pushButtonControl->setText(tr("ARM SYSTEM"));
        ui.pushButtonControl->setStyleSheet(STYLE_GREEN);
        break;
    }
}

void QGCSkyeTestControl::updateMode(SKYE_CONTROL_MODE mode)
{

    // only update GUI if control mode has changed
    if (this->controlMode != mode) {
        this->controlMode = mode;

        updateModeStyleSheet();
    }
}

void QGCSkyeTestControl::updateModeStyleSheet()
{

    switch(controlMode) {
    case SKYE_CONTROL_MODE_MANUAL:
    {
        ui.pushButtonMan->setStyleSheet(STYLE_GREENMODE);
        ui.pushButton5dof->setStyleSheet(STYLE_GRAYMODE);
        ui.pushButton6dof->setStyleSheet(STYLE_GRAYMODE);
        break;
    }
    case SKYE_CONTROL_MODE_5DOF:
    {
        ui.pushButtonMan->setStyleSheet(STYLE_GRAYMODE);
        ui.pushButton5dof->setStyleSheet(STYLE_GREENMODE);
        ui.pushButton6dof->setStyleSheet(STYLE_GRAYMODE);
        break;
    }
    case SKYE_CONTROL_MODE_6DOF:
    {
        ui.pushButtonMan->setStyleSheet(STYLE_GRAYMODE);
        ui.pushButton5dof->setStyleSheet(STYLE_GRAYMODE);
        ui.pushButton6dof->setStyleSheet(STYLE_GREENMODE);
        break;
    }
    case SKYE_CONTROL_MODE_MAX:
    case SKYE_CONTROL_MODE_ENUM_END:
    default:
        qDebug() << "[QGCSkyeTestControl] invalid control mode.";
    }
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
        ui.pushButtonMan->hide();
        ui.pushButton5dof->hide();
        ui.pushButton6dof->hide();
        ui.pushButtonSetZero->show();
        break;
    case QGC_SKYE_CONFIG_TAB_FORCE:
        ui.pushButtonMan->show();
        ui.pushButton5dof->hide();
        ui.pushButton6dof->show();
        ui.pushButtonSetZero->hide();
        break;
    default:
        // this should not be the case.
        break;
    }
}

void QGCSkyeTestControl::showEvent(QShowEvent *event)
{
    if (uas != NULL) {
        // Disable all other inputs when test control is shown
        uas->setInputMode(QGC_INPUT_MODE_NONE);

        // // Disarm on every view change (as in disney configuration)
        // changeMode(MAV_MODE_PREFLIGHT);
        // qDebug() << "DISARMED system because Skye config is shown.";
    }
    QWidget::showEvent(event);
}

void QGCSkyeTestControl::hideEvent(QHideEvent *event)
{
    // // Disarm on every view change (as in disney configuration)
    // changeMode(MAV_MODE_PREFLIGHT);
    // qDebug() << "DISARMED system because Skye config has been left.";

    QWidget::hideEvent(event);
}
