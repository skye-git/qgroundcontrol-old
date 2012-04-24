#include "ElevationProfileDisplay.h"
#include "ElevationPoint.h"

#include <QtGui>

#include <math.h>

ElevationProfileDisplay::ElevationProfileDisplay(QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    //scale(qreal(0.3), qreal(0.3));
    setMinimumSize(200, 200);
    setWindowTitle(tr("Elastic Nodes"));

    ElevationPoint *point1 = new ElevationPoint(this);
    ElevationPoint *point2 = new ElevationPoint(this);

    scene->addItem(point1);
    scene->addItem(point2);

    point1->setPos(0,0);
    point2->setPos(20, 20);
}

void ElevationProfileDisplay::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void ElevationProfileDisplay::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
