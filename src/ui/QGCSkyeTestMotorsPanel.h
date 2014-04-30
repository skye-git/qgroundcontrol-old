#ifndef QGCSKYETESTMOTORSPANEL_H
#define QGCSKYETESTMOTORSPANEL_H

#include <QWidget>
#include <QTimer>
#include "SkyeMAV.h"

namespace Ui {
class QGCSkyeTestMotorsPanel;
}

class QGCSkyeTestMotorsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestMotorsPanel(int index = 0, bool ppm = false, QWidget *parent = 0);
    ~QGCSkyeTestMotorsPanel();
    double getOrientation();
    double getThrust();

public slots:
    void stopAll();
    void setZero();

private:
    Ui::QGCSkyeTestMotorsPanel *ui;

};

#endif // QGCSKYETESTMOTORSPANEL_H
