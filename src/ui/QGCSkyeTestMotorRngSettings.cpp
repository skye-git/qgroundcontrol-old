#include "QGCSkyeTestMotorRngSettings.h"
#include "ui_QGCSkyeTestMotorRngSettings.h"

QGCSkyeTestMotorRngSettings::QGCSkyeTestMotorRngSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestMotorRngSettings)
{
	ui->setupUi(this);
}

QGCSkyeTestMotorRngSettings::~QGCSkyeTestMotorRngSettings()
{
	delete ui;
}

double QGCSkyeTestMotorRngSettings::getFMean() const {
	return ui->doubleSpinBoxFMean->value();
}

double QGCSkyeTestMotorRngSettings::getFStd() const {
	return ui->doubleSpinBoxFStd->value();
}

double QGCSkyeTestMotorRngSettings::getAFrom() const {
	return ui->doubleSpinBoxAFrom->value();
}

double QGCSkyeTestMotorRngSettings::getATo() const {
	return ui->doubleSpinBoxATo->value();
}
