#ifndef QGCSKYETESTFORCEPANEL_H
#define QGCSKYETESTFORCEPANEL_H

#include <tr1/random>
#include <QWidget>

namespace Ui {
class QGCSkyeTestForcePanel;
}

class QGCSkyeTestForcePanel : public QWidget
{
    Q_OBJECT

public:
	explicit QGCSkyeTestForcePanel(QWidget *parent = 0, int index = 0);
    ~QGCSkyeTestForcePanel();
    double getForce();
    double getMoment();
	void randomize(double f_std_dev, double m_std_dev, std::tr1::ranlux64_base_01 &rng);
    void stopAll();

private:
    Ui::QGCSkyeTestForcePanel *ui;
};

#endif // QGCSKYETESTFORCEPANEL_H
