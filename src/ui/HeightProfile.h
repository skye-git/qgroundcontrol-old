#ifndef HEIGHTPROFILE_H
#define HEIGHTPROFILE_H

#include <QGraphicsView>

#include "UASInterface.h"
#include "UASWaypointManager.h"
#include "Waypoint.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class HeightPoint;

class HeightProfile : public QGraphicsView
{
    Q_OBJECT
public:
    HeightProfile(QWidget *parent = 0);


    QGraphicsScene* scene;

    //For Text Label
    bool getelevationwascalled;
    
signals:
    void wapointChanged(Waypoint*wp);
    void setinfoLabelText(QString string);

public:
    qreal fromAltitudeToScene(qreal altitude);
    qreal fromSceneToAltitude(qreal sceneY);
    
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
    /** @brief calculate the angle between two wp */
    qreal getAngle(Waypoint* wp1, Waypoint *wp2);
    /** @brief get the Elevation for each HeightPoint in the scene */
    void getElevationPoints(); //Integrate perhaps in update slots...
    /** @brief construct the URL for the Elevation request */
    QUrl constructUrl(QVector<Waypoint* > wps); //Integrate perhaps in update slots...
    /** @brief processes the xml reply after getElevationPoints request */
    void replyFinished(QNetworkReply* reply); //Integrate perhaps in update slots...
    /** @brief update the values for minHeight /maxHeight */
    void updateExtrema();


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
    void updateElevationItem();
    void scaleView(qreal scaleFactor);

    UASWaypointManager* currWPManager; ///< The current waypoint manager
    QMap<Waypoint* , HeightPoint*> waypointsToHeightPoints;
    QMap<HeightPoint*, Waypoint*> heightPointsToWaypoints;
    Waypoint* firingWaypointChange;
    bool profileInitialized; ///< Profile initialized?
    //QTimer rearrangeTimer;

    //sceneParameters
    QPointF sTopLeftCorner;
    double sWidth;
    double sHeight;
    double minHeight;
    double maxHeight;
    double boundary;

    QGraphicsPolygonItem * elevationItem; //not working!!!!!
    QGraphicsTextItem * displayminHeight;
    QGraphicsTextItem * displaymaxHeight;

    QNetworkAccessManager* networkManager;
    


};

#endif // HEIGHTPROFILE_H
