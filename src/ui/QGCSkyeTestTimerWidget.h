#ifndef QGCSKYETESTTIMERWIDGET_H
#define QGCSKYETESTTIMERWIDGET_H

#include <QWidget>
#include <QTimer>

#define QGC_SKYE_TEST_TIMER_MSEC_INTERVAL  200
#define QGC_SKYE_TEST_TIMER_MSEC_PERIOD   1000

namespace Ui {
class QGCSkyeTestTimerWidget;
}

class QGCSkyeTestTimerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestTimerWidget(QWidget *parent = 0);
    ~QGCSkyeTestTimerWidget();

private slots:
    void toggledCheckBoxUseTimer(bool checked);
    void clickedPushButtonStart();
    void stopTimer(bool stop = true);
    void startTimerCont(bool start = true, int msecInterval = QGC_SKYE_TEST_TIMER_MSEC_INTERVAL);
    void startTimerPeriod(bool start = true,
                          int msecInterval = QGC_SKYE_TEST_TIMER_MSEC_INTERVAL,
                          int msecPeriod =   QGC_SKYE_TEST_TIMER_MSEC_PERIOD);
    void timerTimeout();
    void updateLabel();

signals:
    void emitValues(double inverseFactor);      ///< Set inverseFactor to -1 to send input into inverse (negative) direction

private:
    Ui::QGCSkyeTestTimerWidget *ui;
    QTimer *timer;
    int shotsRemaining;             ///< Counter for periodic inputs (negativ for endless)
    bool isInvertedMovement;        ///< When true, input must be in inverse direction

    int msecInterval;               ///< Interval of timer (for emits)
    int msecPeriod;                 ///< Duration of movement into one direction in millisecond
};

#endif // QGCSKYETESTTIMERWIDGET_H
