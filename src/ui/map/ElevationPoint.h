#ifndef ELEVATIONPOINT_H
#define ELEVATIONPOINT_H

#include <QGraphicsItem>

class ElevationProfileDisplay;

class ElevationPoint : public QGraphicsItem
{
public:
    ElevationPoint(ElevationProfileDisplay *elevationProfileDisplay);

private:
    ElevationProfileDisplay *display;

};

#endif // ELEVATIONPOINT_H
