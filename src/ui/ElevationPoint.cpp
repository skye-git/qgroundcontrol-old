#include "ElevationPoint.h"
#include <QPainter>
#include <QStyleOption>

#include "HeightProfile.h"

ElevationPoint::ElevationPoint(HeightProfile*parent, QColor color)
    : elevation(0),
      color(color),
      parent(parent)
{
    setFlag(ItemStacksBehindParent);
    refreshToolTip();
}

void ElevationPoint::refreshToolTip()
{
    setToolTip(QString("Elevation Point\nAltitude: %1 m (MSL)").arg(QString::number(elevation)));
}

void ElevationPoint::setPos(qreal x, qreal y)
{
    QGraphicsItem::setPos(x,y);
    refreshToolTip();
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
        gradient.setColorAt(1, QColor(Qt::green).light(120));
        gradient.setColorAt(0, QColor(Qt::darkGreen).light(120));
    } else {
        gradient.setColorAt(0, Qt::green);
        gradient.setColorAt(1, Qt::darkGreen);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}
