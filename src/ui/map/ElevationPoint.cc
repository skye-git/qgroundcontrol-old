#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "ElevationPoint.h"
#include "ElevationProfileDisplay.h"

ElevationPoint::ElevationPoint(ElevationProfileDisplay *elevationProfileDisplay)
    : display(elevationProfileDisplay)
{
    setFlag(ItemIsMovable);
}

ElevationPoint::ElevationPoint(Waypoint* wp, ElevationProfileDisplay *elevationProfileDisplay)
    : display(elevationProfileDisplay)
{
    setFlag(ItemIsMovable);
    this->wp = wp;
}

QRectF ElevationPoint::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust,
                  23 + adjust, 23 + adjust);
}

QPainterPath ElevationPoint::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void ElevationPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

void ElevationPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void ElevationPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

