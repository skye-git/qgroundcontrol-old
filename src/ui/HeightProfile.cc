#include "HeightProfile.h"

#include <QtGui>
#include <math.h>
#include <QVector3D>

#include "UASManager.h"
#include "HeightPoint.h"
#include <QXmlStreamReader>
#include <QMessageBox>

#ifndef QGC_EARTH_RADIUS
#define QGC_EARTH_RADIUS 6367449.0
#endif
#ifndef M_PI
#define M_PI 3.14159265359
#endif

HeightProfile::HeightProfile(QWidget *parent) :
    QGraphicsView(parent),
    getelevationwascalled(false),
    currWPManager(NULL),
    firingWaypointChange(NULL),
    profileInitialized(false)
{
    qDebug() << "HeightProfile constructor call";
    sTopLeftCorner.setX(0);
    sTopLeftCorner.setY(-100);
    sWidth = 600;
    sHeight = 100;
    minHeight = 0;
    maxHeight = 100;
    boundary =10;
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(sTopLeftCorner.x(), sTopLeftCorner.y(), sWidth, sHeight);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    //scale(qreal(0.3), qreal(0.3));
    //setMinimumSize(400, 400);//setMinimum (with, height) of widget
    setWindowTitle(tr("Height Profile"));


    displayminHeight = new QGraphicsTextItem();
    displaymaxHeight = new QGraphicsTextItem();
    displayminHeight->setPlainText(QString("%1 m (oG)").arg(QString::number(minHeight)));
    displaymaxHeight->setPlainText(QString("%1 m (oG)").arg(QString::number(maxHeight)));
    scene->addItem(displayminHeight);
    scene->addItem(displaymaxHeight);

    //display constant items
    displayminHeight->setParent(this);
    displaymaxHeight->setParent(this);
    displaymaxHeight->setPos(sTopLeftCorner.x(),sTopLeftCorner.y()+boundary-displaymaxHeight->boundingRect().height()/2);
    displayminHeight->setPos(sTopLeftCorner.x(), sTopLeftCorner.y()+sHeight-boundary-displayminHeight->boundingRect().height()/2);


    //display dynamic items
    elevationItem = new QGraphicsPolygonItem();
    elevationItem->setFlag(QGraphicsItem::ItemStacksBehindParent);
    elevationItem->setBrush(QBrush(Qt::darkGreen));
    elevationItem->setFillRule(Qt::WindingFill);
    scene->addItem(elevationItem);
    elevationItem->setPos(0,0);

    splineItem = new QGraphicsPathItem();
    splineItem->setFlag(QGraphicsItem::ItemStacksBehindParent);
    splineItem->setBrush(Qt::NoBrush);
    scene->addItem(splineItem);
    splineItem->setPos(0,0);

    //Network Manger
    networkManager = new QNetworkAccessManager();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    emit setinfoLabelText(QString("set meters over ground"));

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

qreal HeightProfile::fromAltitudeToScene(qreal altitude)
{
    return -((altitude-minHeight)/(maxHeight-minHeight)*(sHeight-2*boundary)+boundary);
}


qreal HeightProfile::fromSceneToAltitude(qreal sceneY)
{
    return minHeight+(-sceneY-boundary)/(sHeight-2*boundary)*(maxHeight-minHeight);
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

            qDebug() << "UPDATING WAYPOINT" << wpindex << "IN HEIGHT PROFILE";

            // Check if wp exists yet in scene
            if (!waypointsToHeightPoints.contains(wp))
            {
                // Create HeightPoint for new WP
                QColor wpColor(Qt::red);
                if (uasInstance) wpColor = uasInstance->getColor();
                HeightPoint* hp = new HeightPoint(this, wp, wpColor, wpindex);
                //ConnectWP(hp); //Achtung Probleme????!!!
                //hp->setParentItem(this); //Achtung, Height Profile ist kein GraphicsItem
                // Update maps to allow inverse data association
                waypointsToHeightPoints.insert(wp, hp);
                heightPointsToWaypoints.insert(hp, wp);
                scene->addItem(hp);
                wp->setAltitude(maxHeight); //new waypoint should appear in scene!

                updateSplineItem();//working!!!!?
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
                    //wphp->updateHeightPoint(wp);
                    if(wp->getAltitude() < minHeight)
                    {
                        wp->setAltitude(minHeight);//prevents the Height Points from disappearing in the scene
                        wphp->setY(fromAltitudeToScene(wp->getAltitude()));
                    }
                    else
                    {
                        wphp->setY(fromAltitudeToScene(wp->getAltitude()));
                    }
                    updateSplineItem();//working ??!!!-no seems to crash->move to updateWaypointlist
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
        if(getelevationwascalled)
        {
            emit setinfoLabelText(QString("The elevation profile is no more up to date."));
        }

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
                scene->removeItem(hp->elevationPoint);
                delete hp; //No special delete Fct since Number is not correct.
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
        //updateSplineItem(); //working, but not frequent enough!

    }
}

void HeightProfile::arrangeHeightPoints()
{
    //get the Waypoints with the right frame
    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
    int splineNumber = currWPManager->getEditableTrajectory()->getVectorSize();
    int res = currWPManager->getEditableTrajectory()->getSplineResolution();
    int number = wps.size();
    qDebug() << "WPVector Size is " << number;
    QVector<qreal> distanceToFirst(number);
    if(number != 0)
    {
        distanceToFirst[0] = 0;
    }
    for(int i = 1; i < number; i++) //number ==1 won't be processed!
    {
        HeightPoint* currHp0 = waypointsToHeightPoints.value(wps[i-1], NULL);
        bool ishp0 = dynamic_cast<HeightPoint*>(currHp0);
        HeightPoint* currHp1 = waypointsToHeightPoints.value(wps[i], NULL);
        bool ishp1 = dynamic_cast<HeightPoint*>(currHp1);
        if(ishp0 && ishp1)
        {
            if(splineNumber < (number-1)*res) // in this case no spline can be calculated! Trajectory.cc : interpol.clear()=?
            {
                distanceToFirst[i] = distanceToFirst[i-1] + getDistanceStraight(wps[i-1],wps[i]);
            }
            else
            {

                //qDebug() << "The  spline distance between the " << i-1 << "WP" << "and the " << i << "Wp is : "<< getDistanceSpline(i-1, i);
                //qDebug() << "The  straight distance between the " << i-1 << "WP" << "and the " << i << "Wp is : "<< getDistanceStraight(wps[i-1], wps[i]);
                distanceToFirst[i] = distanceToFirst[i-1] + getDistanceSpline(i-1, i);
                //distanceToFirst[i] = distanceToFirst[i-1] + getDistanceStraight(wps[i-1],wps[i]);
            }
            //distanceToFirst[i] = distanceToFirst[i-1] + getDistanceStraight(wps[i-1],wps[i]);
        }
        else
        {
            return; //essential!!! Otherwise setPos is called, although the waypoint has not yet a HeightPoint!
           qDebug() << "crazy error #43 arrangeHeightPoints was called too early. Before all updateWaypoints call!!!";
        }

    }
    if(number == 1)
    {
        HeightPoint* currHp = waypointsToHeightPoints.value(wps[0], NULL);
        currHp->setPos(sWidth/2, fromAltitudeToScene(wps[0]->getAltitude()));
        currHp->elevationPoint->setPos(sWidth/2, fromAltitudeToScene(currHp->elevationPoint->elevation));
    }
    else
    {
        for(int j = 0; j < number; j++)
        {
            HeightPoint* currHp = waypointsToHeightPoints.value(wps[j], NULL);
            currHp->setPos((distanceToFirst[j]/distanceToFirst[number-1])*(sWidth-2*boundary)+boundary, fromAltitudeToScene(wps[j]->getAltitude()));
            currHp->elevationPoint->setPos((distanceToFirst[j]/distanceToFirst[number-1])*(sWidth-2*boundary)+boundary, fromAltitudeToScene(currHp->elevationPoint->elevation));

        }
    }
    //updateElevationItem(); //!!!!seems to produce a crash, if called too early. Should anyways only be called after replyfinished!

}

qreal HeightProfile::getDistanceStraight(Waypoint *wp1, Waypoint *wp2)
{
    HeightPoint* currHp1 = waypointsToHeightPoints.value(wp1, NULL);
    HeightPoint* currHp2 = waypointsToHeightPoints.value(wp2, NULL);
    bool ishp1 = dynamic_cast<HeightPoint*>(currHp1);
    bool ishp2 = dynamic_cast<HeightPoint*>(currHp2);
    if(ishp1 & ishp2)
    {
        qreal lat1 = wp1->getLatitude();
        qreal lon1 = wp1->getLongitude();
        qreal lat2 = wp2->getLatitude();
        qreal lon2 = wp2->getLongitude();
        qreal distancelong = M_PI * 2*QGC_EARTH_RADIUS*cos(M_PI/180*lat1)*fabs(lon1-lon2)/360;
        qreal distancelat = M_PI * 2 *QGC_EARTH_RADIUS*fabs(lat1-lat2)/360;
        qreal distance = sqrt(pow(distancelong,2)+pow(distancelat,2));

        return distance;

    }
    else
    {
        qDebug() << "crazy error (return must have been removed in arrangeHeightPoints!) should first crash in arrangeHeightPoints!!!";
    }

    return -1; //what value is best here ?
}

qreal HeightProfile::getDistanceSpline(uint index1, uint index2)
{
//    uint res = currWPManager->getEditableTrajectory()->getSplineResolution();
//    QPolygonF* splinei1Toi2 = currWPManager->getEditableTrajectory()->getPolyXY(index1*res, index2*res+1); //!!!garden fence problem!
//    qreal distance = 0;
//    for(uint i = 0; i < (index2 - index1)*res; i++)
//    {
////        QPointF sPoint1 = splinei1Toi2->at(i);
////        QPointF sPoint2 = splinei1Toi2->at(i+1);
////        qDebug() << sPoint1;
////        qDebug() << sPoint2;
//        distance = distance + getDistance(sPoint1.x(),sPoint1.y(), sPoint2.x(), sPoint2.y());
////        distance = distance + getDistance((splinei1Toi2->at(i)).x(), (splinei1Toi2->at(i)).y(), (splinei1Toi2->at(i+1)).x(), (splinei1Toi2->at(i+1)).y());//!!!garden fence problem!
//    }
//    return distance;

    QVector<double> trajX; //absolute X value
    QVector<double> trajY;
    QVector<double> trajZ;
    uint res = currWPManager->getEditableTrajectory()->getSplineResolution();
    currWPManager->getEditableTrajectory()->getVector(trajX,trajY,trajZ);
    qreal distance = 0;
    for(uint i = index1*res; i < index2*res; i++)
    {
        distance = distance + getDistance(trajX[i],trajY[i], trajX[i+1],trajY[i+1]);
        qDebug() << "spline distance between wp" << index1 << "and wp" << index2 << "is : " << distance;
    }
    return distance;

}

qreal HeightProfile::getDistance(qreal sp1x, qreal sp1y, qreal sp2x, qreal sp2y)
{
    qreal distance = sqrt(pow(sp1x-sp2x,2)+pow(sp1y-sp2y,2));

    return distance;
}

void HeightProfile::getElevationPoints()
{
    qDebug() << "in getElevationPoints()";
    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
    foreach(Waypoint* wp, wps)
    {
        //qDebug() << "the longitude of the actual waypoint is: " << wp->getLongitude();
        HeightPoint* currHp = waypointsToHeightPoints.value(wp, NULL);
        bool ishp = dynamic_cast<HeightPoint*>(currHp);
        if(ishp)
        {
            scene->addItem(currHp->elevationPoint);
            currHp->elevationPoint->setPos(currHp->x(),fromAltitudeToScene(currHp->elevationPoint->elevation));
        }
        else
        {
            qDebug() << "basically unnecessary check, getElevationPoints() was called before all waypoints updates were made";
        }
    }
    networkManager->get(QNetworkRequest(constructUrl(wps)));
    getelevationwascalled = true;
}

QUrl HeightProfile::constructUrl(QVector<Waypoint* > wps)
{
    QString urlString("http://maps.googleapis.com/maps/api/elevation/xml?locations=");
    foreach(Waypoint* wp, wps)
    {
        HeightPoint* currHp = waypointsToHeightPoints.value(wp, NULL);
        bool ishp = dynamic_cast<HeightPoint*>(currHp);
        if(ishp)
        {
            qDebug() << "the latitude|longitude of the actual waypoint is: " << QString::number(wp->getLatitude(),'f', 8) << "|" << QString::number(wp->getLongitude(),'f', 8);
            urlString.append(QString::number(wp->getLatitude(),'f', 8));
            urlString.append(",");
            urlString.append(QString::number(wp->getLongitude(),'f', 8));
            urlString.append("|");
        }
        else
        {
            qDebug() << "crazy error, not all waypoints in GlobalFrameAndNavTypeWaypointList have a height point,  replyFinished() won't work, see Debug in elevationPoints";
        }
    }
    urlString = urlString.remove(urlString.lastIndexOf("|"),1);
    urlString.append("&sensor=true"); //use false if no GPS Sensor is used
    QUrl constructedUrl(urlString);

    qDebug() << "The constructed Url is:" << constructedUrl;

    return constructedUrl;

}


void HeightProfile::replyFinished(QNetworkReply *reply)
{
    qDebug() << "Is reply readable? - " << reply->isReadable();

    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();

    QByteArray data = reply->readAll();
    QXmlStreamReader reader(data);
    int i = 0;
    while(!reader.atEnd() && !reader.hasError()) {


            QXmlStreamReader::TokenType token = reader.readNext();

            if(token == QXmlStreamReader::StartElement)
            {
                if(reader.name() == "elevation")
                {
                    QString readout = reader.readElementText();
                    //qDebug() << readout;
                    double elevation = readout.toDouble();
                    //qDebug() << QString::number(elevation,'f', 7);
                    HeightPoint* currHp = waypointsToHeightPoints.value(wps[i], NULL);
                    if(wps[i]->getAltitude() < elevation)
                    {
                        if((currHp->elevationPoint->elevation == 0) && wps[i]->getAltitude() < 100) //the number 100 is set arbitrarily
                        {
                            wps[i]->setAltitude(elevation + wps[i]->getAltitude()); //the idea is that the meters over ground are set before getelevation is called
                            qDebug() << "Altitude had to be adjusted to the Elevation: " << wps[i]->getAltitude();
                        }
                        else
                        {
                            wps[i]->setAltitude(elevation);
                            qDebug() << "Altitude had to be adjusted to the Elevation: " << wps[i]->getAltitude();
                        }
                    }
                    currHp->elevationPoint->elevation = elevation;

                    i++;
                }
            }
    }

    if(reader.hasError()) {
        qDebug() << "QMessageBox reader error";
            QMessageBox::critical(this,
            "xmlFile.xml Parse Error",reader.errorString(),
            QMessageBox::Ok);
            return;
    }
    updateExtrema();
    this->update();
    emit setinfoLabelText("The elevation profile is up to date");
}

void HeightProfile::updateExtrema()
{
    minHeight = +4000; //FIXME not nice, assu
    maxHeight = -4000;
    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
    foreach(Waypoint* wp, wps)
    {
        HeightPoint* currHp = waypointsToHeightPoints.value(wp, NULL);
        bool ishp = dynamic_cast<HeightPoint*>(currHp);
        if(ishp)
        {
            if(wp->getAltitude() > maxHeight)
                maxHeight = wp->getAltitude() + 20; //FIXME parametrisch
            if(currHp->elevationPoint->elevation > maxHeight)
                maxHeight = currHp->elevationPoint->elevation + 20;
            if(wp->getAltitude() < minHeight)
                minHeight = wp->getAltitude() - 20;
            if(currHp->elevationPoint->elevation < minHeight)
                minHeight = currHp->elevationPoint->elevation - 20;
        }
        else
        {
            qDebug() << "crazy error #2, not all waypoints in GlobalFrameAndNavTypeWaypointList have a height point,  replyFinished() won't work";
        }
    }

    qDebug() << "min Height" << minHeight;
    qDebug() << "max Height" << maxHeight;
    displayminHeight->setPlainText(QString("%1 m (MSL)").arg(QString::number(minHeight)));
    displaymaxHeight->setPlainText(QString("%1 m (MSL)").arg(QString::number(maxHeight)));

    arrangeHeightPoints();
    updateElevationItem();
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
    gradient.setColorAt(1, Qt::blue);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    //Draw sea mean line
    QLineF line(0,-boundary,sWidth,-boundary);
//    QBrush zerolinebrush();
//    QPen zerolinepen(zerolinebrush, 2, Qt::black);
    painter->setPen(Qt::black);
    painter->drawLine(line);

    //Fill Ground
    QRectF groundRect(0,-boundary, sWidth, boundary);
    painter->fillRect(groundRect, Qt::darkGreen);



    // Text
//    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
//                    sceneRect.width() - 4, sceneRect.height() - 4);
//    QString message(tr("Click and drag the points up and down, and zoom with the mouse "
//                       "..."));

//    QFont font = painter->font();
//    font.setBold(true);
//    font.setPointSize(14);
//    painter->setFont(font);
//    painter->setPen(Qt::lightGray);
//    painter->drawText(textRect.translated(2, 2), message);
//    painter->setPen(Qt::black);
//    painter->drawText(textRect, message);

}

void HeightProfile::updateElevationItem()
{
    QPolygonF elevationPolygon;
    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
    int elevationPolygonsize = wps.size();
    int i = 0;
    elevationPolygon << QPointF(sTopLeftCorner.x(),sTopLeftCorner.y()+sHeight);
    foreach(Waypoint* wp, wps)
    {
        //qDebug() << "the longitude of the actual waypoint is: " << wp->getLongitude();
        HeightPoint* currHp = waypointsToHeightPoints.value(wp, NULL);
        if(i == 0)
        {
            elevationPolygon << QPointF(sTopLeftCorner.x(),currHp->elevationPoint->y());
        }
        bool ishp = dynamic_cast<HeightPoint*>(currHp);
        if(ishp)
        {
            elevationPolygon << currHp->elevationPoint->pos();
        }
        else
        {
            qDebug() << "crazy error  #3";
        }
        i++;
        if(i == elevationPolygonsize)
        {
            elevationPolygon << QPointF(sTopLeftCorner.x() + sWidth, currHp->elevationPoint->y());
        }
    }
    elevationPolygon << QPointF(sTopLeftCorner.x()+sWidth, sTopLeftCorner.y()+sHeight);


    elevationItem->setPolygon(elevationPolygon);

}

void HeightProfile::updateSplineItem()
{
    QPainterPath splinePath; //path to be drawn in scene
    QPolygonF splinePoly; //points in scene coordinates for the splinePat
    QVector<double> trajX; //absolute X value
    QVector<double> trajY;
    QVector<double> trajZ;
    currWPManager->getEditableTrajectory()->getVector(trajX,trajY,trajZ);
    int splineNumber = trajX.size();
    if (splineNumber != trajY.size() && splineNumber != trajZ.size())
    {
        qDebug() << "Error in editableTrajectory";
    }
    if(splineNumber < 3)
    {
        //do something if waypoints are deleted!!!!!!
        return;
    }
    //get first and last wp from list
    QVector<Waypoint* > wps = currWPManager->getGlobalFrameAndNavTypeWaypointList();
    HeightPoint* startHp = dynamic_cast<HeightPoint*>(waypointsToHeightPoints.value(wps[0], NULL));
    HeightPoint* endHp = dynamic_cast<HeightPoint*>(waypointsToHeightPoints.value(wps[wps.size()-1], NULL));
//    qreal startX = waypointsToHeightPoints.value(wps[0], NULL)->x();
//    qreal endX = waypointsToHeightPoints.value(wps[wps.size()-1], NULL)->x();
    qreal startX=boundary;
    qreal endX = sWidth-boundary;
    if(!startHp || !endHp)
    {
        return;
    }
    //construct the splinePoly
    QVector<qreal> distanceToFirst(splineNumber);
    distanceToFirst[0] = 0;
    for(int i = 1; i < splineNumber; i++)
    {
        distanceToFirst[i] = distanceToFirst[i-1] + getDistance(trajX[i-1],trajY[i-1],trajX[i],trajY[i]);

    }
    for(int j = 0; j < splineNumber; j++)
    {
        splinePoly << QPointF(distanceToFirst[j]/distanceToFirst[splineNumber-1]*(endX-startX)+startX,fromAltitudeToScene(trajZ[j]));
    }

    splinePath.addPolygon(splinePoly);
    splineItem->setPath(splinePath);

}

void HeightProfile::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

