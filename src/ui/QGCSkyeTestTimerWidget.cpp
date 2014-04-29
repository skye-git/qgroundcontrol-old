#include "QGCSkyeTestTimerWidget.h"
#include "ui_QGCSkyeTestTimerWidget.h"
#include <QDebug>

QGCSkyeTestTimerWidget::QGCSkyeTestTimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestTimerWidget),
    isInvertedMovement(false)
{
    ui->setupUi(this);

    /* Create timer. Iteratively tell parent to emit signals */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    connect(this, SIGNAL(emitValues(double)), parent, SLOT(emitValues(double)));

    /* Start continuous timer (5 Hz) */
    this->startTimerCont();

    /* Connect Widgets */
    connect(ui->checkBoxUseTimer, SIGNAL(toggled(bool)), this, SLOT(toggledCheckBoxUseTimer(bool)));
    connect(ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(clickedPushButtonStart()));
}

QGCSkyeTestTimerWidget::~QGCSkyeTestTimerWidget()
{
    delete ui;
}

void QGCSkyeTestTimerWidget::toggledCheckBoxUseTimer(bool checked)
{
    if (checked == true) {
        this->stopTimer();
    } else {
        isInvertedMovement = false;
        this->startTimerCont();
    }
}

void QGCSkyeTestTimerWidget::clickedPushButtonStart()
{
    /* Activate checkbox if it has not been set yet */
    if (ui->checkBoxUseTimer->isChecked() == false) {
        ui->checkBoxUseTimer->toggle();
    }

    /* Movement must start in right direction */
    isInvertedMovement = false;

    /* Update period time. This will also be needed for inverse direction (if inverse direction is activated) */
    msecPeriod = 1000 * ui->doubleSpinBoxPeriod->value();

    /* Start timer with default frequency for duration of period */
    this->startTimerPeriod(true, QGC_SKYE_TEST_TIMER_MSEC_INTERVAL, msecPeriod);
}

void QGCSkyeTestTimerWidget::stopTimer(bool stop)
{
    /* Stop timer (and therefore any emits) */
    if (stop == true) {
        timer->stop();

        /* send zero input command one time (XXX this might be unsecure) */
        emit emitValues(0.0);
    }
}

void QGCSkyeTestTimerWidget::startTimerCont(bool start, int msecInterval)
{
    /* Start timer (and therefore emits) until it is stopped externally */
    if (start == true) {
        shotsRemaining = -1;            // negativ value indicates no end
        this->msecInterval = msecInterval;
        timer->start(msecInterval);
    }
}

void QGCSkyeTestTimerWidget::startTimerPeriod(bool start, int msecInterval, int msecPeriod)
{
    if (start == true) {
        shotsRemaining = msecPeriod / msecInterval;
        this->msecInterval = msecInterval;
        timer->start(msecInterval);
    }
}

void QGCSkyeTestTimerWidget::timerTimeout()
{
    updateLabel();

    /* emit if period is either infinite (negative) or not expired (strict positiv) */
    if (shotsRemaining != 0) {
        if (isInvertedMovement) {
            emit emitValues(-1.0);      // inverse direction
        } else {
            emit emitValues( 1.0);      // forward direction
        }

        /* decrement counter if this is finite period */
        if (shotsRemaining > 0) {
            shotsRemaining--;
        }
        return;
    }

    /* period has expired (shotsRemaining == 0).
     * either stop or start movement into inverse direction */
    else {
        if (ui->checkBoxInvertMovement->isChecked() && !isInvertedMovement) {
            /* start movement into inverse direction if requested */
            isInvertedMovement = true;
            startTimerPeriod(true, QGC_SKYE_TEST_TIMER_MSEC_INTERVAL, msecPeriod);
        } else {
            /* inverse movement not requested or this was already inverse movement. stop now */
            this->stopTimer();
        }
    }
}

void QGCSkyeTestTimerWidget::updateLabel()
{
    QString str;
    if (shotsRemaining > 0)
    {
        str = QString("Start (%1 sec)").arg(QString::number(shotsRemaining * msecInterval / 1000.0, 'f', 3));
        if (isInvertedMovement) {
            str.append(" inv");
        }

    } else {
        str = QString("Start");
    }

    ui->pushButtonStart->setText(str);
}
