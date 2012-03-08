#include "TestphaseWidget.h"
#include "ui_TestphaseWidget.h"
#include <QDebug>
#include "UAS.h"
#include "UASManager.h"
#include "QGC.h"

TestphaseWidget::TestphaseWidget(QWidget *parent):
    QDialog(parent),
    uas(NULL),
    m_ui(new Ui::TestphaseWidget)
{
    m_ui->setupUi(this);

    qDebug()<< " AL:TestphaseWidgetConstructor Call";

    this->uas = UASManager::instance()->getActiveUAS();
    connect(this, SIGNAL(valueTestphaseChanged(int, int, int, int, int, int, int, int)), uas, SLOT(setTestphaseCommandsByWidget(int, int, int, int, int, int, int, int)));
    //FIXME Problem, funktioniert nur, falls getActiveUAS() ein UASInterface zurückgibt, dass SkyeMAV
    //mit if abfragen, ........


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
    delete m_ui;
}

void TestphaseWidget::somevalueChanged()
{
    //qDebug()<<"AL:in somevalueChanged"<<m_ui->SliderThrust1->value() << "AL emit valueTestphaseChanged should be called next.";
    emit valueTestphaseChanged(m_ui->SliderThrust1->value(), m_ui->SliderThrust2->value(), m_ui->SliderThrust3->value(), m_ui->SliderThrust4->value(), m_ui->spinBoxOrientation1->value(), m_ui->spinBoxOrientation2->value(), m_ui->spinBoxOrientation3->value(), m_ui->spinBoxOrientation4->value());
    //qDebug()<<"AL:emit should have been called now";
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

