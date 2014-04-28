#ifndef QGCSKYETESTTIMERWIDGET_H
#define QGCSKYETESTTIMERWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class QGCSkyeTestTimerWidget;
}

class QGCSkyeTestTimerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestTimerWidget(QWidget *parent = 0);
    ~QGCSkyeTestTimerWidget();

private:
    Ui::QGCSkyeTestTimerWidget *ui;
    QTimer *timer;
};

#endif // QGCSKYETESTTIMERWIDGET_H
