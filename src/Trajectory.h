#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <QObject>
#include <QVector>
#include <QGraphicsScene>
#include "Waypoint.h"
#include "qwt_spline.h"

class Trajectory : public QObject
{
    Q_OBJECT
public:
    Trajectory();
    /** @brief Returns a pointer to polygon of trajectory in xy plane */
    QPolygonF* getPolyXY();


protected:
    QVector<double> x;
    QVector<double> y;
    QVector<double> z;
    bool blockSplineInterpolation;      ///< If true, spline interpolation will not be calculated
    uint splineResolution;              ///< Number of calculated points per waypoint (including start wp)
    QwtSpline spline;                  ///< Spline interpolation through all points
    QVector<double> interpolX;
    QVector<double> interpolY;
    QVector<double> interpolZ;
    QPolygonF interpolPolyXY;

    /** @brief Get cubic spline interpolation
      * @param points Pointer to list of points
      * @param resolution Number of calculated points per waypoint
      */
    QVector<double> interpolate(const QVector<double> *points, int resolution);

public slots:
//    /** @brief Update trajectory of each wp
//      * @param wpList QVector containing pointers to all existing waypoints
//      */
//    void updateWPList(QVector<Waypoint*> wpList);

    /** @brief Overwrite list of points that defines the trajectory
      * @param wpList QVector containing pointers to all existing waypoints
      */
    void setWPList(QVector<Waypoint*> wpList);

    /** @brief Generate a spline interpolation through internal stored points
      * @param resolution Number of calculated points per waypoint
      */
    void generateSplines(uint resolution);

    /** @brief Generate a spline interpolation through internal stored points */
    void generateSplines();

    /** @brief Set spline interpolation resolution
      * @param resolution Number of calculated points per waypoint
      */
    void setSplineResolution(uint resolution);
    /** @brief Update a point of the trajectory and recalc trajectory
      * @param wp Pointer to Waypoint that has been changed
      */
    void updateWP(Waypoint *wp);

private slots:
    /** @brief Add a point for the trajectory
      * @param wp Pointer to Waypoint that has to be added
      */
    void addWP(Waypoint *wp);

};

#endif // TRAJECTORY_H
