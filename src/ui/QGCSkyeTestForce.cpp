#include "QGCSkyeTestForce.h"
#include <QDebug>
#include "UASManager.h"

QGCSkyeTestForce::QGCSkyeTestForce(QWidget *parent) :
	QGCSkyeTest(parent),
	rng_settings_ui(NULL)
{
	{
		QTime time = QTime::currentTime();
		rand_generator.seed((uint)time.msec());
	}

	rng_settings_ui = new QGCSkyeTestForceRandomSettings();
	ui->groupBoxPanel->layout()->addWidget(rng_settings_ui);
    // Insert 3 Force Widget Panels
    for (int i = 0; i<3; i++)
    {
		panelMap.insert(i, new QGCSkyeTestForcePanel(this, i));
        ui->groupBoxPanel->layout()->addWidget(panelMap[i]);
    }

    // connect UAV
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

}

QGCSkyeTestForce::~QGCSkyeTestForce()
{
    //timer->stop();
	delete rng_settings_ui;
}

void QGCSkyeTestForce::setUAS(UASInterface* uas)
{
    if (this->uas != 0)
    {
        disconnect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), this->uas, SLOT(set6DOFCommandsByWidget(double,double,double,double,double,double)));
    }

    this->uas = dynamic_cast<SkyeUAS*>(uas);
    if (this->uas)
    {
        connect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), this->uas, SLOT(set6DOFCommandsByWidget(double,double,double,double,double,double)));
    }
}

void QGCSkyeTestForce::randomizeInputs() {
	for (int i = 0; i<panelMap.size(); i++) {
		panelMap[i]->randomize(rng_settings_ui->getFStd(), rng_settings_ui->getMStd(), rand_generator);
	}
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
