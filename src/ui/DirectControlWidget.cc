#include "DirectControlWidget.h"
#include "ui_DirectControlWidget.h"
#include <QDebug>
#include "UAS.h"
#include "UASManager.h"
#include "QGC.h"
#include "SkyeMAV.h"

DirectControlWidget::DirectControlWidget(QWidget *parent):
    QDialog(parent),
    uas(NULL),
    engineOn(false),
    ui(new Ui::DirectControlWidget)
{

    ui->setupUi(this);

    maxThrust =  100;
    maxMoment =  100;
    ui->sliderThrustX->setRange(-maxThrust, maxThrust);
    ui->sliderThrustY->setRange(-maxThrust, maxThrust);
    ui->sliderThrustZ->setRange(-maxThrust, maxThrust);
    ui->sliderMomentX->setRange(-maxMoment, maxMoment);
    ui->sliderMomentY->setRange(-maxMoment, maxMoment);
    ui->sliderMomentZ->setRange(-maxMoment, maxMoment);
    ui->spinBoxThrustX->setRange(-maxThrust, maxThrust);
    ui->spinBoxThrustY->setRange(-maxThrust, maxThrust);
    ui->spinBoxThrustZ->setRange(-maxThrust, maxThrust);
    ui->spinBoxMomentX->setRange(-maxMoment, maxMoment);
    ui->spinBoxMomentY->setRange(-maxMoment, maxMoment);
    ui->spinBoxMomentZ->setRange(-maxMoment, maxMoment);

    this->uas = dynamic_cast<SkyeMAV*>(UASManager::instance()->getActiveUAS());

    if(uas)
    {
        connect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), uas, SLOT(setManualControlCommands6DoF(double,double,double,double,double,double)));
        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        uas->setMode(MAV_MODE_DIRECT_CONTROL_DISARMED);
    }

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    //connect Sliders, spinBoxes and dials
    connect(ui->sliderThrustX, SIGNAL(valueChanged(int)), ui->spinBoxThrustX, SLOT(setValue(int)));
    connect(ui->spinBoxThrustX, SIGNAL(valueChanged(int)), ui->sliderThrustX, SLOT(setValue(int)));

    connect(ui->sliderThrustY, SIGNAL(valueChanged(int)), ui->spinBoxThrustY, SLOT(setValue(int)));
    connect(ui->spinBoxThrustY, SIGNAL(valueChanged(int)), ui->sliderThrustY, SLOT(setValue(int)));

    connect(ui->sliderThrustZ, SIGNAL(valueChanged(int)), ui->spinBoxThrustZ, SLOT(setValue(int)));
    connect(ui->spinBoxThrustZ, SIGNAL(valueChanged(int)), ui->sliderThrustZ, SLOT(setValue(int)));

    connect(ui->sliderMomentX, SIGNAL(valueChanged(int)), ui->spinBoxMomentX, SLOT(setValue(int)));
    connect(ui->spinBoxMomentX, SIGNAL(valueChanged(int)), ui->sliderMomentX, SLOT(setValue(int)));

    connect(ui->sliderMomentY, SIGNAL(valueChanged(int)), ui->spinBoxMomentY, SLOT(setValue(int)));
    connect(ui->spinBoxMomentY, SIGNAL(valueChanged(int)), ui->sliderMomentY, SLOT(setValue(int)));

    connect(ui->sliderMomentZ, SIGNAL(valueChanged(int)), ui->spinBoxMomentZ, SLOT(setValue(int)));
    connect(ui->spinBoxMomentZ, SIGNAL(valueChanged(int)), ui->sliderMomentZ, SLOT(setValue(int)));

    //connect Pushbuttons
    connect(ui->stopAllButton, SIGNAL(clicked()),this, SLOT(stopAll()));
    connect(ui->controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));
    connect(ui->closeButton, SIGNAL(clicked()),this, SLOT(stopAll()));
    connect(ui->closeButton, SIGNAL(clicked()),this, SLOT(directControlClose()));


    // Start Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(emitValues()));
    timer->start(200); //5Hz emitValues is called

    // Display the widget
    this->window()->setWindowTitle(tr("Direct Control"));
    this->setStyleSheet("QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #000000, stop: 1 #444444) }");
    this->show();
}

DirectControlWidget::~DirectControlWidget()
{
    if(uas)
    {
        timer->stop();
        uas->setMode(MAV_MODE_PREFLIGHT);
    }
    delete ui;
}

void DirectControlWidget::setUAS(UASInterface* mav)
{
    if (uas != 0)
    {
        disconnect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), uas, SLOT(setManualControlCommands6DoF(double,double,double,double,double,double)));
        disconnect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
    }

    uas = dynamic_cast<SkyeMAV*>(mav);
    if (uas)
    {
        connect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), uas, SLOT(setManualControlCommands6DoF(double,double,double,double,double,double)));
        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        updateState(uas->getUASState());
    }
}

void DirectControlWidget::emitValues()
{
    if (uas)
    {
        if (uas->getMode() == MAV_MODE_DIRECT_CONTROL_ARMED)
        {
            double forceX = (double)ui->sliderThrustX->value() / (double)maxThrust;
            double forceY = (double)ui->sliderThrustY->value() / (double)maxThrust;
            double forceZ = (double)ui->sliderThrustZ->value() / (double)maxThrust;
            double momentX = (double)ui->sliderMomentX->value() / (double)maxMoment;
            double momentY = (double)ui->sliderMomentY->value() / (double)maxMoment;
            double momentZ = (double)ui->sliderMomentZ->value() / (double)maxMoment;
            emit valueDirectControlChanged( forceX, forceY, forceZ, momentX, momentY, momentZ );

        }
    }
}

void DirectControlWidget::changeMode(int mode)
{
    if(uas)
    {
        uas->setMode(mode);
    }
}

void DirectControlWidget::directControlClose()
{
    if(uas)
    {
        emit valueDirectControlChanged( 0, 0, 0, 0, 0, 0 );
        uas->setMode(MAV_MODE_PREFLIGHT);
    }
    engineOn=false;
    //timer->stop(); otherwise if ones reopens the widget, no signal is emitted no more
    this->close();
}

void DirectControlWidget::stopAll()
{
    ui->sliderThrustX->setValue(0);
    ui->sliderThrustY->setValue(0);
    ui->sliderThrustZ->setValue(0);
    ui->sliderMomentX->setValue(0);
    ui->sliderMomentY->setValue(0);
    ui->sliderMomentZ->setValue(0);
}

void DirectControlWidget::cycleContextButton()
{
    if (uas)
    {
        if (!engineOn)
        {
            uas->armSystem();
//            ui->controlButton->setText(tr("DISARMSYSTEM"));
//            ui.controlButton->setStyleSheet("* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); border-color: yellow; color: yellow }");
            uas->setMode(MAV_MODE_DIRECT_CONTROL_ARMED);
            engineOn=true;
        } else {
            emit valueDirectControlChanged( 0, 0, 0, 0, 0, 0 );
            uas->disarmSystem();
//            ui->controlButton->setText(tr("ARM SYSTEM"));
//            ui.controlButton->setStyleSheet("* { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); }");
            uas->setMode(MAV_MODE_DIRECT_CONTROL_DISARMED);
            engineOn=false;
        }

    }
}

void DirectControlWidget::updateState(int state)
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
