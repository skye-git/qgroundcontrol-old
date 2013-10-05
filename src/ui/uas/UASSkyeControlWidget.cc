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
    sensitivityFactorTrans(0.5),
    sensitivityFactorRot(0.5),
    liftFactor(0.0f),
    enabledAdvancedSettings(false)
{
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

    connect(ui.advancedCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleAdvancedSettings(bool)));

    advancedWidget = new UASSkyeControlAdvancedWidget(this);
    advancedWidget->hide();
    ledWidget = new LedControlWidget(this);
    ledWidget->hide();
    infoViewWidget = new QGCTabbedInfoView(this);
    infoViewWidget->show();

    ui.advancedLayout->addWidget(advancedWidget);
    ui.advancedLayout->addWidget(ledWidget);
    ui.advancedLayout->addWidget(infoViewWidget);

    // Multiplication factor for translational commands
    advancedWidget->setSliderValues(sensitivityFactorTrans, sensitivityFactorRot, liftFactor);
    connect(advancedWidget, SIGNAL(transSliderValueChanged(double)), this, SLOT(setSensitivityFactorTrans(double)));
    connect(advancedWidget, SIGNAL(rotSliderValueChanged(double)), this, SLOT(setSensitivityFactorRot(double)));
    connect(advancedWidget, SIGNAL(liftSliderValueChanged(double)), this, SLOT(setLiftFactor(double)));

    //ui.gridLayout->setAlignment(Qt::AlignTop);

    updateStyleSheet();

    // TODO: set correct margins instead of min height
    this->setMinimumHeight(220);

    lastAlertTime.start();
    alertedBatteryLow = false;
    msgBox = new QErrorMessage;
}

void UASSkyeControlWidget::setUAS(UASInterface* uas)
{
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
            disconnect(this, SIGNAL(changedSensitivityTransFactor(float)), mav, SLOT(setSensitivityFactorTrans(float)));
            disconnect(this, SIGNAL(changedSensitivityRotFactor(float)), mav, SLOT(setSensitivityFactorRot(float)));
            disconnect(this, SIGNAL(changedLiftFactor(float)), mav, SLOT(setLiftFactor(float)));
            disconnect(this, SIGNAL(changed6DOFControlCommands(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        //ui.controlStatusLabel->setText(tr("Connected to ") + mav->getUASName());
        this->uasId = mav->getUASID();

        updateMode(mav->getUASID(), mav->getMode());
        updateState(mav->getState());
        updateInput(mav->getInputMode());

        // Connect user interface controls
        connect(ui.controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));
        connect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        connect(mav, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        connect(mav, SIGNAL(batteryLow(double)), this, SLOT(alertBatteryLow(double)));

        connect(this, SIGNAL(changedInput(SkyeMAV::QGC_INPUT_MODE)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE)));
        connect(mav, SIGNAL(inputModeChanged(SkyeMAV::QGC_INPUT_MODE)), this, SLOT(updateInput(SkyeMAV::QGC_INPUT_MODE)));
        connect(this, SIGNAL(changedSensitivityTransFactor(float)), mav, SLOT(setSensitivityFactorTrans(float)));
        connect(this, SIGNAL(changedSensitivityRotFactor(float)), mav, SLOT(setSensitivityFactorRot(float)));
        connect(this, SIGNAL(changedLiftFactor(float)), mav, SLOT(setLiftFactor(float)));
        connect(this, SIGNAL(changed6DOFControlCommands(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
        emit changedSensitivityTransFactor((float)sensitivityFactorTrans);
        emit changedSensitivityRotFactor((float)sensitivityFactorRot);
        emit changedLiftFactor((float)liftFactor);
    }

}

UASSkyeControlWidget::~UASSkyeControlWidget()
{
}

void UASSkyeControlWidget::updateStatemachine()
{
    if (engineOn)
    {
        ui.controlButton->setText(tr("DISARM SYSTEM"));
        ui.controlButton->setStyleSheet("* {  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #DD0044, stop: 1 #AA0022); border-color: yellow; color: yellow }");
        //setInputButtonActivity(false);
    }
    else
    {
        ui.controlButton->setText(tr("ARM SYSTEM"));
        ui.controlButton->setStyleSheet("* { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00DD44, stop: 1 #11AA22); }");
        //setInputButtonActivity(true);
    }
}


void UASSkyeControlWidget::updateMode(int uas,int baseMode)
{
//    qDebug() << "Got uas mode:" << baseMode;
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
}

void UASSkyeControlWidget::updateState(int state)
{
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
}

void UASSkyeControlWidget::updateInput(SkyeMAV::QGC_INPUT_MODE input)
{
    switch ((int)input)
    {
    case (int)SkyeMAV::QGC_INPUT_MODE_NONE:
        inputButtonGroup->setExclusive(false);
        ui.mouseButton->setChecked(false);
        ui.touchButton->setChecked(false);
        ui.keyboardButton->setChecked(false);
        inputButtonGroup->setExclusive(true);
        ui.lastActionLabel->setText("No input set");
        break;
    case (int)SkyeMAV::QGC_INPUT_MODE_MOUSE:
        ui.mouseButton->setChecked(true);
        ui.lastActionLabel->setText("Mouse input set");
        break;
    case (int)SkyeMAV::QGC_INPUT_MODE_TOUCH:
        ui.touchButton->setChecked(true);
        ui.lastActionLabel->setText("Touch input set");
        break;
    case (int)SkyeMAV::QGC_INPUT_MODE_KEYBOARD:
        ui.keyboardButton->setChecked(true);
        ui.lastActionLabel->setText("Keyboard input set");
        break;
    }
}

void UASSkyeControlWidget::setDirectControlMode()
{
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

}

void UASSkyeControlWidget::setRateControlMode()
{
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
}

void UASSkyeControlWidget::setAttitudeControlMode()
{
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
    if (checked)
    {
        ui.lastActionLabel->setText(tr("3dMouse activated!"));
        inputMode = SkyeMAV::QGC_INPUT_MODE_MOUSE;
        emit changedInput(inputMode);
    }
    updateStyleSheet();
}

void UASSkyeControlWidget::setInputTouch(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Touchscreen activated!"));
        inputMode = SkyeMAV::QGC_INPUT_MODE_TOUCH;
        emit changedInput(inputMode);
    }
}

void UASSkyeControlWidget::setInputKeyboard(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Keyboard activated!"));
        inputMode = SkyeMAV::QGC_INPUT_MODE_KEYBOARD;
        emit changedInput(inputMode);
    }
}

void UASSkyeControlWidget::transmitMode(int mode)
{
    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(UASManager::instance()->getUASForId(this->uasId));
    if (mav)
    {
        mav->setModeCommand(mode);

        QString modeStr = UAS::getShortModeTextFor(mode, 0, MAV_AUTOPILOT_PX4);
        ui.lastActionLabel->setText(QString("Sent mode %1 to %2").arg(modeStr).arg(mav->getUASName()));

        qDebug() << "Send mode" << modeStr << "to" << mav->getUASName();
    }
    else
    {
        ui.lastActionLabel->setText("No Skye activated!");
    }
}

void UASSkyeControlWidget::setInputButtonActivity(bool enabled)
{
    ui.mouseButton->setEnabled(enabled);
    ui.touchButton->setEnabled(enabled);
}

void UASSkyeControlWidget::cycleContextButton()
{
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
            style.append("QPushButton#mouseButton {image: url(:files/images/skye/input/3dx_spacenavigator_200x198_trans_rot.png);}");
        }
        if (mouseTranslationEnabled && !mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:files/images/skye/input/3dx_spacenavigator_200x198_trans.png);}");
        }
        if (!mouseTranslationEnabled && mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:files/images/skye/input/3dx_spacenavigator_200x198_rot.png);}");
        }
        if (!mouseTranslationEnabled && !mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:files/images/skye/input/3dx_spacenavigator_200x198.png); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #AA0000, stop: 1 #FF0000);}");
        }
    }else{
        style.append("QPushButton#mouseButton {image: url(:files/images/skye/input/3dx_spacenavigator_200x198.png);}");
    }

    style.append("QPushButton#touchButton {image: url(:files/images/skye/input/FingerPointing.png);}");
    style.append("QPushButton#keyboardButton {image: url(:files/images/skye/input/keyboard-icon_64.png); }");
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

void UASSkyeControlWidget::getMouse6DOFControlCommands(double x, double y, double z, double a, double b, double c)
{
    if (inputMode == SkyeMAV::QGC_INPUT_MODE_MOUSE)
    {
        if (!mouseTranslationEnabled)
        {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
        if (!mouseRotationEnabled)
        {
            a = 0.0;
            b = 0.0;
            c = 0.0;
        }
        emit changed6DOFControlCommands(x, y, z, a, b, c);
    }
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

void UASSkyeControlWidget::setSensitivityFactorTrans(double val)
{
    sensitivityFactorTrans = val;

    emit changedSensitivityTransFactor((float)sensitivityFactorTrans);
}

void UASSkyeControlWidget::setSensitivityFactorRot(double val)
{
    sensitivityFactorRot = val;

    emit changedSensitivityRotFactor((float)sensitivityFactorRot);
}

void UASSkyeControlWidget::setLiftFactor(double val)
{
    liftFactor = val;

    emit changedLiftFactor((float)liftFactor);

}

void UASSkyeControlWidget::toggleAdvancedSettings(bool enabled)
{
    enabledAdvancedSettings = enabled;

    if (enabled) {
        advancedWidget->show();
        ledWidget->show();
        //ui.advancedButton->setText("Hide advanced settings");
        infoViewWidget->hide();
    } else {
        advancedWidget->hide();
        ledWidget->hide();
        //ui.advancedCheckBox->setText("Show advanced settings");
        infoViewWidget->show();
    }
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
