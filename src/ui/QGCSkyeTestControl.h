#ifndef QGCSKYETESTCONTROL_H
#define QGCSKYETESTCONTROL_H

#define QGC_SKYE_CONFIG_TAB_MOTOR     0
#define QGC_SKYE_CONFIG_TAB_MOTOR_PPM 1
#define QGC_SKYE_CONFIG_TAB_FORCE     2

#include <QWidget>
#include "SkyeUAS.h"

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
    SkyeUAS* uas;
    bool engineOn;
    int tab;

    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

};

#endif // QGCSKYETESTCONTROL_H
