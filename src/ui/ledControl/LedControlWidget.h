#ifndef LEDCONTROLWIDGET_H
#define LEDCONTROLWIDGET_H

#include <QWidget>
#include <QColor>
#include <QColorDialog>
#include <QTime>
#include <QString>
#include <UASInterface.h>

#include "UASManager.h"
#include "SkyeUAS.h"

namespace Ui {
class LedControlWidget;
}

class LedControlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LedControlWidget(QWidget *parent = 0);
    ~LedControlWidget();

signals:
    void colorChanged(QColor);
    void redColorChanged(int);
    void greenColorChanged(int);
    void blueColorChanged(int);
    void transmitColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency);

private slots:
    /** set active UAS */
    void setUAS(UASInterface* uas);
    /** show/hide live color dialog */
    void changeColorDialogVisibility();
    /** update color */
    void changeColor(QColor newColor);
    void changeColorRed(int newRed);
    void changeColorGreen(int newGreen);
    void changeColorBlue(int newBlue);
    /** update mode */
    void changeMode(int newMode);
    /** update frequency */
    void changeFrequency (double newFrequency);
    /** update widget style according to color */
    void updateWidget();
    /** Send new color to UAS */
    void sendColor();
    /** Switch LED on/off */
    void setLedEnabled(bool checked);

private:
    QString GetNameForLedColorMode(LED_CONTROL_MODE m);

    Ui::LedControlWidget *ui;
    int uasId;                          ///< Reference to the current uas
    QColor color;                       ///< current color in QColor format
    int red;                            ///< current red RGB part for led color
    int green;                          ///< current green RGB part for led color
    int blue;                           ///< current blue RGB part for led color

    LED_CONTROL_MODE mode;              ///< current led control mode
    double frequency;                   ///< current frequency for led color change
    bool enabled;                       ///< true if LED enabled

    QColorDialog *dialog;               ///< Dialog to choose color
//    bool dialogVisible;                 ///< boolean to hide/show color dialog

    QTime timeOfSubmit;                 ///< Time of last submit
};

#endif // LEDCONTROLWIDGET_H
