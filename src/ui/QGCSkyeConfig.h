#ifndef QGCSKYECONFIG_H
#define QGCSKYECONFIG_H

#include <QWidget>
#include <QTabWidget>

#include "QGCSkyeTestMotors.h"
#include "QGCSkyeTestForce.h"
#include "QGCSkyeTestControl.h"

namespace Ui {
class QGCSkyeConfig;
}

class QGCSkyeConfig : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeConfig(QWidget *parent = 0);
    ~QGCSkyeConfig();

private:
    Ui::QGCSkyeConfig *ui;

    QTabWidget* tabWidget;
    QGCSkyeTestMotors* testMotor;
    QGCSkyeTestForce* testForce;
    QGCSkyeTestControl* testControl;

    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

};

#endif // QGCSKYECONFIG_H
