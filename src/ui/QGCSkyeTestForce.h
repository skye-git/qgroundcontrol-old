#ifndef QGCSKYETESTFORCE_H
#define QGCSKYETESTFORCE_H

#include <QWidget>
#include <QMap>
#include "SkyeMAV.h"
#include "QGCSkyeTest.h"
#include "QGCSkyeTestForcePanel.h"

class QGCSkyeTestForce : public QGCSkyeTest
{
    Q_OBJECT

public:
    explicit QGCSkyeTestForce(QWidget *parent = 0);
    ~QGCSkyeTestForce();

public slots:
    void emitValues(double inverseFactor = 1.0);      ///< set inverse to -1 to do input into inverse direction
    void stopAll();

signals:
    void valueDirectControlChanged(double forceX, double forceY, double forceZ, double momentX, double momentY, double momentZ);

private:    
    QMap<int, QGCSkyeTestForcePanel*> panelMap;

};

#endif // QGCSKYETESTFORCE_H
