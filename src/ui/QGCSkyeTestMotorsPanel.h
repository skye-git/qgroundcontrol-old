#ifndef QGCSKYETESTMOTORSPANEL_H
#define QGCSKYETESTMOTORSPANEL_H

#include <tr1/random>
#include <QWidget>
#include <QTimer>
#include "SkyeUAS.h"

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
	void randomize(double f_mean, double f_std, double a_min, double a_max, std::tr1::ranlux64_base_01 &rng);

public slots:
    void stopAll();
    void setZero();

private slots:
    /// There is no floating point slider UI. Therefore the setThrust slot is needed to switch between integers and doubles
    void setThrust(double thrust);
    void setThrustBySlider(int thrust);

private:
    Ui::QGCSkyeTestMotorsPanel *ui;
    bool usePpm;

};

#endif // QGCSKYETESTMOTORSPANEL_H
