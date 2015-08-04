#ifndef QGCSKYETESTFORCE_H
#define QGCSKYETESTFORCE_H

#include <QWidget>
#include <QMap>
#include "SkyeUAS.h"
#include "QGCSkyeTest.h"
#include "QGCSkyeTestForcePanel.h"
#include "QGCSkyeTestForceRandomSettings.h"

#include <tr1/random>

namespace Ui {
class QGCSkyeTestForceRngSettings;
}

class QGCSkyeTestForce : public QGCSkyeTest
{
    Q_OBJECT

public:
    explicit QGCSkyeTestForce(QWidget *parent = 0);
    ~QGCSkyeTestForce();

public slots:
    void setUAS(UASInterface* uas);
	void stopAll();
    virtual void emitValues(double inverseFactor = 1.0);      ///< set inverse to -1 to do input into inverse direction
	virtual void randomizeInputs();

signals:
    void valueDirectControlChanged(double forceX, double forceY, double forceZ, double momentX, double momentY, double momentZ);

private:    
	std::tr1::ranlux64_base_01 rand_generator;

	QGCSkyeTestForceRandomSettings *rng_settings_ui;

    QMap<int, QGCSkyeTestForcePanel*> panelMap;

};

#endif // QGCSKYETESTFORCE_H
