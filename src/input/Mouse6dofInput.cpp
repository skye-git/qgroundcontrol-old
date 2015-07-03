//#include "QX11Info"
//#include "QDebug"
//#include "XdrvlibIncludes.h"
//#include "Mouse6dofInput.h"


//Mouse6dofInput::Mouse6dofInput(QWidget *parent) {

//MagellanFloatEvent MagellanEvent;

//Display *display = QX11Info::display();
//if(!display)
//{
//    qDebug() << "Cannot open display!" << endl;
//}

//XEvent *event;

//switch (event->type)
//{
//case ClientMessage:
//  switch( MagellanTranslateEvent( display, event, &MagellanEvent, 1.0, 1.0 ) )
//  {
//    case MagellanInputMotionEvent :
//         MagellanRemoveMotionEvents( display );
//  }
//}
//}


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
#include <QX11Info>
#endif // QGC_MOUSE_ENABLED_LINUX

#ifdef QGC_MOUSE_ENABLED_WIN
Mouse6dofInput::Mouse6dofInput(Mouse3DInput* mouseInput) :
    mouse3DMax(0.075),   // TODO: check maximum value fot plugged device
    uas(NULL),
    done(false),
    mouseActive(false),
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
Mouse6dofInput::Mouse6dofInput(QWidget* parent) :
    mouse3DMaxX(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxY(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxZ(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxA(390.0),   // TODO: check maximum value for plugged device
    mouse3DMaxB(390.0),   // TODO: check maximum value for plugged device
    mouse3DMaxC(350.0),   // TODO: check maximum value for plugged device
    parentWidget(parent),
    timerInit3dxDaemon(NULL),
    uasId(0),
    done(false),
    mouseActive(false),
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
}
#endif //QGC_MOUSE_ENABLED_LINUX


Mouse6dofInput::~Mouse6dofInput()
{
    done = true;
}

#ifdef QGC_USE_SKYE_MESSAGES_AAA
void Mouse6dofInput::setActiveUAS(UASInterface* uas)
{
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        this->uasId = 0;
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(oldUAS);
        if (mav)
        {
            disconnect(mav, SIGNAL(inputModeChanged(int)), this, SLOT(updateInputMode(int)));
        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        qDebug() << "[Mouse6DOF] connecting uav slots";

        connect(mav, SIGNAL(inputModeChanged(int)), this, SLOT(updateInputMode(int)));
        connect(this, SIGNAL(resetMouseInputStatus(bool)), mav, SLOT(updateMouseInputStatus(bool)));
    }



    if (!isRunning())
    {
        start();
    }
}
#endif //QGC_USE_SKYE_MESSAGES

void Mouse6dofInput::init()
{
#ifdef QGC_USE_SKYE_MESSAGES_AAA
    // Make sure active UAS is set
    setActiveUAS(UASManager::instance()->getActiveUAS());
#endif //QGC_USE_SKYE_MESSAGES
}

void Mouse6dofInput::run()
{
    init();

    forever
    {
        if (done)
        {
           done = false;
           exit();
        }

        if (mouseActive)
        {
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

            emit mouse6dofChanged(xValue, yValue, zValue, aValue, bValue, cValue);
        }

        // Sleep - Update rate of 3d mouse is approx. 20 Hz (1000 ms / 20 Hz = 50 ms)
        QGC::SLEEP::msleep(50);
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
void Mouse6dofInput::handleX11Event(XEvent *event)
{
    //qDebug("XEvent occured...");
    if (!mouseActive)
    {
//        qDebug() << "3dMouse not initialized. Cancelled handling X11event for 3dMouse";
        return;
    }

    MagellanFloatEvent MagellanEvent;

    display = QX11Info::display();
    if(!display)
    {
        qDebug() << "Cannot open display!" << endl;
    }

    switch (event->type)
    {
    case ClientMessage:
      switch( MagellanTranslateEvent( display, event, &MagellanEvent, 1.0, 1.0 ) )
      {
        case MagellanInputMotionEvent :
             MagellanRemoveMotionEvents( display );

             /**
              * Consider the following axis interpretation
              * X: Mouse front (point where wire is connected)
              * Y: Mouse right
              * Z: Mouse down
              */

             // Check whether translational motions are enabled
             if (translationActive)
             {
                 xValue = MagellanEvent.MagellanData[ MagellanZ ] / mouse3DMaxX;
                 yValue = MagellanEvent.MagellanData[ MagellanX ] / mouse3DMaxY;
                 zValue = - MagellanEvent.MagellanData[ MagellanY ] / mouse3DMaxZ;
//                 qDebug() << "Unsaturated Mouse value x" << xValue << "\t y" << yValue << "\t z" << zValue;
             }else{
                 xValue = 0;
                 yValue = 0;
                 zValue = 0;
             }
             // Check whether rotational motions are enabled
             if (rotationActive)
             {
                 aValue = MagellanEvent.MagellanData[ MagellanC ] / mouse3DMaxA;
                 bValue = MagellanEvent.MagellanData[ MagellanA ] / mouse3DMaxB;
                 cValue = - MagellanEvent.MagellanData[ MagellanB ] / mouse3DMaxC;
//                 qDebug() << "Unsaturated Mouse value a" << aValue << "\t b" << bValue << "\t c" << cValue;
             }else{
                 aValue = 0;
                 bValue = 0;
                 cValue = 0;
             }
             // Saturation
             xValue = saturate(xValue);
             yValue = saturate(yValue);
             zValue = saturate(zValue);
             aValue = saturate(aValue);
             bValue = saturate(bValue);
             cValue = saturate(cValue);
             //qDebug() << "NEW 3D MOUSE VALUES -- X" << xValue << " -- Y" << yValue << " -- Z" << zValue << " -- A" << aValue << " -- B" << bValue << " -- C" << cValue;
        break;

        case MagellanInputButtonPressEvent :
            qDebug() << "MagellanInputButtonPressEvent called with button " << MagellanEvent.MagellanButton;
            switch (MagellanEvent.MagellanButton)
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
        default:
            break;
        }
    }
}
#endif //QGC_MOUSE_ENABLED_LINUX

void Mouse6dofInput::updateInputMode(int inputMode)
{
#ifdef QGC_MOUSE_ENABLED_WIN
    if (inputMode & QGC_INPUT_MODE_MOUSE)
    {
        mouseActive = true;
    }else{
        mouseActive = false;
    }
#endif //QGC_MOUSE_ENABLED_WIN

#ifdef QGC_MOUSE_ENABLED_LINUX
    qDebug() << "[Mouse6dofInput] update input called with" << inputMode;
    if (inputMode & QGC_INPUT_MODE_MOUSE)
    {
        if (!mouseActive)
        {
            ///////////////// Reinitialize 3DMouse //////////////////
            display = QX11Info::display();
            if(!display)
            {
                qDebug() << "[Mouse6dofInput] Cannot open display!" << endl;
            }
            if ( !MagellanInit( display, parentWidget->winId() ) )
            {
    //            QMessageBox msgBox;
    //            msgBox.setIcon(QMessageBox::Information);
    //            msgBox.setText(tr("No 3DxWare driver is running."));
    //            msgBox.setInformativeText(tr("Enter in Terminal 'sudo /etc/3DxWare/daemon/3dxsrv -d usb' and then restart QGroundControl."));
    //            msgBox.setStandardButtons(QMessageBox::Ok);
    //            msgBox.setDefaultButton(QMessageBox::Ok);
    //            msgBox.exec();

                qDebug() << "Starting 3DxWare Daemon for 3dConnexion 3dMouse";
                QString processProgramm = "gksudo";
                QStringList processArguments;
                processArguments << "/etc/3DxWare/daemon/3dxsrv -d usb";
                process3dxDaemon = new QProcess();
                process3dxDaemon->start(processProgramm, processArguments);

                // 3dxsrv was not running, therefore deactivate 3dMouse input
                emit resetMouseInputStatus(false);
            }
            else
            {
                qDebug() << "[Mouse6dofInput] Initialized 3dMouse";
                mouseActive = true;
                emit resetMouseInputStatus(true);
            }
        } else {
            // mouseActive already true. Do nothing.
        }
    }
    else
    {
        if (mouseActive)
        {
            MagellanClose(display);
            mouseActive = false;
        }
    }
#endif // QGC_MOUSE_ENABLED_LINUX
}

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
