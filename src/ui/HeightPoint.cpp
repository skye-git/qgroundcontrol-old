#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>


#include "HeightPoint.h"

#include "HeightProfile.h"

HeightPoint::HeightPoint(HeightProfile* parent, Waypoint* wp, QColor color, int listindex)
    :  parent(parent),
       wp(wp),
       color(color),
       oldMousePos(0,0)
{
    elevationPoint = new ElevationPoint(parent,Qt::red);
    setNumber(listindex);
    setFlag(ItemIsMovable);
    //setParent(parent);

    //connect waypoint and this item
    //connect(this, SIGNAL(move(double)), wp, SLOT(setAltitude(double)));
    connect(wp, SIGNAL(changed(Waypoint*)), this, SLOT(updateHeightPoint(Waypoint*)));
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

void HeightPoint::setPos(qreal x, qreal y)
{
    elevationPoint->setPos(x, elevationPoint->y());
    QGraphicsItem::setPos(x,y);
}

void HeightPoint::setNumber(const int &value)
{
    number = value;
    this->update();
}

void HeightPoint::updateHeightPoint(Waypoint *_wp)
{
    this->setY(-(_wp->getAltitude()));
}


void HeightPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    oldMousePos = this->pos();//event->scenePos();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void HeightPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    wp->setAltitude(-(this->y()));
    //emit move(-(this->y()));
}

void HeightPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "The  Items corrdinates are " << this->pos();
    this->setPos(oldMousePos.x(), event->scenePos().y());
    //QGraphicsItem::mouseMoveEvent(event);
}
