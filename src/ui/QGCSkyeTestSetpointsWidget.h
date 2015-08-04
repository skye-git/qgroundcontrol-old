#ifndef QGCSKYETESTSETPOINTSWIDGET_H
#define QGCSKYETESTSETPOINTSWIDGET_H

#include <QWidget>

namespace Ui {
class QGCSkyeTestSetpointsWidget;
}

class QGCSkyeTestSetpointsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGCSkyeTestSetpointsWidget(QWidget *parent = 0);
    ~QGCSkyeTestSetpointsWidget();

private:
    Ui::QGCSkyeTestSetpointsWidget *ui;
};

#endif // QGCSKYETESTSETPOINTSWIDGET_H
