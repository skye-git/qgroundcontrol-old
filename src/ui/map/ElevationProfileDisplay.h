#ifndef ELEVATIONPROFILEDISPLAY_H
#define ELEVATIONPROFILEDISPLAY_H

#include <QtGui/QGraphicsView>

class ElevationProfileDisplay : public QGraphicsView
{
    Q_OBJECT
public:
    ElevationProfileDisplay(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void wheelEvent(QWheelEvent *event);


    void scaleView(qreal scaleFactor);

private:
    
};

#endif // ELEVATIONPROFILEDISPLAY_H
