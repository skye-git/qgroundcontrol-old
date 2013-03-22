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
    void redColorChanged(int);
    void greenColorChanged(int);
    void blueColorChanged(int);

private slots:
    /** show live color dialog */
    void openColorDialog();
    /** update color */
    void updateColor(QColor newColor);
    /** update widget style */
    void updateWidget();
    
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
