#include "QGCSkyeTestMotors.h"
#include <QDebug>
#include "UASManager.h"

#define QGC_MAX_THRUST 400
#define QGC_MAX_ABS_DEGREE 180

QGCSkyeTestMotors::QGCSkyeTestMotors(QWidget *parent) :
    QGCSkyeTest(parent)
{
    // Insert 4 Test Widget Panels
    for (int i = 0; i<4; i++)
    {
        panelMap.insert(i, new QGCSkyeTestMotorsPanel(this, i));
        ui->groupBoxPanel->layout()->addWidget(panelMap[i]);
    }

    // Connect UAS
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());
}

QGCSkyeTestMotors::~QGCSkyeTestMotors()
{
    //timer->stop();
    delete ui;
}

void QGCSkyeTestMotors::setUAS(UASInterface* uas)
{
    // disconnect old UAS
    if (this->uas)
    {
        disconnect(this, SIGNAL(valueTestControlChanged(double, double, double, double, double, double, double, double)), uas, SLOT(setTestphaseCommandsByWidget(double, double, double, double, double, double, double, double)));
        this->uas = NULL;
    }

    this->uas = dynamic_cast<SkyeMAV*>(uas);

    // connect new UAS
    if (this->uas != NULL)
    {
        connect(this, SIGNAL(valueTestControlChanged(double, double, double, double, double, double, double, double)), uas, SLOT(setTestphaseCommandsByWidget(double, double, double, double, double, double, double, double)));
    }
}

void QGCSkyeTestMotors::emitValues(double inverseFactor)
{
    double thrust[4];
    double orient[4];
    for (int i = 0; i<4; i++) {
        if (inverseFactor > 0.0) {
            thrust[i] = panelMap[i]->getThrust();
            orient[i] = panelMap[i]->getOrientation();
        } else if (inverseFactor == 0.0) {
            thrust[i] = 0.0;
            orient[i] = panelMap[i]->getOrientation();
        } else if (inverseFactor < 0.0) {
            thrust[i] = panelMap[i]->getThrust();
            orient[i] = panelMap[i]->getOrientation();
            if (orient [i] <= 0.0)
                orient[i] += 180.0;
            else
                orient[i] -= 180.0;
        }
    }

    emit valueTestControlChanged(thrust[0], thrust[1], thrust[2], thrust[3],
                                 orient[0], orient[1], orient[2], orient[3]);
}

void QGCSkyeTestMotors::setZero()
{
    for (int i = 0; i<4; i++) {
        panelMap[i]->setZero();
    }
    this->emitValues();
}

void QGCSkyeTestMotors::stopAll()
{
    for (int i = 0; i<4; i++) {
        panelMap[i]->stopAll();
    }
    this->emitValues();
}
