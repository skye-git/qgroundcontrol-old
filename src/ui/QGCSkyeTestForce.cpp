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

    // Insert 3 Force Widget Panels
    for (int i = 0; i<3; i++)
    {
        panelMap.insert(i, new QGCSkyeTestForcePanel(this, i));
        ui->groupBoxPanel->layout()->addWidget(panelMap[i]);
    }

    // Insert box for periodic timing
    timerWidget = new QGCSkyeTestTimerWidget(this);
    ui->groupBoxTimer->layout()->addWidget(timerWidget);

    // connect UAV
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

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
    double force[3];
    double moment[3];
    for (int i = 0; i<3; i++) {
        force[i] = panelMap[i]->getForce();
        moment[i] = panelMap[i]->getMoment();
    }

    emit valueDirectControlChanged( force[0],  force[1],  force[2],
                                   moment[0], moment[1], moment[2] );
}

void QGCSkyeTestForce::stopAll()
{
    for (int i = 0; i<3; i++) {
        panelMap[i]->stopAll();
    }
    this->emitValues();
}
