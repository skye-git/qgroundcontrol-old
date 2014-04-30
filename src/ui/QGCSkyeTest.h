#ifndef QGCSKYETEST_H
#define QGCSKYETEST_H

#include <QWidget>
#include "SkyeMAV.h"
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
    virtual void emitValues(double inverseFactor = 1.0);      ///< set inverse to -1 to do input into inverse direction
    virtual void stopAll();
    void setUAS(UASInterface* uas);

protected:
    Ui::QGCSkyeTest *ui;

private:
    SkyeMAV* uas;
    QGCSkyeTestTimerWidget* timerWidget;
};

#endif // QGCSKYETEST_H
