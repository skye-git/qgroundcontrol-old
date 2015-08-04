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
    ui->groupBoxTimer->layout()->addWidget(timerWidget);
    connect(timerWidget, SIGNAL(emitValues(double)), this, SLOT(emitValues(double)));
	connect(timerWidget, SIGNAL(randomizeInputs()), this, SLOT(randomizeInputs()));

    // Insert box for setpoints
	//setpointWidget = new QGCSkyeTestSetpointsWidget(this);
	//ui->groupBoxSetpoints->layout()->addWidget(setpointWidget);
    //connect()  XXX Todo
}

QGCSkyeTest::~QGCSkyeTest()
{
    delete ui;
}

void QGCSkyeTest::activeTabChanged(bool active)
{
    timerWidget->activeTabChanged(active);
}
