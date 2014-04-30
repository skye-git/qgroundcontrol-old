#include "QGCSkyeTest.h"
#include "ui_QGCSkyeTest.h"
#include <QDebug>

QGCSkyeTest::QGCSkyeTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTest),
    uas(NULL)
{
    ui->setupUi(this);

    // Insert box for periodic timing
    timerWidget =  new QGCSkyeTestTimerWidget(this);
    connect(timerWidget, SIGNAL(emitValues(double)), this, SLOT(emitValues(double)));

    ui->groupBoxTimer->layout()->addWidget(timerWidget);
}

QGCSkyeTest::~QGCSkyeTest()
{
    delete ui;
}

void QGCSkyeTest::activeTabChanged(bool active)
{
    timerWidget->activeTabChanged(active);
}
