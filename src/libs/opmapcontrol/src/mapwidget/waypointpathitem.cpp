#include "waypointpathitem.h"

namespace mapcontrol
{
WaypointPathItem::WaypointPathItem(QPolygonF* poly, QColor color, mapcontrol::MapGraphicItem* map) :
    QGraphicsPathItem(map),
    polyLatLng(poly),
    map(map)
{
    // Make sure this stick to the map
    //this->setFlag(QGraphicsItem::Item,true);
    setParentItem(map);

    // Set up the pen for this icon with the UAV color
    QPen pen(color);
    pen.setWidth(2);
    setPen(pen);

    // Pixel coordinates of the local points
    QPolygonF polyLocal;
    for (int i = 0; i < polyLatLng->size(); i++)
    {
        internals::PointLatLng pointLatLong;
        double newX = poly->at(i).x();
        double newY = poly->at(i).y();
//        qDebug() << "CONSTRUCTOR Point" << i << "of Polygon at" << newX << newY;
        pointLatLong.SetLat(newX);
        pointLatLong.SetLng(newY);
        core::Point localPoint = map->FromLatLngToLocal(pointLatLong);
        polyLocal.append( QPoint( localPoint.X(), localPoint.Y() ) );
    }
    // Draw Path
    QPainterPath pathLocal;
    pathLocal.addPolygon(polyLocal);
    setPath(pathLocal);

    // Map Zoom and move
    connect(map, SIGNAL(mapChanged()), this, SLOT(updateWPValues())); // FIXME DANGER !! mapChanged is emited very often !!
}

WaypointPathItem::WaypointPathItem(QVector<double> height, QVector<double> horizontalDistance, QColor color, MapGraphicItem *parent)
 //   QGraphicsPathItem(map),
 //   polyLatLng(poly),
 //   map(map)
{
//    // Make sure this stick to the map
//    //this->setFlag(QGraphicsItem::Item,true);
//    setParentItem(map);

//    // Set up the pen for this icon with the UAV color
//    QPen pen(color);
//    pen.setWidth(2);
//    setPen(pen);

//    // Pixel coordinates of the local points
//    QPolygonF polyLocal;
//    for (int i = 0; i < polyLatLng->size(); i++)
//    {
//        internals::PointLatLng pointLatLong;
//        double newX = poly->at(i).x();
//        double newY = poly->at(i).y();
////        qDebug() << "CONSTRUCTOR Point" << i << "of Polygon at" << newX << newY;
//        pointLatLong.SetLat(newX);
//        pointLatLong.SetLng(newY);
//        core::Point localPoint = map->FromLatLngToLocal(pointLatLong);
//        polyLocal.append( QPoint( localPoint.X(), localPoint.Y() ) );
//    }
//    // Draw Path
//    QPainterPath pathLocal;
//    pathLocal.addPolygon(polyLocal);
//    setPath(pathLocal);

//    // Map Zoom and move
//    connect(map, SIGNAL(mapChanged()), this, SLOT(updateWPValues())); // FIXME DANGER !! mapChanged is emited very often !!
}

void WaypointPathItem::RefreshPos()
{
    {

        // Set new pixel coordinates based on new global coordinates
        QPolygonF polyLocal;
        if ( polyLatLng ) {
            for (int i = 0; i < polyLatLng->size(); i++)
            {
                internals::PointLatLng pointLatLong;
                double newX = polyLatLng->at(i).x();
                double newY = polyLatLng->at(i).y();
                qDebug() << "REFRESH POS Point" << i << "of Polygon at" << newX << newY;
                pointLatLong.SetLat(newX);
                pointLatLong.SetLng(newY);
                core::Point localPoint = map->FromLatLngToLocal(pointLatLong);
                polyLocal.append( QPoint( localPoint.X(), localPoint.Y() ) );
            }
            // Draw Path
            QPainterPath pathLocal;
            pathLocal.addPolygon(polyLocal);
            setPath(pathLocal);
        }
    }
}

void WaypointPathItem::updateWPValues(WayPointItem* waypoint)
{
    Q_UNUSED(waypoint);

    QPolygonF polyLocal;
    for (int i = 0; i < polyLatLng->size(); i++)
    {
        internals::PointLatLng pointLatLong;
        double newX = polyLatLng->at(i).x();
        double newY = polyLatLng->at(i).y();
        pointLatLong.SetLat(newX);
        pointLatLong.SetLng(newY);
        core::Point localPoint = map->FromLatLngToLocal(pointLatLong);
        polyLocal.append( QPoint( localPoint.X(), localPoint.Y() ) );
    }
    // Draw Path
    QPainterPath pathLocal;
    pathLocal.addPolygon(polyLocal);
    setPath(pathLocal);
}

void WaypointPathItem::updateWPValues()
{
//    if UASWaypointManager::currentWaypointChanged()
    updateWPValues(NULL);
}

int WaypointPathItem::type()const
{
    return Type;
}

}
