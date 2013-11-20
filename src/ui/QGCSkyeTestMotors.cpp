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

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

    // connect Sliders, spinBoxes and dials
    connect(ui->SliderThrust1, SIGNAL(valueChanged(int)), ui->spinBoxThrust1, SLOT(setValue(int)));
    connect(ui->spinBoxThrust1, SIGNAL(valueChanged(int)), ui->SliderThrust1, SLOT(setValue(int)));

    connect(ui->dialOrientation1, SIGNAL(valueChanged(int)), ui->spinBoxOrientation1, SLOT(setValue(int)));
    connect(ui->spinBoxOrientation1, SIGNAL(valueChanged(int)), ui->dialOrientation1, SLOT(setValue(int)));

    connect(ui->SliderThrust2, SIGNAL(valueChanged(int)), ui->spinBoxThrust2, SLOT(setValue(int)));
    connect(ui->spinBoxThrust2, SIGNAL(valueChanged(int)), ui->SliderThrust2, SLOT(setValue(int)));

    connect(ui->dialOrientation2, SIGNAL(valueChanged(int)), ui->spinBoxOrientation2, SLOT(setValue(int)));
    connect(ui->spinBoxOrientation2, SIGNAL(valueChanged(int)), ui->dialOrientation2, SLOT(setValue(int)));

    connect(ui->SliderThrust3, SIGNAL(valueChanged(int)), ui->spinBoxThrust3, SLOT(setValue(int)));
    connect(ui->spinBoxThrust3, SIGNAL(valueChanged(int)), ui->SliderThrust3, SLOT(setValue(int)));

    connect(ui->dialOrientation3, SIGNAL(valueChanged(int)), ui->spinBoxOrientation3, SLOT(setValue(int)));
    connect(ui->spinBoxOrientation3, SIGNAL(valueChanged(int)), ui->dialOrientation3, SLOT(setValue(int)));

    connect(ui->SliderThrust4, SIGNAL(valueChanged(int)), ui->spinBoxThrust4, SLOT(setValue(int)));
    connect(ui->spinBoxThrust4, SIGNAL(valueChanged(int)), ui->SliderThrust4, SLOT(setValue(int)));

    connect(ui->dialOrientation4, SIGNAL(valueChanged(int)), ui->spinBoxOrientation4, SLOT(setValue(int)));
    connect(ui->spinBoxOrientation4, SIGNAL(valueChanged(int)), ui->dialOrientation4, SLOT(setValue(int)));

    // set limits
    ui->SliderThrust1->setMaximum(QGC_MAX_THRUST);
    ui->SliderThrust2->setMaximum(QGC_MAX_THRUST);
    ui->SliderThrust3->setMaximum(QGC_MAX_THRUST);
    ui->SliderThrust4->setMaximum(QGC_MAX_THRUST);
    ui->spinBoxThrust1->setMaximum(QGC_MAX_THRUST);
    ui->spinBoxThrust2->setMaximum(QGC_MAX_THRUST);
    ui->spinBoxThrust3->setMaximum(QGC_MAX_THRUST);
    ui->spinBoxThrust4->setMaximum(QGC_MAX_THRUST);

    ui->dialOrientation1->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->dialOrientation2->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->dialOrientation3->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->dialOrientation4->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation1->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation2->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation3->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation4->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);

    // Start Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(emitValues()));
    timer->start(200); //5Hz emitValues is called


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
    // scale orientation from degree to QC
    int orient1 = (int)( ((double)ui->dialOrientation1->value()) / 180.0 * 86016.0 );
    int orient2 = (int)( ((double)ui->dialOrientation2->value()) / 180.0 * 86016.0 );
    int orient3 = (int)( ((double)ui->dialOrientation3->value()) / 180.0 * 86016.0 );
    int orient4 = (int)( ((double)ui->dialOrientation4->value()) / 180.0 * 86016.0 );

    emit valueTestControlChanged(ui->SliderThrust1->value(), ui->SliderThrust2->value(), ui->SliderThrust3->value(), ui->SliderThrust4->value(), orient1, orient2, orient3, orient4);
}

void QGCSkyeTestMotors::setZero()
{
    ui->dialOrientation1->setValue(0);
    ui->dialOrientation2->setValue(0);
    ui->dialOrientation3->setValue(0);
    ui->dialOrientation4->setValue(0);
}

void QGCSkyeTestMotors::stopAll()
{
    ui->SliderThrust1->setValue(0);
    ui->SliderThrust2->setValue(0);
    ui->SliderThrust3->setValue(0);
    ui->SliderThrust4->setValue(0);
}
