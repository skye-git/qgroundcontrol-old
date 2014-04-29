#ifndef QGCSKYETESTFORCEPANEL_H
#define QGCSKYETESTFORCEPANEL_H

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
    void stopAll();

private:
    Ui::QGCSkyeTestForcePanel *ui;
};

#endif // QGCSKYETESTFORCEPANEL_H
