#include "QGCSkyeTestSetpointsWidget.h"
#include "ui_QGCSkyeTestSetpointsWidget.h"

QGCSkyeTestSetpointsWidget::QGCSkyeTestSetpointsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCSkyeTestSetpointsWidget)
{
    ui->setupUi(this);
}

QGCSkyeTestSetpointsWidget::~QGCSkyeTestSetpointsWidget()
{
    delete ui;
}
