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
#include <QtGui/QApplication>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <ui_UASSkyeControl.h>
#include <UASInterface.h>
//#include "Ui_UASSkyeControl.h"
#include "SkyeMAV.h"
#include "UASSkyeControlAdvancedWidget.h"
#include "ledControl/LedControlWidget.h"
#include "QGCTabbedInfoView.h"
#include "UASSkyeInputMixer.h"

/**
 * @brief Widget controlling one (skye) MAV
 */
class UASSkyeControlWidget : public QWidget
{
    Q_OBJECT

public:
    UASSkyeControlWidget(QWidget *parent = 0);
    ~UASSkyeControlWidget();

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);
    /** @brief Block input change buttons */
    void setInputButtonActivity(bool enabled);
    /** @brief Trigger next context action */
    void cycleContextButton();
    /** @brief Transmit the operation mode */
    void transmitMode(int mode);
    /** @brief Update the mode */
    void updateMode(int uas,int baseMode);
    /** @brief Update state */
    void updateState(int state);
    /** @brief Update internal state machine */
    void updateStatemachine();
    /** @brief Update input buttons */
    void updateInput(SkyeMAV::QGC_INPUT_MODE input);
    /** @brief Update 3dMouse button image */
    void changeMouseTranslationEnabled(bool transEnabled);
    /** @brief Update 3dMouse button image */
    void changeMouseRotationEnabled(bool rotEnabled);
    /** @brief Get 3dmouse control commands */
    void getMouse6DOFControlCommands(double x, double y, double z, double a, double b, double c);

    /** @brief Alert user that battery is low */
    void alertBatteryLow(double voltage);

signals:
    void changedMode(int);
    void changedInput(SkyeMAV::QGC_INPUT_MODE);
    void changedSensitivityTransFactor(float);
    void changedSensitivityRotFactor(float);
    void changedLiftFactor(float);
    void changed6DOFControlCommands(double, double, double, double, double, double);

    protected slots:
//        /** @brief Set the background color for the widget */
//        void setBackgroundColor(QColor color);
        /** @brief Set Direct Control */
        void setDirectControlMode();
        /** @brief Set Rate Control */
        void setRateControlMode();
        /** @brief Set Attitude Control */
        void setAttitudeControlMode();
//        /** @brief Set uasMode to Half Automatic Control */
//        void setHalfAutomaticControlMode(bool checked);
//        /** @brief Set uasMode to Full Automatic Control */
//        void setFullAutomaticControlMode(bool checked);
        /** @brief 3dMouse activated */
        void mouseActivated(bool success);
        /** @brief Set 3d Mouse as active inpute device */
        void setInputMouse(bool checked);
        /** @brief Set Touchscreen as active inpute device */
        void setInputTouch(bool checked);
        /** @brief Set Keyboard as active inpute device */
        void setInputKeyboard(bool checked);
        /** @brief Set new (double)sensitivityFactorTrans by double */
        void setSensitivityFactorTrans(double val);
        /** @brief Set new (double)sensitivityFactorRot by double */
        void setSensitivityFactorRot(double val);
        /** @brief Set new (double)liftFactor by double */
        void setLiftFactor(double val);
        /** @brief Show/Hide advanced settings */
        void toggleAdvancedSettings(bool enabled);


    private:
        int uasId;                          ///< Reference to the current uas
        unsigned int uasMode;               ///< Current uas mode
        bool engineOn;                      ///< Engine state
        SkyeMAV::QGC_INPUT_MODE inputMode;           ///< Current device for input
        bool mouseTranslationEnabled;       ///< True when translational motions enabled
        bool mouseRotationEnabled;          ///< True when rotational motions enabled

        double sensitivityFactorTrans;       ///< Gain rotational manual inputs.
        double sensitivityFactorRot;         ///< Gain rotational manual inputs.
        double liftFactor;                   ///< Additive z value (for constant lift gain)

        QTime lastAlertTime;                ///< Time when last low battery alert was prompted
        bool alertedBatteryLow;             ///< True if system had low battery once
        QErrorMessage *msgBox;

        UASSkyeInputMixer *inputMixer;      ///< Thread to mix and emit inputs

        /** @brief Set up widget, don't use ui file */
        void buildWidget();
        /** @brief Update stylesheet for SkyeControlWidget */
        void updateStyleSheet();
        /** @brief Uncheck all mode buttons when mode is default */
        void uncheckAllModeButtons();
//        Ui_UASSkyeControl ui;
        Ui::uasSkyeControl ui;
        QButtonGroup *modeButtonGroup;
        QButtonGroup *inputButtonGroup;

        UASSkyeControlAdvancedWidget *advancedWidget;       ///< sub widget containing advanced settings
        bool enabledAdvancedSettings;

        LedControlWidget *ledWidget;                        ///< sub widget for led control
        QGCTabbedInfoView *infoViewWidget;                        ///< sub widget for mavlink messages;


    };

    #endif // _UASCONTROLWIDGET_H_
