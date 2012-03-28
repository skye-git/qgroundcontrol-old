#include <QtGui>
#include <cmath>
#include "UAS.h"
#include "UASManager.h"
#include "SkyeMAV.h"

#ifndef M_PI
#define M_PI 3.14159265359
#endif


#include "QGCMapRing.h"

QGCMapRing::QGCMapRing(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
        setPalette((Qt::transparent));
        setVisible(false);//!!!!!
        countingup = false;
        stepsize = multiplicator= 1.1;
        x_0 = y_0 = z_0 = x = y = z = 0;
        side = qMin(width(), height());
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this, SLOT(emitValues()));
        timer->start(100); //every 0.1 seconds emitValues is calles
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



    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    QColor ringColor(0, 0, 127,150);
    QRadialGradient grad(0,0,180,-75,0);
        grad.setColorAt(0.0, Qt::white);
//        grad.setColorAt(0.1, Qt::green);
        grad.setColorAt(0.99, ringColor);
    QBrush brush(grad);
    painter.setPen(Qt::gray);
    painter.setBrush(brush);

    QPainterPath path;

    //Ring
        path.moveTo(80,0);
        path.arcTo(-80,-80,160,160,0,360);
        path.moveTo(70,0);
        path.arcTo(-70,-70,140,140,0,360);

     //Buttons
        path.moveTo(88,73);
        path.arcTo(58,58,30,30,0,360);


        path.moveTo(88,-73);
        path.arcTo(58,-88,30,30,0,360);


        painter.drawPath(path);



}

void QGCMapRing::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();

    if((point.x() > 0.58*side/2) && (point.y() > 0.58*side/2))
        z_0 = 0.1;
    else if((point.x() > 0.58*side/2) && (point.y() < -0.58*side/2))
        z_0 = -0.1;
    else
    {
        double theta = std::atan2(-point.x(), -point.y());
        x_0 = cos(theta)*0.1;
        y_0 = -sin(theta)*0.1;
    }

    countingup = true;
    emitValues();
}

void QGCMapRing::mouseMoveEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();

    if(((point.x() > 0.58*side/2) && (point.y() > 0.58*side/2)) && (x_0 == 0 && y_0 == 0))
        z_0 = 0.1;
    else if(((point.x() > 0.58*side/2) && (point.y() < -0.58*side/2)) && (x_0 == 0 && y_0 == 0))
        z_0 = -0.1;
    else if(z_0 ==0)
    {
        double theta = std::atan2(-point.x(), -point.y());
        x_0 = cos(theta)*0.1;
        y_0 = -sin(theta)*0.1;
    }

//    double theta = std::atan2(-point.x(), -point.y());
//    x_0 = cos(theta)*0.1;
//    y_0 = -sin(theta)*0.1;

    x = x_0*multiplicator;
    y = y_0*multiplicator;
    z = z_0*multiplicator;

    emitValues();
}


void QGCMapRing::mouseReleaseEvent(QMouseEvent *event)
{
    countingup = false;
    x_0 = 0;
    y_0 = 0;
    z_0 = 0;
    x = 0;
    y = 0;
    z = 0;
    multiplicator = stepsize;
    emit xValuechanged(x);
    emit yValuechanged(y);
    emit zValuechanged(z);
    emit valueTouchInputChanged(x,y,z,0,0,0);
}

void QGCMapRing::emitValues()
{
    if(countingup)
    {
        emit xValuechanged(x);
        emit yValuechanged(y);
        emit zValuechanged(z);
        emit valueTouchInputChanged(x,y,z,0,0,0);
        if(multiplicator*stepsize < 10)
        {
            multiplicator = multiplicator*stepsize;
        }
        x = x_0*multiplicator;
        y = y_0*multiplicator;
        z = z_0*multiplicator;
    }
}

void QGCMapRing::resizeEvent(QResizeEvent * /* event */)
{
    //int side = qMin(width(), height());
    side = qMin(width(), height());

    QRegion outerCircle(width()/2-side/2*0.81, height()/2-side/2*0.81, side*0.81, side*0.81, QRegion::Ellipse);
    QRegion innerCircle(width()/2-side/2*0.69, height()/2-side/2*0.69, side*0.69, side*0.69, QRegion::Ellipse);
    QRegion Ring = outerCircle.subtracted(innerCircle);

    QRegion lowerButton(width()/2+side/2*0.58, height()/2+side/2*0.58, side/2*0.3, side/2*0.3, QRegion::Ellipse);
    QRegion upperButton(width()/2+side/2*0.58, height()/2-side/2*0.88, side/2*0.3, side/2*0.3, QRegion::Ellipse);
    QRegion Buttons = lowerButton.united(upperButton);

    QRegion unitedRegion = Ring.united(Buttons);


    setMask(unitedRegion);


//      QRegion outerCircle(width()/2-outerradius, height()/2-outerradius,2*outerradius,2*outerradius, QRegion::Ellipse);
//      QRegion innerCircle(width()/2-innerradius, height()/2-innerradius,2*innerradius,2*innerradius,QRegion::Ellipse);
//      QRegion Ring = outerCircle.subtracted(innerCircle);

//      setMask(Ring);
}



QSize QGCMapRing::sizeHint() const
{
    return QSize(100, 100);
}
