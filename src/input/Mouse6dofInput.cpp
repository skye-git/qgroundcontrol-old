/**
 * @file
 *   @brief 3dConnexion 3dMouse interface for QGroundControl
 *
 *   @author Matthias Krebs <makrebs@student.ethz.ch>
 *
 */

#include "UAS.h"
#include "UASManager.h"
#include "QMessageBox"
#include "QString"
#include "QStringList"

#include "Mouse6dofInput.h"
#include "src/input/QGCInputs.h"

#ifdef QGC_MOUSE_ENABLED_LINUX
#include "spnav.h"
#endif // QGC_MOUSE_ENABLED_LINUX

#define MOUSE3D_EMIT_INTERVAL 50 // Emit mouse values with approx. every 50ms (=20Hz)

#ifdef QGC_MOUSE_ENABLED_WIN
Mouse6dofInput::Mouse6dofInput(Mouse3DInput* mouseInput) :
    mouse3DMax(0.075),   // TODO: check maximum value fot plugged device
    done(false),
    translationActive(true),
    rotationActive(true),
    xValue(0.0),
    yValue(0.0),
    zValue(0.0),
    aValue(0.0),
    bValue(0.0),
    cValue(0.0)
{
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));
    // Connect 3DxWare SDK MotionEvent
    connect(mouseInput, SIGNAL(Move3d(std::vector<float>&)), this, SLOT(motion3DMouse(std::vector<float>&)));
    connect(mouseInput, SIGNAL(On3dmouseKeyDown(int)), this, SLOT(button3DMouseDown(int)));
    //connect(mouseInput, SIGNAL(On3dmouseKeyUp(int)), this, SLOT(FUNCTION(int)));

}
#endif //QGC_MOUSE_ENABLED_WIN

#ifdef QGC_MOUSE_ENABLED_LINUX
Mouse6dofInput::Mouse6dofInput() :
    mouse3DMaxX(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxY(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxZ(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxA(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxB(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxC(350.0),   // TODO: check maximum value for plugged device
    done(false),
    translationActive(true),
    rotationActive(true),
    xValue(0.0),
    yValue(0.0),
    zValue(0.0),
    aValue(0.0),
    bValue(0.0),
    cValue(0.0)
{
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));

    if (spnav_open() < 0) {
        qDebug("Failed to open spnav (spacenavigator)");
    } else {
        qDebug() << "[Mouse6dofInput] Opened spnav (spacenavigator)";
//        mouseActive = true;
//        emit resetMouseInputStatus(true);
    }

    if (!isRunning())
    {
        start();
    }
}
#endif //QGC_MOUSE_ENABLED_LINUX


Mouse6dofInput::~Mouse6dofInput()
{
    done = true;
}

void Mouse6dofInput::run()
{
    qDebug() << "3d Mouse thread started...";

    // start timer for emits
    QTime time;
    time.start();

    forever
    {
        if (done)
        {
           done = false;
           exit();
        }

#ifdef QGC_MOUSE_ENABLED_LINUX
        pollSpnavEvent();
#endif //QGC_MOUSE_ENABLED_LINUX

        // Use progressive sensibility
        xValue = progressive(xValue);
        yValue = progressive(yValue);
        zValue = progressive(zValue);
        aValue = progressive(aValue);
        bValue = progressive(bValue);
        cValue = progressive(cValue);

        // Bound value to +/-1
        xValue = saturate(xValue);
        yValue = saturate(yValue);
        zValue = saturate(zValue);
        aValue = saturate(aValue);
        bValue = saturate(bValue);
        cValue = saturate(cValue);

        // Only emit with certain time interval
        if (time.elapsed() >= MOUSE3D_EMIT_INTERVAL) {
            time.restart();
//            qDebug() << "[Mouse6dofInput]: Emitting the values:" << xValue << yValue << zValue << aValue << bValue << cValue;
            emit mouse6dofChanged(xValue, yValue, zValue, aValue, bValue, cValue);
        }

        // Sleep - But much less than emit: Be ready again with fresh inputs
        // This is not an exact timer, but quite efficient.
        QGC::SLEEP::msleep(MOUSE3D_EMIT_INTERVAL * 0.2);
    }
}

#ifdef QGC_MOUSE_ENABLED_WIN
void Mouse6dofInput::motion3DMouse(std::vector<float> &motionData)
{
    if (motionData.size() < 6) return;
    mouseActive = true;

    if (translationActive)
    {
        xValue = -(double)(0.05e2f*motionData[ 1 ] / mouse3DMax);
        yValue = (double)(0.05e2f*motionData[ 0 ] / mouse3DMax);
        zValue = (double)(0.05e2f*motionData[ 2 ] / mouse3DMax);
    }else{
        xValue = 0;
        yValue = 0;
        zValue = 0;
    }
    if (rotationActive)
    {
        aValue = -(double)(0.05e2f*motionData[ 4 ] / mouse3DMax);
        bValue = (double)(0.05e2f*motionData[ 3 ] / mouse3DMax);
        cValue = (double)(0.05e2f*motionData[ 5 ] / mouse3DMax);
    }else{
        aValue = 0;
        bValue = 0;
        cValue = 0;
    }

    //qDebug() << "NEW 3D MOUSE VALUES -- X" << xValue << " -- Y" << yValue << " -- Z" << zValue << " -- A" << aValue << " -- B" << bValue << " -- C" << cValue;
}
#endif //QGC_MOUSE_ENABLED_WIN

#ifdef QGC_MOUSE_ENABLED_WIN
void Mouse6dofInput::button3DMouseDown(int button)
{
    switch(button)
    {
    case 1:
    {
            translationActive = !translationActive;
            emit mouseTranslationActiveChanged(translationActive);
            qDebug() << "Changed 3DMouse Translation to" << (bool)translationActive;
        break;
    }
    case 2:
    {
            rotationActive = !rotationActive;
            emit mouseRotationActiveChanged(rotationActive);
            qDebug() << "Changed 3DMouse Rotation to " << (bool)rotationActive;
        break;
    }
    default:
        break;
    }
}
#endif //QGC_MOUSE_ENABLED_WIN

#ifdef QGC_MOUSE_ENABLED_LINUX
void Mouse6dofInput::pollSpnavEvent()
{

    spnav_event spacenavEvent;

    int spacenavEventType = spnav_poll_event(&spacenavEvent);
    switch (spacenavEventType)
    {
        case SPNAV_EVENT_MOTION:
        {
             /**
              * Consider the following axis interpretation
              * X: Mouse front (point where wire is connected)
              * Y: Mouse right
              * Z: Mouse down
              */

             // Check whether translational motions are enabled
             if (translationActive)
             {
                 xValue = spacenavEvent.motion.z / mouse3DMaxX;
                 yValue = spacenavEvent.motion.x / mouse3DMaxY;
                 zValue = - spacenavEvent.motion.y / mouse3DMaxZ;
//                 qDebug() << "Unsaturated Mouse value x" << xValue << "\t y" << yValue << "\t z" << zValue;
             }else{
                 xValue = 0;
                 yValue = 0;
                 zValue = 0;
             }
             // Check whether rotational motions are enabled
             if (rotationActive)
             {
                 aValue = spacenavEvent.motion.rz / mouse3DMaxA;
                 bValue = spacenavEvent.motion.rx / mouse3DMaxB;
                 cValue = - spacenavEvent.motion.ry / mouse3DMaxC;
//                 qDebug() << "Unsaturated Mouse value a" << aValue << "\t b" << bValue << "\t c" << cValue;
             }else{
                 aValue = 0;
                 bValue = 0;
                 cValue = 0;
             }
        break;

        case SPNAV_EVENT_BUTTON :
            qDebug() << "SPNAV button event with button " << spacenavEvent.button.bnum;
            switch (spacenavEvent.button.bnum)
            {
            case 0:
            {
                if (spacenavEvent.button.press == 1) {
                    // Button klicked. Do nothing.
                } else {
                    // Button released. Switch translation.
                    translationActive = !translationActive;
                    emit mouseTranslationActiveChanged(translationActive);
                    qDebug() << "Changed 3DMouse Translation to" << (bool)translationActive;
                }
                break;
            }
            case 1:
            {
                if (spacenavEvent.button.press == 1) {
                    // Button klicked. Do nothing.
                } else {
                    // Button released. Switch rotation.
                    rotationActive = !rotationActive;
                    emit mouseRotationActiveChanged(rotationActive);
                    qDebug() << "Changed 3DMouse Rotation to " << (bool)rotationActive;
                }
                break;
            }
            default:
                break;
            }
        default:
            break;
        }
    }
}
#endif //QGC_MOUSE_ENABLED_LINUX

double Mouse6dofInput::progressive(double value)
{
    // assuming value is in range [-1,1]
    return (value * value * (double)sign(value));
}

double Mouse6dofInput::saturate(double value)
{
    return (qAbs(value) > 1.0) ? (double)sign(value) : value;
}

int Mouse6dofInput::sign(double value)
{
    if (value > 0.0)
        return 1;
    else if (value == 0.0)
        return 0;
    else
        return -1;
}
