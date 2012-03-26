#ifndef QGCMAPRING_H
#define QGCMAPRING_H

#include <QWidget>
#include "UASInterface.h"

class QGCMapRing : public QWidget
{
    Q_OBJECT
public:
    QGCMapRing(QWidget *parent = 0);
    QSize sizeHint() const;

    void draw(QPainter *painter);

signals:
    void xValuechanged(double x);
    void yValuechanged(double y);
    void zValuechanged(double z);
    void valueTouchInputChanged(double, double, double, double, double, double);

public slots:
    void emitValues();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *);
    //UASInterface* uas;

private:
    bool countingup;
    double stepsize;
    double x;
    double y;
    double z;
    int side;
//    int sidescaling;
//    int outerradius;
//    int innerradius;

};

#endif // QGCMAPRING_H
