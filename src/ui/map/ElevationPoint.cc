#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "ElevationPoint.h"
#include "ElevationProfileDisplay.h"

ElevationPoint::ElevationPoint(ElevationProfileDisplay *elevationProfileDisplay)
    : display(elevationProfileDisplay)
{
    setFlag(ItemIsMovable);
}
