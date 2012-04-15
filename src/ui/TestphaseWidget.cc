#include "TestphaseWidget.h"
#include "ui_TestphaseWidget.h"
#include <QDebug>
#include "UAS.h"
#include "UASManager.h"
#include "QGC.h"
#include "SkyeMAV.h"

TestphaseWidget::TestphaseWidget(QWidget *parent):
    QDialog(parent , Qt::WindowStaysOnTopHint),
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
        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
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
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(emitValues()));
    timer->start(200); //5Hz emitValues is called



    // Display the widget
    this->window()->setWindowTitle(tr("Testphase"));
    this->show();
}

TestphaseWidget::~TestphaseWidget()
{
    if(uas)
    {
        //timer->stop();
        uas->setMode(MAV_MODE_PREFLIGHT);
    }
    qDebug()<< " AL:TestphaseWidgetDestructor Call";
    delete m_ui;
}

void TestphaseWidget::closeEvent(QCloseEvent *event)
{
    Testphaseclose();
    event->accept();
}

void TestphaseWidget::setUAS(UASInterface* mav)
{
    if (uas != 0)
    {
        disconnect(this, SIGNAL(valueTestphaseChanged(double,double,double,double,double,double)), uas, SLOT(setManualControlCommands6DoF(double,double,double,double,double,double)));
        disconnect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
    }

    uas = dynamic_cast<SkyeMAV*>(mav);
    if (uas)
    {
        connect(this, SIGNAL(valueTestphaseChanged(double,double,double,double,double,double)), uas, SLOT(setManualControlCommands6DoF(double,double,double,double,double,double)));
        connect(uas, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        updateState(uas->getUASState());
    }
}

void TestphaseWidget::emitValues()
{
    //qDebug()<<"AL:in emitValues"<<m_ui->spinBoxOrientation1->value() << "AL emit valueTestphaseChanged should be called next.";
    if (uas && this->isVisible())
    {
        if (uas->getMode() == MAV_MODE_TESTPHASE_ARMED)
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
        emit valueTestphaseChanged(0, 0, 0, 0, 0, 0 ,0 ,0);
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
    if (uas)
    {
        if (!engineOn)
        {
            uas->armSystem();
            //m_ui->controlButton->setText(tr("DISARMSYSTEM"));
            //m_ui->controlButton->setStyleSheet("* { background-color: rgb(255,125,100) }");
            uas->setMode(MAV_MODE_TESTPHASE_ARMED);
            engineOn=true;
        } else {
            emit valueTestphaseChanged( 0, 0, 0, 0, 0, 0, 0, 0);
            uas->disarmSystem();
            //m_ui->controlButton->setText(tr("ARM SYSTEM"));
            //m_ui->controlButton->setStyleSheet("* { background-color: rgb(125,255,100) }");
            uas->setMode(MAV_MODE_TESTPHASE_DISARMED);
            engineOn=false;
        }

    }
}

void TestphaseWidget::updateState(int state)
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
    }
}

