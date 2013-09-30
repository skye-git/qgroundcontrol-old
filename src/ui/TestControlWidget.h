/**
 * @file
 *   @brief Definition of TestControl widget
 *   @author Anton Ledergerber <antonl@student.ethz.ch>
 *
 */
 
// 2013/09/30 renamed widget from TestphaseWidget to TestControlWidget
 
#ifndef TESTCONTROLWIDGET_H
#define TESTCONTROLWIDGET_H

#include <QtGui/QDialog>
#include <QTimer>
#include "SkyeMAV.h"
#include <QCloseEvent>

namespace Ui
{
class TestControlWidget;
}

class TestControlWidget : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(TestControlWidget)
public:
    explicit TestControlWidget(QWidget *parent = 0);
    virtual ~TestControlWidget();

public slots:

    void setUAS(UASInterface* mav);
    void stopall();
    void setzero();
    void emitValues();
    void modeChanged(int mode_in);
    void TestControlclose();
    void cycleContextButton();
    void updateState(int state);

signals:
    void valueTestControlChanged(int Thrust1, int Thrust2, int Thrust3, int Thrust4, int Orientation1, int Orientation2, int Orientation3, int Orientation4);
    void initiatehoming();

protected:
    void closeEvent(QCloseEvent *event);


private:
    SkyeMAV* uas;
    bool engineOn;
    QTimer *timer;
    Ui::TestControlWidget *m_ui;

};


#endif // TESTCONTROLWIDGET_H
