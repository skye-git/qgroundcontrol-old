#ifndef ELEVATIONPROFILEDISPLAY_H
#define ELEVATIONPROFILEDISPLAY_H

#include <QtGui/QGraphicsView>
#include "ElevationProfile.h"
#include "ElevationPoint.h"
#include "UASWaypointManager.h"
#include "UASManager.h"
//#include "WaypointEditableView.h"

class ElevationProfileDisplay : public QGraphicsView
{
    Q_OBJECT
public:
    ElevationProfileDisplay(QWidget *parent = 0);
    
signals:
    void waypointChanged(Waypoint* wp); //is emitted if height is changed
    void emitupdateParentStatusLabel(const QString &string);
    
public slots:
    void setUAS(UASInterface*mav);

    //Update events
    /** @brief sets statusLabel string */
    void updateParentStatusLabel(const QString &string);
//    /** @brief The user wants to change the current waypoint */
//    void changeCurrentWaypoint(quint16 seq);
//    /** @brief Current waypoint in edit-tab was changed, so the list must be updated (to contain only one waypoint checked as "current")  */
//    void currentWaypointEditableChanged(quint16 seq);
//    /** @brief Current waypoint on UAV was changed, update view-tab  */
//    void currentWaypointViewOnlyChanged(quint16 seq);
//    /** @brief The waypoint manager informs that one editable waypoint was changed */
//    void updateWaypointEditable(int uas, Waypoint* wp);
//    /** @brief The waypoint manager informs that one viewonly waypoint was changed */
//    void updateWaypointViewOnly(int uas, Waypoint* wp);
//    /** @brief The waypoint manager informs that the editable waypoint list was changed */
//    void waypointEditableListChanged(void);
//    /** @brief The waypoint manager informs that the waypoint list on the MAV was changed */
//    void waypointViewOnlyListChanged(void);

protected slots:
    /** @brief Convert a ElevationPoint edit into a QGC waypoint event */
    //void handleElevationPointEdit(ElevationPoint* elevationPoint);//taken from QGCMapWidget

protected:
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);

    UASInterface* uas;
    UASWaypointManager* currWPManager; ///< The current waypoint manager
    QMap<Waypoint*, ElevationPoint*> wpElevationPoint;
    Waypoint* firingWaypointChange;

private:
    ElevationProfile* parentPointer;
    
};

#endif // ELEVATIONPROFILEDISPLAY_H
