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
    inputMixer(NULL)
{

    ui.setupUi(this);
    ui.manControlButton->setObjectName("manControlButtonGray");
    ui.rateControlButton->setObjectName("rateControlButtonGray");
    ui.attControlButton->setObjectName("attControlButtonGray");

    ui.manControlButton->setStyleSheet("");
    ui.rateControlButton->setStyleSheet("");
    ui.attControlButton->setStyleSheet("");

    ui.controlButton->setObjectName("controlButtonGreen");
    ui.controlButton->setStyleSheet("");

    // Uncheck and group buttons to enable exclusiv checkable
//    ui.manControlButton->setChecked(uasMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL);
//    ui.rateControlButton->setChecked(uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE);
//    ui.attControlButton->setChecked(uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE);
//    ui.halfAutomaticControlButton->setChecked(uasMode & MAV_MODE_HALF_AUTOMATIC_DISARMED);
//    ui.fullAutomaticControlButton->setChecked(uasMode & MAV_MODE_FULL_AUTOMATIC_DISARMED);
    ui.manControlButton->setCheckable(false);
    ui.rateControlButton->setCheckable(false);
    ui.attControlButton->setCheckable(false);

    ui.mouseButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_MOUSE);
    ui.touchButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_TOUCH);
    ui.keyboardButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_KEYBOARD);
    ui.xboxButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_XBOX);

    ui.keyboardButton->hide();

    // alert widget
    alertWidget = new UASSkyeAlertWidget(this);
    ui.verticalLayoutForLabels->addWidget(alertWidget);

    // tabbed info view widget
    infoViewWidget = new QGCTabbedInfoView(this);
    infoViewWidget->show();

    ui.advancedLayout->addWidget(infoViewWidget);

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    connect(ui.manControlButton, SIGNAL(clicked()), this, SLOT(setDirectControlMode()));
    connect(ui.rateControlButton, SIGNAL(clicked()), this, SLOT(setRateControlMode()));
    connect(ui.attControlButton, SIGNAL(clicked()), this, SLOT(setAttitudeControlMode()));

    connect(ui.mouseButton, SIGNAL(clicked(bool)), this, SLOT(setInputMouse(bool)));
    connect(ui.touchButton, SIGNAL(clicked(bool)), this, SLOT(setInputTouch(bool)));
    connect(ui.keyboardButton, SIGNAL(clicked(bool)), this, SLOT(setInputKeyboard(bool)));
    connect(ui.xboxButton, SIGNAL(clicked(bool)), this, SLOT(setInputXbox(bool)));

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
    qDebug() << "Slot set UAS called";
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
            disconnect(this, SIGNAL(changedInput(SkyeMAV::QGC_INPUT_MODE, bool)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE, bool)));
            disconnect(mav, SIGNAL(inputModeChanged(int)), this, SLOT(updateInput(int)));

            disconnect(mav, SIGNAL(mouseButtonRotationChanged(bool)), this, SLOT(changeMouseRotationEnabled(bool)));
            disconnect(mav, SIGNAL(mouseButtonTranslationChanged(bool)), this, SLOT(changeMouseTranslationEnabled(bool)));
            //disconnect(mav, SIGNAL(batteryLow(double)), this, SLOT(alertBatteryLow(double)));
            disconnect(mav, SIGNAL(batteryLow(double,bool,uint)), alertWidget, SLOT(batteryLow(double,bool,uint)));

            disconnect(inputMixer, SIGNAL(changed6DOFInput(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));

            // Disconnect slots for Change of Actuation Unit Configuration
            disconnect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(getAllocCase(int)));


            // stop input mixer
            if (inputMixer)
            {
                inputMixer->terminate();
                inputMixer = NULL;
            }
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

        // start input mixer
        inputMixer = new UASSkyeInputMixer(this);
        inputMixer->init();
        inputMixer->start();

        // Connect user interface controls
        connect(ui.controlButton, SIGNAL(clicked()), this, SLOT(cycleContextButton()));
        connect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        connect(mav, SIGNAL(statusChanged(int)), this, SLOT(updateState(int)));
        //connect(mav, SIGNAL(batteryLow(double)), this, SLOT(alertBatteryLow(double)));
        connect(mav, SIGNAL(batteryLow(double,bool,uint)), alertWidget, SLOT(batteryLow(double,bool,uint)));

        connect(this, SIGNAL(changedInput(SkyeMAV::QGC_INPUT_MODE, bool)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE, bool)));
        connect(mav, SIGNAL(inputModeChanged(int)), this, SLOT(updateInput(int)));

        connect(inputMixer, SIGNAL(changed6DOFInput(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));

        // Connect slots for Change of Actuation Unit Configuration
        connect(mav, SIGNAL(allocCaseChanged(int)), this, SLOT(getAllocCase(int)));

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
        ui.controlButton->setObjectName("controlButtonRed");
        ui.controlButton->setStyleSheet("");
        //setInputButtonActivity(false);
    }
    else
    {
        ui.controlButton->setText(tr("ARM SYSTEM"));
        ui.controlButton->setObjectName("controlButtonGreen");
        ui.controlButton->setStyleSheet("");
        //setInputButtonActivity(true);
    }
}


void UASSkyeControlWidget::updateMode(int uas,int baseMode)
{
//    qDebug() << "Got uas mode:" << baseMode;
    if ((uasId == uas) && ((int)uasMode != baseMode))
    {
        uasMode = (unsigned int)baseMode;

		if (uasMode == MAV_MODE_PREFLIGHT)
        {
            ui.manControlButton->setObjectName("manControlButtonGray");
            ui.rateControlButton->setObjectName("rateControlButtonGray");
            ui.attControlButton->setObjectName("attControlButtonGray");
		}

        if (uasMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL)
        {
            ui.manControlButton->setObjectName("manControlButtonGreen");
            ui.rateControlButton->setObjectName("rateControlButtonGray");
            ui.attControlButton->setObjectName("attControlButtonGray");
        }

        if ((uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE) && (uasMode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE))
        {
            ui.manControlButton->setObjectName("manControlButtonGray");
            ui.rateControlButton->setObjectName("rateControlButtonGreen");
            ui.attControlButton->setObjectName("attControlButtonGray");
        }

        if ((uasMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE) && !(uasMode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE))
        {
            ui.manControlButton->setObjectName("manControlButtonGray");
            ui.rateControlButton->setObjectName("rateControlButtonGray");
            ui.attControlButton->setObjectName("attControlButtonGreen");
        }

        ui.manControlButton->setStyleSheet("");
        ui.rateControlButton->setStyleSheet("");
        ui.attControlButton->setStyleSheet("");
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

void UASSkyeControlWidget::updateInput(int input)
{
    if (inputMode != input)
    {
        inputMode = input;

        ui.mouseButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_MOUSE);
        ui.touchButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_TOUCH);
        ui.keyboardButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_KEYBOARD);
        ui.xboxButton->setChecked(inputMode & SkyeMAV::QGC_INPUT_MODE_XBOX);
    }
    updateStyleSheet();
}

void UASSkyeControlWidget::setDirectControlMode()
{
    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (engineOn) {

        newMode = newMode | MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
        transmitMode(newMode);

        if (uasMode != newMode)
        {
            ui.manControlButton->setObjectName("manControlButtonWhite");
            ui.manControlButton->setStyleSheet("");
        }

    } else {
        ui.lastActionLabel->setText("Arm system first");
    }

}

void UASSkyeControlWidget::setRateControlMode()
{
    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (engineOn) {
        newMode = newMode | MAV_MODE_FLAG_SAFETY_ARMED;
        // Set rate control
        newMode |= MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
        transmitMode(newMode);

        if (uasMode != newMode)
        {
            ui.rateControlButton->setObjectName("rateControlButtonWhite");
            ui.rateControlButton->setStyleSheet("");
        }
    } else {
        ui.lastActionLabel->setText("Arm system first");
    }
}

void UASSkyeControlWidget::setAttitudeControlMode()
{
    uint8_t newMode = MAV_MODE_PREFLIGHT;
    if (engineOn) {
        newMode = newMode | MAV_MODE_FLAG_SAFETY_ARMED;
        // Set attitude control
        newMode |= MAV_MODE_FLAG_STABILIZE_ENABLED;
        transmitMode(newMode);

        if (uasMode != newMode)
        {
            ui.attControlButton->setObjectName("attControlButtonWhite");
            ui.attControlButton->setStyleSheet("");
        }

    } else {
        ui.lastActionLabel->setText("Arm system first");
    }
}

void UASSkyeControlWidget::mouseActivated(bool success)
{
    if (!success)
    {
        ui.mouseButton->setChecked(false);
    }
    qDebug() << "Mouse activated is" << success;
}

void UASSkyeControlWidget::setInputMouse(bool checked)
{
    ui.lastActionLabel->setText(tr("Starting 3dMouse... Click again for activate."));
    emit changedInput(SkyeMAV::QGC_INPUT_MODE_MOUSE, checked);

    //updateStyleSheet();
}

void UASSkyeControlWidget::setInputTouch(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Activating Touchscreen..."));
    } else {
        ui.lastActionLabel->setText(tr("Deactivated Touchscreen"));
    }

    emit changedInput(SkyeMAV::QGC_INPUT_MODE_TOUCH, checked);
}

void UASSkyeControlWidget::setInputKeyboard(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Activating Keyboard..."));
    } else {
        ui.lastActionLabel->setText(tr("Deactivating Keyboard"));
    }

    emit changedInput(SkyeMAV::QGC_INPUT_MODE_KEYBOARD, checked);
}

void UASSkyeControlWidget::setInputXbox(bool checked)
{
    if (checked)
    {
        ui.lastActionLabel->setText(tr("Xbox Controller activated!"));
    } else {
        ui.lastActionLabel->setText(tr("Xbox Controller deactivated!"));
    }

    emit changedInput(SkyeMAV::QGC_INPUT_MODE_XBOX, checked);
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
    if (inputMode == SkyeMAV::QGC_INPUT_MODE_MOUSE)
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
    style.append("QPushButton#xboxButton {image: url(:files/images/skye/input/xbox_controller.png); }");
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
    updateStyleSheet();
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
    updateStyleSheet();
}

void UASSkyeControlWidget::getMouse6DOFControlCommands(double x, double y, double z, double a, double b, double c)
{
    if (inputMode & SkyeMAV::QGC_INPUT_MODE_MOUSE)
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
    if (inputMode & SkyeMAV::QGC_INPUT_MODE_XBOX)
    {
        inputMixer->updateXboxValues(x, y, z, a, b, c);
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

void UASSkyeControlWidget::getAllocCase(int allocCase)
{
    ui.lastActionLabel->setText(QString("Set allocation case %1").arg(allocCase));
}
