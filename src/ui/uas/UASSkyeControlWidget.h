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
#include <ui_UASSkyeControl.h>
#include <UASInterface.h>

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
    /** @brief Trigger next context action */
    void cycleContextButton();
    /** @brief Set the operation mode of the MAV */
    void setMode(int mode);
    /** @brief Transmit the operation mode */
    void transmitMode();
    /** @brief Update the mode */
    void updateMode(int uas,QString mode,QString description);
    /** @brief Update state */
    void updateState(int state);
    /** @brief Update internal state machine */
    void updateStatemachine();

signals:
    void changedMode(int);


protected slots:
    /** @brief Set the background color for the widget */
    void setBackgroundColor(QColor color);
    /** @brief Set uasMode to Direct Control */
    void setDirectControlMode(bool checked);
    /** @brief Set uasMode to Assisted Control */
    void setAssistedControlMode(bool checked);
    /** @brief Set uasMode to Half Automatic Control */
    void setHalfAutomaticControlMode(bool checked);
    /** @brief Set uasMode to Full Automatic Control */
    void setFullAutomaticControlMode(bool checked);

protected:
    int uas;              ///< Reference to the current uas
    unsigned int uasMode; ///< Current uas mode
    bool engineOn;        ///< Engine state
//    enum ctrlMode{        ///< Possible control modes
//        directControl,
//        assistedControl,
//        halfAutomaticControl,
//        fullAutomaticControl
//    };
//    ctrlMode controlMode;      ///< Current uas control mode


private:
    Ui::uasSkyeControl ui;
    QButtonGroup *modeButtonGroup;
    QButtonGroup *inputButtonGroup;

};

#endif // _UASCONTROLWIDGET_H_
