#include "TestphaseWidget.h"
#include "ui_TestphaseWidget.h"
#include <QDebug>
#include "UAS.h"
#include "UASManager.h"
#include "QGC.h"

TestphaseWidget::TestphaseWidget(QWidget *parent):
    QDialog(parent),
    uas(NULL),
    engineOn(false),
    m_ui(new Ui::TestphaseWidget)
{
    //m_ui->setAttribute(Qt::WA_DeleteOnClose, true);//why no member named 'setAttribute'
    m_ui->setupUi(this);

    qDebug()<< " AL:TestphaseWidgetConstructor Call";

    //get active UAS
    this->uas = UASManager::instance()->getActiveUAS();

#ifdef MAVLINK_ENABLED_SKYE
    if (uas->getUASID()!= 0)
    {

    connect(this, SIGNAL(valueTestphaseChanged(int, int, int, int, int, int, int, int)), uas, SLOT(setTestphaseCommandsByWidget(int, int, int, int, int, int, int, int)));
    uas->setMode(MAV_MODE_TESTPHASE_DISARMED);
    }
#endif //MAVLINK_ENABLED_SKye


    //connect Sliders, spinBoxes and dials

    connect(m_ui->SliderThrust1, SIGNAL(valueChanged(int)), m_ui->spinBoxThrust1, SLOT(setValue(int)));
    connect(m_ui->spinBoxThrust1, SIGNAL(valueChanged(int)), m_ui->SliderThrust1, SLOT(setValue(int)));

    connect(m_ui->dialOrientation1, SIGNAL(valueChanged(int)), m_ui->spinBoxOrientation1, SLOT(setValue(int)));
    connect(m_ui->spinBoxOrientation1, SIGNAL(valueChanged(int)), m_ui->dialOrientation1, SLOT(setValue(int)));

    connect(m_ui->SliderThrust2, SIGNAL(valueChanged(int)), m_ui->spinBoxThrust2, SLOT(setValue(int)));
    connect(m_ui->spinBoxThrust2, SIGNAL(valueChanged(int)), m_ui->SliderThrust2, SLOT(setValue(int)));

    connect(m_ui->dialOrientation2, SIGNAL(valueChanged(int)), m_ui->spinBoxOrientation2, SLOT(setValue(int)));
    connect(m_ui->spinBoxOrientation2, SIGNAL(valueChanged(int)), m_ui->dialOrientation2, SLOT(setValue(int)));

    connect(m_ui->SliderThrust3, SIGNAL(valueChanged(int)), m_ui->spinBoxThrust3, SLOT(setValue(int)));
    connect(m_ui->spinBoxThrust3, SIGNAL(valueChanged(int)), m_ui->SliderThrust3, SLOT(setValue(int)));

    connect(m_ui->dialOrientation3, SIGNAL(valueChanged(int)), m_ui->spinBoxOrientation3, SLOT(setValue(int)));
    connect(m_ui->spinBoxOrientation3, SIGNAL(valueChanged(int)), m_ui->dialOrientation3, SLOT(setValue(int)));

    connect(m_ui->SliderThrust4, SIGNAL(valueChanged(int)), m_ui->spinBoxThrust4, SLOT(setValue(int)));
    connect(m_ui->spinBoxThrust4, SIGNAL(valueChanged(int)), m_ui->SliderThrust4, SLOT(setValue(int)));

    connect(m_ui->dialOrientation4, SIGNAL(valueChanged(int)), m_ui->spinBoxOrientation4, SLOT(setValue(int)));
    connect(m_ui->spinBoxOrientation4, SIGNAL(valueChanged(int)), m_ui->dialOrientation4, SLOT(setValue(int)));

    //connect Pushbuttons
    connect(m_ui->HomingButton, SIGNAL(clicked()),this,SLOT(homing()));
    connect(m_ui->stopallButton, SIGNAL(clicked()),this, SLOT(stopall())); //Why connect to this?
    connect(m_ui->controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));
    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(stopall()));
    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(homing()));
    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(Testphaseclose()));

    //emit valueTestphaseChanged if some valueChanged
    connect(m_ui->SliderThrust1, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->SliderThrust2, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->SliderThrust3, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->SliderThrust4, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->dialOrientation1, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->dialOrientation2, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->dialOrientation3, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));
    connect(m_ui->dialOrientation4, SIGNAL(valueChanged(int)),this, SLOT(somevalueChanged()));

    // Display the widget
    this->window()->setWindowTitle(tr("Testphase"));
    this->show();
}

TestphaseWidget::~TestphaseWidget()
{
    uas->setMode(MAV_MODE_PREFLIGHT);
    qDebug()<< " AL:TestphaseWidgetDestructor Call";
    delete m_ui;
}

void TestphaseWidget::somevalueChanged()
{
    //qDebug()<<"AL:in somevalueChanged"<<m_ui->SliderThrust1->value() << "AL emit valueTestphaseChanged should be called next.";
    emit valueTestphaseChanged(m_ui->SliderThrust1->value(), m_ui->SliderThrust2->value(), m_ui->SliderThrust3->value(), m_ui->SliderThrust4->value(), m_ui->spinBoxOrientation1->value(), m_ui->spinBoxOrientation2->value(), m_ui->spinBoxOrientation3->value(), m_ui->spinBoxOrientation4->value());
    //qDebug()<<"AL:emit should have been called now";
}

void TestphaseWidget::modeChanged(int mode_in)
{
    uas->setMode(mode_in);
}

void TestphaseWidget::Testphaseclose()
{

    uas->setMode(MAV_MODE_PREFLIGHT);
    this->close();
}

void TestphaseWidget::homing()
{
    m_ui->dialOrientation1->setValue(0);
    m_ui->dialOrientation2->setValue(0);
    m_ui->dialOrientation3->setValue(0);
    m_ui->dialOrientation4->setValue(0);
}

void TestphaseWidget::stopall()
{
    m_ui->SliderThrust1->setValue(0);
    m_ui->SliderThrust2->setValue(0);
    m_ui->SliderThrust3->setValue(0);
    m_ui->SliderThrust4->setValue(0);
}

void TestphaseWidget::cycleContextButton()
{
#ifdef MAVLINK_ENABLED_SKYE
    UAS* mav = dynamic_cast<UAS*>(UASManager::instance()->getUASForId(uas->getUASID()));
    if (mav)
    {
        if (!engineOn)
        {
            mav->armSystem();
            m_ui->controlButton->setText(tr("ARM SYSTEM"));
            m_ui->controlButton->setStyleSheet("* { background-color: rgb(125,255,100) }");
            uas->setMode(MAV_MODE_TESTPHASE_ARMED);
            engineOn=true;
        } else {
            mav->disarmSystem();
            m_ui->controlButton->setText(tr("DISARMSYSTEM"));
            m_ui->controlButton->setStyleSheet("* { background-color: rgb(255,125,100) }");
            uas->setMode(MAV_MODE_TESTPHASE_DISARMED);
            engineOn=false;
        }

    }
#endif // MAVLINK_ENABLED_SKYE
}

