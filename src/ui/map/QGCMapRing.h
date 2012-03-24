#ifndef QGCMAPRING_H
#define QGCMAPRING_H

#include <QWidget>

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

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *);

//private:
//    int sidescaling;
//    int outerradius;
//    int innerradius;

//    void mousePressEvent(QMouseEvent *event);
};

#endif // QGCMAPRING_H
