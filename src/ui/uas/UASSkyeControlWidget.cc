/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009, 2010 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of widget controlling one (skye) MAV. Newimplemetation of UASControlWidget.
 *
 *   @author Matthias Krebs <makrebs@student.ethz.ch>
 *
 */

#define QGC_SKYE_DEFAULT_SENS_DIRECT_TRANS 0.5
#define QGC_SKYE_DEFAULT_SENS_DIRECT_ROT 0.5
#define QGC_SKYE_DEFAULT_SENS_ASSIST_TRANS 0.5
#define QGC_SKYE_DEFAULT_SENS_ASSIST_ROT 0.5
#define QGC_SKYE_MAX_SENS_DIRECT_TRANS 1.0
#define QGC_SKYE_MAX_SENS_DIRECT_ROT 1.0
#define QGC_SKYE_MAX_SENS_ASSIST_TRANS 1.0
#define QGC_SKYE_MAX_SENS_ASSIST_ROT 1.0

#include <QString>
#include <QTimer>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QPalette>
//#include <QMessageBox>

#include "UASSkyeControlWidget.h"
#include "UASManager.h"
#include "QGC.h"

UASSkyeControlWidget::UASSkyeControlWidget(QWidget *parent) : QWidget(parent),
    uasId(0),
    uasMode(0),
    engineOn(false),
    inputMode(SkyeMAV::QGC_INPUT_MODE_NONE),
    mouseTranslationEnabled(true),
    mouseRotationEnabled(true),
    sensitivityFactorTrans(QGC_SKYE_DEFAULT_SENS_DIRECT_TRANS),
    minSensitivityFactorTrans(0.0f),
    maxSensitivityFactorTrans(QGC_SKYE_MAX_SENS_DIRECT_TRANS),
    sensitivityFactorRot(QGC_SKYE_DEFAULT_SENS_DIRECT_ROT),
    minSensitivityFactorRot(0.0f),
    maxSensitivityFactorRot(QGC_SKYE_MAX_SENS_DIRECT_ROT),
    liftFactorEnabled(true),
    liftFactor(0.0f),
    minLiftFactor(0.0f),
    maxLiftFactor(0.5f)
{
#ifdef QGC_USE_SKYE_INTERFACE
    ui.setupUi(this);

    // Uncheck and group buttons to enable exclusiv checkable
//    ui.directControlButton->setChecked(uasMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL);
//    ui.rateControlButton->setChecked(uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE);
//    ui.attitudeControlButton->setChecked(uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE);
//    ui.halfAutomaticControlButton->setChecked(uasMode & MAV_MODE_HALF_AUTOMATIC_DISARMED);
//    ui.fullAutomaticControlButton->setChecked(uasMode & MAV_MODE_FULL_AUTOMATIC_DISARMED);
    ui.directControlButton->setCheckable(false);
    ui.rateControlButton->setCheckable(false);
	ui.attitudeControlButton->setCheckable(false);
    ui.halfAutomaticControlButton->hide();
    ui.fullAutomaticControlButton->hide();

    ui.mouseButton->setChecked(inputMode == SkyeMAV::QGC_INPUT_MODE_MOUSE);
    ui.touchButton->setChecked(inputMode == SkyeMAV::QGC_INPUT_MODE_TOUCH);
    ui.keyboardButton->setChecked(inputMode == SkyeMAV::QGC_INPUT_MODE_KEYBOARD);
    inputButtonGroup = new QButtonGroup;
    inputButtonGroup->addButton(ui.mouseButton);
    inputButtonGroup->addButton((ui.touchButton));
    inputButtonGroup->addButton((ui.keyboardButton));
    ui.keyboardButton->hide();

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    connect(ui.directControlButton, SIGNAL(clicked()), this, SLOT(setDirectControlMode()));
    connect(ui.rateControlButton, SIGNAL(clicked()), this, SLOT(setRateControlMode()));
	connect(ui.attitudeControlButton, SIGNAL(clicked()), this, SLOT(setAttitudeControlMode()));

    connect(ui.mouseButton, SIGNAL(clicked(bool)), this, SLOT(setInputMouse(bool)));
    connect(ui.touchButton, SIGNAL(clicked(bool)), this, SLOT(setInputTouch(bool)));
    connect(ui.keyboardButton, SIGNAL(clicked(bool)), this, SLOT(setInputKeyboard(bool)));

    // Multiplication factor for translational commands
    ui.sensitivityTransSlider->setValue(ui.sensitivityTransSlider->maximum()*sensitivityFactorTrans/maxSensitivityFactorTrans);
    connect(ui.sensitivityTransSlider, SIGNAL(valueChanged(int)), this, SLOT(setSensitivityFactorTrans(int)));
    setSensitivityFactorTrans(ui.sensitivityTransSlider->value());
    ui.minSensitivityTransLabel->setNum((double)minSensitivityFactorTrans);
    ui.maxSensitivityTransLabel->setNum((double)maxSensitivityFactorTrans);

    // Multiplication factor for rotational commands
    ui.sensitivityRotSlider->setValue(ui.sensitivityRotSlider->maximum()*sensitivityFactorRot/maxSensitivityFactorRot);
    connect(ui.sensitivityRotSlider, SIGNAL(valueChanged(int)), this, SLOT(setSensitivityFactorRot(int)));
    setSensitivityFactorRot(ui.sensitivityRotSlider->value());
    ui.minSensitivityRotLabel->setNum((double)minSensitivityFactorRot);
    ui.maxSensitivityRotLabel->setNum((double)maxSensitivityFactorRot);

    //ui.gridLayout->setAlignment(Qt::AlignTop);

    ui.bluefoxLeftButton->hide();
    ui.bluefoxRightButton->hide();
    ui.prosilicaButton->hide();

    // additive lift factor fields
    ui.liftCheckBox->setChecked(liftFactorEnabled);
    connect(ui.liftCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableLiftFactor(bool)));

    ui.liftSlider->setRange(0, 999);
    ui.liftSlider->setValue(ui.liftSlider->maximum()*liftFactor/maxLiftFactor);
    connect(ui.liftSlider, SIGNAL(valueChanged(int)), this, SLOT(setLiftFactor(int)));

    ui.minSensitivityRotLabel->setNum((double)minLiftFactor);
    ui.maxLiftSpinBox->setValue((double)maxLiftFactor);
    connect(ui.maxLiftSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMaxLiftFactor(double)));


    updateStyleSheet();

    // TODO: set correct margins instead of min height
    this->setMinimumHeight(220);

    lastAlertTime.start();
    alertedBatteryLow = false;
    msgBox = new QErrorMessage;

#endif //QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setUAS(UASInterface* uas)
{
#ifdef QGC_USE_SKYE_INTERFACE
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        ui.lastActionLabel->setText("Disconnected from " + oldUAS->getUASName());
        this->uasId = 0;
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(oldUAS);
        if (mav)
        {
            disconnect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
            disconnect(mav, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
            disconnect(this, SIGNAL(changedInput(SkyeMAV::QGC_INPUT_MODE)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE)));
            disconnect(mav, SIGNAL(mouseButtonRotationChanged(bool)), this, SLOT(changeMouseRotationEnabled(bool)));
            disconnect(mav, SIGNAL(mouseButtonTranslationChanged(bool)), this, SLOT(changeMouseTranslationEnabled(bool)));
            disconnect(mav, SIGNAL(batteryLow(double)), this, SLOT(alertBatteryLow(double)));

        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        //ui.controlStatusLabel->setText(tr("Connected to ") + mav->getUASName());
        this->uasId = mav->getUASID();

        updateMode(mav->getUASID(), mav->getUASMode());
        updateState(mav->getUASState());
        updateInput(mav->getInputMode());

        // Connect user interface controls
        connect(ui.controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));
        connect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        connect(mav, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        connect(mav, SIGNAL(mouseButtonRotationChanged(bool)), this, SLOT(changeMouseRotationEnabled(bool)));
        connect(mav, SIGNAL(mouseButtonTranslationChanged(bool)), this, SLOT(changeMouseTranslationEnabled(bool)));
        connect(mav, SIGNAL(batteryLow(double)), this, SLOT(alertBatteryLow(double)));

        connect(this, SIGNAL(changedInput(SkyeMAV::QGC_INPUT_MODE)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE)));
        connect(mav, SIGNAL(inputModeChanged(SkyeMAV::QGC_INPUT_MODE)), this, SLOT(updateInput(SkyeMAV::QGC_INPUT_MODE)));
        connect(this, SIGNAL(changedSensitivityTransFactor(float)), mav, SLOT(setSensitivityFactorTrans(float)));
        connect(this, SIGNAL(changedSensitivityRotFactor(float)), mav, SLOT(setSensitivityFactorRot(float)));
        connect(this, SIGNAL(changedLiftFactor(float)), mav, SLOT(setLiftFactor(float)));
        emit changedSensitivityTransFactor(sensitivityFactorTrans);
        emit changedSensitivityRotFactor(sensitivityFactorRot);
        if (liftFactorEnabled) {
            emit changedLiftFactor(liftFactor);
        }
    }


#endif // QGC_USE_SKYE_INTERFACE
}

UASSkyeControlWidget::~UASSkyeControlWidget()
{
#ifdef QGC_USE_SKYE_INTERFACE
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::updateStatemachine()
{
#ifdef QGC_USE_SKYE_INTERFACE

    if (engineOn)
    {
        ui.controlButton->setText(tr("DISARM SYSTEM"));
        ui.controlButton->setStyleSheet("* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); border-color: yellow; color: yellow }");
        setInputButtonActivity(false);
    }
    else
    {
        ui.controlButton->setText(tr("ARM SYSTEM"));
        ui.controlButton->setStyleSheet("* { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); }");
        setInputButtonActivity(true);
    }
#endif // QGC_USE_SKYE_INTERFACE
}

///**
// * Set the background color based on the MAV color. If the MAV is selected as the
// * currently actively controlled system, the frame color is highlighted
// */
//void UASSkyeControlWidget::setBackgroundColor(QColor color)
//{
//#ifdef QGC_USE_SKYE_INTERFACE
//    // UAS color
//    QColor uasColor = color;
//    QString colorstyle;
//    QString borderColor = "#4A4A4F";
//    borderColor = "#FA4A4F";
//    uasColor = uasColor.darker(900);
//    colorstyle = colorstyle.sprintf("QLabel { border-radius: 3px; padding: 0px; margin: 0px; background-color: #%02X%02X%02X; border: 0px solid %s; }",
//                                    uasColor.red(), uasColor.green(), uasColor.blue(), borderColor.toStdString().c_str());
//    setStyleSheet(colorstyle);
//    QPalette palette = this->palette();
//    palette.setBrush(QPalette::Window, QBrush(uasColor));
//    setPalette(palette);
//    setAutoFillBackground(true);
//#endif // QGC_USE_SKYE_INTERFACE
//}

void UASSkyeControlWidget::updateMode(int uas,int baseMode)
{
    qDebug() << "Got uas mode:" << baseMode;
#ifdef QGC_USE_SKYE_INTERFACE
    if ((uasId == uas) && ((int)uasMode != baseMode))
    {
        uasMode = (unsigned int)baseMode;
        QString green = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #004433, stop: 1 #228822)}";
        QString gray  = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #999999, stop: 1 #444444)}";
		if (uasMode == MAV_MODE_PREFLIGHT)
        {
            ui.directControlButton->setStyleSheet(gray);
            ui.rateControlButton->setStyleSheet(gray);
            ui.attitudeControlButton->setStyleSheet(gray);
		}
        if ((uasMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL) || (uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE))
        {
            ui.directControlButton->setStyleSheet(green);
		} else {
            ui.directControlButton->setStyleSheet(gray);
		}


		if (uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE)
		{
			if (uasMode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE)
			{
                ui.rateControlButton->setStyleSheet(green);
                ui.attitudeControlButton->setStyleSheet(gray);
			} else {
                ui.rateControlButton->setStyleSheet(green);
                ui.attitudeControlButton->setStyleSheet(green);
			}
        } else {
            ui.rateControlButton->setStyleSheet(gray);
            ui.attitudeControlButton->setStyleSheet(gray);
        }

//        case MAV_MODE_HALF_AUTOMATIC_DISARMED:
//        case MAV_MODE_HALF_AUTOMATIC_ARMED:
//        {
//            ui.halfAutomaticControlButton->setChecked(true);
//        }break;
//        case MAV_MODE_FULL_AUTOMATIC_DISARMED:
//        case MAV_MODE_FULL_AUTOMATIC_ARMED:
//        {
//            ui.fullAutomaticControlButton->setChecked(true);
//        }break;
//        default:
//        {
//            uncheckAllModeButtons();
//        }break;
//        }


    }
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::updateState(int state)
{
#ifdef QGC_USE_SKYE_INTERFACE
    switch (state)
    {
    case (int)MAV_STATE_ACTIVE:
        engineOn = true;
        break;
    case (int)MAV_STATE_STANDBY:
        engineOn = false;
        break;
    }
    updateStatemachine();
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::updateInput(SkyeMAV::QGC_INPUT_MODE input)
{
#ifdef QGC_USE_SKYE_INTERFACE
    switch ((int)input)
    {
    case (int)SkyeMAV::QGC_INPUT_MODE_NONE:
        inputButtonGroup->setExclusive(false);
        ui.mouseButton->setChecked(false);
        ui.touchButton->setChecked(false);
        ui.keyboardButton->setChecked(false);
        inputButtonGroup->setExclusive(true);
        break;
    case (int)SkyeMAV::QGC_INPUT_MODE_MOUSE:
        ui.mouseButton->setChecked(true);
        break;
    case (int)SkyeMAV::QGC_INPUT_MODE_TOUCH:
        ui.touchButton->setChecked(true);
        break;
    case (int)SkyeMAV::QGC_INPUT_MODE_KEYBOARD:
        ui.keyboardButton->setChecked(true);
        break;
    }
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setDirectControlMode()
{
#ifdef  QGC_USE_SKYE_INTERFACE

    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (engineOn) {

    if ( !(uasMode & MAV_MODE_FLAG_MANUAL_INPUT_ENABLED) || (uasMode & MAV_MODE_FLAG_STABILIZE_ENABLED) ) {
        // Set direct manual control (otherwise reset to PREFLIGHT)
        newMode = newMode | MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
    }

    transmitMode(newMode);

    QString white = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DDDDDD, stop: 1 #999999)}";
    ui.directControlButton->setStyleSheet(white);

    } else {
        ui.lastActionLabel->setText("Arm system first");
    }

#endif  // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setRateControlMode()
{
#ifdef QGC_USE_SKYE_INTERFACE
    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (engineOn) {
        newMode = newMode | MAV_MODE_FLAG_SAFETY_ARMED;

        if ( !(uasMode & MAV_MODE_FLAG_CUSTOM_MODE_ENABLED) ) {
            // Set rate control
            newMode |= MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
        } else {
            // Reset to direct manual control
            newMode |= MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
        }

        transmitMode(newMode);

        QString white = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DDDDDD, stop: 1 #999999)}";
        ui.rateControlButton->setStyleSheet(white);
    } else {
        ui.lastActionLabel->setText("Arm system first");
    }

#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setAttitudeControlMode()
{
#ifdef QGC_USE_SKYE_INTERFACE
    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (engineOn) {
        newMode = newMode | MAV_MODE_FLAG_SAFETY_ARMED;

        if ( (uasMode & MAV_MODE_FLAG_CUSTOM_MODE_ENABLED) || !(uasMode & MAV_MODE_FLAG_STABILIZE_ENABLED) ) {
            // Set attitude control
            newMode |= MAV_MODE_FLAG_STABILIZE_ENABLED;
        } else {
            // Reset to rate control
            newMode |= MAV_MODE_FLAG_CUSTOM_MODE_ENABLED | MAV_MODE_FLAG_STABILIZE_ENABLED;
        }

        transmitMode(newMode);

        QString white = "* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DDDDDD, stop: 1 #999999)}";
        ui.attitudeControlButton->setStyleSheet(white);

    } else {
        ui.lastActionLabel->setText("Arm system first");
    }

#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::mouseActivated(bool success)
{
    if (!success)
    {
        inputButtonGroup->setExclusive(false);
        ui.mouseButton->setChecked(false);
//        foreach(QAbstractButton *inputButton, inputButtonGroup->buttons())
//        {
//            inputButton->setChecked(false);
//        }
        inputButtonGroup->setExclusive(true);
    }
    qDebug() << "Mouse activated is" << success;
}

void UASSkyeControlWidget::setInputMouse(bool checked)
{
#ifdef QGC_USE_SKYE_INTERFACE
    if (checked)
    {
        inputMode = SkyeMAV::QGC_INPUT_MODE_MOUSE;
        emit changedInput(inputMode);
        ui.lastActionLabel->setText(tr("3dMouse activated!"));
    }
    updateStyleSheet();
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setInputTouch(bool checked)
{
#ifdef QGC_USE_SKYE_INTERFACE
    if (checked)
    {
        inputMode = SkyeMAV::QGC_INPUT_MODE_TOUCH;
        emit changedInput(inputMode);
        ui.lastActionLabel->setText(tr("Touchscreen activated!"));
    }
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setInputKeyboard(bool checked)
{
#ifdef QGC_USE_SKYE_INTERFACE
    if (checked)
    {
        inputMode = SkyeMAV::QGC_INPUT_MODE_KEYBOARD;
        emit changedInput(inputMode);
        ui.lastActionLabel->setText(tr("Keyboard activated!"));
    }
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::transmitMode(int mode)
{
#ifdef QGC_USE_SKYE_INTERFACE
    UASInterface* mav = UASManager::instance()->getUASForId(this->uasId);
    if (mav)
    {
        mav->setMode(mode);

        QString modeStr = UAS::getShortModeTextFor(mode);

        ui.lastActionLabel->setText(QString("Sent mode %1 to %2").arg(modeStr).arg(mav->getUASName()));
    }
    else
    {
        ui.lastActionLabel->setText("No UAS activated!");
    }
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::setInputButtonActivity(bool enabled)
{
    ui.mouseButton->setEnabled(enabled);
    ui.touchButton->setEnabled(enabled);
}

void UASSkyeControlWidget::cycleContextButton()
{
#ifdef QGC_USE_SKYE_INTERFACE
	SkyeMAV* mav = dynamic_cast<SkyeMAV*>(UASManager::instance()->getUASForId(this->uasId));
    if (mav)
    {
        if (!engineOn)
        {
//            if (uasMode)
//            {
                mav->armSystem();
                mav->setModeCommand(uasMode | MAV_MODE_FLAG_SAFETY_ARMED);

                ui.lastActionLabel->setText(QString("Enabled motors on %1").arg(mav->getUASName()));
//            } else {
//                ui.lastActionLabel->setText("Set mode before!");
//            }

        } else {
            mav->disarmSystem();
            mav->setModeCommand(0);
            ui.lastActionLabel->setText(QString("Disabled motors on %1").arg(mav->getUASName()));
        }
        // Update state now and in several intervals when MAV might have changed state
        updateStatemachine();

        QTimer::singleShot(50, this, SLOT(updateStatemachine()));
        QTimer::singleShot(200, this, SLOT(updateStatemachine()));

    }
#endif // QGC_USE_SKYE_INTERFACE
}

void UASSkyeControlWidget::updateStyleSheet()
{
    QString style = "";
    style.append("QPushButton { min-height: 30; }");
    if (ui.mouseButton->isChecked())
    {
//        qDebug() << "3dMouse TRANSLATION is: " << mouseTranslationEnabled << ", ROTATION is: " << mouseRotationEnabled;
        if (mouseTranslationEnabled && mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:images/skye_images/input/3dx_spacenavigator_200x198_trans_rot.png);}");
        }
        if (mouseTranslationEnabled && !mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:images/skye_images/input/3dx_spacenavigator_200x198_trans.png);}");
        }
        if (!mouseTranslationEnabled && mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:images/skye_images/input/3dx_spacenavigator_200x198_rot.png);}");
        }
        if (!mouseTranslationEnabled && !mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:images/skye_images/input/3dx_spacenavigator_200x198.png); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #AA0000, stop: 1 #FF0000);}");
        }
    }else{
        style.append("QPushButton#mouseButton {image: url(:images/skye_images/input/3dx_spacenavigator_200x198.png);}");
    }

    style.append("QPushButton#touchButton {image: url(:images/skye_images/input/FingerPointing.png);}");
    style.append("QPushButton#keyboardButton {image: url(:images/skye_images/input/keyboard-icon_64.png); }");
    style.append("QPushButton:disabled {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #BBBBBB, stop: 1 #444444); color: #333333 }");
    this->setStyleSheet(style);
}

void UASSkyeControlWidget::changeMouseTranslationEnabled(bool transEnabled)
{
    if (mouseTranslationEnabled != transEnabled)
    {
        mouseTranslationEnabled = transEnabled;
    }
    updateStyleSheet();
}

void UASSkyeControlWidget::changeMouseRotationEnabled(bool rotEnabled)
{
    if (mouseRotationEnabled != rotEnabled)
    {
        mouseRotationEnabled = rotEnabled;
    }
    updateStyleSheet();
}

void UASSkyeControlWidget::uncheckAllModeButtons()
{
////    modeButtonGroup->setExclusive(false);
//    QAbstractButton* checkedButton = modeButtonGroup->checkedButton();
//    if (checkedButton)
//    {
//        checkedButton->toggle();
//        ui.lastActionLabel->setText("No mode set!");
//    }
////    modeButtonGroup->setExclusive(true);
}

void UASSkyeControlWidget::setSensitivityFactorTrans(int val)
{
    sensitivityFactorTrans = (float)val*maxSensitivityFactorTrans/ui.sensitivityTransSlider->maximum();
    QString str = QString("Translation-Sensitivity: %1").arg(sensitivityFactorTrans);
    ui.sensitivityTransLabel->setText(str);
    int red = 16*16;
    int green = 16;
    int blue = 1;
    int colorStart = (int)(( 1+10*ui.sensitivityTransSlider->value()/ui.sensitivityTransSlider->maximum() ) * red + (  10*(ui.sensitivityTransSlider->maximum()-ui.sensitivityTransSlider->value())/ui.sensitivityTransSlider->maximum()) * green + 6 * blue);
    int colorEnd =   (int)(( 1+14*ui.sensitivityTransSlider->value()/ui.sensitivityTransSlider->maximum() ) * red + (  14*(ui.sensitivityTransSlider->maximum()-ui.sensitivityTransSlider->value())/ui.sensitivityTransSlider->maximum()) * green + 6 * blue);
//    qDebug() << "COLORS" << colorStart << colorEnd;
    QString style = QString("QSlider::sub-page:horizontal {border: 1px solid #bbb; border-radius: 4px; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #%1, stop: 1 #%2); }").arg(colorStart, 1, 16).arg(colorEnd, 1, 16);
    ui.sensitivityTransSlider->setStyleSheet(style);
    emit changedSensitivityTransFactor(sensitivityFactorTrans);
}

void UASSkyeControlWidget::setSensitivityFactorRot(int val)
{
    sensitivityFactorRot = (float)val*maxSensitivityFactorRot/ui.sensitivityRotSlider->maximum();
    QString str = QString("Rotation-Sensitivity: %1").arg(sensitivityFactorRot);
    ui.sensitivityRotLabel->setText(str);
    int red = 16*16;
    int green = 16;
    int blue = 1;
    int colorStart = (int)(( 1+10*ui.sensitivityRotSlider->value()/ui.sensitivityRotSlider->maximum() ) * red + (  10*(ui.sensitivityRotSlider->maximum()-ui.sensitivityRotSlider->value())/ui.sensitivityRotSlider->maximum()) * green + 6 * blue);
    int colorEnd =   (int)(( 1+14*ui.sensitivityRotSlider->value()/ui.sensitivityRotSlider->maximum() ) * red + (  14*(ui.sensitivityRotSlider->maximum()-ui.sensitivityRotSlider->value())/ui.sensitivityRotSlider->maximum()) * green + 6 * blue);
//    qDebug() << "COLORS" << colorStart << colorEnd;
    QString style = QString("QSlider::sub-page:horizontal {border: 1px solid #bbb; border-radius: 4px; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #%1, stop: 1 #%2); }").arg(colorStart, 1, 16).arg(colorEnd, 1, 16);
//    style.append("QSlider::groove:horizontal {border: 1px solid #bbb; border-radius: 4px;  background: qlineargradient(x1: 0, y1: %1, x2: 1, y2: %2, stop: 0 #6e6, stop: 1 #e66); }").arg((float)val/maxSensitivityFactorRot-0.1).arg((float)val/maxSensitivityFactorRot+0.1);
    ui.sensitivityRotSlider->setStyleSheet(style);
    emit changedSensitivityRotFactor(sensitivityFactorRot);
}

void UASSkyeControlWidget::setLiftFactor(int val)
{
    liftFactor = (float)val*maxLiftFactor/ui.liftSlider->maximum();

    int red = 16*16;
    int green = 16;
    int blue = 1;
    int colorStart = (int)(( 1+10*ui.liftSlider->value()/ui.liftSlider->maximum() ) * red + (  10*(ui.sensitivityRotSlider->maximum()-ui.sensitivityRotSlider->value())/ui.liftSlider->maximum()) * green + 6 * blue);
    int colorEnd =   (int)(( 1+14*ui.liftSlider->value()/ui.liftSlider->maximum() ) * red + (  14*(ui.sensitivityRotSlider->maximum()-ui.sensitivityRotSlider->value())/ui.liftSlider->maximum()) * green + 6 * blue);
    QString style = QString("QSlider::sub-page:horizontal {border: 1px solid #bbb; border-radius: 4px; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #%1, stop: 1 #%2); }").arg(colorStart, 1, 16).arg(colorEnd, 1, 16);
    ui.liftSlider->setStyleSheet(style);

    if (liftFactorEnabled) {
        emit changedLiftFactor(liftFactor);
        QString str = QString("Lift Factor: %1").arg(liftFactor);
        ui.liftLabel->setText(str);
    } else {
        emit changedLiftFactor(0.0f);
        QString str = QString("Lift Factor (DISABLED): %1").arg(liftFactor);
        ui.liftLabel->setText(str);
    }
}

void UASSkyeControlWidget::setLiftFactor(float val)
{
    setLiftFactor((int)((float)ui.liftSlider->maximum()/maxLiftFactor*val));
}

void UASSkyeControlWidget::setMaxLiftFactor(double max)
{
    maxLiftFactor = (float)max;
    ui.liftSlider->setValue(liftFactor/maxLiftFactor*ui.liftSlider->maximum());
}

void UASSkyeControlWidget::enableLiftFactor(bool enabled)
{
    liftFactorEnabled = enabled;
    setLiftFactor(liftFactor);
}

void UASSkyeControlWidget::alertBatteryLow(double voltage)
{
    if ( (lastAlertTime.elapsed() > 60000) || (alertedBatteryLow == false) )
    {
        lastAlertTime.restart();
        alertedBatteryLow = true;

        msgBox->showMessage("Battery low! Shut down system immediately.");
//        msgBox->exec();

//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setText(tr("BATTERY LOW"));
//        msgBox.setInformativeText(tr("Please shut down the system and charge the batteries."));
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.setDefaultButton(QMessageBox::Ok);
//        msgBox.exec();
    }
}
