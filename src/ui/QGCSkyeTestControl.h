#ifndef QGCSKYETESTCONTROL_H
#define QGCSKYETESTCONTROL_H

#define QGC_SKYE_CONFIG_TAB_MOTOR     0
#define QGC_SKYE_CONFIG_TAB_MOTOR_PPM 1
#define QGC_SKYE_CONFIG_TAB_FORCE     2

#include <QWidget>
#include "SkyeUAS.h"
#include "ui_QGCSkyeTestControl.h"

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

    void changeMode(SKYE_CONTROL_MODE mode);
    void setManualMode();
    void set5dofMode();
    void set6dofMode();

    void setArmDisarmState();
    void updateState(int state);
    void updateMode(SKYE_CONTROL_MODE mode);
    void updateModeStyleSheet();

    void tabChanged(int tab);

signals:
    void stopAllRequested();
    void setZeroRequested();

private:
    Ui::QGCSkyeTestControl ui;
    SkyeUAS* uas;
    bool engineOn;
    int tab;
    SKYE_CONTROL_MODE controlMode;

    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

};

#endif // QGCSKYETESTCONTROL_H
