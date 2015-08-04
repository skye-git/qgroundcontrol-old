#include "QGCSkyeTestForceRandomSettings.h"
#include "ui_QGCSkyeTestForceRandomSettings.h"

QGCSkyeTestForceRandomSettings::QGCSkyeTestForceRandomSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestForceRandomSettings)
{
	ui->setupUi(this);
}

QGCSkyeTestForceRandomSettings::~QGCSkyeTestForceRandomSettings()
{
	delete ui;
}

double QGCSkyeTestForceRandomSettings::getMStd() const {
	return ui->doubleSpinBoxMStd->value();
}

double QGCSkyeTestForceRandomSettings::getFStd() const {
	return ui->doubleSpinBoxFStd->value();
}
