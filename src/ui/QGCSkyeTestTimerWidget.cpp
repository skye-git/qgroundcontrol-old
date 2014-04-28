#include "QGCSkyeTestTimerWidget.h"
#include "ui_QGCSkyeTestTimerWidget.h"

QGCSkyeTestTimerWidget::QGCSkyeTestTimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestTimerWidget)
{
    ui->setupUi(this);

    /* Create timer. Iteratively pull values from SliderWidgets and then emit them (to UAV). */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), parent, SLOT(emitValues()));

    /* Start continuous timer (5 Hz) */
    timer->start(200);
}

QGCSkyeTestTimerWidget::~QGCSkyeTestTimerWidget()
{
    delete ui;
}
