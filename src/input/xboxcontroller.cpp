#include "xboxcontroller.h"

XboxController::XboxController():
    uas(NULL),
    done(false),
    xboxActive(false),
    xValue(0.0),
    yValue(0.0),
    zValue(0.0),
    aValue(0.0),
    bValue(0.0),
    cValue(0.0),
    liftValue(0),
    liftValueButtonCounter(5)
{
    joystick_.init("/dev/input/js0");
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));
}

void XboxController::init()
{
    // Make sure active UAS is set
    setActiveUAS(UASManager::instance()->getActiveUAS());
}

void XboxController::run()
{
    init();

    forever
    {
        if (done)
        {
           done = false;
           exit();
        }

        if (xboxActive)
        {
            xValue = zerosnap(XBOX_FILTER_FACTOR*xValue + (1-XBOX_FILTER_FACTOR)*progressive(normalize(joystick_.getAxis(XBOX_XAXIS))));
            yValue = zerosnap(XBOX_FILTER_FACTOR*yValue + (1-XBOX_FILTER_FACTOR)*progressive(normalize(joystick_.getAxis(XBOX_YAXIS))));
            bValue = zerosnap(XBOX_FILTER_FACTOR*bValue + (1-XBOX_FILTER_FACTOR)*progressive(normalize(joystick_.getAxis(XBOX_BAXIS))));
            cValue = zerosnap(XBOX_FILTER_FACTOR*cValue + (1-XBOX_FILTER_FACTOR)*progressive(normalize(joystick_.getAxis(XBOX_CAXIS))));

            zValue = zerosnap(XBOX_FILTER_FACTOR*zValue + (1-XBOX_FILTER_FACTOR)*progressive((joystick_.getAxis(XBOX_ZAXIS1)-joystick_.getAxis(XBOX_ZAXIS2))/XBOX_RESOLUTION_TRIGGER));

            if (joystick_.getButton(XBOX_AAXIS) > 0 and aValue < 0.99)
            {
                aValue += 0.01;
            }
            else if (joystick_.getButton(XBOX_AAXIS) < 0 and aValue > -0.99)
            {
                aValue -= 0.01;
            }
            else
            {
               aValue = 0;
            }

            if (joystick_.getButton(XBOX_UPLIFT_PLUS_BUTTON) and !joystick_.getButton(XBOX_UPLIFT_MINUS_BUTTON) and liftValue <= LIFT_RESOLUTION-1)
            {
                switch (liftValueButtonCounter)
                {
                case 0:
                case 5:
                    emit setLiftValue(++liftValue);
                    liftValueButtonCounter--;
                    break;
                default:
                    liftValueButtonCounter--;
                }
            }
            else if (joystick_.getButton(XBOX_UPLIFT_MINUS_BUTTON) and !joystick_.getButton(XBOX_UPLIFT_PLUS_BUTTON) and liftValue >= 1)
            {
                switch (liftValueButtonCounter)
                {
                case 0:
                case 5:
                    emit setLiftValue(--liftValue);
                    liftValueButtonCounter--;
                    break;
                default:
                    liftValueButtonCounter--;
                }
            }
            else
            {
                liftValueButtonCounter = 5;
            }


            SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
            if (mav)
            {
                if (mav->getInputMode() == SkyeMAV::QGC_INPUT_MODE_MOUSE)
                {
                    emit xboxControllerChanged(xValue, yValue, zValue, aValue, bValue, cValue);
                }
            }else{
                emit xboxControllerChanged(xValue, yValue, zValue, aValue, bValue, cValue);
            }
        }

        // Sleep - Update rate is approx. 20 Hz (1000 ms / 20 Hz = 50 ms)
        QGC::SLEEP::msleep(50);
    }
}



void XboxController::setActiveUAS(UASInterface* uas)
{
    // Only connect / disconnect is the UAS is of a controllable UAS class
    UAS* tmp = 0;
    if (this->uas)
    {
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(tmp);
        if(mav)
        {
            //disconnect(this, SIGNAL(xboxControllerChanged(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
            disconnect(this, SIGNAL(SetLiftValue(int)), mav, SLOT(setLiftValue(int)));
            disconnect(mav, SIGNAL(liftValueChanged(int)), this, SLOT(liftValueChanged(int)));
            disconnect(mav, SIGNAL(inputModeChanged(SkyeMAV::QGC_INPUT_MODE)), this, SLOT(updateInputMode(SkyeMAV::QGC_INPUT_MODE)));
        }else{
            tmp = dynamic_cast<UAS*>(this->uas);
            if(tmp)
            {
                disconnect(this, SIGNAL(xboxControllerChanged(double,double,double,double,double,double)), tmp, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
            }
        }
    }

    this->uas = uas;

    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(tmp);
    if(mav)
    {
        //connect(this, SIGNAL(xboxControllerChanged(double,double,double,double,double,double)), mav, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
        connect(this, SIGNAL(SetLiftValue(int)), mav, SLOT(setLiftValue(int)));
        connect(mav, SIGNAL(liftValueChanged(int)), this, SLOT(liftValueChanged(int)));
        connect(this, SIGNAL(resetInputMode(SkyeMAV::QGC_INPUT_MODE)), mav, SLOT(setInputMode(SkyeMAV::QGC_INPUT_MODE)));
        connect(mav, SIGNAL(inputModeChanged(SkyeMAV::QGC_INPUT_MODE)), this, SLOT(updateInputMode(SkyeMAV::QGC_INPUT_MODE)));

    }else{

        tmp = dynamic_cast<UAS*>(this->uas);
        if(tmp)
        {
            connect(this, SIGNAL(xboxControllerChanged(double,double,double,double,double,double)), tmp, SLOT(setManual6DOFControlCommands(double,double,double,double,double,double)));
        }
    }

    if (!isRunning())
    {
        start();
    }

}

void XboxController::updateInputMode(SkyeMAV::QGC_INPUT_MODE inputMode)
{
    if (inputMode == SkyeMAV::QGC_INPUT_MODE_XBOX)
    {
        xboxActive = true;
        emit setLiftValue(0);
    }else{
        xboxActive = false;
    }
}

void XboxController::liftValueChanged(int val)
{
    liftValue = val;
}


double XboxController::progressive(double value)
{
    // assuming value is in range [-1,1]
    return ((1-XBOX_PROGRESSION_FACTOR)*value+XBOX_PROGRESSION_FACTOR*value * value * (double)sign(value));
}

double XboxController::normalize(double value)
{
    if (value < XBOX_THRESHOLD_AXIS and value >-XBOX_THRESHOLD_AXIS)
    {
        return 0;
    }
    else if(value < -XBOX_RESOLUTION_AXIS or value > XBOX_RESOLUTION_AXIS)
    {
        /*TODO return error */
        return 0;
    }
    else
    {
        if (value < 0) return (value + XBOX_THRESHOLD_AXIS) / (XBOX_RESOLUTION_AXIS-XBOX_THRESHOLD_AXIS);
        return (value - XBOX_THRESHOLD_AXIS) / (XBOX_RESOLUTION_AXIS-XBOX_THRESHOLD_AXIS);
    }
}

double XboxController::zerosnap(double value)
{
    if (value < XBOX_ZERO_SNAP_THRESHOLD and value >-XBOX_ZERO_SNAP_THRESHOLD)
    {
        return 0;
    }
    return value;
}

int XboxController::sign(double val)
{
    return (0 < val) - (val < 0);
}
