#include "QGCSkyeTestMotorsPanel.h"
#include "ui_QGCSkyeTestMotorsPanel.h"
#include <QDebug>
#include "UASManager.h"

#define QGC_MAX_NEWTON      15.0
#define QGC_MAX_PPM        400.0
#define QGC_MAX_ABS_DEGREE 180

#define QGC_SLIDER_STEPS 1000

QGCSkyeTestMotorsPanel::QGCSkyeTestMotorsPanel(int index, bool ppm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestMotorsPanel),
    usePpm(ppm)
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
    ui->SliderThrust-> setMaximum(QGC_SLIDER_STEPS);    // there is no floating point slider
    if (ppm) {
        ui->doubleSpinBoxThrust->setMaximum(QGC_MAX_PPM);
    } else {
        ui->doubleSpinBoxThrust->setMaximum(QGC_MAX_NEWTON);
    }
    ui->   dialOrientation->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);
    ui->spinBoxOrientation->setRange(-QGC_MAX_ABS_DEGREE, QGC_MAX_ABS_DEGREE);

    // connect Sliders, spinBoxes and dials
    connect(ui->SliderThrust, SIGNAL(valueChanged(int)), this, SLOT(setThrustBySlider(int)));
    connect(ui->doubleSpinBoxThrust, SIGNAL(valueChanged(double)), this, SLOT(setThrust(double)));
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
    // no scaling. doubleSpinBox holds true value
    return ui->doubleSpinBoxThrust->value();
}

void QGCSkyeTestMotorsPanel::setZero()
{
    ui->dialOrientation->setValue(0);
}

void QGCSkyeTestMotorsPanel::stopAll()
{
    ui->SliderThrust->setValue(0);
}

void QGCSkyeTestMotorsPanel::setThrust(double thrust)
{
    // calculate slider position
    int sliderThrust;
    if (usePpm) {
        sliderThrust = (int)(thrust / QGC_MAX_PPM    * (double)QGC_SLIDER_STEPS);
    } else {
        sliderThrust = (int)(thrust / QGC_MAX_NEWTON * (double)QGC_SLIDER_STEPS);
    }
    if (sliderThrust != ui->SliderThrust->value()) {
        ui->SliderThrust->setValue(sliderThrust);
    }
}

void QGCSkyeTestMotorsPanel::setThrustBySlider(int intThrust)
{
    // calculate thrust from slider position
    double thrust;
    if (usePpm) {
        thrust = (double)intThrust / (double)QGC_SLIDER_STEPS * QGC_MAX_PPM;
    } else {
        thrust = (double)intThrust / (double)QGC_SLIDER_STEPS * QGC_MAX_NEWTON;
    }
    ui->doubleSpinBoxThrust->setValue(thrust);
}
