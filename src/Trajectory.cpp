#include "Trajectory.h"
#include <QDebug>

Trajectory::Trajectory()
{
    x = NULL;
    y = NULL;
    z = NULL;
    blockSplineInterpolation = false;
    splineResolution = 100;
    spline = NULL;
}

QPainterPath Trajectory::getPathXY()
{
    polyXY = getPolyXY();
    QPainterPath pathXY;
    pathXY.addPolygon(polyXY);
    return pathXY;
}

QPolygonF Trajectory::getPolyXY()
{
    for (int i = 0; i<x->size(); i++)
    {
        polyXY.append( QPointF( x->at(i), y->at(i) ) );
    }
    return polyXY;
}

void Trajectory::updateWPList(QVector<Waypoint *> wpList)
{
    /* Update path to wp if it is not first wp */
    for (int i = 1; i<wpList.size(); i++)
    {
        wpList.at(i)->pathX2WP = interpolX.mid(splineResolution * (i-1) + 1, splineResolution);
        wpList.at(i)->pathY2WP = interpolY.mid(splineResolution * (i-1) + 1, splineResolution);
        wpList.at(i)->pathZ2WP = interpolZ.mid(splineResolution * (i-1) + 1, splineResolution);
    }
}

void Trajectory::setWPList(QVector<Waypoint *> wpList)
{
    blockSplineInterpolation = true;
    foreach (Waypoint *wp, wpList)
    {
        addWP(wp);
    }
    blockSplineInterpolation = true;
    generateSplines();
    updateWPList(wpList);
}

void Trajectory::addWP(Waypoint *wp)
{
    if(!x)
        x = new QVector<double>;
    x->append(wp->getX());
    if(!y)
        y = new QVector<double>;
    y->append(wp->getY());
    if(!z)
        z = new QVector<double>;
    z->append(wp->getZ());
    generateSplines();
//    updateWPList(wpList); // FIXME !!!!!!!!!!!
}

void Trajectory::generateSplines(uint resolution)
{
    if (!blockSplineInterpolation)
    {
        interpolX = interpolate(x, resolution);
        interpolY = interpolate(y, resolution);
        interpolZ = interpolate(z, resolution);
    }
}

void Trajectory::generateSplines()
{
    if (splineResolution)
    {
        generateSplines(splineResolution);
    }
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
    }

    if ( !spline->setPoints(poly) )
    {
        qDebug() << "No valid points passed for interpolation.";
        return *points;
    }

    QVector<double> interpolatedPoints;

    const double delta = (points->size()) / (resolution + 1);

    for(int i = 0; i < resolution; i++)  // interpolate
    {
        const double x = (i+1) * delta;
        interpolatedPoints.append(spline->value(x));
    }
    return interpolatedPoints;
}
