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

    qDebug() << "This TimerWidget isActiveTab is" << active;
}

void QGCSkyeTestTimerWidget::toggledCheckBoxUseTimer(bool checked)
{
    // reset switch. This makes that we will always start with forward movement
    isInvertedMovement = false;

    if (checked == true) {
        shotsRemaining = 0;     // stop. timeout will send 0
    } else {
        shotsRemaining = -1;
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
    this->startPeriod(msecPeriod);
}

void QGCSkyeTestTimerWidget::stopTimer(bool stop)
{
    /* Stop timer (and therefore any emits) */
    if (stop == true) {
        timer->stop();

        /* send zero input command one time when this timer stops */
        emit emitValues(0.0);
    }
}

void QGCSkyeTestTimerWidget::startTimer(bool start, int msecInterval)
{
    /* reset number of emits */
    if (ui->checkBoxUseTimer->isChecked()) {
        shotsRemaining = 0;    // stop. timeout will send 0
    } else {
        shotsRemaining = -1;
    }

    /* Start timer until it will be stopped */
    if (start == true) {
        this->msecInterval = msecInterval;
        timer->start(msecInterval);
    }
}

void QGCSkyeTestTimerWidget::startPeriod(int msecPeriod)
{
    shotsRemaining = msecPeriod / msecInterval;
    this->msecPeriod = msecPeriod;
}

void QGCSkyeTestTimerWidget::timerTimeout()
{
    updateLabel();

    /* emit if period is either infinite (negative) or not expired (strict positiv)
     * and this is the active tab of the tab widget
     */
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
    }

    /* period has expired (shotsRemaining == 0).
     * either stop or start movement into inverse direction */
    else {
        if (ui->checkBoxInvertMovement->isChecked() && !isInvertedMovement) {
            /* start movement into inverse direction if requested */
            isInvertedMovement = true;
            startPeriod(msecPeriod);
        } else {
            /* inverse movement not requested or this was already inverse movement. send zero */
            emit emitValues(0.0);
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
