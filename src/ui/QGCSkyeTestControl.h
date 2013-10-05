#ifndef QGCSKYETESTCONTROL_H
#define QGCSKYETESTCONTROL_H

#define QGC_SKYE_CONFIG_TAB_MOTOR 0
#define QGC_SKYE_CONFIG_TAB_FORCE 1

#include <QWidget>
#include "SkyeMAV.h"

namespace Ui {
class QGCSkyeTestControl;
}

class QGCSkyeTestControl : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestControl(QWidget *parent = 0);
    ~QGCSkyeTestControl();

public slots:

    void setUAS(UASInterface* mav);
    void stopAll();
    void setZero();

    void changeMode(int mode);
    void setManualMode();
    void setRateMode();
    void setAttMode();

    void cycleContextButton();
    void updateState(int state);
    void updateMode(int uas,int baseMode);

    void tabChanged(int tab);

signals:
    void stopAllRequested();
    void setZeroRequested();

private:
    Ui::QGCSkyeTestControl *ui;
    SkyeMAV* uas;
    bool engineOn;
    int tab;

};

#endif // QGCSKYETESTCONTROL_H
