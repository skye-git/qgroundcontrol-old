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

bool Trajectory::getVector(QVector<double> &trajX, QVector<double> &trajY, QVector<double> &trajZ)
{
    if ( interpolX.isEmpty() || interpolY.isEmpty() || interpolZ.isEmpty())
    {
        qDebug() << "isEmpty" << interpolX.isEmpty() << interpolY.isEmpty() << interpolZ.isEmpty();
        return false;
    }
    trajX = interpolX;
    trajY = interpolY;
    trajZ = interpolZ;
    return true;
}

bool Trajectory::getVectorX(QVector<double>* trajX)
{
    if ( interpolX.isEmpty() )
    {
        return false;
    }

    trajX = &interpolX;
    return true;
}

bool Trajectory::getVectorY(QVector<double>* trajY)
{
    if ( interpolY.isEmpty() )
    {
        return false;
    }

    trajY = &interpolY;
    return true;
}

bool Trajectory::getVectorZ(QVector<double>* trajZ)
{
    if ( interpolZ.isEmpty() )
    {
        return false;
    }

    trajZ = &interpolZ;
    return true;
}

QPolygonF* Trajectory::getPolyXY()
{
//    qDebug() << "Return a polygon for" << x.size() << "Points," << "Resolution =" << splineResolution << "Polygonpoints = " << interpolPolyXY.size();
    return &interpolPolyXY;
}

QPolygonF* Trajectory::getPolyXY(int from, int to)
{
//    qDebug() << "Return a partial polygon from" << from << "to" << to;
    if (interpolPolyXY.size() > to)
    {
        interpolPolyXYpart = interpolPolyXY.mid(from, to - from + 1);
    }
    else
    {
        interpolPolyXYpart.clear();
    }
    return &interpolPolyXYpart;
}

void Trajectory::setWPList(QVector<Waypoint *> wpList)
{
    x.clear();
    y.clear();
    z.clear();
//    blockSplineInterpolation = true;
    foreach (Waypoint *wp, wpList)
    {
//        qDebug() << "setWPList: addWP" << wp->getId() << "with Lat" << wp->getLatitude() << "Lon" << wp->getLongitude();
        addWP(wp);
    }
//    blockSplineInterpolation = false;

    // Avoid generating nonsense trajectories going trough lat/lon 0/0
    if (x.last() != 0.0 && y.last() != 0.0)
    {
        generateSplines();
    }
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
//    if (!blockSplineInterpolation)
//    {
        interpolX = interpolate(&x, resolution);
        interpolY = interpolate(&y, resolution);
        interpolZ = interpolate(&z, resolution);
        qDebug() << "generated Splines length" << interpolX.size() << interpolY.size() << interpolZ.size();
//    }

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

QVector<double> Trajectory::getDeltaNorm(const QVector<double> *x, const QVector<double> *y)
{
    // Check if input vectors are valid
    if (x->size() != y->size())
    {
        qDebug() << "Invalid input vectors for delta norm calculation";
        return QVector<double>();
    }

    double deltaX;
    double deltaY;

    QVector<double> deltaNorm(x->size() - 1);
    for (int i=0; i<deltaNorm.size(); i++)
    {
        deltaX = x->value(i+1) - x->value(i);
        deltaY = y->value(i+1) - y->value(i);
        deltaNorm[i] = qwtSqr(deltaX*deltaX + deltaY*deltaY);
    }
    return deltaNorm;
}
