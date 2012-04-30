#include "Trajectory.h"
#include <QDebug>

Trajectory::Trajectory()
{
    x = new QVector<double>;
    y = new QVector<double>;
    z = new QVector<double>;
    blockSplineInterpolation = false;
    splineResolution = 100;
//    spline = NULL;
}

QPainterPath Trajectory::getPathXY()
{
    getPolyXY();
    QPainterPath pathXY;
    pathXY.addPolygon(polyXY);
    return pathXY;
}

QPolygonF* Trajectory::getPolyXY()
{
    return &polyXY;
}

//void Trajectory::updateWPList(QVector<Waypoint *> wpList)
//{
//    /* Update path to wp if it is not first wp */
//    for (int i = 1; i<wpList.size(); i++)
//    {
//        wpList.at(i)->pathX2WP = interpolX.mid(splineResolution * (i-1) + 1, splineResolution);
//        wpList.at(i)->pathY2WP = interpolY.mid(splineResolution * (i-1) + 1, splineResolution);
//        wpList.at(i)->pathZ2WP = interpolZ.mid(splineResolution * (i-1) + 1, splineResolution);
//    }
//}

void Trajectory::setWPList(QVector<Waypoint *> wpList)
{
    x->clear();
    y->clear();
    z->clear();
    blockSplineInterpolation = true;
    foreach (Waypoint *wp, wpList)
    {
        qDebug() << "setWPList: addWP" << wp->getId() << "with Lat" << wp->getLatitude() << "Lon" << wp->getLongitude();
        addWP(wp);
    }
    blockSplineInterpolation = false;
    generateSplines();
//    updateWPList(wpList);     // FIXME
}

void Trajectory::addWP(Waypoint *wp)
{
    x->append(wp->getX());
    y->append(wp->getY());
    z->append(wp->getZ());
}

void Trajectory::updateWP(Waypoint *wp)
{
    x->replace(wp->getId(), wp->getX());
    y->replace(wp->getId(), wp->getY());
    z->replace(wp->getId(), wp->getZ());
    generateSplines();
}

void Trajectory::generateSplines(uint resolution)
{
    if (!blockSplineInterpolation)
    {
        interpolX = interpolate(x, resolution);
        interpolY = interpolate(y, resolution);
        interpolZ = interpolate(z, resolution);
    }

    polyXY.clear();
    for (int i = 0; i<interpolX.size(); i++)
    {
        polyXY.append( QPointF( interpolX.at(i), interpolY.at(i) ) );
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
        qDebug() << "interpolate: Appended to poly" << poly.last().x() << poly.last().y();
    }

    if ( !spline.setPoints(poly) )
    {
        qDebug() << "No valid points passed for interpolation.";
        return *points;
    }

    QVector<double> interpolatedPoints;
    interpolatedPoints = QVector<double>(); //FIXME

    const double delta = (double)points->size() / (resolution + 1);

    for (int i = 0; i < resolution; i++)  // interpolate
    {
        const double x = (double)(i+1) * delta;
        interpolatedPoints.append(spline.value(x));
//        qDebug() << "interpolate: Interpolated point" << x << interpolatedPoints.last();
    }
    return interpolatedPoints;
}
