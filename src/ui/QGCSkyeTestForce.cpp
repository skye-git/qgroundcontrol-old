#include "QGCSkyeTestForce.h"
#include "ui_QGCSkyeTest.h"
#include <QDebug>
#include "UASManager.h"
#include "SkyeMAV.h"

QGCSkyeTestForce::QGCSkyeTestForce(QWidget *parent) :
    QGCSkyeTest(parent)
{
    // Insert 3 Force Widget Panels
    for (int i = 0; i<3; i++)
    {
        panelMap.insert(i, new QGCSkyeTestForcePanel(this, i));
        ui->groupBoxPanel->layout()->addWidget(panelMap[i]);
    }

}

QGCSkyeTestForce::~QGCSkyeTestForce()
{
    //timer->stop();
    delete ui;
}

void QGCSkyeTestForce::emitValues(double inverseFactor)
{
    double force[3];
    double moment[3];
    for (int i = 0; i<3; i++) {
        force[i]  = inverseFactor * panelMap[i]->getForce();
        moment[i] = inverseFactor * panelMap[i]->getMoment();
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
