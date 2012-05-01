/**
 * @file
 *   @brief Interface for generating trajectories
 *
 *   @author Matthias Krebs <makrebs@student.ethz.ch>
 *
 */

#include "Trajectory.h"
#include <QDebug>

Trajectory::Trajectory()
{
    blockSplineInterpolation = false;
    splineResolution = 15;
}

//QPainterPath Trajectory::getPathXY() // FIXME: Not in use anymore
//{
//    QPainterPath pathXY;
//    pathXY.addPolygon(interpolPolyXY);
//    return pathXY;
//}

QPolygonF* Trajectory::getPolyXY()
{
    qDebug() << "Return a polygon for" << x.size() << "Points," << "Resolution =" << splineResolution << "Poygonpoints = " << interpolPolyXY.size();
    return &interpolPolyXY;
}

void Trajectory::getWaypointTrajectory(WaypointWithTrajectory* wp)
{
    if (interpolX.size() == 0)
    {
        qDebug() << "Interpolated trajectory is empty";
        return;
    }
    qint16 wpId = wp->getId();

    wp->trajectoryToWP.setX(interpolX.mid(wpId * splineResolution, splineResolution));
    wp->trajectoryToWP.setY(interpolY.mid(wpId * splineResolution, splineResolution));
    wp->trajectoryToWP.setZ(interpolZ.mid(wpId * splineResolution, splineResolution));
    for (int i = 0; i < wp->trajectoryToWP.getX().size(); i++)
    {
        qDebug() << "WAYPOINT UPDATED:" << wp->trajectoryToWP.getX().at(i);
    }
}

void Trajectory::setWPList(QVector<Waypoint *> wpList)
{
    x.clear();
    y.clear();
    z.clear();
    blockSplineInterpolation = true;
    foreach (Waypoint *wp, wpList)
    {
//        qDebug() << "setWPList: addWP" << wp->getId() << "with Lat" << wp->getLatitude() << "Lon" << wp->getLongitude();
        addWP(wp);
    }
    blockSplineInterpolation = false;
    generateSplines();
//    updateWPList(wpList);     // FIXME
}

void Trajectory::addWP(Waypoint *wp)
{
    x.append(wp->getX());
    y.append(wp->getY());
    z.append(wp->getZ());
}

void Trajectory::updateWP(Waypoint *wp)
{
    x.replace(wp->getId(), wp->getX());
    y.replace(wp->getId(), wp->getY());
    z.replace(wp->getId(), wp->getZ());
    generateSplines();
}

void Trajectory::generateSplines(uint resolution)
{
    if (!blockSplineInterpolation)
    {
        interpolX = interpolate(&x, resolution);
        interpolY = interpolate(&y, resolution);
        interpolZ = interpolate(&z, resolution);
    }

    interpolPolyXY.clear();
    for (int i = 0; i<interpolX.size(); i++)
    {
        interpolPolyXY.append( QPointF( interpolX.at(i), interpolY.at(i) ) );
    }
}

void Trajectory::generateSplines()
{
    if (!splineResolution)
        generateSplines(20);
    else
        generateSplines(splineResolution);
}

void Trajectory::setSplineResolution(uint resolution)
{
    splineResolution = resolution;
}

QVector<double> Trajectory::interpolate(const QVector<double> *points, int resolution)
{
    QPolygonF poly;
    foreach (double value, *points)
    {
        poly.append( QPointF( (qreal)poly.size(), value ) );
//        qDebug() << "interpolate: Appended to poly" << poly.last().x() << poly.last().y();
    }

    if ( !spline.setPoints(poly) )
    {
        qDebug() << "No valid points passed for interpolation.";
        return *points;
    }

    QVector<double> interpolatedPoints;
    interpolatedPoints = QVector<double>(); //FIXME

    const double delta = (1.0 / (double)(resolution));
    for (int i = 0; i <= ((points->size() - 1) * resolution); i++)  // interpolate
    {
        const double x = (double)(i) * delta;
        interpolatedPoints.append(spline.value(x));
//        qDebug() << "interpolate: Interpolated point" << x << interpolatedPoints.last();
    }
    return interpolatedPoints;
}
