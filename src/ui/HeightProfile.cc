#include "HeightProfile.h"

#include <QtGui>
#include <math.h>

#include "UASManager.h"
#include "HeightPoint.h"

HeightProfile::HeightProfile(QWidget *parent) :
    QGraphicsView(parent),
    currWPManager(NULL),
    firingWaypointChange(NULL),
    profileInitialized(false)
{



    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, -100, 500, 100);
    setScene(scene);
    //setSceneRect(0,-100,200,100);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    //scale(qreal(0.3), qreal(0.3));
    //setMinimumSize(400, 400);//setMinimum (with, height) of widget
    setWindowTitle(tr("Height Profile"));

    //Test Debug
    //HeightPoint* hp0 = new HeightPoint
    //connect(&rearrangeTimer, SIGNAL(timeout()), this, SLOT(arrangeHeightPoints()));
    //rearrangeTimer.start(4000);
}

void HeightProfile::showEvent(QShowEvent *event)
{
    //Pass on to parent widget
    QGraphicsView::showEvent(event);

    connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(addUAS(UASInterface*)), Qt::UniqueConnection);
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(activeUASSet(UASInterface*)), Qt::UniqueConnection);
    foreach (UASInterface* uas, UASManager::instance()->getUASList())
    {
        addUAS(uas);
    }

    if(!profileInitialized)
    {
        // Set currently selected system
        activeUASSet(UASManager::instance()->getActiveUAS()); //!!!!!???????????

        profileInitialized = true;
    }

}

void HeightProfile::hideEvent(QHideEvent *event)
{
    QGraphicsView::hideEvent(event);
}

void HeightProfile::addUAS(UASInterface* uas)
{
    Q_UNUSED(uas) //so far nothing, compare QGCMapWidget::addUAS()
}

void HeightProfile::activeUASSet(UASInterface *uas)
{
    //Only execute if proper UAS is set
    if(!uas) return;

    //Disconnect old MAV manager
    if(currWPManager)
    {
        //Disconnect hte waypoint manager / data storage from the UI
        disconnect(currWPManager, SIGNAL(waypointEditableListChanged(int)), this, SLOT(updateWaypointList(int)));
        disconnect(currWPManager, SIGNAL(waypointEditableChanged(int, Waypoint*)), this, SLOT(updateWaypoint(int,Waypoint*)));
    }

    if (uas)
    {
        currWPManager = uas->getWaypointManager();

        // Connect the waypoint manager / data storage to the UI
        connect(currWPManager, SIGNAL(waypointEditableListChanged(int)), this, SLOT(updateWaypointList(int)));
        connect(currWPManager, SIGNAL(waypointEditableChanged(int, Waypoint*)), this, SLOT(updateWaypoint(int,Waypoint*)));
        connect(this, SIGNAL(waypointChanged(Waypoint*)), currWPManager, SLOT(notifyOfChangeEditable(Waypoint*)));
        updateSelectedSystem(uas->getUASID());

        // Delete all waypoints and add waypoint from new system
        updateWaypointList(uas->getUASID());
    }
}

void HeightProfile::updateSelectedSystem(int uas)
{
    Q_UNUSED(uas); //compare QGCMapWidget::updateSelectedSystem()
}

//WAYPOINT HEIGHT PROFILE INTERACTION FUNCTIONS

void HeightProfile::handleHeightPointWaypointEdit(HeightPoint* hp)
{
    // Block circle updates
    Waypoint* wp = heightPointsToWaypoints.value(hp, NULL);
    // Protect from vicious double update cycle
    if (firingWaypointChange == wp) return;
    // Not in cycle, block now from entering it
    firingWaypointChange = wp;
    // // qDebug() << "UPDATING WP FROM MAP";

    // Update WP values
    //internals::PointLatLng pos = waypoint->Coord(); //adapt this!!

    // Block waypoint signals
    wp->blockSignals(true);
    //wp->setAltitude(hp->Altitude()); //adapt this!!
    wp->blockSignals(false);


    firingWaypointChange = NULL;

    emit wapointChanged(wp);
}

// WAYPOINT UPDATE FUNCTIONS
/**
 * This function is called if a a single waypoint is updated and
 * also if the whole list changes.
 */

void HeightProfile::updateWaypoint(int uas, Waypoint* wp)
{
    qDebug() << "UPDATING WP FUNCTION CALLED";
    // Source of the event was in this widget, do nothing
    if (firingWaypointChange == wp) return;
    // Currently only accept waypoint updates from the UAS in focus
    // this has to be changed to accept read-only updates from other systems as well.
    UASInterface* uasInstance = UASManager::instance()->getUASForId(uas);
    if (uasInstance->getWaypointManager() == currWPManager || uas == -1)
    {
        // Only accept waypoints in global coordinate frame
        if (((wp->getFrame() == MAV_FRAME_GLOBAL) || (wp->getFrame() == MAV_FRAME_GLOBAL_RELATIVE_ALT)) && wp->isNavigationType())
        {
            // We're good, this is a global waypoint

            // Get the index of this waypoint
            // note the call to getGlobalFrameAndNavTypeIndexOf()
            // as we're only handling global waypoints
            int wpindex = currWPManager->getGlobalFrameAndNavTypeIndexOf(wp);
            // If not found, return (this should never happen, but helps safety)
            if (wpindex == -1) return;
            // Mark this wp as currently edited
            firingWaypointChange = wp;

            qDebug() << "UPDATING WAYPOINT" << wpindex << "IN 2D MAP";

            // Check if wp exists yet in map
            if (!waypointsToHeightPoints.contains(wp))
            {
                // Create icon for new WP
                QColor wpColor(Qt::red);
                if (uasInstance) wpColor = uasInstance->getColor();
                HeightPoint* hp = new HeightPoint(this, wp, wpColor, wpindex);
                //ConnectWP(hp); //Achtung Probleme????!!!
                //hp->setParentItem(this); //Achtung, Height Profile ist kein GraphicsItem
                // Update maps to allow inverse data association
                waypointsToHeightPoints.insert(wp, hp);
                heightPointsToWaypoints.insert(hp, wp);
                scene->addItem(hp);

                //not yet uses
                // Add line element if this is NOT the first waypoint
//                if (wpindex > 0)
//                {
//                    // Get predecessor of this WP
//                    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
//                    Waypoint* wp1 = wps.at(wpindex-1);
//                    mapcontrol::WayPointItem* prevIcon = waypointsToIcons.value(wp1, NULL);
//                    // If we got a valid graphics item, continue
//                    if (prevIcon)
//                    {
//                        mapcontrol::WaypointLineItem* line = new mapcontrol::WaypointLineItem(prevIcon, icon, wpColor, map);
//                        line->setParentItem(map);
//                        QGraphicsItemGroup* group = waypointLines.value(uas, NULL);
//                        if (group)
//                        {
//                            group->addToGroup(line);
//                            group->setParentItem(map);
//                        }
//                    }
//                }
            }
            else
            {
                // Waypoint exists, block it's signals and update it
                HeightPoint* hp = waypointsToHeightPoints.value(wp);
                // Make sure we don't die on a null pointer
                // this should never happen, just a precaution
                if (!hp) return;
                // Block outgoing signals to prevent an infinite signal loop
                // should not happen, just a precaution
                this->blockSignals(true);
                // Update the WP
                HeightPoint* wphp = dynamic_cast<HeightPoint*>(hp);
                if (wphp)
                {
                    // Let icon read out values directly from waypoint
                    hp->setNumber(wpindex);
                    wphp->updateHeightPoint(wp);
                }
                else
                {
                    qDebug() << "Copy paste problem";
                    hp->setNumber(wpindex);
                }
                // Re-enable signals again
                this->blockSignals(false);
            }

            firingWaypointChange = NULL;

        }
        else
        {
            // Check if the index of this waypoint is larger than the global
            // waypoint list. This implies that the coordinate frame of this
            // waypoint was changed and the list containing only global
            // waypoints was shortened. Thus update the whole list
            if (waypointsToHeightPoints.size() > currWPManager->getGlobalFrameAndNavTypeCount())
            {
                updateWaypointList(uas);
            }
        }
        arrangeHeightPoints();
    }
}

/**
 * Update the whole list of waypoints. This is e.g. necessary if the list order changed.
 * The UAS manager will emit the appropriate signal whenever updating the list
 * is necessary.
 */


void HeightProfile::updateWaypointList(int uas)
{
    qDebug() << "UPDATE WP LIST IN 2D MAP CALLED FOR UAS" << uas;
    // Currently only accept waypoint updates from the UAS in focus
    // this has to be changed to accept read-only updates from other systems as well.
    UASInterface* uasInstance = UASManager::instance()->getUASForId(uas);
    if ((uasInstance && (uasInstance->getWaypointManager() == currWPManager)) || uas == -1)
    {
        // ORDER MATTERS HERE!
        // TWO LOOPS ARE NEEDED - INFINITY LOOP ELSE

        qDebug() << "DELETING NOW OLD WPS";

        // Delete first all old waypoints
        // this is suboptimal (quadratic, but wps should stay in the sub-100 range anyway)
        QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
        foreach (Waypoint* wp, waypointsToHeightPoints.keys())
        {
            if (!wps.contains(wp))
            {
                // Get icon to work on
                HeightPoint* hp = waypointsToHeightPoints.value(wp);
                waypointsToHeightPoints.remove(wp);
                heightPointsToWaypoints.remove(hp);
                scene->removeItem(hp);//correct!!!!?????
                //WPDelete(hp);
            }
        }

        // Update all existing waypoints
        foreach (Waypoint* wp, waypointsToHeightPoints.keys())
        {
            // Update remaining waypoints
            updateWaypoint(uas, wp);
        }

        // Update all potentially new waypoints
        foreach (Waypoint* wp, wps)
        {
            qDebug() << "UPDATING NEW WP" << wp->getId();
            // Update / add only if new
            if (!waypointsToHeightPoints.contains(wp)) updateWaypoint(uas, wp);
        }
        //arrangeHeightPoints();

        //not yet used
//        // Delete connecting waypoint lines
//        QGraphicsItemGroup* group = waypointLines.value(uas, NULL);
//        if (group)
//        {
//            foreach (QGraphicsItem* item, group->childItems())
//            {
//                delete item;
//            }
//        }

//        // Add line element if this is NOT the first waypoint
//        mapcontrol::WayPointItem* prevIcon = NULL;
//        foreach (Waypoint* wp, wps)
//        {
//            mapcontrol::WayPointItem* currIcon = waypointsToIcons.value(wp, NULL);
//            // Do not work on first waypoint, but only increment counter
//            // do not continue if icon is invalid
//            if (prevIcon && currIcon)
//            {
//                // If we got a valid graphics item, continue
//                QColor wpColor(Qt::red);
//                if (uasInstance) wpColor = uasInstance->getColor();
//                mapcontrol::WaypointLineItem* line = new mapcontrol::WaypointLineItem(prevIcon, currIcon, wpColor, map);
//                line->setParentItem(map);
//                QGraphicsItemGroup* group = waypointLines.value(uas, NULL);
//                if (group)
//                {
//                    group->addToGroup(line);
//                    group->setParentItem(map);
//                }
//            }
//            prevIcon = currIcon;
//        }
    }
}

void HeightProfile::arrangeHeightPoints()
{
    //get the Waypoints with the right frame
    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
    int number = wps.size();
    qDebug() << "WPVector Size is " << number;
    qreal width = this->width();
    qreal distance = 500/(number+1);
    int i = 1;
//    foreach (Waypoint* wp, wps)
//    {
//        HeightPoint* currHp = waypointsToHeightPoints.value(wp, NULL);
//        //currHp->setPos((i*distance), 0);
//        if(i == 1)
//        {
//            bool ishp = dynamic_cast<HeightPoint*>(currHp);
//            qDebug() << "before changning Pos of i==1";
//            if(ishp) //why necessary???!!!!
//                currHp->setPos(30.0,-30.1);
//            qDebug() << "item  = " << i << " Pos is set ";
//            qDebug() << "wp id is = "<< wp->getId();
//        }
//        if(i == 0)
//        {
//            qDebug() << "befor changing Pos of i == 0";
//            currHp->setPos(50,0);
//            qDebug() << "item  = " << i << " Pos is set ";
//        }
//        i++;
//    }
    foreach (Waypoint* wp, wps)
    {
        HeightPoint* currHp = waypointsToHeightPoints.value(wp, NULL);
        //currHp->setPos((i*distance), 0);
        bool ishp = dynamic_cast<HeightPoint*>(currHp);
        if(ishp)
        {
            currHp->setPos((i*distance), currHp->y());
        }
        else
        {
            qDebug() << "crazy error";
        }
        i++;
    }
}



void HeightProfile::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void HeightProfile::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
    painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
    painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);


    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the points up and down, and zoom with the mouse "
                       "..."));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);

}

void HeightProfile::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

