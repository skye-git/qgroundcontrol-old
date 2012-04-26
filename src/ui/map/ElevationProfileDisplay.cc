#include "ElevationProfileDisplay.h"


#include <QtGui>

#include <math.h>

ElevationProfileDisplay::ElevationProfileDisplay(QWidget *parent) :
    QGraphicsView(parent),
    uas(NULL)
{
    parentPointer = dynamic_cast<ElevationProfile*>(parent);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    //scale(qreal(0.3), qreal(0.3));
    setMinimumSize(200, 200);
    setWindowTitle(tr("Elastic Nodes"));

    //connections
    if(parentPointer)
    {
        connect(this, SIGNAL(emitupdateParentStatusLabel(QString)), parentPointer, SLOT(updateStatusLabel(QString)));
    }

    // SET UAS AFTER ALL SIGNALS/SLOTS ARE CONNECTED
    if(parentPointer->uas)
    {
        currWPManager = parentPointer->uas->getWaypointManager();
    }
    else
    {
        currWPManager = new UASWaypointManager(NULL);
    }

    setUAS(parentPointer->uas);

    //Elevation Points
    ElevationPoint *point1 = new ElevationPoint(this);
    ElevationPoint *point2 = new ElevationPoint(this);

    scene->addItem(point1);
    scene->addItem(point2);

    point1->setPos(0,0);
    point2->setPos(20, 20);
}

void ElevationProfileDisplay::setUAS(UASInterface* mav) //used instead of show Event addUAs and activeUASSet compare QGCMapWidget
{
    if (this->uas == NULL && mav != NULL)
    {
        currWPManager = mav->getWaypointManager();
    }
    if (this->uas ==NULL)
    {
        this->uas = mav;
        connect(currWPManager, SIGNAL(updateStatusString(const QString &)), this, SLOT(updateParentStatusLabel(const QString &)));
    }
    if (mav != NULL) //just get the new WPManager
    {
        currWPManager = mav->getWaypointManager();
    }
}

void ElevationProfileDisplay::updateParentStatusLabel(const QString &string)
{
    // Status label in Elevation Profile Widget
    emit emitupdateParentStatusLabel(string);
}

//void ElevationProfileDisplay::waypointEditableListChanged()
//{
//    // Prevent updates to prevent visual flicker
//    this->setUpdatesEnabled(false);
//    const QVector<Waypoint *> &waypoints = currWPManager->getWaypointEditableList();

//    if (!wpElevationPoint.empty()) {
//        QMapIterator<Waypoint*,ElevationPoint*> viewIt(wpElevationPoint);
//        viewIt.toFront();
//        while(viewIt.hasNext()) {
//            viewIt.next();
//            Waypoint *cur = viewIt.key();
//            int i;
//            for (i = 0; i < waypoints.size(); i++) {
//                if (waypoints[i] == cur) {
//                    break;
//                }
//            }
//            if (i == waypoints.size()) {
//                ElevationPoint* point = wpElevationPoint.find(cur).value();
//                point->hide();
//                //editableListLayout->removeWidget(widget);//remove from scene
//                wpElevationPoint.remove(cur);
//            }
//        }
//    }

//    // then add/update the views for each waypoint in the list
//    for(int i = 0; i < waypoints.size(); i++) {
//        Waypoint *wp = waypoints[i];
//        if (!wpElevationPoint.contains(wp)) {
//            ElevationPoint* epview = new ElevationPoint(wp, this);
//            wpElevationPoint.insert(wp, epview);
//            //connect(wpview, SIGNAL(currentWaypointChanged(quint16)), this, SLOT(currentWaypointChanged(quint16)));
//            //connect(wpview, SIGNAL(changeCurrentWaypoint(quint16)), this, SLOT(currentWaypointEditableChanged(quint16)));
//            //editableListLayout->insertWidget(i, wpview);
//        }
//        ElevationPoint *epv = wpElevationPoint.value(wp);

//        //check if ordering has changed
//        if(editableListLayout->itemAt(i)->widget() != epv) {
//            editableListLayout->removeWidget(epv);
//            editableListLayout->insertWidget(i, epv);
//        }

//        epv->updateValues();    // update the values of the ui elements in the view
//    }
//    this->setUpdatesEnabled(true);
//    loadFileGlobalWP = false;


//}

//void ElevationProfileDisplay::handleElevationPointEdit(ElevationPoint* elevationPoint)
//{
//    // Block circle updates
//    Waypoint* wp = elevationPointToWaypoints.value(elevationPoint, NULL);
//    // Protect from vicious double update cycle
//    if (firingWaypointChange == wp) return;
//    // Not in cycle, block now from entering it
//    firingWaypointChange = wp;
//    // // qDebug() << "UPDATING WP FROM MAP";

//    // Update WP values
//    double height = elevationPoint->y();

//    // Block waypoint signals
//    wp->blockSignals(true);
//    wp->setAltitude(height);
//    wp->blockSignals(false);

//    firingWaypointChange = NULL;

//    emit waypointChanged(wp);
//}


void ElevationProfileDisplay::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void ElevationProfileDisplay::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
