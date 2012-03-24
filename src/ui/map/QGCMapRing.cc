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
}

void QGCMapRing::paintEvent(QPaintEvent *)
{


    QColor ringColor(0, 0, 127);

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(ringColor);

    QPainterPath path;
        path.moveTo(75,0);
        path.arcTo(-75,-75,150,150,0,360);
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
    //QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side, side, QRegion::Ellipse);

    QRegion outerCircle(width()/2-side/2, height()/2-side/2,side,side, QRegion::Ellipse);
    QRegion innerCircle(width()/2-side/3, height()/2-side/3, side*2/3,side*2/3,QRegion::Ellipse);
    QRegion Ring = outerCircle.subtracted(innerCircle);


    //setMask(maskedRegion);
    setMask(Ring);
}



QSize QGCMapRing::sizeHint() const
{
    return QSize(100, 100);
}
