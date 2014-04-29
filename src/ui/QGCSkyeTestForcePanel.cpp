#include "QGCSkyeTestForcePanel.h"
#include "ui_QGCSkyeTestForcePanel.h"

#define QGC_MAX_FORCE 100.0
#define QGC_MAX_MOMENT 100.0

QGCSkyeTestForcePanel::QGCSkyeTestForcePanel(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestForcePanel)
{
    ui->setupUi(this);

    // label
    ui->labelForce->setText(QString("Force %1 [%]").arg(index+1));
    ui->labelMoment->setText(QString("Moment %1 [%]").arg(index+1));

    // range
    ui->sliderForce->setRange(-QGC_MAX_FORCE, QGC_MAX_FORCE);
    ui->sliderMoment->setRange(-QGC_MAX_MOMENT, QGC_MAX_MOMENT);
    ui->spinBoxForce->setRange(-QGC_MAX_FORCE, QGC_MAX_FORCE);
    ui->spinBoxMoment->setRange(-QGC_MAX_MOMENT, QGC_MAX_MOMENT);

    //connect Sliders and spinBoxes
    connect(ui->sliderForce, SIGNAL(valueChanged(int)), ui->spinBoxForce, SLOT(setValue(int)));
    connect(ui->spinBoxForce, SIGNAL(valueChanged(int)), ui->sliderForce, SLOT(setValue(int)));

    connect(ui->sliderMoment, SIGNAL(valueChanged(int)), ui->spinBoxMoment, SLOT(setValue(int)));
    connect(ui->spinBoxMoment, SIGNAL(valueChanged(int)), ui->sliderMoment, SLOT(setValue(int)));

}

QGCSkyeTestForcePanel::~QGCSkyeTestForcePanel()
{
    delete ui;
}

double QGCSkyeTestForcePanel::getForce()
{
    return (double)ui->sliderForce->value() / QGC_MAX_FORCE;
}

double QGCSkyeTestForcePanel::getMoment()
{
    return (double)ui->sliderMoment->value() / QGC_MAX_MOMENT;
}

void QGCSkyeTestForcePanel::stopAll()
{
    ui->sliderForce->setValue(0);
    ui->sliderMoment->setValue(0);
}
