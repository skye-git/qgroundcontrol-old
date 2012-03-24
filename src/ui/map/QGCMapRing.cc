#include <QtGui>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265359
#endif


#include "QGCMapRing.h"

QGCMapRing::QGCMapRing(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
        setPalette((Qt::transparent));
//        sidescaling = 200;
//        outerradius = 75;
//        innerradius = 70;
}

void QGCMapRing::paintEvent(QPaintEvent *)
{


//    QColor ringColor(0, 0, 127);

//    int side = qMin(width(), height());

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.translate(width() / 2, height() / 2);
//    painter.scale(side/sidescaling, side/sidescaling);

//    painter.setPen(Qt::NoPen);
//    painter.setBrush(ringColor);

//    QPainterPath path;
//    path.moveTo(outerradius,0);
//    path.arcTo(-outerradius,-outerradius,2*outerradius,2*outerradius,0,360);
//    path.moveTo(innerradius,0);
//    path.arcTo(-innerradius,-innerradius,2*innerradius,2*innerradius,0,360);

//    painter.drawPath(path);

    QColor ringColor(0, 0, 127);

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(ringColor);

    QPainterPath path;
        path.moveTo(80,0);
        path.arcTo(-80,-80,160,160,0,360);
        path.moveTo(70,0);
        path.arcTo(-70,-70,140,140,0,360);

        painter.drawPath(path);


}

void QGCMapRing::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();
    double x = point.x();
    double y = point.y();
    emit xValuechanged(x);
    emit yValuechanged(y);
}


void QGCMapRing::resizeEvent(QResizeEvent * /* event */)
{
    int side = qMin(width(), height());

    QRegion outerCircle(width()/2-side/2*0.8, height()/2-side/2*0.8, side*0.8, side*0.8, QRegion::Ellipse);
    QRegion innerCircle(width()/2-side/2*0.7, height()/2-side/2*0.7, side*0.7, side*0.7, QRegion::Ellipse);
    QRegion Ring = outerCircle.subtracted(innerCircle);


    setMask(Ring);


//      QRegion outerCircle(width()/2-outerradius, height()/2-outerradius,2*outerradius,2*outerradius, QRegion::Ellipse);
//      QRegion innerCircle(width()/2-innerradius, height()/2-innerradius,2*innerradius,2*innerradius,QRegion::Ellipse);
//      QRegion Ring = outerCircle.subtracted(innerCircle);

//      setMask(Ring);
}



QSize QGCMapRing::sizeHint() const
{
    return QSize(100, 100);
}
