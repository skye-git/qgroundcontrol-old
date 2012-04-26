#ifndef ELEVATIONPOINT_H
#define ELEVATIONPOINT_H

#include <QGraphicsItem>
#include "Waypoint.h"

class ElevationProfileDisplay;

class ElevationPoint : public QGraphicsItem
{
public:
    ElevationPoint(ElevationProfileDisplay *elevationProfileDisplay); //to be removed once the other is working
    ElevationPoint(Waypoint* wp, ElevationProfileDisplay *elevationProfileDisplay);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    Waypoint* wp; //waypoint belonging to this elevationPoint


private:
    ElevationProfileDisplay *display;

};

#endif // ELEVATIONPOINT_H
