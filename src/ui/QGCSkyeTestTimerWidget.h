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
    void activeTabChanged(bool active);

private slots:
    void toggledCheckBoxUseTimer(bool checked);
    void clickedPushButtonStart();
    void stopTimer(bool stop = true);
	void startTimer(bool start = true, int msecInterval = QGC_SKYE_TEST_TIMER_MSEC_INTERVAL);
    void timerTimeout();
    void updateLabel();

signals:
	void emitValues(double inverseFactor);      ///< Set inverseFactor to -1 to send input into inverse (negative) direction. Set to some small negative value to prime the inverse direction.
	void randomizeInputs();						///< Randomize with std_dev.

private:
	enum State {
		StateContinous,
		StateStopped,
		StateForwardStart,
		StateForward,
		StatePause,
		StateReverse
	};

	void startPhase(QGCSkyeTestTimerWidget::State phase, int msecPeriod);

    Ui::QGCSkyeTestTimerWidget *ui;
    QTimer *timer;
	QGCSkyeTestTimerWidget::State currentState;
	int shotsRemaining;             ///< Counter for periodic inputs (negativ for endless)

    int msecInterval;               ///< Interval of timer (for emits)
    int msecPeriod;                 ///< Duration of movement into one direction in millisecond
	int msecPause;                  ///< Pause of movement when switching direction in millisecond
};

#endif // QGCSKYETESTTIMERWIDGET_H
