#ifndef QGCSKYETEST_H
#define QGCSKYETEST_H

#include <QWidget>
#include "SkyeMAV.h"
#include "ui_QGCSkyeTest.h"
#include "QGCSkyeTestTimerWidget.h"

namespace Ui {
class QGCSkyeTest;
}

class QGCSkyeTest : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTest(QWidget *parent = 0);
    ~QGCSkyeTest();

public slots:
    virtual void emitValues(double inverseFactor = 1.0) = 0;
    void activeTabChanged(bool active);

protected:
    Ui::QGCSkyeTest *ui;
    SkyeMAV* uas;
    QGCSkyeTestTimerWidget *timerWidget;
    bool isActiveTab;
};

#endif // QGCSKYETEST_H
