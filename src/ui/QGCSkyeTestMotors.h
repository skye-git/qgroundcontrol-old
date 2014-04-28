#ifndef QGCSKYETESTMOTORS_H
#define QGCSKYETESTMOTORS_H

#include <QWidget>
#include <QTimer>
#include <QMap>
#include "SkyeMAV.h"
#include "QGCSkyeTestMotorsPanel.h"
#include "QGCSkyeTestTimerWidget.h"

namespace Ui {
class QGCSkyeTestMotors;
}

class QGCSkyeTestMotors : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestMotors(QWidget *parent = 0);
    ~QGCSkyeTestMotors();

public slots:
    void setUAS(UASInterface* uas);
    void stopAll();
    void setZero();
    void emitValues();

signals:
    void valueTestControlChanged(int Thrust1, int Thrust2, int Thrust3, int Thrust4, int Orientation1, int Orientation2, int Orientation3, int Orientation4);

private:
    Ui::QGCSkyeTestMotors *ui;
    SkyeMAV* uas;
    QMap<int, QGCSkyeTestMotorsPanel*> panelMap;
    QGCSkyeTestTimerWidget* timerWidget;
};

#endif // QGCSKYETESTMOTORS_H
