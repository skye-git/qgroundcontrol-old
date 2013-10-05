#include "QGCSkyeTestForce.h"
#include "ui_QGCSkyeTestForce.h"
#include <QDebug>
#include "UASManager.h"
#include "SkyeMAV.h"

QGCSkyeTestForce::QGCSkyeTestForce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestForce),
    uas(NULL)
{
    ui->setupUi(this);

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

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


    // Start Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(emitValues()));
    timer->start(200); //5Hz emitValues is called
}

QGCSkyeTestForce::~QGCSkyeTestForce()
{
    //timer->stop();
    delete ui;
}

void QGCSkyeTestForce::setUAS(UASInterface* uas)
{
    if (this->uas != 0)
    {
        disconnect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), this->uas, SLOT(set6DOFCommandsByWidget(double,double,double,double,double,double)));
    }

    this->uas = dynamic_cast<SkyeMAV*>(uas);
    if (this->uas)
    {
        connect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), this->uas, SLOT(set6DOFCommandsByWidget(double,double,double,double,double,double)));
    }
}

void QGCSkyeTestForce::emitValues()
{
    double forceX = (double)ui->sliderThrustX->value() / (double)maxThrust;
    double forceY = (double)ui->sliderThrustY->value() / (double)maxThrust;
    double forceZ = (double)ui->sliderThrustZ->value() / (double)maxThrust;
    double momentX = (double)ui->sliderMomentX->value() / (double)maxMoment;
    double momentY = (double)ui->sliderMomentY->value() / (double)maxMoment;
    double momentZ = (double)ui->sliderMomentZ->value() / (double)maxMoment;
    emit valueDirectControlChanged( forceX, forceY, forceZ, momentX, momentY, momentZ );
}

void QGCSkyeTestForce::stopAll()
{
    ui->sliderThrustX->setValue(0);
    ui->sliderThrustY->setValue(0);
    ui->sliderThrustZ->setValue(0);
    ui->sliderMomentX->setValue(0);
    ui->sliderMomentY->setValue(0);
    ui->sliderMomentZ->setValue(0);
}
