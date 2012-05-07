#ifndef WAYPOINTPATHITEM_H
#define WAYPOINTPATHITEM_H

#include <QGraphicsPathItem>
#include <QPolygonF>
#include <QVector>
#include "opmapcontrol.h"
#include "Trajectory.h"
#include "UASWaypointManager.h"

namespace mapcontrol {
class WaypointPathItem : public QObject,public QGraphicsPathItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Type = UserType + 7 };
    WaypointPathItem(QPolygonF* polyLatLng, QColor color=QColor(Qt::red), MapGraphicItem* parent=0);
    WaypointPathItem(QVector<double> height, QVector<double> horizontalDistance, QColor color=QColor(Qt::red), MapGraphicItem* parent=0);
    int type() const;

public slots:
    /**
    * @brief Update waypoint values
    *
    * @param waypoint The waypoint object that just changed
    */
    void updateWPValues(WayPointItem* waypoint);
    /**
    * @brief Update waypoint values
    */
    void updateWPValues();
    /**
    * @brief Update waypoint values
    *
    */
    void RefreshPos();

protected:
//    Trajectory trajectory;
    QPolygonF* polyLatLng;
//    QVector<Waypoint* > wpList;
    MapGraphicItem* map;              ///< The map this item is parent of
};
}

#endif // WAYPOINTPATHITEM_H
