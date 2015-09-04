#include "InputMixer.h"
#include "QGC.h"
#include <QDebug>

#define INPUTMIXER_MAX_DELAY_MS 100     // Values older than this will be cancelled
#define INPUTMIXER_PERIOD_MS 50         // Approx. input period time

UASSkyeInputMixer::UASSkyeInputMixer(QWidget *parent)
{
    init();
}

UASSkyeInputMixer::~UASSkyeInputMixer()
{
    this->deleteLater();
    /* destructor */
}

void UASSkyeInputMixer::init()
{

    // init input arrays
    for (int i=0; i<6; i++)
    {
        valuesMouse[i] = 0.0;
        valuesTouch[i] = 0.0;
        valuesXbox[i] = 0.0;

        valuesAccum[i] = 0.0;
    }

    // reset time
    timeMouse.start();
    timeTouch.start();
}

/** @brief Emit the sum of 3dmouse, touch and xbox input values every 50ms */
void UASSkyeInputMixer::run()
{
    forever
    {
        // clean input
        for (int i=0; i<6; i++) {
            valuesAccum[i] = 0.0;
        }

        // sum up inputs from devices
        // last input from device must not be older than threshold
        if (timeMouse.elapsed() < INPUTMIXER_MAX_DELAY_MS) {
            for (int i=0; i<6; i++) {
                valuesAccum[i] = valuesAccum[i] + valuesMouse[i];
            }
        }

        if (timeTouch.elapsed() < INPUTMIXER_MAX_DELAY_MS) {
            for (int i=0; i<6; i++) {
                valuesAccum[i] = valuesAccum[i] + valuesTouch[i];
            }
        }

        if (timeXbox.elapsed() < INPUTMIXER_MAX_DELAY_MS) {
            for (int i=0; i<6; i++) {
                valuesAccum[i] = valuesAccum[i] + valuesXbox[i];
            }
        }

        // saturate values
        for (int i=0; i<6; i++) {
            valuesAccum[i] = valuesAccum[i] >  1.0 ?  1.0 : valuesAccum[i];
            valuesAccum[i] = valuesAccum[i] < -1.0 ? -1.0 : valuesAccum[i];
        }

        //qDebug() << "[MIXER] Emit accumulated values" << valuesAccum[0] << valuesAccum[1] << valuesAccum[2] << valuesAccum[3] << valuesAccum[4] << valuesAccum[5];

        // emit inputs with approx 20Hz
        emit changed6DOFInput(valuesAccum[0],
                              valuesAccum[1],
                              valuesAccum[2],
                              valuesAccum[3],
                              valuesAccum[4],
                              valuesAccum[5] );

        // Sleep - Emit by approx. 20 Hz (1000 ms / 20 Hz = 50 ms)
        QGC::SLEEP::msleep(INPUTMIXER_PERIOD_MS);
    }
}

void UASSkyeInputMixer::updateMouseValues(double x, double y, double z, double a, double b, double c)
{
    // update time and values
    timeMouse.restart();

    valuesMouse[0] = x;
    valuesMouse[1] = y;
    valuesMouse[2] = z;
    valuesMouse[3] = a;
    valuesMouse[4] = b;
    valuesMouse[5] = c;

    //qDebug() << "[MIXER] Update Mouse values" << x << y << z << a << b << c;
}

void UASSkyeInputMixer::updateTouchValues(double x, double y, double z, double a, double b, double c)
{

    // update time and values
    timeTouch.restart();

    valuesTouch[0] = x;
    valuesTouch[1] = y;
    valuesTouch[2] = z;
    valuesTouch[3] = a;
    valuesTouch[4] = b;
    valuesTouch[5] = c;

    //qDebug() << "[MIXER] Update Touch values" << x << y << z << a << b << c;
}

void UASSkyeInputMixer::updateXboxValues(double x, double y, double z, double a, double b, double c)
{

    // update time and values
    timeXbox.restart();

    valuesXbox[0] = x;
    valuesXbox[1] = y;
    valuesXbox[2] = z;
    valuesXbox[3] = a;
    valuesXbox[4] = b;
    valuesXbox[5] = c;

    //qDebug() << "[MIXER] Update Xbox values" << x << y << z << a << b << c;
}

