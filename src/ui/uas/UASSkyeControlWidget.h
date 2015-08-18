/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of class UASSkyeControlWidget
 *
 *   @author Matthias Krebs <makrebs@student.ethz.ch>
 *
 */

#ifndef _UASSKYECONTROLWIDGET_H_
#define _UASSKYECONTROLWIDGET_H_

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QButtonGroup>
#include <QTime>
#include <QErrorMessage>
#include <QApplication>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <ui_UASSkyeControl.h>
#include <UASInterface.h>
#include <QGCMAVLink.h>
#include "SkyeUAS.h"
#include "QGCTabbedInfoView.h"
#include "QGCInputs.h"
#include "InputMixer.h"

/**
 * @brief Widget controlling one (skye) MAV
 */
class UASSkyeControlWidget : public QWidget
{
    Q_OBJECT

public:
    UASSkyeControlWidget(QWidget *parent = 0);
    ~UASSkyeControlWidget();

    QString getControlModeString(SKYE_CONTROL_MODE ctrlMode);
    /** @brief Update the mode button style sheet */
    void updateControlModeStyleSheet();
    /** @brief Update arm button style sheet */
    void updateArmButtonStyleSheet();

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);

    /** @brief Set arm/disarm command */
    void setArmDisarmStatus();

    /** @brief Update arm status */
    void updateArmingState(bool armed);
    /** @brief Update the control mode */
    void updateControlMode(SKYE_CONTROL_MODE ctrlMode);

    /** @brief Update if mouse driver is ready */
    void updateMouseAvailable(bool available);
    /** @brief De-/activate mouse by check-button */
    void setMouseActive(bool active);
    /** @brief Update 3dMouse button image */
    void changeMouseTranslationEnabled(bool transEnabled);
    /** @brief Update 3dMouse button image */
    void changeMouseRotationEnabled(bool rotEnabled);
    /** @brief Get 3dmouse control commands */
    void getMouse6DOFControlCommands(double x, double y, double z, double a, double b, double c);
    /** @brief Get xbox control commands */
    void getXboxControlCommands(double x, double y, double z, double a, double b, double c);
    /** @brief New allocation case has been set on UAV */
    void updateAllocCase(int allocCase);

signals:
    void changedMode(int);
    void changedInput(QGC_INPUT_MODE, bool);
    void changed6DOFControlCommands(double, double, double, double, double, double);

    /** @brief change actuation unit configuration parameter */
    void changeAUConfiguration(int disabledAU);

    protected slots:
        /** @brief Set manual Control */
        void setManualControlMode();
        /** @brief Set 5 dof Control */
        void set5dofControlMode();
        /** @brief Set 6 dof Control */
        void set6dofControlMode();
        /** @brief Set 3d Mouse as active inpute device */
        void setInputMouse(bool checked);
        /** @brief Set Touchscreen as active inpute device */
        void setInputTouch(bool checked);
        /** @brief Set Keyboard as active inpute device */
        void setInputKeyboard(bool checked);
        /** @brief Set XboxController as active input device */
        void setInputXbox(bool checked);



    protected:
        /** @brief Transmit the operation mode. Returns true if mode is transmitted. */
        bool transmitMode(SKYE_CONTROL_MODE mode);

        SKYE_CONTROL_MODE controlMode;      ///< Copy of SKYE_C_MODE onboard parameter

        UASInterface *uas;                  ///< Reference to the current uas
        int baseMode;                       ///< Base mode
        bool isArmed;                       ///< Engine state
        int inputMode;                      ///< Active device flags for input (see QGC_INPUT_MODE)
        bool mouseAvailable;                ///< True when mouse driver running and device plugged in
        bool mouseTranslationEnabled;       ///< True when translational motions enabled
        bool mouseRotationEnabled;          ///< True when rotational motions enabled

        UASSkyeInputMixer *inputMixer;      ///< Thread to mix and emit inputs

        /** @brief Set up widget, don't use ui file */
        void buildWidget();
        /** @brief Update stylesheet for SkyeControlWidget */
        void updateInputButtonStyleSheet();
        Ui::uasSkyeControl ui;
        QButtonGroup *modeButtonGroup;
        QButtonGroup *inputButtonGroup;

        QGCTabbedInfoView *infoViewWidget;  ///< sub widget for mavlink messages;


    };

    #endif // _UASCONTROLWIDGET_H_
