#ifndef QGCSKYETESTFORCE_H
#define QGCSKYETESTFORCE_H

#include <QWidget>
#include <QMap>
#include "SkyeMAV.h"
#include "QGCSkyeTestForcePanel.h"
#include "QGCSkyeTestTimerWidget.h"

namespace Ui {
class QGCSkyeTestForce;
}

class QGCSkyeTestForce : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestForce(QWidget *parent = 0);
    ~QGCSkyeTestForce();

public slots:
    void setUAS(UASInterface* uas);
    void emitValues();
    void stopAll();

signals:
    void valueDirectControlChanged(double forceX, double forceY, double forceZ, double momentX, double momentY, double momentZ);


private:
    Ui::QGCSkyeTestForce *ui;
    SkyeMAV* uas;
    QMap<int, QGCSkyeTestForcePanel*> panelMap;
    QGCSkyeTestTimerWidget* timerWidget;
};

#endif // QGCSKYETESTFORCE_H
