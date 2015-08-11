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

    testMotor    = new QGCSkyeTestMotors(false, this);
    testMotorPpm = new QGCSkyeTestMotors(true,  this);
    testForce = new QGCSkyeTestForce(this);

    tabWidget->addTab(testMotor, "Motor Force");
    tabWidget->addTab(testMotorPpm, "Motor PPM");
    tabWidget->addTab(testForce, "Blimp Force");

    connect(testControl, SIGNAL(stopAllRequested()), testMotor,    SLOT(stopAll()));
    connect(testControl, SIGNAL(setZeroRequested()), testMotor,    SLOT(setZero()));
    connect(testControl, SIGNAL(stopAllRequested()), testMotorPpm, SLOT(stopAll()));
    connect(testControl, SIGNAL(setZeroRequested()), testMotorPpm, SLOT(setZero()));
    connect(testControl, SIGNAL(stopAllRequested()), testForce,    SLOT(stopAll()));

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(tabWidget, SIGNAL(currentChanged(int)), testControl, SLOT(tabChanged(int)));

    testControl->tabChanged(QGC_SKYE_CONFIG_TAB_MOTOR);
    tabWidget->setCurrentIndex(QGC_SKYE_CONFIG_TAB_MOTOR);
    this->tabChanged(QGC_SKYE_CONFIG_TAB_MOTOR);

}

QGCSkyeConfig::~QGCSkyeConfig()
{
    delete ui;
}

void QGCSkyeConfig::tabChanged(int tab)
{
    if (tabWidget->currentIndex() != tab) {
        qDebug() << "ERROR: SkyeConfig tab has not been updated correctly. Trying again..";
        tabWidget->setCurrentIndex(tab);
    }

    for (int i = 0; i < tabWidget->count(); i++) {
        QGCSkyeTest* skyeTestTab = dynamic_cast<QGCSkyeTest*> (tabWidget->widget(i));
        if (skyeTestTab) {
            /* inform each skyeTest widget about its visibility */
            skyeTestTab->activeTabChanged(i == tab);
        }
    }
}
