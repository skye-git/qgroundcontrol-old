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
 *   @brief Definition of class MainWindow
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtGui/QMainWindow>
#include <QStatusBar>
#include <QStackedWidget>
#include <QSettings>
#include <QProcess>                     // Beginn Ende Code MA (08.03.2012)
#include <QTime>                        // Beginn Ende Code MA (14.04.2012)
#include <qlist.h>

#include "ui_MainWindow.h"
#include "LinkManager.h"
#include "LinkInterface.h"
#include "UASInterface.h"
#include "UASManager.h"
#include "UASControlWidget.h"
#include "UASSkyeControlWidget.h"       // Beginn Ende Code MA (06.03.2012)
#include "Linecharts.h"
#include "UASInfoWidget.h"
#include "WaypointList.h"
//#include "CameraView.h"               // Not used Code MA (19.03.2012)
#include "UASListWidget.h"
#include "MAVLinkProtocol.h"
#include "MAVLinkSimulationLink.h"
#include "ObjectDetectionView.h"
#include "HUD.h"
#include "JoystickWidget.h"
#include "TestphaseWidget.h"                //Beginn Ende Code AL (01.03.12)
#include "DirectControlWidget.h"            //Beginn Ende Code MA (12.04.12)
#include "SkyeCameraReconfigure.h"          //Beginn Ende Code MA (20.03.2012)
#include "input/JoystickInput.h"
#include "DebugConsole.h"
#include "ParameterInterface.h"
#include "XMLCommProtocolWidget.h"
#include "HDDisplay.h"
#include "WatchdogControl.h"
#include "HSIDisplay.h"
#include "QGCDataPlot2D.h"
#include "QGCRemoteControlView.h"
#include "opmapcontrol.h"
#if (defined Q_OS_MAC) | (defined _MSC_VER)
#include "QGCGoogleEarthView.h"
#endif
#include "QGCToolBar.h"
#include "SlugsDataSensorView.h"
#include "LogCompressor.h"

#include "SlugsHilSim.h"

#include "SlugsPadCameraControl.h"
#include "UASControlParameters.h"
#include "QGCMAVLinkInspector.h"
#include "QGCMAVLinkLogPlayer.h"
#include "MAVLinkDecoder.h"
#include "UASSkyeBatteryInfoWidget.h"       // Beginn Code MA (15.03.2012)
#include "UASSkyeBatteryPackWidget.h"       // Ende Code MA (15.03.2012)

class QGCMapTool;
class QGCMAVLinkMessageSender;
class QGCFirmwareUpdate;
class QSplashScreen;

/**
 * @brief Main Application Window
 *
 **/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* instance(QSplashScreen* screen = 0);
    ~MainWindow();

    enum QGC_MAINWINDOW_STYLE
    {
        QGC_MAINWINDOW_STYLE_NATIVE,
        QGC_MAINWINDOW_STYLE_INDOOR,
        QGC_MAINWINDOW_STYLE_OUTDOOR,
        QGC_MAINWINDOW_STYLE_SKYE              //Beginn Ende Code AL (14.03.12)
    };

    /** @brief Get current visual style */
    int getStyle()
    {
        return currentStyle;
    }
    /** @brief Get auto link reconnect setting */
    bool autoReconnectEnabled()
    {
        return autoReconnect;
    }

    /** @brief Get low power mode setting */
    bool lowPowerModeEnabled()
    {
        return lowPowerMode;
    }

    QList<QAction*> listLinkMenuActions(void);

#ifdef MOUSE_ENABLED
    /** @brief Moving average filter for mouse values */
    void filterMouseValues(double newX, double newY, double newZ, double newA, double newB, double newC);
#endif

public slots:

    /** @brief Shows a status message on the bottom status bar */
    void showStatusMessage(const QString& status, int timeout);
    /** @brief Shows a status message on the bottom status bar */
    void showStatusMessage(const QString& status);
    /** @brief Shows a critical message as popup or as widget */
    void showCriticalMessage(const QString& title, const QString& message);
    /** @brief Shows an info message as popup or as widget */
    void showInfoMessage(const QString& title, const QString& message);

    /** @brief Show the application settings */
    void showSettings();
    /** @brief Show the TestphaseWidget */              //Beginn Code AL (01.03.12)------------------
    void showTestphase();                               //Ende Code AL--------------------
    /** @brief Show the DirectControlWidget */          //Beginn Code MA (12.04.12)------------------
    void showDirectControl();                           //Ende Code MA--------------------
    /** @brief Show the Camera Reconfigure Widget */    //Beginn Code MA (20.03.12)------------------
    void showSkyeCamReconfig();                         //Ende Code MA--------------------
    /** @brief Add a communication link */
    void addLink();
    void addLink(LinkInterface* link);
    void configure();
    /** @brief Set the currently controlled UAS */
    void setActiveUAS(UASInterface* uas);

    /** @brief Add a new UAS */
    void UASCreated(UASInterface* uas);
    /** @brief Update system specs of a UAS */
    void UASSpecsChanged(int uas);
    void startVideoCapture();
    void stopVideoCapture();
    void saveScreen();

    /** @brief Load default view when no MAV is connected */
    void loadUnconnectedView();
    /** @brief Load view for pilot */
    void loadPilotView();
    /** @brief Load view for engineer */
    void loadEngineerView();
    /** @brief Load view for operator */
    void loadOperatorView();
    /** @brief Load view for skye */ //Beginn Code AL (01.03.12)----------------------------------------
    void loadSkyeView();             //Ende Code AL-----------------------------------------------------
    /** @brief Load MAVLink XML generator view */
    void loadMAVLinkView();
    /** @brief Load firmware update view */
    void loadFirmwareUpdateView();

    /** @brief Show the online help for users */
    void showHelp();
    /** @brief Show the authors / credits */
    void showCredits();
    /** @brief Show the project roadmap */
    void showRoadMap();

    /** @brief Reload the CSS style sheet */
    void reloadStylesheet();
    /** @brief Let the user select the CSS style sheet */
    void selectStylesheet();
    /** @brief Automatically reconnect last link */
    void enableAutoReconnect(bool enabled);
    /** @brief Save power by reducing update rates */
    void enableLowPowerMode(bool enabled) { lowPowerMode = enabled; }
    /** @brief Switch to native application style */
    void loadNativeStyle();
    /** @brief Switch to indoor mission style */
    void loadIndoorStyle();
    /** @brief Switch to outdoor mission style */
    void loadOutdoorStyle();
    /** @brief Switch to skye mission style */
    void loadSkyeStyle();                               //Beginn Ende Code AL (14.03.12)
    /** @brief Load a specific style */
    void loadStyle(QGC_MAINWINDOW_STYLE style);

    /** @brief Add a custom tool widget */
    void createCustomWidget();

    /** @brief Load a custom tool widget from a file chosen by user (QFileDialog) */
    void loadCustomWidget();

    /** @brief Load a custom tool widget from a file */
    void loadCustomWidget(const QString& fileName, bool singleinstance=false);

    /** @brief Load custom widgets from default file */
    void loadCustomWidgetsFromDefaults(const QString& systemType, const QString& autopilotType);

    void closeEvent(QCloseEvent* event);

    /** @brief Load data view, allowing to plot flight data */
    void loadDataView(QString fileName);

    /**
     * @brief Shows a Docked Widget based on the action sender
     *
     * This slot is written to be used in conjunction with the addTool() function
     * It shows the QDockedWidget based on the action sender
     *
     */
    void showTool(bool visible);

    /**
     * @brief Shows a Widget from the center stack based on the action sender
     *
     * This slot is written to be used in conjunction with the addCentralWidget() function
     * It shows the Widget based on the action sender
     *
     */
    void showCentralWidget();

    /** @brief Update the window name */
    void configureWindowName();

    /** @brief Set input device to control uav */
    void setInputMode(int inputMode);
#ifdef MOUSE_ENABLED                                        // Beginn Code MA (21.03.2012)
    /** @brief Start 3DxWare driver for 3dMouse (3dConnexion) and initialize */
    void start3dMouse();
    /** @brief Get current mouse value and filter signal */
    void filterMouseValues();
    /** @brief Emit mouse values */
    void emitMouseValues();
#endif // MOUSE_ENABLED                                     // Ende Code MA (21.03.2012)

    /** @Collect TouchInput from HUD */                             //Beginn Code AL (11.04.12)
    void setTouchInputYawPitchRoll(double roll, double pitch, double yaw);
    /** @Collect TouchInput from QGCMapTool */
    void setTouchInputXYZ(double x, double y, double z);
    /** @brief Emit TouchInput values */
    void emitTouchInputValues();                                    //Ende Code AL (11.04.12)



signals:
    void initStatusChanged(const QString& message);

    /**
    * @brief Emits new values of 3d mouse device
    *
    * @param xValue Translational motion of 3dmouse along x axis, scaled to in range [-1, 1]
    * @param yValue Translational motion of 3dmouse along x axis, scaled to in range [-1, 1]
    * @param zValue Translational motion of 3dmouse along x axis, scaled to in range [-1, 1]
    * @param aValue Rotational motion of 3dmouse, scaled to in range [-1, 1]
    * @param bValue Rotational motion of 3dmouse, scaled to in range [-1, 1]
    * @param cValue Rotational motion of 3dmouse, scaled to in range [-1, 1]
    *
    */
    void valueMouseChanged(double xValue, double yValue, double zValue, double aValue, double bValue, double cValue);   // Beginn und Ende Code MA (06.03.2012)
    /** @brief Translational degrees of 3dMouse are activated/disactivated */                                           // Beginn Code MA (18.03.2012)
    void mouseTranslationEnabledChanged(bool transEnabled);
    /** @brief Rotational degrees of 3dMouse are activated/disactivated */
    void mouseRotationEnabledChanged(bool rotEnabled);
    /** @brief Signal when successfully initialized and started 3dMouse input */
    void mouseStarted(bool success);                                                                                    // Ende Code MA (18.03.2012)
    /** @brief Emits new contol values for UAS given by keyboard in range [-1, 1] */
    void valueKeyboardChanged(double xValue, double yValue, double zValue, double rollValue, double pitchValue, double yawValue);   // Beginn und Ende Code MA (07.03.2012)
    /** @brief Emits bool whether TouchInput Interface is shown or not */
    void emitTouchInputVisibility(bool);                                                                                 // Beginn und Ende code AL(10.04.2012)
    /** @brief Emits new contol values for UAS given by keyboard in range [-1, 1] */
    void valueTouchInputChanged(double xValue, double yValue, double zValue, double rollValue, double pitchValue, double yawValue); //Beginn und Ende Code AL(11.04.12)

public:
    QGCMAVLinkLogPlayer* getLogPlayer()
    {
        return logPlayer;
    }

    MAVLinkProtocol* getMAVLink()
    {
        return mavlink;
    }

protected:

    MainWindow(QWidget *parent = 0);

    typedef enum _VIEW_SECTIONS
    {
        VIEW_ENGINEER,
        VIEW_OPERATOR,
        VIEW_SKYE, // Beginn und Ende Code AL (01.03.12)-------------------------------------
        VIEW_PILOT,
        VIEW_MAVLINK,
        VIEW_FIRMWAREUPDATE,
        VIEW_UNCONNECTED,    ///< View in unconnected mode, when no UAS is available
        VIEW_FULL            ///< All widgets shown at once
    } VIEW_SECTIONS;

    /**
     * @brief Adds an already instantiated QDockedWidget to the Tools Menu
     *
     * This function does all the hosekeeping to have a QDockedWidget added to the
     * tools menu and connects the QMenuAction to a slot that shows the widget and
     * checks/unchecks the tools menu item
     *
     * @param widget    The QDockWidget being added
     * @param title     The entry that will appear in the Menu and in the QDockedWidget title bar
     * @param location  The default location for the QDockedWidget in case there is no previous key in the settings
     */
    void addTool(QDockWidget* widget, const QString& title, Qt::DockWidgetArea location=Qt::RightDockWidgetArea);

    /**
     * @brief Adds an already instantiated QWidget to the center stack
     *
     * This function does all the hosekeeping to have a QWidget added to the tools menu
     * tools menu and connects the QMenuAction to a slot that shows the widget and
     * checks/unchecks the tools menu item. This is used for all the central widgets (those in
     * the center stack.
     *
     * @param widget        The QWidget being added
     * @param title         The entry that will appear in the Menu
     */
    void addCentralWidget(QWidget* widget, const QString& title);

    /** @brief Catch window resize events */
    void resizeEvent(QResizeEvent * event);

    /** @brief Keeps track of the current view */
    VIEW_SECTIONS currentView;
    QGC_MAINWINDOW_STYLE currentStyle;
    bool aboutToCloseFlag;
    bool changingViewsFlag;

    void storeViewState();
    void loadViewState();

    void buildCustomWidget();
    void buildCommonWidgets();
    void connectCommonWidgets();
    void connectCommonActions();
	void connectSenseSoarActions();

    void loadSettings();
    void storeSettings();

    // TODO Should be moved elsewhere, as the protocol does not belong to the UI
    MAVLinkProtocol* mavlink;

    MAVLinkSimulationLink* simulationLink;
    LinkInterface* udpLink;

    QSettings settings;
    QStackedWidget *centerStack;
    QActionGroup* centerStackActionGroup;

    // Center widgets
    QPointer<Linecharts> linechartWidget;
    QPointer<HUD> hudWidget;
    QPointer<QGCMapTool> mapWidget;
    QPointer<XMLCommProtocolWidget> protocolWidget;
    QPointer<QGCDataPlot2D> dataplotWidget;
#ifdef QGC_OSG_ENABLED
    QPointer<QWidget> _3DWidget;
#endif
#if (defined _MSC_VER) || (defined Q_OS_MAC)
    QPointer<QGCGoogleEarthView> gEarthWidget;
#endif
    QPointer<QGCFirmwareUpdate> firmwareUpdateWidget;

    // Dock widgets
    QPointer<QDockWidget> controlDockWidget;
    QPointer<QDockWidget> skyeControlDockWidget;        // Beginn Ende Code MA (06.03.2012)
    QPointer<QDockWidget> controlParameterWidget;
    QPointer<QDockWidget> infoDockWidget;
    QPointer<QDockWidget> cameraDockWidget;
    QPointer<QDockWidget> listDockWidget;
    QPointer<QDockWidget> waypointsDockWidget;
    QPointer<QDockWidget> detectionDockWidget;
    QPointer<QDockWidget> debugConsoleDockWidget;
    QPointer<QDockWidget> parametersDockWidget;
    QPointer<QDockWidget> headDown1DockWidget;
    QPointer<QDockWidget> headDown2DockWidget;
    QPointer<QDockWidget> watchdogControlDockWidget;

    QPointer<QDockWidget> headUpDockWidget;
    QPointer<QDockWidget> video1DockWidget;
    QPointer<QDockWidget> video2DockWidget;
    QPointer<QDockWidget> rgbd1DockWidget;
    QPointer<QDockWidget> rgbd2DockWidget;
    QPointer<QDockWidget> logPlayerDockWidget;

    QPointer<QDockWidget> hsiDockWidget;
    QPointer<QDockWidget> rcViewDockWidget;
    QPointer<QDockWidget> hudDockWidget;
    QPointer<QDockWidget> slugsDataWidget;
    QPointer<QDockWidget> slugsHilSimWidget;
    QPointer<QDockWidget> slugsCamControlWidget;

    QPointer<QGCToolBar> toolBar;

    QPointer<QDockWidget> mavlinkInspectorWidget;
    QPointer<MAVLinkDecoder> mavlinkDecoder;
    QPointer<QDockWidget> mavlinkSenderWidget;
    QGCMAVLinkLogPlayer* logPlayer;

    QPointer<QDockWidget> skyeBatteryInfoDockWidget;        // Beginn und Ende Code MA (15.03.2012)

    // Popup widgets
    JoystickWidget* joystickWidget;
    TestphaseWidget* testphaseWidget;                       //Beginn Ende Code AL (01.03.12)
    DirectControlWidget* directControlWidget;               //Beginn Ende Code MA (12.04.12)
    SkyeCameraReconfigure* skyeCameraReconfigureWidget;     //Beginn Ende Code MA (20.03.12)

    JoystickInput* joystick;

    /** User interface actions **/
    QAction* connectUASAct;
    QAction* disconnectUASAct;
    QAction* startUASAct;
    QAction* returnUASAct;
    QAction* stopUASAct;
    QAction* killUASAct;
    QAction* simulateUASAct;


    LogCompressor* comp;
    QString screenFileName;
    QTimer* videoTimer;
    QString styleFileName;
    bool autoReconnect;
    Qt::WindowStates windowStateVal;
    bool lowPowerMode; ///< If enabled, QGC reduces the update rates of all widgets
    QGCFlightGearLink* fgLink;
    QTimer windowNameUpdateTimer;

private:
    Ui::MainWindow ui;
    UASSkyeControlWidget::QGC_INPUT_MODE inputMode; // Beginn Ende Code MA (07.03.2012)
    QString getWindowStateKey();
    QString getWindowGeometryKey();

    // Event handler for 3dConnexion 3DMouse        //  Beginn Code MA 06.03.2012 ----------
    #ifdef MOUSE_ENABLED
    QProcess *process3dxDaemon;     ///< Process running 3dxDaemon 3dConnexion Mouse Driver
    /** @brief Reimplementation of X11Event to handle 3dMouse Events (magellan) */
    bool x11Event(XEvent *event);
    bool mouseTranslationEnable;    ///< True when translations of 3dMouse are enabled
    bool mouseRotationEnable;       ///< True when rotations of 3dMouse are enabled
    bool mouseInitialized;          ///< True when 3dMouse initialized successfully
    QTimer *mouseTimer;             ///< Timer calling 3dMouse
    QTime newMouseValueTime;        ///< Time when X11 event wrote new MouseValues. Used to check X11 timeout
    int mouseFilterSize;            ///< Size of moving average filter of skye
    int emitMouseValuesCounter;     ///< Counts up to mouseFilterSize and than values are emited
    double *mouseRawValues;         ///< Array containing last #mouseFilterSize mouse values for each axis
    double newMouseXValue;          ///< New mouse value read from 3dMouse device
    double newMouseYValue;          ///< New mouse value read from 3dMouse device
    double newMouseZValue;          ///< New mouse value read from 3dMouse device
    double newMouseAValue;          ///< New mouse value read from 3dMouse device
    double newMouseBValue;          ///< New mouse value read from 3dMouse device
    double newMouseCValue;          ///< New mouse value read from 3dMouse device
    double mouseXValueFiltered;     ///< Filtered mouse value
    double mouseYValueFiltered;     ///< Filtered mouse value
    double mouseZValueFiltered;     ///< Filtered mouse value
    double mouseAValueFiltered;     ///< Filtered mouse value
    double mouseBValueFiltered;     ///< Filtered mouse value
    double mouseCValueFiltered;     ///< Filtered mouse value
    #endif //MOUSE_ENABLED                          // Ende Code MA 06.03.2012 ------------

    void keyPressEvent(QKeyEvent *event);           // Beginn Code MA (07.03.2012)
    void keyReleaseEvent(QKeyEvent *event);
    void handleKeyEvents(QKeyEvent *event, bool keyPressed);         // Ende Code MA (07.03.2012)

    double keyXValue;        ///< X value caused by keyboard input (S,W)
    double keyYValue;        ///< Y value caused by keyboard input (A,D)
    double keyZValue;        ///< Z value caused by keyboard input (R,F)
    double keyRollValue;     ///< Roll value caused by keyboard input (???)
    double keyPitchValue;    ///< Pitch value caused by keyboard input (down, up)
    double keyYawValue;      ///< Yaw value caused by keyboard input (left, right)

    QTimer touchInputTimer;                         //Beginn code AL (11.04.12)
    double touchXValue;
    double touchYValue;
    double touchZValue;
    double touchRollValue;
    double touchPitchValue;
    double touchYawValue;                           //Ende Code AL

};

#endif /* _MAINWINDOW_H_ */
