#include "UASSkyeControlAdvancedWidget.h"
#include "ui_UASSkyeControlAdvancedWidget.h"

#include "UASManager.h"
#include "SkyeUAS.h"

UASSkyeControlAdvancedWidget::UASSkyeControlAdvancedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSkyeControlAdvancedWidget),
    uas(NULL),
    addRollEnabled(false),
    addPitchEnabled(false),
    addYawEnabled(false),
    liftValue(QGC_SKYE_LIFT_DEFAULT),
    sensitivityTrans(QGC_SENSITIVITY_TRANS_DEFAULT),
    sensitivityRot(QGC_SENSITIVITY_ROT_DEFAULT)
{
    ui->setupUi(this);

    ui->groupBoxAllocation->hide();

    // connect spinboxes
    connect(ui->doubleSpinBoxTranslation, SIGNAL(valueChanged(double)), this, SLOT(changeTransValue(double)));
    connect(ui->doubleSpinBoxRotation, SIGNAL(valueChanged(double)), this, SLOT(changeRotValue(double)));
    connect(ui->doubleSpinBoxLift, SIGNAL(valueChanged(double)), this, SLOT(changeLiftValue(double)));
    connect(ui->doubleSpinBoxRoll, SIGNAL(valueChanged(double)), this, SLOT(changeRollValue(double)));
    connect(ui->doubleSpinBoxPitch, SIGNAL(valueChanged(double)), this, SLOT(changePitchValue(double)));
    connect(ui->doubleSpinBoxYaw, SIGNAL(valueChanged(double)), this, SLOT(changeYawValue(double)));

    ui->doubleSpinBoxLift->setRange(-QGC_SKYE_LIFT_MAX, QGC_SKYE_LIFT_MAX);

    // update spinboxes
    ui->doubleSpinBoxTranslation->setValue(sensitivityTrans);
    ui->doubleSpinBoxRotation->setValue(sensitivityRot);
    ui->doubleSpinBoxLift->setValue(liftValue);

    // connect checkboxes
    connect(ui->checkBoxRoll, SIGNAL(clicked(bool)), this, SLOT(clickedRollCheckBox(bool)));
    connect(ui->checkBoxPitch, SIGNAL(clicked(bool)), this, SLOT(clickedPitchCheckBox(bool)));
    connect(ui->checkBoxYaw, SIGNAL(clicked(bool)), this, SLOT(clickedYawCheckBox(bool)));

    // connect AU radio buttons
    connect(ui->radioButtonAllAU, SIGNAL(clicked()), this, SLOT(clickedAllAURadioButton()));
    connect(ui->radioButtonWoAU1, SIGNAL(clicked()), this, SLOT(clickedWoAU1RadioButton()));
    connect(ui->radioButtonWoAU2, SIGNAL(clicked()), this, SLOT(clickedWoAU2RadioButton()));
    connect(ui->radioButtonWoAU3, SIGNAL(clicked()), this, SLOT(clickedWoAU3RadioButton()));
    connect(ui->radioButtonWoAU4, SIGNAL(clicked()), this, SLOT(clickedWoAU4RadioButton()));

    // update checkboxes
    ui->checkBoxRoll->setChecked(addRollEnabled);
    ui->checkBoxPitch->setChecked(addPitchEnabled);
    ui->checkBoxYaw->setChecked(addYawEnabled);

    // connect uav activation
    this->setUAS(UASManager::instance()->getActiveUAS());
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

}

UASSkyeControlAdvancedWidget::~UASSkyeControlAdvancedWidget()
{
    delete ui;
}

void UASSkyeControlAdvancedWidget::setUAS(UASInterface* uas)
{

    if (this->uas!= NULL)
    {
        SkyeUAS* mav = dynamic_cast<SkyeUAS*>(this->uas);
        this->uas = NULL;
        if (mav)
        {

            disconnect(this, SIGNAL(transSliderValueChanged(float)), mav, SLOT(setSensitivityFactorTrans(float)));
            disconnect(this, SIGNAL(rotSliderValueChanged(float)), mav, SLOT(setSensitivityFactorRot(float)));
            disconnect(this, SIGNAL(liftSliderValueChanged(double)), mav, SLOT(setLiftValue(double)));

            disconnect(mav,SIGNAL(sensitivityTransChanged(double)), this, SLOT(changeTransValue(double)));
            disconnect(mav,SIGNAL(sensitivityRotChanged(double)), this, SLOT(changeRotValue(double)));

            disconnect(this, SIGNAL(rollSliderValueChanged(double)), mav, SLOT(setAddRollValue(double)));
            disconnect(this, SIGNAL(pitchSliderValueChanged(double)), mav, SLOT(setAddPitchValue(double)));
            disconnect(this, SIGNAL(yawSliderValueChanged(double)), mav, SLOT(setAddYawValue(double)));

            // Disconnect slots for Change of Actuation Unit Configuration
            disconnect(this, SIGNAL(requestAUConfiguration(int)), mav, SLOT(sendAllocationCase(int)));
            disconnect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocCase(int)));
        }
    }


    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(uas);
    if (mav)
    {
        this->uas = uas;

        // Connect user interface controls

        connect(this, SIGNAL(transSliderValueChanged(float)), mav, SLOT(setSensitivityFactorTrans(float)));
        connect(this, SIGNAL(rotSliderValueChanged(float)), mav, SLOT(setSensitivityFactorRot(float)));
        connect(this, SIGNAL(liftSliderValueChanged(double)), mav, SLOT(setLiftValue(double)));

        connect(mav, SIGNAL(sensitivityTransChanged(double)), this, SLOT(changeTransValue(double)));
        connect(mav, SIGNAL(sensitivityRotChanged(double)), this, SLOT(changeRotValue(double)));

        connect(this, SIGNAL(rollSliderValueChanged(double)), mav, SLOT(setAddRollValue(double)));
        connect(this, SIGNAL(pitchSliderValueChanged(double)), mav, SLOT(setAddPitchValue(double)));
        connect(this, SIGNAL(yawSliderValueChanged(double)), mav, SLOT(setAddYawValue(double)));

        // Connect slots for Change of Actuation Unit Configuration
        connect(this, SIGNAL(requestAUConfiguration(int)), mav, SLOT(sendAllocationCase(int)));
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocCase(int)));

        // Initial emitment of spinbox values
        emit transSliderValueChanged((float)sensitivityTrans);
        emit rotSliderValueChanged((float)sensitivityRot);
        emit liftSliderValueChanged(liftValue);
    }
}


void UASSkyeControlAdvancedWidget::setSliderValues(double transValue, double rotValue, double liftValue)
{
    ui->doubleSpinBoxTranslation->setValue(transValue);
    ui->doubleSpinBoxRotation->setValue(rotValue);
    ui->doubleSpinBoxLift->setValue(liftValue);
}

void UASSkyeControlAdvancedWidget::emitSliderValues()
{
    emit transSliderValueChanged(ui->doubleSpinBoxTranslation->value());
    emit rotSliderValueChanged(ui->doubleSpinBoxRotation->value());
    emit liftSliderValueChanged(ui->doubleSpinBoxLift->value());
    emit rollSliderValueChanged(ui->doubleSpinBoxRoll->value());
    emit pitchSliderValueChanged(ui->doubleSpinBoxPitch->value());
    emit yawSliderValueChanged(ui->doubleSpinBoxYaw->value());
}

void UASSkyeControlAdvancedWidget::changeTransValue(double value)
{
    if (sensitivityTrans != value)
    {
        sensitivityTrans = value;

        ui->doubleSpinBoxTranslation->setValue(sensitivityTrans);
        ui->doubleSpinBoxTranslation->setStyleSheet(getStyleString(value));

        emit transSliderValueChanged((float)value);
    }
}

void UASSkyeControlAdvancedWidget::changeRotValue(double value)
{
    if (sensitivityRot != value)
    {
        sensitivityRot = value;

        ui->doubleSpinBoxRotation->setValue(sensitivityRot);
        ui->doubleSpinBoxRotation->setStyleSheet(getStyleString(value));

        emit rotSliderValueChanged((float)value);
    }
}

void UASSkyeControlAdvancedWidget::changeLiftValue(double value)
{
    if (liftValue != value)
    {
        liftValue = value;

        ui->doubleSpinBoxLift->setStyleSheet(getStyleString(value));

        emit liftSliderValueChanged(liftValue);
    }
}

void UASSkyeControlAdvancedWidget::changeRollValue(double value)
{
    ui->doubleSpinBoxRoll->setStyleSheet(getStyleString(value));

    if (ui->checkBoxRoll->isChecked())
    {
        emit rollSliderValueChanged(value);
    }
    else
    {
        emit rollSliderValueChanged(0.0);
    }
}

void UASSkyeControlAdvancedWidget::changePitchValue(double value)
{
    ui->doubleSpinBoxPitch->setStyleSheet(getStyleString(value));
    if (ui->checkBoxPitch->isChecked())
    {
        emit pitchSliderValueChanged(value);
    }
    else
    {
        emit pitchSliderValueChanged(0.0);
    }
}

void UASSkyeControlAdvancedWidget::changeYawValue(double value)
{
    ui->doubleSpinBoxYaw->setStyleSheet(getStyleString(value));

    if (ui->checkBoxYaw->isChecked())
    {
        emit yawSliderValueChanged(value);
    }
    else
    {
        emit yawSliderValueChanged(0.0);
    }
}

QString UASSkyeControlAdvancedWidget::getStyleString(double val)
{
    int red = 16*16;
    int green = 16;
    int blue = 1;
    int colorStart = (int)(( 1+10*val ) * red + (  10*(1-val)) * green + 6 * blue);
    int colorEnd =   (int)(( 1+14*val ) * red + (  14*(1-val)) * green + 6 * blue);
    QString style = QString("QSlider::sub-page:horizontal {border: 1px solid #bbb; border-radius: 4px; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #%1, stop: 1 #%2); }").arg(colorStart, 1, 16).arg(colorEnd, 1, 16);

    return style;
}

void UASSkyeControlAdvancedWidget::clickedRollCheckBox(bool active)
{
    addRollEnabled = active;
    // update value
    changeRollValue(ui->doubleSpinBoxRoll->value());
}


void UASSkyeControlAdvancedWidget::clickedPitchCheckBox(bool active)
{
    addPitchEnabled = active;
    // update value
    changePitchValue(ui->doubleSpinBoxPitch->value());
}


void UASSkyeControlAdvancedWidget::clickedYawCheckBox(bool active)
{
    addYawEnabled = active;
    // update value
    changeYawValue(ui->doubleSpinBoxYaw->value());
}

void UASSkyeControlAdvancedWidget::clickedAllAURadioButton()
{
    emit requestAUConfiguration(0);
}

void UASSkyeControlAdvancedWidget::clickedWoAU1RadioButton()
{
    emit requestAUConfiguration(1);
}
void UASSkyeControlAdvancedWidget::clickedWoAU2RadioButton()
{
    emit requestAUConfiguration(2);
}
void UASSkyeControlAdvancedWidget::clickedWoAU3RadioButton()
{
    emit requestAUConfiguration(3);
}
void UASSkyeControlAdvancedWidget::clickedWoAU4RadioButton()
{
    emit requestAUConfiguration(4);
}

void UASSkyeControlAdvancedWidget::updateAllocCase(int allocCase)
{

    // reset all radio buttons
    ui->radioButtonAllAU->setStyleSheet("QLabel {color: #000;}");
    ui->radioButtonWoAU1->setStyleSheet("QLabel {color: #000;}");
    ui->radioButtonWoAU2->setStyleSheet("QLabel {color: #000;}");
    ui->radioButtonWoAU3->setStyleSheet("QLabel {color: #000;}");
    ui->radioButtonWoAU4->setStyleSheet("QLabel {color: #000;}");

    // highlight active radio button
    switch(allocCase)
    {
    case 0:
        ui->radioButtonAllAU->setStyleSheet("QLabel {color: #00DD00;}");
        ui->radioButtonAllAU->setChecked(true);
        break;
    case 1:
        ui->radioButtonWoAU1->setStyleSheet("QLabel {color: #00DD00;}");
        ui->radioButtonWoAU1->setChecked(true);
        break;
    case 2:
        ui->radioButtonWoAU2->setStyleSheet("QLabel {color: #00DD00;}");
        ui->radioButtonWoAU2->setChecked(true);
        break;
    case 3:
        ui->radioButtonWoAU3->setStyleSheet("QLabel {color: #00DD00;}");
        ui->radioButtonWoAU3->setChecked(true);
        break;
    case 4:
        ui->radioButtonWoAU4->setStyleSheet("QLabel {color: #00DD00;}");
        ui->radioButtonWoAU4->setChecked(true);
        break;
    default: break;
    }
}

