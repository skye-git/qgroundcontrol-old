#ifndef QGCSKYETESTMOTORS_H
#define QGCSKYETESTMOTORS_H

#include <QWidget>
#include <QMap>
#include "SkyeMAV.h"
#include "QGCSkyeTest.h"
#include "QGCSkyeTestMotorsPanel.h"

class QGCSkyeTestMotors : public QGCSkyeTest
{
    Q_OBJECT

public:
    explicit QGCSkyeTestMotors(QWidget *parent = 0);
    ~QGCSkyeTestMotors();

public slots:
    void setUAS(UASInterface* uas);
    void stopAll();
    void setZero();
    virtual void emitValues(double inverseFactor = 1.0);    ///< set inverse to -1 to do input into inverse direction

signals:
    void valueTestControlChanged(double Thrust1, double Thrust2, double Thrust3, double Thrust4, double Orientation1, double Orientation2, double Orientation3, double Orientation4);

private:
    QMap<int, QGCSkyeTestMotorsPanel*> panelMap;
};

#endif // QGCSKYETESTMOTORS_H
