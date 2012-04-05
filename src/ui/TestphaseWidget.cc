#include "TestphaseWidget.h"
#include "ui_TestphaseWidget.h"
#include <QDebug>
#include "UAS.h"
#include "UASManager.h"
#include "QGC.h"
#include "SkyeMAV.h"

TestphaseWidget::TestphaseWidget(QWidget *parent):
    QDialog(parent),
    uas(NULL),
    engineOn(false),
    m_ui(new Ui::TestphaseWidget)
{

    m_ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);//The system crashes everytime one tries to reopen the Testphase Widget once it was closed if this attribute is set.
                                        //This is because, the pointer testphase in mainwindow.cc points to somewhere, and somewhere.show crashes.

//    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowFlags(Qt::WindowStaysOnTopHint);
    qDebug()<< " AL:TestphaseWidgetConstructor Call";


    this->uas = dynamic_cast<SkyeMAV*>(UASManager::instance()->getActiveUAS());

    if(uas)
    {
        connect(this, SIGNAL(valueTestphaseChanged(int, int, int, int, int, int, int, int)), uas, SLOT(setTestphaseCommandsByWidget(int, int, int, int, int, int, int, int)));
        connect(m_ui->homingButton, SIGNAL(clicked()), uas, SLOT(sendHomingCommand()));
        uas->setMode(MAV_MODE_TESTPHASE_DISARMED);
        qDebug()<< " AL:TestphaseWidget connect valueTestphaseChanged to setTestphaseCommandsByWidget";
    }




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
    connect(m_ui->SetZeroButton, SIGNAL(clicked()),this,SLOT(setzero()));
    connect(m_ui->stopallButton, SIGNAL(clicked()),this, SLOT(stopall())); //Why connect to this?
//    connect(m_ui->homingButton, SIGNAL(clicked()),this,SLOT(homing()));
    connect(m_ui->controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));
    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(stopall()));
    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(setzero()));
    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(Testphaseclose()));

//    //emit valueTestphaseChanged if some valueChanged
//    connect(m_ui->SliderThrust1, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->SliderThrust2, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->SliderThrust3, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->SliderThrust4, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation1, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation2, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation3, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation4, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));

    // Start Timer
    mouseTimer = new QTimer(this);
    connect(mouseTimer, SIGNAL(timeout()),this, SLOT(emitValues()));
    mouseTimer->start(200); //5Hz emitValues is called



    // Display the widget
    this->window()->setWindowTitle(tr("Testphase"));
    this->show();
}

TestphaseWidget::~TestphaseWidget()
{
    if(uas)
    {
        uas->setMode(MAV_MODE_PREFLIGHT);
    }
    qDebug()<< " AL:TestphaseWidgetDestructor Call";
    delete m_ui;
}

//bool TestphaseWidget::close()
//{
//    if(uas)
//    {
//        uas->setMode(MAV_MODE_PREFLIGHT);
//    }
//    engineOn=false;
//    this->hide();
//    qDebug()<< " AL:TestphaseWidgetclose";

//    return true;
//}
//void TestphaseWidget::closeEvent(QCloseEvent *event)
//{
//    if(uas)
//    {
//        uas->setMode(MAV_MODE_PREFLIGHT);
//    }
//    engineOn=false;
//    qDebug()<< " AL:TestphaseWidgetclose";
//    event->accept();
//}


void TestphaseWidget::emitValues()
{
    //qDebug()<<"AL:in emitValues"<<m_ui->spinBoxOrientation1->value() << "AL emit valueTestphaseChanged should be called next.";
    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        if (mav->getMode() == MAV_MODE_TESTPHASE_ARMED)
        {
            emit valueTestphaseChanged(m_ui->SliderThrust1->value(), m_ui->SliderThrust2->value(), m_ui->SliderThrust3->value(), m_ui->SliderThrust4->value(), m_ui->spinBoxOrientation1->value(), m_ui->spinBoxOrientation2->value(), m_ui->spinBoxOrientation3->value(), m_ui->spinBoxOrientation4->value());
//            qDebug()<<"AL:emit should have been called now. Thrust for Motor1 is"<< m_ui->SliderThrust1->value();
        }
    }
//    qDebug() << "Should have emitted TESTPHASE, mode is " << uas->getShortMode() << "autopilot " << uas->getAutopilotTypeName();
}

void TestphaseWidget::modeChanged(int mode_in)
{
    if(uas)
    {
        uas->setMode(mode_in);
    }
}

void TestphaseWidget::Testphaseclose()
{
    if(uas)
    {
        uas->setMode(MAV_MODE_PREFLIGHT);
    }
    engineOn=false;
    this->close();
}

void TestphaseWidget::setzero()
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
//void TestphaseWidget::homing()
//{

//}

void TestphaseWidget::cycleContextButton()
{
#ifdef MAVLINK_ENABLED_SKYE
    UAS* mav = dynamic_cast<UAS*>(UASManager::instance()->getUASForId(uas->getUASID()));
    if (mav)
    {
        if (!engineOn)
        {
            mav->armSystem();
            m_ui->controlButton->setText(tr("DISARMSYSTEM"));
            m_ui->controlButton->setStyleSheet("* { background-color: rgb(255,125,100) }");
            uas->setMode(MAV_MODE_TESTPHASE_ARMED);
            engineOn=true;
        } else {
            mav->disarmSystem();
            m_ui->controlButton->setText(tr("ARM SYSTEM"));
            m_ui->controlButton->setStyleSheet("* { background-color: rgb(125,255,100) }");
            uas->setMode(MAV_MODE_TESTPHASE_DISARMED);
            engineOn=false;
        }

    }
#endif // MAVLINK_ENABLED_SKYE
}

