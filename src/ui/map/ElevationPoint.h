#ifndef ELEVATIONPOINT_H
#define ELEVATIONPOINT_H

#include <QGraphicsItem>

class ElevationProfileDisplay;

class ElevationPoint : public QGraphicsItem
{
public:
    ElevationPoint(ElevationProfileDisplay *elevationProfileDisplay);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
    ElevationProfileDisplay *display;

};

#endif // ELEVATIONPOINT_H
