#ifndef QGCSKYETESTMOTORS_H
#define QGCSKYETESTMOTORS_H

#include <QWidget>
#include <QMap>
#include "SkyeUAS.h"
#include "QGCSkyeTest.h"
#include "QGCSkyeTestMotorsPanel.h"
#include "QGCSkyeTestMotorRngSettings.h"

#include <tr1/random>

class QGCSkyeTestMotors : public QGCSkyeTest
{
    Q_OBJECT

public:
    explicit QGCSkyeTestMotors(bool ppm = false, QWidget *parent = 0);
    ~QGCSkyeTestMotors();

public slots:
    void setUAS(UASInterface* uas);
    void stopAll();
	void setZero();
    virtual void emitValues(double inverseFactor = 1.0);    ///< set inverse to -1 to do input into inverse direction
	virtual void randomizeInputs();

signals:
    void valueTestControlChanged(double Thrust1, double Thrust2, double Thrust3, double Thrust4, double Orientation1, double Orientation2, double Orientation3, double Orientation4, bool usePpm);

private:
	std::tr1::ranlux64_base_01 rand_generator;

	QGCSkyeTestMotorRngSettings *rng_settings_ui;

    QMap<int, QGCSkyeTestMotorsPanel*> panelMap;
    bool usePpm;
};

#endif // QGCSKYETESTMOTORS_H
