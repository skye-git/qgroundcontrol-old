#include "QGCSkyeTestTimerWidget.h"
#include "ui_QGCSkyeTestTimerWidget.h"
#include <QDebug>

QGCSkyeTestTimerWidget::QGCSkyeTestTimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestTimerWidget),
	currentState(QGCSkyeTestTimerWidget::StateContinous)
{
    ui->setupUi(this);

    /* Create timer. Iteratively tell parent to emit signals */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

    /* Connect Widgets */
    connect(ui->checkBoxUseTimer, SIGNAL(toggled(bool)), this, SLOT(toggledCheckBoxUseTimer(bool)));
    connect(ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(clickedPushButtonStart()));
}

QGCSkyeTestTimerWidget::~QGCSkyeTestTimerWidget()
{
    delete ui;
}

void QGCSkyeTestTimerWidget::activeTabChanged(bool active)
{
    /* start timer if this gets active tab
     * or stop timer if tab gets hidden
     */
    if (active) {
        this->startTimer();
    } else {
        this->stopTimer();
    }

	//qDebug() << "This TimerWidget isActiveTab is" << active;
}

void QGCSkyeTestTimerWidget::toggledCheckBoxUseTimer(bool checked)
{
	// reset switch. This makes that we will always start with forward movement
	if (checked) {
		currentState = StateStopped;
	} else {
		currentState = StateContinous;
	}
}

void QGCSkyeTestTimerWidget::clickedPushButtonStart()
{
    /* Activate checkbox if it has not been set yet */
    if (ui->checkBoxUseTimer->isChecked() == false) {
        ui->checkBoxUseTimer->toggle();
    }

    /* Update period time. This will also be needed for inverse direction (if inverse direction is activated) */
    msecPeriod = 1000 * ui->doubleSpinBoxPeriod->value();
	msecPause  = 1000 * ui->doubleSpinBoxPause->value();

	/* Start forward phase: */
	startPhase(StateForwardStart, 0);
}

void QGCSkyeTestTimerWidget::stopTimer(bool stop)
{
    /* Stop timer (and therefore any emits) */
    if (stop == true) {
        timer->stop();
		currentState = StateStopped;

        /* send zero input command one time when this timer stops */
        emit emitValues(0.0);
    }
}

void QGCSkyeTestTimerWidget::startTimer(bool start, int msecInterval)
{
    /* reset number of emits */
	if (ui->checkBoxUseTimer->isChecked()) {
		currentState = StateStopped;
	} else {
		currentState = StateContinous;
    }

    /* Start timer until it will be stopped */
    if (start == true) {
        this->msecInterval = msecInterval;
        timer->start(msecInterval);
    }
}

void QGCSkyeTestTimerWidget::startPhase(QGCSkyeTestTimerWidget::State phase, int msecPeriod)
{
	currentState = phase;
	// divide with round-up:
	shotsRemaining = (msecPeriod + msecInterval - 1) / msecInterval;
}

void QGCSkyeTestTimerWidget::timerTimeout()
{
	updateLabel();
	// decide wether to update shotsRemaining:
	switch(currentState)  {
		case StateContinous:
		case StateStopped:
			break;
		case StateForwardStart:
		case StateForward:
		case StatePause:
		case StateReverse:
			if (shotsRemaining > 0) {
				shotsRemaining--;
			}
			break;
	}
	// update state:
	if (shotsRemaining == 0) {
		switch(currentState)  {
			case StateContinous:
			case StateStopped:
				// stay in this state.
				break;
			case StateForwardStart:
				startPhase(StateForward, msecPeriod);
				break;
			case StateForward:
				if (ui->checkBoxInvertMovement->isChecked()) {
					if (msecPause > 0) {
						// goto next phase:
						startPhase(StatePause, msecPause);
					} else {
						startPhase(StateReverse, msecPeriod);
					}
				} else {
					// goto stopped state:
					currentState = StateStopped;
					// emit randomize command:
					if (ui->checkBoxRandomize->isChecked()) {
						emit randomizeInputs();
					}
				}
				break;
			case StatePause:
				// goto next phase:
				startPhase(StateReverse, msecPeriod);
				break;
			case StateReverse:
				currentState = StateStopped;
				// emit randomize command:
				if (ui->checkBoxRandomize->isChecked()) {
					emit randomizeInputs();
				}
				break;
		}
	}
	// decide what to emit:
	switch(currentState)  {
		case StateContinous:
			emit emitValues( 1.0);
			break;
		case StateForwardStart:
		case StateStopped:
			emit emitValues( 0.0);
			break;
		case StateForward:
			emit emitValues( 1.0);
			break;
		case StatePause:
			// emit small negative value to make the acutators move:
			emit emitValues(-0.001);
			break;
		case StateReverse:
			emit emitValues(-1.0);
			break;
	}
}

void QGCSkyeTestTimerWidget::updateLabel()
{
    QString str;
	switch(currentState)  {
		case StateContinous:
			str = QString("Start");
			break;
		case StateForwardStart:
		case StateStopped:
			str = QString("Start");
			break;
		case StateForward:
		case StatePause:
		case StateReverse:
			str = QString("Start (%1 sec)").arg(QString::number(shotsRemaining * msecInterval / 1000.0, 'f', 1));
			if (currentState == StatePause) {
				str.append(" p");
			} else if (currentState == StateReverse) {
				str.append(" inv");
			}
			break;
	}
    ui->pushButtonStart->setText(str);
}
