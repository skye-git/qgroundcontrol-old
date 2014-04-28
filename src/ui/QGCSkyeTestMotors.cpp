#include "QGCSkyeTestMotors.h"
#include "ui_QGCSkyeTestMotors.h"
#include <QDebug>
#include "UASManager.h"

#define QGC_MAX_THRUST 400
#define QGC_MAX_ABS_DEGREE 180

QGCSkyeTestMotors::QGCSkyeTestMotors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestMotors),
    uas(NULL)
{
    ui->setupUi(this);

    // Insert 4 Test Widget Panels
    for (int i = 0; i<4; i++)
    {
        panelMap.insert(i, new QGCSkyeTestMotorsPanel(this, i));
        ui->groupBoxPanel->layout()->addWidget(panelMap[i]);
    }

    // Insert box for periodic timing
    timerWidget = new QGCSkyeTestTimerWidget(this);
    ui->groupBoxTimer->layout()->addWidget(timerWidget);

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
        disconnect(this, SIGNAL(valueTestControlChanged(int, int, int, int, int, int, int, int)), uas, SLOT(setTestphaseCommandsByWidget(int, int, int, int, int, int, int, int)));
        this->uas = NULL;
    }

    this->uas = dynamic_cast<SkyeMAV*>(uas);

    // connect new UAS
    if (this->uas != NULL)
    {
        connect(this, SIGNAL(valueTestControlChanged(int, int, int, int, int, int, int, int)), uas, SLOT(setTestphaseCommandsByWidget(int, int, int, int, int, int, int, int)));
    }
}

void QGCSkyeTestMotors::emitValues()
{
    int thrust[4];
    int orient[4];
    for (int i = 0; i<4; i++) {
        thrust[i] = panelMap[i]->getOrientationQC();
        orient[i] = panelMap[i]->getThrust();
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
