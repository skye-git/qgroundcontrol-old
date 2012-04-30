#ifndef HEIGHTPROFILE_H
#define HEIGHTPROFILE_H

#include <QGraphicsView>

#include "UASInterface.h"
#include "UASWaypointManager.h"
#include "Waypoint.h"

class HeightPoint;

class HeightProfile : public QGraphicsView
{
    Q_OBJECT
public:
    HeightProfile(QWidget *parent = 0);


    QGraphicsScene* scene;
    
signals:
    void wapointChanged(Waypoint*wp);
    
public slots:
    /** @brief Add system to Height Profile view */
    void addUAS(UASInterface* uas);
    /** @brief Change current system in focus / editing */
    void activeUASSet(UASInterface* uas);
    /** @brief Update this waypoint for this UAS */
    void updateWaypoint(int uas, Waypoint* wp);
    /** @brief Update the whole waypoint */
    void updateWaypointList(int uas);
    /** @brief arrange the HeightPoints in the scene */
    void arrangeHeightPoints(); //Integrate perhaps in update slots...

protected slots:
    /** @brief Convert a HeightPoint edit into a QGC waypoint event */
    void handleHeightPointWaypointEdit(HeightPoint* hp);

protected:
    /** @brief Update the highlighting of the currently controlled system */
    void updateSelectedSystem(int uas);
    /** @brief Initialize */
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);




    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void scaleView(qreal scaleFactor);

    UASWaypointManager* currWPManager; ///< The current waypoint manager
    QMap<Waypoint* , HeightPoint*> waypointsToHeightPoints;
    QMap<HeightPoint*, Waypoint*> heightPointsToWaypoints;
    Waypoint* firingWaypointChange;
    bool profileInitialized; ///< Profile initialized?
    //QTimer rearrangeTimer;



    
};

#endif // HEIGHTPROFILE_H
