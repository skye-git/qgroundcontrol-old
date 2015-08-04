#include "QGCSkyeTestForcePanel.h"
#include "ui_QGCSkyeTestForcePanel.h"
#include <QDebug>

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

void QGCSkyeTestForcePanel::randomize(double f_std_dev, double m_std_dev, std::tr1::ranlux64_base_01 &rng) {
	std::tr1::normal_distribution<double> f_normal(0.0, f_std_dev);
	std::tr1::normal_distribution<double> m_normal(0.0, m_std_dev);
	//qDebug() << "Random value" << normal(rand_generator);
	if (ui->checkBoxRngForce->isChecked()) {
		ui->sliderForce->setValue(f_normal(rng));
	}
	if (ui->checkBoxRngMoment->isChecked()) {
		ui->sliderMoment->setValue(m_normal(rng));
	}
}

void QGCSkyeTestForcePanel::stopAll()
{
    ui->sliderForce->setValue(0);
    ui->sliderMoment->setValue(0);
}
