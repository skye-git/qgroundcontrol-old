#include "QGCSkyeTestMotorsPanel.h"
#include "ui_QGCSkyeTestMotorsPanel.h"
#include <QDebug>
#include "UASManager.h"

#define QGC_MAX_THRUST 400
#define QGC_MAX_ABS_DEGREE 180

QGCSkyeTestMotorsPanel::QGCSkyeTestMotorsPanel(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestMotorsPanel)
{
    ui->setupUi(this);

    // label
    ui->labelThrust->setText(QString("Thrust %1").arg(index+1));
    ui->labelOrientation->setText(QString("Orientation %1 in QC").arg(index+1));

    // connect Sliders, spinBoxes and dials
    connect(ui->SliderThrust, SIGNAL(valueChanged(int)), ui->spinBoxThrust, SLOT(setValue(int)));
    connect(ui->spinBoxThrust, SIGNAL(valueChanged(int)), ui->SliderThrust, SLOT(setValue(int)));

    connect(ui->dialOrientation, SIGNAL(valueChanged(int)), ui->spinBoxOrientation, SLOT(setValue(int)));
    connect(ui->spinBoxOrientation, SIGNAL(valueChanged(int)), ui->dialOrientation, SLOT(setValue(int)));

    // set limits
    ui->SliderThrust->setMaximum(QGC_MAX_THRUST);
    ui->spinBoxThrust->setMaximum(QGC_MAX_THRUST);

    ui->dialOrientation->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);

}

QGCSkyeTestMotorsPanel::~QGCSkyeTestMotorsPanel()
{
    delete ui;
}

int QGCSkyeTestMotorsPanel::getOrientationQC()
{
    // scale orientation from degree to QC
    return (int)( ((double)ui->dialOrientation->value()) / 180.0 * 86016.0 );
}

int QGCSkyeTestMotorsPanel::getThrust()
{
    // no scaling. maximum by QGC_MAX_THRUST
    return ui->SliderThrust->value();
}

void QGCSkyeTestMotorsPanel::setZero()
{
    ui->dialOrientation->setValue(0);
}

void QGCSkyeTestMotorsPanel::stopAll()
{
    ui->SliderThrust->setValue(0);
}
