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

#include "UASSkyeControlWidget.h"
#include "UASManager.h"
#include "QGC.h"

UASSkyeControlWidget::UASSkyeControlWidget(QWidget *parent) : QWidget(parent),
    ctrlMode(SKYE_CONTROL_MODE_NONE),
    mode5dof(false),
    uasId(0),
    baseMode(0),
    isArmed(false),
    inputMode(QGC_INPUT_MODE_NONE),
    mouseTranslationEnabled(true),
    mouseRotationEnabled(true),
    inputMixer(NULL)
{

    ui.setupUi(this);
    ui.manControlButton->setObjectName("manControlButtonGray");
    ui.stab5dofControlButton->setObjectName("stab5dofControlButtonGray");
    ui.stab6dofControlButton->setObjectName("stab6dofControlButtonGray");

    ui.manControlButton->setStyleSheet("");
    ui.stab5dofControlButton->setStyleSheet("");
    ui.stab6dofControlButton->setStyleSheet("");

    ui.armButton->setObjectName("armButtonGreen");
    ui.armButton->setStyleSheet("");

    ui.manControlButton->setCheckable(false);
    ui.stab5dofControlButton->setCheckable(false);
    ui.stab6dofControlButton->setCheckable(false);

    ui.mouseButton->setChecked(inputMode & QGC_INPUT_MODE_MOUSE);
    ui.touchButton->setChecked(inputMode & QGC_INPUT_MODE_TOUCH);
    ui.keyboardButton->setChecked(inputMode & QGC_INPUT_MODE_KEYBOARD);
    ui.xboxButton->setChecked(inputMode & QGC_INPUT_MODE_XBOX);

    ui.keyboardButton->hide();

    // tabbed info view widget
    infoViewWidget = new QGCTabbedInfoView(this);
    infoViewWidget->show();

    ui.advancedLayout->addWidget(infoViewWidget);

    this->setUAS(UASManager::instance()->getActiveUAS());
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    connect(ui.armButton, SIGNAL(clicked()), this, SLOT(setArmDisarmStatus()));
    connect(ui.manControlButton, SIGNAL(clicked()), this, SLOT(setManualControlMode()));
    connect(ui.stab5dofControlButton, SIGNAL(clicked()), this, SLOT(set5dofControlMode()));
    connect(ui.stab6dofControlButton, SIGNAL(clicked()), this, SLOT(set6dofControlMode()));

    connect(ui.mouseButton, SIGNAL(clicked(bool)), this, SLOT(setInputMouse(bool)));
    connect(ui.touchButton, SIGNAL(clicked(bool)), this, SLOT(setInputTouch(bool)));
    connect(ui.keyboardButton, SIGNAL(clicked(bool)), this, SLOT(setInputKeyboard(bool)));
    connect(ui.xboxButton, SIGNAL(clicked(bool)), this, SLOT(setInputXbox(bool)));

    updateInputButtonStyleSheet();

    // TODO: set correct margins instead of min height
    this->setMinimumHeight(220);

}

void UASSkyeControlWidget::setUAS(UASInterface* uas)
{
    qDebug() << "Slot set UAS called";
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        ui.lastActionLabel->setText("Disconnected from " + oldUAS->getUASName());
        this->uasId = 0;
        SkyeUAS* mav = dynamic_cast<SkyeUAS*>(oldUAS);
        if (mav)
        {
            disconnect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
            disconnect(mav, SIGNAL(statusChanged(int)), this, SLOT(updateArmingState(int)));
            disconnect(this, SIGNAL(changedInput(QGC_INPUT_MODE, bool)), mav, SLOT(setInputMode(QGC_INPUT_MODE, bool)));
            disconnect(mav, SIGNAL(inputModeChanged(int)), this, SLOT(updateInput(int)));

            disconnect(mav, SIGNAL(mouseButtonRotationChanged(bool)), this, SLOT(changeMouseRotationEnabled(bool)));
            disconnect(mav, SIGNAL(mouseButtonTranslationChanged(bool)), this, SLOT(changeMouseTranslationEnabled(bool)));

            disconnect(inputMixer, SIGNAL(changed6DOFInput(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));

            // Disconnect slots for Change of Actuation Unit Configuration
            disconnect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocCase(int)));
            disconnect(mav, SIGNAL(mode5dofChanged(int)), this, SLOT(updateMode5dof(int)));


            // stop input mixer
            if (inputMixer)
            {
                inputMixer->terminate();
                inputMixer = NULL;
            }
        }
    }


    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(uas);
    if (mav)
    {
        ui.lastActionLabel->setText(tr("Connected to ") + mav->getUASName());
        this->uasId = mav->getUASID();
        qDebug() << "UAS id:" << mav->getUASID() << ", name:" << mav->getUASName();

        updateMode(mav->getUASID(), mav->getMode());
        updateArmingState(mav->getState());
        updateInput(mav->getInputMode());

        // start input mixer
        inputMixer = new UASSkyeInputMixer(this);
        inputMixer->init();
        inputMixer->start();

        // Connect user interface controls
        connect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        connect(mav, SIGNAL(statusChanged(int)), this, SLOT(updateArmingState(int)));

        connect(this, SIGNAL(changedInput(QGC_INPUT_MODE, bool)), mav, SLOT(setInputMode(QGC_INPUT_MODE, bool)));
        connect(mav, SIGNAL(inputModeChanged(int)), this, SLOT(updateInput(int)));
        connect(mav, SIGNAL(resetMouseInput(bool)), this, SLOT(updateMouseInput(bool)));

        connect(inputMixer, SIGNAL(changed6DOFInput(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));

        // Connect slots for onboard parameter changes
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocCase(int)));
        connect(mav, SIGNAL(mode5dofChanged(int)), this, SLOT(updateMode5dof(int)));

    }
}

UASSkyeControlWidget::~UASSkyeControlWidget()
{
}

void UASSkyeControlWidget::updateArmButtonStyleSheet()
{
    if (isArmed)
    {
        ui.armButton->setText(tr("DISARM SYSTEM"));
        ui.armButton->setObjectName("armButtonRed");
    }
    else
    {
        ui.armButton->setText(tr("ARM SYSTEM"));
        ui.armButton->setObjectName("armButtonGreen");
    }

    // update stylesheet
    ui.armButton->setStyleSheet("");
}


void UASSkyeControlWidget::updateMode(int uas, int baseMode)
{
    // qDebug() << "Got uas mode:" << baseMode;
    this->baseMode = baseMode;

    bool modeChanged = false;
    if (uasId == uas) {
        if (baseMode & MAV_MODE_FLAG_MANUAL_INPUT_ENABLED) {


            if (baseMode & MAV_MODE_FLAG_STABILIZE_ENABLED) {
                // STABILIZED MODE (6DOF or 5DOF)
                if (mode5dof == false) {
                    if (ctrlMode != SKYE_CONTROL_MODE_6DOF) {
                        ctrlMode  = SKYE_CONTROL_MODE_6DOF;
                        modeChanged = true;
                    }
                } else {
                    if (ctrlMode != SKYE_CONTROL_MODE_5DOF) {
                        ctrlMode  = SKYE_CONTROL_MODE_5DOF;
                        modeChanged = true;
                    }
                }
            } else {


                // MANUAL MODE
                if (ctrlMode != SKYE_CONTROL_MODE_MANUAL) {
                    ctrlMode  = SKYE_CONTROL_MODE_MANUAL;
                    modeChanged = true;
                }
            }
        }
    }
    updateModeStyleSheet();
}


void UASSkyeControlWidget::updateMode5dof(int mode5dof)
{
    this->mode5dof = mode5dof;
    updateMode(this->uasId, this->baseMode);
}

void UASSkyeControlWidget::updateModeStyleSheet()
{
    // Set stylesheets to display active mode

    ui.manControlButton->setObjectName("manControlButtonGray");
    ui.stab5dofControlButton->setObjectName("stab5dofControlButtonGray");
    ui.stab6dofControlButton->setObjectName("stab6dofControlButtonGray");

    switch (ctrlMode) {
    case SKYE_CONTROL_MODE_MANUAL:
        ui.manControlButton->setObjectName("manControlButtonGreen");
        break;
    case SKYE_CONTROL_MODE_5DOF:
        ui.manControlButton->setObjectName("stab5dofControlButtonGreen");
        break;
    case SKYE_CONTROL_MODE_6DOF:
        ui.manControlButton->setObjectName("stab6dofControlButtonGreen");
        break;
    case SKYE_CONTROL_MODE_NONE:
    default:
        break;
    }

    // update style sheets
    ui.manControlButton->setStyleSheet("");
    ui.stab5dofControlButton->setStyleSheet("");
    ui.stab6dofControlButton->setStyleSheet("");
}

void UASSkyeControlWidget::updateArmingState(int state)
{
    switch (state)
    {
    case (int)MAV_STATE_ACTIVE:
        isArmed = true;
        break;
    case (int)MAV_STATE_STANDBY:
        isArmed = false;
        break;
    }
    updateArmButtonStyleSheet();
}

void UASSkyeControlWidget::updateInput(int input)
{
	qDebug() << "[UASSkyeControl] changing input from" << inputMode << "to" << input;

    // Update last-action-label when input mode has changed
    if ( (inputMode & QGC_INPUT_MODE_MOUSE) != (input & QGC_INPUT_MODE_MOUSE) )
    {
        if (input & QGC_INPUT_MODE_MOUSE)
        {
            ui.lastActionLabel->setText("3dMouse input activated.");
        } else {
            ui.lastActionLabel->setText("3dMouse input deactivated.");
        }
    }

    if ( (inputMode & QGC_INPUT_MODE_TOUCH) != (input & QGC_INPUT_MODE_TOUCH) )
    {
        if (input & QGC_INPUT_MODE_TOUCH)
        {
            ui.lastActionLabel->setText("Touch input activated.");
        } else {
            ui.lastActionLabel->setText("Touch input deactivated.");
        }
    }

    if ( (inputMode & QGC_INPUT_MODE_XBOX) != (input & QGC_INPUT_MODE_XBOX) )
    {
        if (input & QGC_INPUT_MODE_XBOX)
        {
            ui.lastActionLabel->setText("Xbox input activated.");
        } else {
            ui.lastActionLabel->setText("Xbox input deactivated.");
        }
    }

    ui.mouseButton->setChecked(input & QGC_INPUT_MODE_MOUSE);
    ui.touchButton->setChecked(input & QGC_INPUT_MODE_TOUCH);
    ui.keyboardButton->setChecked(input & QGC_INPUT_MODE_KEYBOARD);
    ui.xboxButton->setChecked(input & QGC_INPUT_MODE_XBOX);

    inputMode = input;

    updateInputButtonStyleSheet();
}

void UASSkyeControlWidget::updateMouseInput(bool active)
{
    ui.mouseButton->setChecked(active);
    if (active)
    {
        // 3d mouse has successfully been started
        ui.lastActionLabel->setText("3dMouse started");

        if ((inputMode & QGC_INPUT_MODE_MOUSE) == false)
        {
            inputMode += QGC_INPUT_MODE_MOUSE;
        }

    } else {
        // 3d mouse starting not succeeded. User must push the button again
        ui.lastActionLabel->setText("3dMouse was not initialized. Click again to activate...");

        if ((inputMode & QGC_INPUT_MODE_MOUSE) == true)
        {
            inputMode -= QGC_INPUT_MODE_MOUSE;
        }
    }
}

void UASSkyeControlWidget::setManualControlMode()
{
    if (isArmed) {
        uint8_t newMode = MAV_MODE_FLAG_SAFETY_ARMED;

        newMode |= MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
        transmitMode(newMode);

        if (ctrlMode != SKYE_CONTROL_MODE_MANUAL) {
            ui.manControlButton->setObjectName("manControlButtonWhite");
            ui.manControlButton->setStyleSheet("");
        }

    } else {
        ui.lastActionLabel->setText("Arm system first");
    }

}

void UASSkyeControlWidget::set5dofControlMode()
{
    if (isArmed) {
        uint8_t newMode = MAV_MODE_FLAG_SAFETY_ARMED;

        // Set rate control
        newMode |= MAV_MODE_FLAG_STABILIZE_ENABLED;
        transmitMode(newMode);

        if (ctrlMode != SKYE_CONTROL_MODE_5DOF) {
            ui.stab5dofControlButton->setObjectName("stab5dofControlButtonWhite");
            ui.stab5dofControlButton->setStyleSheet("");
        }
    } else {
        ui.lastActionLabel->setText("Arm system first");
    }
}

void UASSkyeControlWidget::set6dofControlMode()
{
    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (isArmed) {
        newMode = newMode | MAV_MODE_FLAG_SAFETY_ARMED;
        // Set attitude control
        newMode |= MAV_MODE_FLAG_STABILIZE_ENABLED;
        transmitMode(newMode);

        if (ctrlMode != SKYE_CONTROL_MODE_6DOF) {
            ui.stab6dofControlButton->setObjectName("stab6dofControlButtonWhite");
            ui.stab6dofControlButton->setStyleSheet("");
        }

    } else {
        ui.lastActionLabel->setText("Arm system first");
    }
}

void UASSkyeControlWidget::setInputMouse(bool checked)
{
	if (checked)
	{
        ui.lastActionLabel->setText(tr("Starting 3dMouse..."));
	} else {
        ui.lastActionLabel->setText(tr("Stopping 3dMouse..."));
	}
    emit changedInput(QGC_INPUT_MODE_MOUSE, checked);

}

void UASSkyeControlWidget::setInputTouch(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Activating Touchscreen..."));
    } else {
        ui.lastActionLabel->setText(tr("Deactivating Touchscreen..."));
    }

    emit changedInput(QGC_INPUT_MODE_TOUCH, checked);
}

void UASSkyeControlWidget::setInputKeyboard(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Activating Keyboard..."));
    } else {
        ui.lastActionLabel->setText(tr("Deactivating Keyboard..."));
    }

    emit changedInput(QGC_INPUT_MODE_KEYBOARD, checked);
}

void UASSkyeControlWidget::setInputXbox(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Activating Xbox Controller..."));
    } else {
        ui.lastActionLabel->setText(tr("Deactivating Xbox Controller..."));
    }

    emit changedInput(QGC_INPUT_MODE_XBOX, checked);
}

void UASSkyeControlWidget::transmitMode(int mode)
{
    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(UASManager::instance()->getUASForId(this->uasId));
    if (mav)
    {
        mav->setModeCommand(mode);

        QString modeStr = mav->getShortModeTextFor(mode, 0);
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

void UASSkyeControlWidget::setArmDisarmStatus()
{
	SkyeUAS* mav = dynamic_cast<SkyeUAS*>(UASManager::instance()->getUASForId(this->uasId));
    if (mav)
    {
        if (!isArmed)
        {
//            mav->armSystem();
            mav->setModeArm(MAV_MODE_MANUAL_ARMED, 0);
            ui.lastActionLabel->setText(QString("Requested arming of %1").arg(mav->getUASName()));
        } else {
//            mav->disarmSystem();
            mav->setMode(MAV_MODE_MANUAL_DISARMED, 0);
            ui.lastActionLabel->setText(QString("Requested disarming of %1").arg(mav->getUASName()));
        }
    }
}

void UASSkyeControlWidget::updateInputButtonStyleSheet()
{
    QString style = "";
    style.append("QPushButton { min-height: 30; }");
    if (inputMode == QGC_INPUT_MODE_MOUSE)
    {
		qDebug() << "3dMouse TRANSLATION is: " << mouseTranslationEnabled << ", ROTATION is: " << mouseRotationEnabled;
        if (mouseTranslationEnabled && mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:/res/input/3dmouse_trans_rot.png);}");
        }
        if (mouseTranslationEnabled && !mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:/res/input/3dmouse_trans.png);}");
        }
        if (!mouseTranslationEnabled && mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:/res/input/3dmouse_rot.png);}");
        }
        if (!mouseTranslationEnabled && !mouseRotationEnabled)
        {
            style.append("QPushButton#mouseButton {image: url(:/res/input/3dmouse.png); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #AA0000, stop: 1 #FF0000);}");
        }
    }else{
        style.append("QPushButton#mouseButton {image: url(:/res/input/3dmouse.png);}");
    }
    style.append("QPushButton#touchButton {image: url(:/res/input/touch.png);}");
    style.append("QPushButton#keyboardButton {image: url(:/res/input/keyboard.png); }");
    style.append("QPushButton#xboxButton {image: url(:/res/input/xbox.png); }");
    style.append("QPushButton:disabled {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #BBBBBB, stop: 1 #444444); color: #333333 }");
    this->setStyleSheet(style);
}

void UASSkyeControlWidget::changeMouseTranslationEnabled(bool transEnabled)
{
    if (mouseTranslationEnabled != transEnabled)
    {
        mouseTranslationEnabled = transEnabled;
        if (!transEnabled)
        {
            ui.lastActionLabel->setText("Deactivated translational inputs.");
        } else
        {
            ui.lastActionLabel->setText("Activated translational inputs.");
        }
    }
    updateInputButtonStyleSheet();
}

void UASSkyeControlWidget::changeMouseRotationEnabled(bool rotEnabled)
{
    if (mouseRotationEnabled != rotEnabled)
    {
        mouseRotationEnabled = rotEnabled;
        if (!rotEnabled)
        {
            ui.lastActionLabel->setText("Deactivated rotational inputs.");
        } else
        {
            ui.lastActionLabel->setText("Activated rotational inputs.");
        }
    }
    updateInputButtonStyleSheet();
}

void UASSkyeControlWidget::getMouse6DOFControlCommands(double x, double y, double z, double a, double b, double c)
{
    if (inputMode & QGC_INPUT_MODE_MOUSE)
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
        inputMixer->updateMouseValues(x, y, z, a, b, c);
    }
}

void UASSkyeControlWidget::getXboxControlCommands(double x, double y, double z, double a, double b, double c)
{
    if (inputMode & QGC_INPUT_MODE_XBOX)
    {
        inputMixer->updateXboxValues(x, y, z, a, b, c);
    }
}

void UASSkyeControlWidget::updateAllocCase(int allocCase)
{
    ui.lastActionLabel->setText(QString("Set allocation case %1").arg(allocCase));
}
