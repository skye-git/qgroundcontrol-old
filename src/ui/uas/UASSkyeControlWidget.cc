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


enum PX4_CUSTOM_MAIN_MODE {
    PX4_CUSTOM_MAIN_MODE_MANUAL = 1,
    PX4_CUSTOM_MAIN_MODE_ALTCTL,
    PX4_CUSTOM_MAIN_MODE_POSCTL,
    PX4_CUSTOM_MAIN_MODE_AUTO,
    PX4_CUSTOM_MAIN_MODE_ACRO,
    PX4_CUSTOM_MAIN_MODE_OFFBOARD,
    PX4_CUSTOM_MAIN_MODE_STABILIZED,
};

enum PX4_CUSTOM_SUB_MODE_AUTO {
    PX4_CUSTOM_SUB_MODE_AUTO_READY = 1,
    PX4_CUSTOM_SUB_MODE_AUTO_TAKEOFF,
    PX4_CUSTOM_SUB_MODE_AUTO_LOITER,
    PX4_CUSTOM_SUB_MODE_AUTO_MISSION,
    PX4_CUSTOM_SUB_MODE_AUTO_RTL,
    PX4_CUSTOM_SUB_MODE_AUTO_LAND,
    PX4_CUSTOM_SUB_MODE_AUTO_RTGS
};

union px4_custom_mode {
    struct {
        uint16_t reserved;
        uint8_t main_mode;
        uint8_t sub_mode;
    };
    uint32_t data;
    float data_float;
};

UASSkyeControlWidget::UASSkyeControlWidget(QWidget *parent) : QWidget(parent),
    controlMode(SKYE_CONTROL_MODE_MAX),
    uas(NULL),
    baseMode(0),
    isArmed(false),
    inputMode(QGC_INPUT_MODE_NONE),
    mouseAvailable(false),
    mouseTranslationEnabled(false),
    mouseRotationEnabled(false),
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
#ifndef QGC_MOUSE_ENABLED_LINUX
    ui.mouseButton->setEnabled(false);
#endif
    ui.touchButton->setEnabled(false);
    ui.xboxButton->setEnabled(false);

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
    updateControlModeStyleSheet();
    updateArmButtonStyleSheet();

    // TODO: set correct margins instead of min height
    this->setMinimumHeight(220);

}

void UASSkyeControlWidget::setUAS(UASInterface* uas)
{
    if (this->uas!= NULL) {
        // Disconnect old system
        ui.lastActionLabel->setText("Disconnected from " + this->uas->getUASName());
        SkyeUAS* mav = dynamic_cast<SkyeUAS*>(this->uas);
        if (mav)
        {
            disconnect(mav, SIGNAL(armingChanged(bool)), this, SLOT(updateArmingState(bool)));

            disconnect(inputMixer, SIGNAL(changed6DOFInput(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));

            // Disconnect slots for Change of Actuation Unit Configuration
            disconnect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocCase(int)));
            disconnect(mav, SIGNAL(skyeControlModeChanged(SKYE_CONTROL_MODE)), this, SLOT(updateControlMode(SKYE_CONTROL_MODE)));
            this->uas = NULL;

            // stop input mixer
            if (inputMixer)
            {
                inputMixer->terminate();
                inputMixer = NULL;
            }
        }
    }

    // Connect new system
    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(uas);
    if (mav) {
        ui.lastActionLabel->setText(tr("Connected to ") + mav->getUASName());
        this->uas = uas;
        qDebug() << "UAS id:" << mav->getUASID() << ", name:" << mav->getUASName();

        //updateControlMode(mav->getControlMode);
        updateArmingState(mav->isArmed());

        // start input mixer
        inputMixer = new UASSkyeInputMixer(this);
        inputMixer->init();
        inputMixer->start();

        // Connect user interface controls
        connect(mav, SIGNAL(armingChanged(bool)), this, SLOT(updateArmingState(bool)));

        connect(inputMixer, SIGNAL(changed6DOFInput(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));

        // Connect slots for onboard parameter changes
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(updateAllocCase(int)));
        connect(mav, SIGNAL(skyeControlModeChanged(SKYE_CONTROL_MODE)), this, SLOT(updateControlMode(SKYE_CONTROL_MODE)));

        // Request parameters
        mav->requestParameters();
    }

    // start always with MANUAL mode
    setManualControlMode();
}

UASSkyeControlWidget::~UASSkyeControlWidget()
{
}


void UASSkyeControlWidget::updateArmingState(bool armed)
{
    isArmed = armed;

    updateArmButtonStyleSheet();
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

void UASSkyeControlWidget::updateControlMode(SKYE_CONTROL_MODE ctrlMode)
{
    // only update GUI if control mode has changed
    if (this->controlMode != ctrlMode) {
        this->controlMode = ctrlMode;
        qDebug() << "Control mode is now" << getControlModeString(ctrlMode);
        updateControlModeStyleSheet();
    } else {
        qDebug() << "Control mode is already" << getControlModeString(ctrlMode);
    }
}

void UASSkyeControlWidget::updateControlModeStyleSheet()
{
    // Set stylesheets to display active mode

    ui.manControlButton->setObjectName("manControlButtonGray");
    ui.stab5dofControlButton->setObjectName("stab5dofControlButtonGray");
    ui.stab6dofControlButton->setObjectName("stab6dofControlButtonGray");

    switch (controlMode) {
    case SKYE_CONTROL_MODE_MANUAL:
        ui.manControlButton->setObjectName("manControlButtonGreen");
        break;
    case SKYE_CONTROL_MODE_5DOF:
        ui.stab5dofControlButton->setObjectName("stab5dofControlButtonGreen");
        break;
    case SKYE_CONTROL_MODE_6DOF:
        ui.stab6dofControlButton->setObjectName("stab6dofControlButtonGreen");
        break;
    default:
        break;
    }

    // update style sheets
    ui.manControlButton->setStyleSheet("");
    ui.stab5dofControlButton->setStyleSheet("");
    ui.stab6dofControlButton->setStyleSheet("");
}


void UASSkyeControlWidget::setArmDisarmStatus()
{
    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(this->uas);
    if (mav)
    {
        if (!isArmed)
        {
            mav->armSystem();
//            mav->setModeArm(MAV_MODE_MANUAL_ARMED, 0);
            ui.lastActionLabel->setText(QString("Requested arming of %1").arg(mav->getUASName()));
        } else {
            mav->disarmSystem();
//            mav->setMode(MAV_MODE_MANUAL_DISARMED, 0);
            ui.lastActionLabel->setText(QString("Requested disarming of %1").arg(mav->getUASName()));
        }
    } else {
        ui.lastActionLabel->setText("No Skye connected!");
    }

}

void UASSkyeControlWidget::setManualControlMode()
{
    if (controlMode != SKYE_CONTROL_MODE_MANUAL) {
        if (transmitMode(SKYE_CONTROL_MODE_MANUAL)) {
            ui.manControlButton->setObjectName("manControlButtonWhite");
            ui.manControlButton->setStyleSheet("");
        }
    } else {
        ui.lastActionLabel->setText(QString("Already in %1 mode").arg(getControlModeString(controlMode)));
    }

}

void UASSkyeControlWidget::set5dofControlMode()
{
    if (controlMode != SKYE_CONTROL_MODE_5DOF) {
        if (transmitMode(SKYE_CONTROL_MODE_5DOF)) {
            ui.stab5dofControlButton->setObjectName("stab5dofControlButtonWhite");
            ui.stab5dofControlButton->setStyleSheet("");
        }
    } else {
        ui.lastActionLabel->setText(QString("Already in %1 mode").arg(getControlModeString(controlMode)));
    }

}

void UASSkyeControlWidget::set6dofControlMode()
{
    if (controlMode != SKYE_CONTROL_MODE_6DOF) {
        if (transmitMode(SKYE_CONTROL_MODE_6DOF)) {
            ui.stab6dofControlButton->setObjectName("stab6dofControlButtonWhite");
            ui.stab6dofControlButton->setStyleSheet("");
        }
    } else {
        ui.lastActionLabel->setText(QString("Already in %1 mode").arg(getControlModeString(controlMode)));
    }
}


bool UASSkyeControlWidget::transmitMode(SKYE_CONTROL_MODE ctrlMode)
{
    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(this->uas);
    if (mav)
    {
        px4_custom_mode custom_mode;
        if (ctrlMode > 0) {
            custom_mode.main_mode = PX4_CUSTOM_MAIN_MODE_STABILIZED;
        } else {
            custom_mode.main_mode = PX4_CUSTOM_MAIN_MODE_MANUAL;
        }
        mav->setMode(MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, custom_mode.data);
        mav->sendControlModeCommand(ctrlMode);

        // Display what has been sent
        QString modeStr = getControlModeString(ctrlMode);
        ui.lastActionLabel->setText(QString("Sent mode %1 to %2").arg(modeStr).arg(mav->getUASName()));
        qDebug() << "Send mode" << modeStr << "to" << mav->getUASName();
        return true;
    }
    else
    {
        ui.lastActionLabel->setText("No Skye connected!");
        return false;
    }
}

QString UASSkyeControlWidget::getControlModeString(SKYE_CONTROL_MODE ctrlMode)
{
    QString modeStr;
    switch (ctrlMode) {
    case SKYE_CONTROL_MODE_MANUAL:
        modeStr = "MANUAL";
        break;
    case SKYE_CONTROL_MODE_5DOF:
        modeStr = "5DOF";
        break;
    case SKYE_CONTROL_MODE_6DOF:
        modeStr = "6DOF";
        break;
    default:
        modeStr = "UNKNOWN";
    }
    return modeStr;
}

void UASSkyeControlWidget::setInputMouse(bool checked)
{
	if (checked)
	{
        ui.lastActionLabel->setText(tr("Starting 3dMouse..."));
        qDebug() << "Starting 3dMouse...";
	} else {
        ui.lastActionLabel->setText(tr("Stopping 3dMouse..."));
        qDebug() << "Stopping 3dMouse...";
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

void UASSkyeControlWidget::updateInputButtonStyleSheet()
{
    QString style = "";
    style.append("QPushButton { min-height: 30; }");

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
        style.append("QPushButton#mouseButton {image: url(:/res/input/3dmouse.png);}");
    }

    style.append("QPushButton#touchButton {image: url(:/res/input/touch.png);}");
    style.append("QPushButton#keyboardButton {image: url(:/res/input/keyboard.png); }");
    style.append("QPushButton#xboxButton {image: url(:/res/input/xbox.png); }");
    style.append("QPushButton:disabled {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #444444, stop: 1 #444444); color: #333333 }");
    this->setStyleSheet(style);
}

void UASSkyeControlWidget::updateMouseAvailable(bool available)
{
    mouseAvailable = available;
    setMouseActive(available);
}

void UASSkyeControlWidget::setMouseActive(bool active)
{
    ui.mouseButton->setChecked(active);
    if (active && mouseAvailable)
    {
        // 3d mouse has successfully been started
        ui.lastActionLabel->setText("3D mouse ON");

        inputMode &= QGC_INPUT_MODE_MOUSE;


    } else {
        // 3d mouse starting not succeeded. User must push the button again
        ui.lastActionLabel->setText("3D mouse OFF");

        inputMode &= QGC_INPUT_MODE_MOUSE;
        inputMode -= QGC_INPUT_MODE_MOUSE;
    }

}

void UASSkyeControlWidget::changeMouseTranslationEnabled(bool transEnabled)
{
    if (mouseTranslationEnabled != transEnabled)
    {
        mouseTranslationEnabled = transEnabled;
        if (!transEnabled)
        {
            ui.lastActionLabel->setText("Translation OFF");
        } else
        {
            ui.lastActionLabel->setText("Translation ON");
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
            ui.lastActionLabel->setText("Rotation OFF");
        } else
        {
            ui.lastActionLabel->setText("Rotation ON");
        }
    }
    updateInputButtonStyleSheet();
}

void UASSkyeControlWidget::getMouse6DOFControlCommands(double x, double y, double z, double a, double b, double c)
{
    // input mixer must exist
    if (inputMixer == NULL)
        return;

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
    } else {
        inputMixer->updateMouseValues(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    }
}

void UASSkyeControlWidget::getXboxControlCommands(double x, double y, double z, double a, double b, double c)
{
    // input mixer must exist
    if (inputMixer == NULL)
        return;

    if (inputMode & QGC_INPUT_MODE_XBOX)
    {
        inputMixer->updateXboxValues(x, y, z, a, b, c);
    }
}

void UASSkyeControlWidget::updateAllocCase(int allocCase)
{
    ui.lastActionLabel->setText(QString("Set allocation case %1").arg(allocCase));
}
