/**
 * @file
 *   @brief Definition of testphase widget
 *   @author Anton Ledergerber <antonl@student.ethz.ch>
 *
 */
#ifndef TESTPHASEWIDGET_H
#define TESTPHASEWIDGET_H

#include <QtGui/QDialog>
#include "UASInterface.h"
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

protected:
    UASInterface* uas;
    //QList<int> uasButtonList;

public slots:

//    void setThrust1(int thrust1);
//    void setThrust2(int thrust2);
//    void setThrust3(int thrust3);
//    void setThrust4(int thrust4);

//    void setOrientation1(int orientation1);
//    void setOrientation2(int orientation2);
//    void setOrientation3(int orientation3);
//    void setOrientation4(int orientation4);

    void stopall();
    void homing();
    void setActiveUAS(UASInterface* uas);
    void somevalueChanged();

signals:
    void valueTestphaseChanged(int Thrust1, int Thrust2, int Thrust3, int Thrust4, int Orientation1, int Orientation2, int Orientation3, int Orientation4);


private:
    Ui::TestphaseWidget *m_ui;
};


#endif // TESTPHASEWIDGET_H
