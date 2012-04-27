#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "HeightPoint.h"

HeightPoint::HeightPoint(Waypoint* wp, HeightProfile* heightProfile)
    : display(heightProfile)
{
    setFlag(ItemIsMovable);
    this->wp = wp;
}

QRectF HeightPoint::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -20 - adjust,
                  43 + adjust, 43 + adjust);
}

QPainterPath HeightPoint::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void HeightPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
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

    //draw id Number
    QPainterPath textPath;
    QFont timesFont("Times", 20);
    QString waypointid = QString("%1").arg(wp->getId());
    timesFont.setStyleStrategy(QFont::ForceOutline);
    textPath.addText(8, -8, timesFont, waypointid);
    painter->drawPath(textPath);
}

void HeightPoint::updateValues()
{
    ;
}

void HeightPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void HeightPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
