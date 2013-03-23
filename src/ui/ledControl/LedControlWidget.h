#ifndef LEDCONTROLWIDGET_H
#define LEDCONTROLWIDGET_H

#include <QWidget>
#include <QColor>
#include <QColorDialog>
#include <UASInterface.h>

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
    /** show live color dialog */
    void openColorDialog();
    /** update color */
    void updateColor(QColor newColor);
    void changedColorRed(int newRed);
    void changedColorGreen(int newGreen);
    void changedColorBlue(int newBlue);
    /** update widget style */
    void updateWidget();
    /** Send new color to UAS */
    void sendColor(QColor newColor);

private:
    Ui::LedControlWidget *ui;
    int uasId;                          ///< Reference to the current uas
    QColor color;                       ///< current color in QColor format
    uint16_t red;                       ///< current 16bit red RGB part for led color
    uint16_t green;                     ///< current 16bit red RGB part for led color
    uint16_t blue;                      ///< current 16bit red RGB part for led color

    QColorDialog *dialog;               ///< Dialog to choose color
};

#endif // LEDCONTROLWIDGET_H
