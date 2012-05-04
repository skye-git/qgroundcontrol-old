#ifndef ELEVATIONPOINT_H
#define ELEVATIONPOINT_H

#include <QGraphicsItem>
#include "Waypoint.h"

class HeightProfile;

class ElevationPoint : public QGraphicsObject
{
public:
    ElevationPoint(HeightProfile* parent, QColor color);

    void refreshToolTip();

    void setPos(qreal x, qreal y);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor color;
    double elevation;

protected:
//    Waypoint* wp;
    HeightProfile * parent;

};

#endif // ELEVATIONPOINT_H
