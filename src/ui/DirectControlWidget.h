/**
 * @file
 *   @brief Definition of testphase widget
 *   @author Anton Ledergerber <antonl@student.ethz.ch>
 *
 */
#ifndef DIRECTCONTROLWIDGET_H
#define DIRECTCONTROLWIDGET_H

#include <QtGui/QDialog>
#include <QTimer>
#include "SkyeMAV.h"
#include <QCloseEvent>

namespace Ui
{
class DirectControlWidget;
}

class DirectControlWidget : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(DirectControlWidget)
public:
    explicit DirectControlWidget(QWidget *parent = 0);
    virtual ~DirectControlWidget();

public slots:

    void setUAS(UASInterface* mav);
    void stopAll();
    void emitValues();
    void changeMode(int mode);
    void changeAssistedMode(bool isAssisted);
    void directControlShow();
    void directControlClose();
    void cycleContextButton();
    void updateState(int state);

signals:
    void valueDirectControlChanged(double forceX, double forceY, double forceZ, double momentX, double momentY, double momentZ);

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *event);

private:
    int maxThrust;
    int maxMoment;
    SkyeMAV* uas;
    bool engineOn;
    QTimer *timer;
    Ui::DirectControlWidget *ui;

};


#endif // DIRECTCONTROLWIDGET_H
