#ifndef HEIGHTPROFILE_H
#define HEIGHTPROFILE_H

#include <QGraphicsView>

class HeightProfile : public QGraphicsView
{
    Q_OBJECT
public:
    HeightProfile(QWidget *parent = 0);


    QGraphicsScene* scene;
    
signals:
    
public slots:

protected:
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);



    
};

#endif // HEIGHTPROFILE_H
