#include "TestControlWidget.h"
#include "ui_TestControlWidget.h"
#include <QDebug>
#include "UAS.h"
#include "UASManager.h"
#include "QGC.h"
#include "SkyeMAV.h"

TestControlWidget::TestControlWidget(QWidget *parent):
    QDialog(parent , Qt::WindowStaysOnTopHint),
    uas(NULL),
    engineOn(false),
    m_ui(new Ui::TestControlWidget)
{

    m_ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);//The system crashes everytime one tries to reopen the TestControl Widget once it was closed if this attribute is set.
                                        //This is because, the pointer TestControl in mainwindow.cc points to somewhere, and somewhere.show crashes.

//    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowFlags(Qt::WindowStaysOnTopHint);
    qDebug()<< " AL:TestControlWidgetConstructor Call";


    this->uas = dynamic_cast<SkyeMAV*>(UASManager::instance()->getActiveUAS());

    if(uas)
    {
        connect(this, SIGNAL(valueTestControlChanged(int, int, int, int, int, int, int, int)), uas, SLOT(setTestphaseCommandsByWidget(int, int, int, int, int, int, int, int)));
        connect(m_ui->homingButton, SIGNAL(clicked()), uas, SLOT(sendHomingCommand()));
        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        uas->setMode(MAV_MODE_TESTPHASE_DISARMED,0);
        qDebug()<< " AL:TestControlWidget connect valueTestControlChanged to setTestphaseCommandsByWidget";
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
//    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(stopall()));
//    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(setzero()));
//    connect(m_ui->closeButton, SIGNAL(clicked()),this, SLOT(TestControlclose()));

//    //emit valueTestControlChanged if some valueChanged
//    connect(m_ui->SliderThrust1, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->SliderThrust2, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->SliderThrust3, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->SliderThrust4, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation1, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation2, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation3, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));
//    connect(m_ui->dialOrientation4, SIGNAL(valueChanged(int)),this, SLOT(emitValues()));

    // Start Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(emitValues()));
    timer->start(200); //5Hz emitValues is called



    // Display the widget
    this->window()->setWindowTitle(tr("TestControl"));
    this->show();
}

TestControlWidget::~TestControlWidget()
{
    if(uas)
    {
        //timer->stop();
        uas->setMode(MAV_MODE_PREFLIGHT,0);
    }
    qDebug()<< " AL:TestControlWidgetDestructor Call";
    delete m_ui;
}

void TestControlWidget::closeEvent(QCloseEvent *event)
{
    TestControlclose();
    event->accept();
}

void TestControlWidget::setUAS(UASInterface* mav)
{
//    if (uas != 0)
//    {
//        disconnect(this, SIGNAL(valueTestControlChanged(double,double,double,double,double,double)), uas, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
//        disconnect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
//    }

//    uas = dynamic_cast<SkyeMAV*>(mav);
//    if (uas)
//    {
//        connect(this, SIGNAL(valueTestControlChanged(double,double,double,double,double,double)), uas, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
//        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
//        updateState(uas->getUASState());
//    }
}

void TestControlWidget::emitValues()
{
    //qDebug()<<"AL:in emitValues"<<m_ui->spinBoxOrientation1->value() << "AL emit valueTestControlChanged should be called next.";
    if (uas && this->isVisible())
    {
        if (uas->getMode() & MAV_MODE_FLAG_SAFETY_ARMED)
        {
            emit valueTestControlChanged(m_ui->SliderThrust1->value(), m_ui->SliderThrust2->value(), m_ui->SliderThrust3->value(), m_ui->SliderThrust4->value(), m_ui->spinBoxOrientation1->value(), m_ui->spinBoxOrientation2->value(), m_ui->spinBoxOrientation3->value(), m_ui->spinBoxOrientation4->value());
//            qDebug()<<"AL:emit should have been called now. Thrust for Motor1 is"<< m_ui->SliderThrust1->value();
        }
    }
//    qDebug() << "Should have emitted TestControl, mode is " << uas->getShortMode() << "autopilot " << uas->getAutopilotTypeName();
}

void TestControlWidget::modeChanged(int mode_in)
{
    if(uas)
    {
        uas->setMode(mode_in, 0);
    }
}

void TestControlWidget::TestControlclose()
{
    if(uas)
    {
        emit valueTestControlChanged(0, 0, 0, 0, 0, 0 ,0 ,0);
        uas->setMode(MAV_MODE_PREFLIGHT, 0);
    }
    engineOn=false;
    this->close();
}

void TestControlWidget::setzero()
{
    m_ui->dialOrientation1->setValue(0);
    m_ui->dialOrientation2->setValue(0);
    m_ui->dialOrientation3->setValue(0);
    m_ui->dialOrientation4->setValue(0);
}

void TestControlWidget::stopall()
{
    m_ui->SliderThrust1->setValue(0);
    m_ui->SliderThrust2->setValue(0);
    m_ui->SliderThrust3->setValue(0);
    m_ui->SliderThrust4->setValue(0);
}
//void TestControlWidget::homing()
//{

//}


void TestControlWidget::cycleContextButton()
{    
    if (uas)
    {
        if (!engineOn)
        {
            uas->armSystem();
            uas->setModeCommand(MAV_MODE_FLAG_TEST_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED);

            //m_ui->controlButton->setText(tr("DISARMSYSTEM"));
            //m_ui->controlButton->setStyleSheet("* { background-color: rgb(255,125,100) }");
//            uas->setMode(MAV_MODE_TESTPHASEARMED);
            engineOn=true;
        } else {
            emit valueTestControlChanged( 0, 0, 0, 0, 0, 0, 0, 0);
            uas->disarmSystem();
            //m_ui->controlButton->setText(tr("ARM SYSTEM"));
            //m_ui->controlButton->setStyleSheet("* { background-color: rgb(125,255,100) }");
            uas->setModeCommand(MAV_MODE_PREFLIGHT);
            engineOn=false;
        }

    }
}

void TestControlWidget::updateState(int state)
{
    switch(state)
    {
    case (int)MAV_STATE_ACTIVE:
        engineOn = true;
        m_ui->controlButton->setText(tr("DISARM SYSTEM"));
        m_ui->controlButton->setStyleSheet("* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); border-color: yellow; color: yellow }");
        break;
    case (int)MAV_STATE_STANDBY:
        engineOn = false;
        stopall();
        setzero();
        m_ui->controlButton->setText(tr("ARM SYSTEM"));
        m_ui->controlButton->setStyleSheet("* { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); }");
        break;
    default:
        engineOn = true;
        m_ui->controlButton->setText(tr("UNKNOWN STATE"));
        m_ui->controlButton->setStyleSheet("* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); border-color: yellow; color: yellow }");
        break;
    }
}

