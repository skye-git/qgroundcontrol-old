/**
 * @file
 *   @brief Definition of Xbox Controller interface for QGroundControl
 *
 *   @author Roman Ebneter rebneter@student.ethz.ch
 *
 */

#ifndef XBOXCONTROLLER_H
#define XBOXCONTROLLER_H

//#ifdef MOUSE_ENABLED_LINUX
#include "thirdParty/xbox/joystick.h"
//#endif //MOUSE_ENABLED_WIN

#include <QThread>

#include "UAS.h"
#include "UASManager.h"
#include "UASInterface.h"
#include "SkyeMAV.h"


#define XBOX_RESOLUTION_AXIS 32768
#define XBOX_THRESHOLD_AXIS 5000
#define XBOX_RESOLUTION_TRIGGER 255
#define XBOX_THRESHOLD_TRIGGER 10
#define XBOX_PROGRESSION_FACTOR 0.5 //the higher, the stronger the progressrion (1-a)*x+a*x²
#define XBOX_FILTER_FACTOR 0.2 //the higher, the lower the cutoff freqency a*x_old+(1-a)*x_new
#define XBOX_ZERO_SNAP_THRESHOLD 0.001
#define XBOX_XAXIS 1
#define XBOX_YAXIS 0
#define XBOX_ZAXIS1 5
#define XBOX_ZAXIS2 4
#define XBOX_CAXIS 2
#define XBOX_BAXIS 3
#define XBOX_AAXIS  6
#define XBOX_UPLIFT_PLUS_BUTTON 3
#define XBOX_UPLIFT_MINUS_BUTTON 1


class XboxController : public QThread
{
    Q_OBJECT
public:
    XboxController();
    void init();
    void run();
    double progressive(double);
    double zerosnap(double);
    double normalize(double);
    int sign(double);
protected:
    Joystick joystick_;

    UASInterface* uas;
    bool done;
    bool xboxActive;
    double xValue;
    double yValue;
    double zValue;
    double aValue;
    double bValue;
    double cValue;
    int liftValue;
    int liftValueButtonCounter;

signals:
    void xboxControllerChanged(double x, double y, double z, double a, double b, double c);
    void setLiftValue(int up);

public slots:
    void setActiveUAS(UASInterface* uas);
    void updateInputMode(SkyeMAV::QGC_INPUT_MODE inputMode);
    void liftValueChanged(int up);

};

#endif // XBOXCONTROLLER_H
