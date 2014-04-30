#include "QGCSkyeTest.h"
#include "ui_QGCSkyeTest.h"
#include "UASManager.h"

QGCSkyeTest::QGCSkyeTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTest),
    uas(NULL)
{
    ui->setupUi(this);

    // Insert box for periodic timing
    timerWidget = new QGCSkyeTestTimerWidget(this);
    ui->groupBoxTimer->layout()->addWidget(timerWidget);

    // connect UAV
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());

}

QGCSkyeTest::~QGCSkyeTest()
{
    delete ui;
}

void QGCSkyeTest::setUAS(UASInterface* uas)
{
    if (this->uas != 0)
    {
        disconnect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), this->uas, SLOT(set6DOFCommandsByWidget(double,double,double,double,double,double)));
    }

    this->uas = dynamic_cast<SkyeMAV*>(uas);
    if (this->uas)
    {
        connect(this, SIGNAL(valueDirectControlChanged(double,double,double,double,double,double)), this->uas, SLOT(set6DOFCommandsByWidget(double,double,double,double,double,double)));
    }
}

