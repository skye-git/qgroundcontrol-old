#ifndef QGCMAPTOOL_H
#define QGCMAPTOOL_H

#include <QWidget>
#include <QMenu>
#include "UASInterface.h"
#include "UASManager.h"
#include "SkyeMAV.h"

namespace Ui {
    class QGCMapTool;
}

class QGCMapTool : public QWidget
{
    Q_OBJECT

public:
    explicit QGCMapTool(QWidget *parent = 0);
    ~QGCMapTool();

public slots:
    /** @brief Set the system this widget controls */       // Beginn Code MA (23.04.2012)
    void setUAS(UASInterface* uas);
    /** @brief Update the mode */
    void updateMode(int uas,int baseMode);                 // Ende Code MA
    /** @brief Update slider zoom from map change */
    void setZoom(int zoom);
    void setRingvisible(bool visib); //Beginn/Ende Code AL (26.03.12)
    void transmitMapRingvalues(double, double, double); //Beginn/Ende Code AL (11.04.12)

signals:
    void visibilityChanged(bool visible);
    void valueTouchInputChangedMap(double,double,double); // Beginn/Ende Code AL (11.04.12)

protected:
    void showEvent(QShowEvent* event)
    {
        QWidget::showEvent(event);
        emit visibilityChanged(true);
    }

    void hideEvent(QHideEvent* event)
    {
        QWidget::hideEvent(event);
        emit visibilityChanged(false);
    }

    void resizeEvent(QResizeEvent *event);//Beginn und Ende Code AL (18.03.12)

    bool touchInputvisib;     ///< Visibility of Touch Ring     //Beginn und Ende Code AL (11.04.12)
    bool touchInputModeSet;   ///< True if InputMode == TOUCH   //Beginn und Ende Code MA (23.04.12)

private:
    int uasId;                          ///< Reference to the current uas
    unsigned int uasMode;               ///< Current uas mode
    Ui::QGCMapTool *ui;
};

#endif // QGCMAPTOOL_H
