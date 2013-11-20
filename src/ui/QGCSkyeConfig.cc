#include "QGCSkyeConfig.h"
#include "ui_QGCSkyeConfig.h"

QGCSkyeConfig::QGCSkyeConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeConfig)
{
    ui->setupUi(this);

    tabWidget = new QTabWidget(this);
    testControl = new QGCSkyeTestControl(this);
    ui->verticalLayout->addWidget(tabWidget);
    ui->verticalLayout->addWidget(testControl);

    testMotor = new QGCSkyeTestMotors(this);
    testForce = new QGCSkyeTestForce(this);

    tabWidget->addTab(testMotor, "Motor Test");
    tabWidget->addTab(testForce, "Force Test");

    connect(testControl, SIGNAL(stopAllRequested()), testMotor, SLOT(stopAll()));
    connect(testControl, SIGNAL(setZeroRequested()), testMotor, SLOT(setZero()));
    connect(testControl, SIGNAL(stopAllRequested()), testForce, SLOT(stopAll()));

    connect(tabWidget, SIGNAL(currentChanged(int)), testControl, SLOT(tabChanged(int)));

    testControl->tabChanged(QGC_SKYE_CONFIG_TAB_MOTOR);
    tabWidget->setCurrentIndex(QGC_SKYE_CONFIG_TAB_MOTOR);

}

QGCSkyeConfig::~QGCSkyeConfig()
{
    delete ui;
}

void QGCSkyeConfig::showEvent(QShowEvent *event)
{
    //testControl->changeMode(MAV_MODE_PREFLIGHT);
    //qDebug() << "DISARMED system because Skye config is shown.";
    QWidget::showEvent(event);
}

void QGCSkyeConfig::hideEvent(QHideEvent *event)
{
    //testControl->changeMode(MAV_MODE_PREFLIGHT);
    //qDebug() << "DISARMED system because Skye config has been left.";
    QWidget::hideEvent(event);
}
