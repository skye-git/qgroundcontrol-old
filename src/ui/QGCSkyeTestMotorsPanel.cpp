#include "QGCSkyeTestMotorsPanel.h"
#include "ui_QGCSkyeTestMotorsPanel.h"
#include <QDebug>
#include "UASManager.h"

#define QGC_MAX_NEWTON 15
#define QGC_MAX_PPM 400
#define QGC_MAX_ABS_DEGREE 180

QGCSkyeTestMotorsPanel::QGCSkyeTestMotorsPanel(int index, bool ppm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestMotorsPanel)
{
    ui->setupUi(this);

    // label
    if (ppm) {
        ui->labelThrust->setText(QString("Thrust %1 [PPM]").arg(index+1));
    } else {
        ui->labelThrust->setText(QString("Thrust %1 [N]").arg(index+1));
    }
    ui->labelOrientation->setText(QString("Orientation %1 [deg]").arg(index+1));

    // set limits
    if (ppm) {
        ui->SliderThrust-> setMaximum(QGC_MAX_PPM);
        ui->spinBoxThrust->setMaximum(QGC_MAX_PPM);
    } else {
        ui->SliderThrust-> setMaximum(QGC_MAX_NEWTON);
        ui->spinBoxThrust->setMaximum(QGC_MAX_NEWTON);
    }
    ui->   dialOrientation->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);

    // connect Sliders, spinBoxes and dials
    connect(ui->SliderThrust, SIGNAL(valueChanged(int)), ui->spinBoxThrust, SLOT(setValue(int)));
    connect(ui->spinBoxThrust, SIGNAL(valueChanged(int)), ui->SliderThrust, SLOT(setValue(int)));

    connect(ui->dialOrientation, SIGNAL(valueChanged(int)), ui->spinBoxOrientation, SLOT(setValue(int)));
    connect(ui->spinBoxOrientation, SIGNAL(valueChanged(int)), ui->dialOrientation, SLOT(setValue(int)));

}

QGCSkyeTestMotorsPanel::~QGCSkyeTestMotorsPanel()
{
    delete ui;
}

double QGCSkyeTestMotorsPanel::getOrientation()
{
    // no scaling. degree
    return (double)ui->dialOrientation->value();
}

double QGCSkyeTestMotorsPanel::getThrust()
{
    // no scaling. maximum by QGC_MAX_THRUST
    return (double)ui->SliderThrust->value();
}

void QGCSkyeTestMotorsPanel::setZero()
{
    ui->dialOrientation->setValue(0);
}

void QGCSkyeTestMotorsPanel::stopAll()
{
    ui->SliderThrust->setValue(0);
}
