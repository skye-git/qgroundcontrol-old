#ifndef UASSKYEINPUTMIXER_H
#define UASSKYEINPUTMIXER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QTime>

class UASSkyeInputMixer : public QThread
{
    Q_OBJECT

public:
    UASSkyeInputMixer(QWidget *parent = 0);
    ~UASSkyeInputMixer();
    /** @brief accumulate and emit inputs from different devices.
     *  @note values will be scaled by SkyeMAV class.
     **/
    void run();
    /** @brief initialize input values with zeros and current time */
    void init();

public slots:
    /** @brief get new 6dof values from mouse and set timestamp **/
    void updateMouseValues(double x, double y, double z, double a, double b, double c);
    /** @brief get new 6dof values from touchscreen and set timestamp **/
    void updateTouchValues(double x, double y, double z, double a, double b, double c);
    /** @brief get new 6dof values from xbox controller and set timestamp **/
    void updateXboxValues(double x, double y, double z, double a, double b, double c);

signals:
    void changed6DOFInput(double, double, double, double, double, double);

private:

    QWidget *p;                     ///< parent

    double valuesMouse[6];          ///< mouse input values (x,y,z,a,b,c)
    QTime timeMouse;                ///< timestamp of mouse values
    double valuesTouch[6];          ///< touch input values (x,y,z,a,b,c)
    QTime timeTouch;                ///< timestamp of touch screen values
    double valuesXbox[6];           ///< xbox input values  (x,y,z,a,b,c)
    QTime timeXbox;                 ///< timestamp of xbox values

    double valuesAccum[6];          ///< accumulated (mouse & touch) input values (x,y,z,a,b,c)


};

#endif // UASSKYEINPUTMIXER_H
