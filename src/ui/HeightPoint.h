#ifndef HEIGHTPOINT_H
#define HEIGHTPOINT_H

#include <QGraphicsItem>
#include "Waypoint.h"
#include "HeightProfile.h"

class HeightPoint : public QGraphicsItem
{
public:
    HeightPoint(Waypoint* wp, HeightProfile *heightProfile);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void updateValues(void);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    Waypoint* wp; //waypoint data container this item represents.

private:
    HeightProfile *display;
    //QGraphicsSimpleTextItem* numberI; //to display wp's id number

signals:
    void move(Waypoint*);



};

#endif // HEIGHTPOINT_H
