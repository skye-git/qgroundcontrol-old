/**
 * @file
 *   @brief 3dConnexion 3dMouse interface for QGroundControl
 *
 *   @author Matthias Krebs <makrebs@student.ethz.ch>
 *
 */

#include "Mouse6dofInput.h"
#include "UAS.h"
#include "UASManager.h"
#include "QMessageBox"

#ifdef MOUSE_ENABLED_LINUX
#include <QX11Info>
#include <X11/Xlib.h>
#ifdef Success
#undef Success              // Eigen library doesn't work if Success is defined
#endif //Success
extern "C"
{
#include "xdrvlib.h"
}
#endif // MOUSE_ENABLED_LINUX

#ifdef MOUSE_ENABLED_WIN
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
#endif //MOUSE_ENABLED_WIN

#ifdef MOUSE_ENABLED_LINUX
Mouse6dofInput::Mouse6dofInput(QWidget* parent) :
    mouse3DMaxX(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxY(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxZ(350.0),   // TODO: check maximum value for plugged device
    mouse3DMaxA(390.0),   // TODO: check maximum value for plugged device
    mouse3DMaxB(390.0),   // TODO: check maximum value for plugged device
    mouse3DMaxC(350.0),   // TODO: check maximum value for plugged device
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
    cValue(0.0),
    parentWidget(parent)
{
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));

//    if (true)       //(!mouseActive)
//    {
////        // man visudo --> then you can omit giving password (success not guarantied..)
////        qDebug() << "Starting 3DxWare Daemon for 3dConnexion 3dMouse";
////        QString processProgramm = "gksudo";
////        QStringList processArguments;
////        processArguments << "/etc/3DxWare/daemon/3dxsrv -d usb";
////        process3dxDaemon = new QProcess();
////        process3dxDaemon->start(processProgramm, processArguments);
////    //    process3dxDaemon->waitForFinished();
////    //    {
////    //        qDebug() << "... continuing without 3DxWare. May not be initialized properly!";
////    //        qDebug() << "Try in terminal as user root:" << processArguments.last();
////    //    }

//        Display *display = QX11Info::display();
//        if(!display)
//        {
//            qDebug() << "Cannot open display!" << endl;
//        }
//        if ( !MagellanInit( display, parent->winId() ) )
//        {
//            QMessageBox msgBox;
//            msgBox.setIcon(QMessageBox::Information);
//            msgBox.setText(tr("No 3DxWare driver is running."));
//            msgBox.setInformativeText(tr("Enter in Terminal 'sudo /etc/3DxWare/daemon/3dxsrv -d usb' and then restart QGroundControl."));
//            msgBox.setStandardButtons(QMessageBox::Ok);
//            msgBox.setDefaultButton(QMessageBox::Ok);
//            msgBox.exec();

//            qDebug() << "No 3DxWare driver is running!";
//            return;
//        }
//        else
//        {
//            qDebug() << "Initialized 3dMouse";
//            mouseActive = true;
//        }
//    }
//    else
//    {
//        qDebug() << "3dMouse already initialized..";
//    }

}
#endif //MOUSE_ENABLED_LINUX


Mouse6dofInput::~Mouse6dofInput()
{
    done = true;
}

void Mouse6dofInput::setActiveUAS(UASInterface* uas)
{
    // Only connect / disconnect is the UAS is of a controllable UAS class
    UAS* tmp = 0;
    if (this->uas)
    {
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(tmp);
        if(mav)
        {
            disconnect(this, SIGNAL(mouse6dofChanged(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
            disconnect(this, SIGNAL(mouseRotationActiveChanged(bool)), mav, SLOT(changeMouseRotationActive(bool)));
            disconnect(this, SIGNAL(mouseTranslationActiveChanged(bool)), mav, SLOT(changeMouseTranslationActive(bool)));
            disconnect(mav, SIGNAL(inputModeChanged(SkyeMAV::QGC_INPUT_MODE)), this, SLOT(updateInputMode(SkyeMAV::QGC_INPUT_MODE)));
        }else{
            tmp = dynamic_cast<UAS*>(this->uas);
            if(tmp)
            {
                disconnect(this, SIGNAL(mouse6dofChanged(double,double,double,double,double,double)), tmp, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
            }
        }
    }

    this->uas = uas;

    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(tmp);
    if(mav)
    {
        connect(this, SIGNAL(mouse6dofChanged(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
        connect(this, SIGNAL(mouseRotationActiveChanged(bool)), mav, SLOT(changeMouseRotationActive(bool)));
        connect(this, SIGNAL(mouseTranslationActiveChanged(bool)), mav, SLOT(changeMouseTranslationActive(bool)));
        connect(this, SIGNAL(resetInputMode(SkyeMAV::QGC_INPUT_MODE)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE)));
        connect(mav, SIGNAL(inputModeChanged(SkyeMAV::QGC_INPUT_MODE)), this, SLOT(updateInputMode(SkyeMAV::QGC_INPUT_MODE)));

        emit mouseRotationActiveChanged(this->rotationActive);
        emit mouseTranslationActiveChanged(this->translationActive);
    }else{

        tmp = dynamic_cast<UAS*>(this->uas);
        if(tmp)
        {
            connect(this, SIGNAL(mouse6dofChanged(double,double,double,double,double,double)), tmp, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
        }
    }

    if (!isRunning())
    {
        start();
    }
}

void Mouse6dofInput::init()
{
    // Make sure active UAS is set
    setActiveUAS(UASManager::instance()->getActiveUAS());
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

            SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
            if (mav)
            {
                if (mav->getInputMode() == SkyeMAV::QGC_INPUT_MODE_MOUSE)
                {
                    emit mouse6dofChanged(xValue, yValue, zValue, aValue, bValue, cValue);
                }
            }else{
                emit mouse6dofChanged(xValue, yValue, zValue, aValue, bValue, cValue);
            }
        }

        // Sleep - Update rate of 3d mouse is approx. 20 Hz (1000 ms / 20 Hz = 50 ms)
        QGC::SLEEP::msleep(50);
    }
}

#ifdef MOUSE_ENABLED_WIN
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
#endif //MOUSE_ENABLED_WIN

#ifdef MOUSE_ENABLED_WIN
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
#endif //MOUSE_ENABLED_WIN

#ifdef MOUSE_ENABLED_LINUX
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
#endif //MOUSE_ENABLED_LINUX


void Mouse6dofInput::updateInputMode(SkyeMAV::QGC_INPUT_MODE inputMode)
{
#ifdef MOUSE_ENABLED_WIN
    if (inputMode == SkyeMAV::QGC_INPUT_MODE_MOUSE)
    {
        mouseActive = true;
    }else{
        mouseActive = false;
    }
#endif //MOUSE_ENABLED_WIN

#ifdef MOUSE_ENABLED_LINUX
    if (inputMode == SkyeMAV::QGC_INPUT_MODE_MOUSE)
    {
        ///////////////// Reinitialize 3DMouse //////////////////
        display = QX11Info::display();
        if(!display)
        {
            qDebug() << "[update] Cannot open display!" << endl;
        }
        if ( !MagellanInit( display, parentWidget->winId() ) )
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText(tr("No 3DxWare driver is running."));
            msgBox.setInformativeText(tr("Enter in Terminal 'sudo /etc/3DxWare/daemon/3dxsrv -d usb' and then restart QGroundControl."));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();

            emit resetInputMode(SkyeMAV::QGC_INPUT_MODE_NONE);
            qDebug() << "[update] No 3DxWare driver is running!";
        }
        else
        {
            qDebug() << "[update] Initialized 3dMouse";
            mouseActive = true;
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
#endif // MOUSE_ENABLED_LINUX
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
