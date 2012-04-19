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
#include <QtGui/QApplication>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <ui_UASSkyeControl.h>
#include <UASInterface.h>
//#include "Ui_UASSkyeControl.h"

/**
 * @brief Widget controlling one (skye) MAV
 */
class UASSkyeControlWidget : public QWidget
{
    Q_OBJECT

public:
    UASSkyeControlWidget(QWidget *parent = 0);
    ~UASSkyeControlWidget();

    enum QGC_INPUT_MODE {
        QGC_INPUT_MODE_NONE,
        QGC_INPUT_MODE_MOUSE,
        QGC_INPUT_MODE_TOUCH,
        QGC_INPUT_MODE_KEYBOARD
    };

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);
    /** @brief Trigger next context action */
    void cycleContextButton();
    /** @brief Set the operation mode of the MAV */
    void setMode(int mode);
    /** @brief Transmit the operation mode */
    void transmitMode();
    /** @brief Update the mode */
    void updateMode(int uas,int baseMode);
    /** @brief Update state */
    void updateState(int state);
    /** @brief Update internal state machine */
    void updateStatemachine();
    /** @brief Update 3dMouse button image */
    void changeMouseTranslationEnabled(bool transEnabled);
    /** @brief Update 3dMouse button image */
    void changeMouseRotationEnabled(bool rotEnabled);

signals:
    void changedMode(int);
    void changedInput(int);
    void triggeredImageShot(MAV_CAM_ID);
    void changedSensitivityFactor(int);

    protected slots:
//        /** @brief Set the background color for the widget */
//        void setBackgroundColor(QColor color);
        /** @brief Set uasMode to Direct Control */
        void setDirectControlMode(bool checked);
        /** @brief Set uasMode to Assisted Control */
        void setAssistedControlMode(bool checked);
        /** @brief Set uasMode to Half Automatic Control */
        void setHalfAutomaticControlMode(bool checked);
        /** @brief Set uasMode to Full Automatic Control */
        void setFullAutomaticControlMode(bool checked);
        /** @brief Set 3d Mouse as active inpute device */
        void setInputMouse(bool checked);
        /** @brief Set Touchscreen as active inpute device */
        void setInputTouch(bool checked);
        /** @brief Set Keyboard as active inpute device */
        void setInputKeyboard(bool checked);
        /** @brief Trigger image shot with left Bluefox Camera */
        void triggerLeftBluefoxImageShot();
        /** @brief Trigger image shot with right Bluefox Camera */
        void triggerRightBluefoxImageShot();
        /** @brief Trigger image shot with Prosilica Camera */
        void triggerProsilicaImageShot();
        /** @brief Set new (float)sensitivityFactor by int */
        void setSensitivityFactor(int val);


    protected:
        int uasId;                          ///< Reference to the current uas
        unsigned int uasMode;               ///< Current uas mode
        bool engineOn;                      ///< Engine state
        QGC_INPUT_MODE inputMode;           ///< Current device for input
        bool mouseTranslationEnabled;       ///< True when translational motions enabled
        bool mouseRotationEnabled;          ///< True when rotational motions enabled
        int sensitivityFactor;               ///< Value of velocitySlider in float scale. Defines scaling of all inputs.
        int minSensitivityFactor;            ///< Minimum value of velocitySlider in float scale.
        int maxSensitivityFactor;            ///< Maximum value of velocitySlider in float scale.

    private:
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

    };

    #endif // _UASCONTROLWIDGET_H_
