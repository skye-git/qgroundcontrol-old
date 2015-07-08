/**
 * @file
 *   @brief Definition of 3dConnexion 3dMouse interface for QGroundControl
 *
 *   @author Matthias Krebs <makrebs@student.ethz.ch>
 *
 */

#ifndef MOUSE6DOFINPUT_H
#define MOUSE6DOFINPUT_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QTimer>

#ifdef QGC_MOUSE_ENABLED_WIN
#include "Mouse3DInput.h"
#endif //QGC_MOUSE_ENABLED_WIN

#include "UASInterface.h"
#ifdef QGC_USE_SKYE_MESSAGES
#include "SkyeUAS.h"
#endif //QGC_USE_SKYE_MESSAGES

class Mouse6dofInput : public QThread
{
    Q_OBJECT

public:
#ifdef QGC_MOUSE_ENABLED_WIN
    Mouse6dofInput(Mouse3DInput* mouseInput);
#endif //QGC_MOUSE_ENABLED_WIN
#ifdef QGC_MOUSE_ENABLED_LINUX
    Mouse6dofInput();
#endif //QGC_MOUSE_ENABLED_LINUX

    ~Mouse6dofInput();
    void run();

#ifdef QGC_MOUSE_ENABLED_LINUX
    const double mouse3DMaxX;
    const double mouse3DMaxY;
    const double mouse3DMaxZ;
    const double mouse3DMaxA;
    const double mouse3DMaxB;
    const double mouse3DMaxC;
#else
#ifdef QGC_MOUSE_ENABLED_WIN
    const double mouse3DMax;
#endif
#endif

protected:
    /** Progressive incremention */
    double progressive(double value);
    /** Saturation to 1.0 */
    double saturate(double value);
    /** 1: greater than zero, 0: equal zero, -1 else */
    int sign(double value);

    int uasId;
    bool done;
    bool mouseActive;
    bool translationActive;
    bool rotationActive;

    double xValue;
    double yValue;
    double zValue;
    double aValue;
    double bValue;
    double cValue;


signals:
    /**
     * @brief Input of the 3d mouse has changed
     *
     * @param x Input x direction, range [-1, 1]
     * @param y Input y direction, range [-1, 1]
     * @param z Input z direction, range [-1, 1]
     * @param a Input x rotation,  range [-1, 1]
     * @param b Input y rotation,  range [-1, 1]
     * @param c Input z rotation,  range [-1, 1]
     */
    void mouse6dofChanged(double x, double y, double z, double a, double b, double c);

   /**
     * @brief Activity of translational 3DMouse inputs changed
     * @param translationEnable, true: translational inputs active; false: translational inputs ingored
     */
    void mouseTranslationActiveChanged(bool translationEnable);

   /**
     * @brief Activity of rotational 3DMouse inputs changed
     * @param rotationEnable, true: rotational inputs active; false: rotational inputs ingored
     */
    void mouseRotationActiveChanged(bool rotationEnable);

    /**
      * @brief Reset input mode (to indicate whether initialization succeded)
      * @param active: true if mouse activated
      */
    void resetMouseInputStatus(bool active);

public slots:
#ifdef QGC_USE_SKYE_MESSAGES
    void setActiveUAS(UASInterface* uas);
#endif // QGC_USE_SKYE_MESSAGES
#ifdef QGC_MOUSE_ENABLED_WIN
    /** @brief Get a motion input from 3DMouse */
    void motion3DMouse(std::vector<float> &motionData);
    /** @brief Get a button input from 3DMouse */
    void button3DMouseDown(int button);
#endif //QGC_MOUSE_ENABLED_WIN
#ifdef QGC_MOUSE_ENABLED_LINUX
    /** @brief Poll spnav event (motion or button) */
    void pollSpnavEvent();
#endif //QGC_MOUSE_ENABLED_LINUX
    /** @brief Input mode changed. Start 3dMouse if requested. */
    void updateInputMode(int inputMode);

};

#endif // MOUSE6DOFINPUT_H
