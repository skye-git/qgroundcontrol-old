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
    QGCSkyeTestMotors* testMotorPpm;
    QGCSkyeTestForce* testForce;
    QGCSkyeTestControl* testControl;

private slots:
    void tabChanged(int tab);

};

#endif // QGCSKYECONFIG_H
