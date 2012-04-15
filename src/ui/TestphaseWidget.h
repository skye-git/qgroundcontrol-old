/**
 * @file
 *   @brief Definition of testphase widget
 *   @author Anton Ledergerber <antonl@student.ethz.ch>
 *
 */
#ifndef TESTPHASEWIDGET_H
#define TESTPHASEWIDGET_H

#include <QtGui/QDialog>
#include <QTimer>
#include "SkyeMAV.h"

//#include "TestphaseInput.h"//not yet implemented

namespace Ui
{
class TestphaseWidget;
}

class TestphaseWidget : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(TestphaseWidget)
public:
    explicit TestphaseWidget(QWidget *parent = 0);
    virtual ~TestphaseWidget();

public slots:

    void setUAS(UASInterface* mav);
    void stopall();
    void setzero();
    void emitValues();
    void modeChanged(int mode_in);
    void Testphaseclose();
    void cycleContextButton();
    void updateState(int state);

signals:
    void valueTestphaseChanged(int Thrust1, int Thrust2, int Thrust3, int Thrust4, int Orientation1, int Orientation2, int Orientation3, int Orientation4);
    void initiatehoming();

protected:


private:
    SkyeMAV* uas;
    bool engineOn;
    QTimer *timer;
    Ui::TestphaseWidget *m_ui;

};


#endif // TESTPHASEWIDGET_H
