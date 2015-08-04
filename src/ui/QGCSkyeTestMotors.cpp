#include "QGCSkyeTestMotors.h"
#include <QDebug>
#include "UASManager.h"

#define QGC_MAX_THRUST 400
#define QGC_MAX_ABS_DEGREE 180

QGCSkyeTestMotors::QGCSkyeTestMotors(bool ppm, QWidget *parent) :
    QGCSkyeTest(parent),
    usePpm(ppm)
{
	{
		QTime time = QTime::currentTime();
		rand_generator.seed((uint)time.msec());
	}

	if (!usePpm) {
		rng_settings_ui = new QGCSkyeTestMotorRngSettings();
		ui->groupBoxPanel->layout()->addWidget(rng_settings_ui);
	}
    // Insert 4 Test Widget Panels
    for (int i = 0; i<4; i++)
    {
        panelMap.insert(i, new QGCSkyeTestMotorsPanel(i, usePpm, this));
        ui->groupBoxPanel->layout()->addWidget(panelMap[i]);
    }

    // Connect UAS
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());
}

QGCSkyeTestMotors::~QGCSkyeTestMotors()
{
    //timer->stop();
	delete rng_settings_ui;
}

void QGCSkyeTestMotors::setUAS(UASInterface* uas)
{
    // disconnect old UAS
    if (this->uas)
    {
        disconnect(this, SIGNAL(valueTestControlChanged(double, double, double, double, double, double, double, double, bool)), this->uas, SLOT(setTestphaseCommandsByWidget(double, double, double, double, double, double, double, double, bool)));
        this->uas = NULL;
    }

    this->uas = dynamic_cast<SkyeUAS*>(uas);

    // connect new UAS
    if (this->uas != NULL)
    {
        connect(this, SIGNAL(valueTestControlChanged(double, double, double, double, double, double, double, double, bool)), this->uas, SLOT(setTestphaseCommandsByWidget(double, double, double, double, double, double, double, double, bool)));
    }
}
 void QGCSkyeTestMotors::randomizeInputs() {
	for (int i = 0; i<panelMap.size(); i++) {
		panelMap[i]->randomize(rng_settings_ui->getFMean(), rng_settings_ui->getFStd(),
							   rng_settings_ui->getAFrom(), rng_settings_ui->getATo(), rand_generator);
	}
}

void QGCSkyeTestMotors::emitValues(double inverseFactor)
{
    double thrust[4];
    double orient[4];
    for (int i = 0; i<4; i++) {
        if (inverseFactor > 0.0) {
			thrust[i] = panelMap[i]->getThrust() * fabs(inverseFactor);
			orient[i] = panelMap[i]->getOrientation();
        } else if (inverseFactor < 0.0) {
			thrust[i] = panelMap[i]->getThrust() * fabs(inverseFactor);
            orient[i] = panelMap[i]->getOrientation();
			if (orient[i] < 0.0) {
                orient[i] += 180.0;
			} else {
                orient[i] -= 180.0;
			}
		} else {
			thrust[i] = 0.0;
			orient[i] = panelMap[i]->getOrientation();
		}
    }

    emit valueTestControlChanged(thrust[0], thrust[1], thrust[2], thrust[3],
                                 orient[0], orient[1], orient[2], orient[3],
                                 usePpm);
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
