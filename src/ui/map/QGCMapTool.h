#ifndef QGCMAPTOOL_H
#define QGCMAPTOOL_H

#include <QWidget>
#include <QMenu>

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

    bool touchInputvisib; //Beginn und Ende Code AL (11.04.12)

private:
    Ui::QGCMapTool *ui;
};

#endif // QGCMAPTOOL_H
