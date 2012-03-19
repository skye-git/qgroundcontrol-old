#include "QGCMapTool.h"
#include "ui_QGCMapTool.h"
#include <QAction>
#include <QMenu>

QGCMapTool::QGCMapTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCMapTool)
{
    ui->setupUi(this);

    // Connect map and toolbar
    ui->toolBar->setMap(ui->map);
    // Connect zoom slider and map
    ui->zoomSlider->setMinimum(ui->map->MinZoom());
    ui->zoomSlider->setMaximum(ui->map->MaxZoom());
    ui->zoomSlider->setValue(ui->map->ZoomReal());
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), ui->map, SLOT(SetZoom(int)));
    connect(ui->map, SIGNAL(zoomChanged(int)), this, SLOT(setZoom(int)));

    connect(ui->Ring, SIGNAL(xValuechanged(double)), ui->doubleSpinBox_x, SLOT(setValue(double)));//Code AL (18.03.12)
    connect(ui->Ring, SIGNAL(yValuechanged(double)), ui->doubleSpinBox_y, SLOT(setValue(double)));//Ende
}

void QGCMapTool::setZoom(int zoom)
{
    if (ui->zoomSlider->value() != zoom)
    {
        ui->zoomSlider->setValue(zoom);
    }
}

QGCMapTool::~QGCMapTool()
{
    delete ui;
}

void QGCMapTool::resizeEvent(QResizeEvent *event) //Beginn Code AL (18.03.12)
{
    ui->Ring->resize(event->size());
    event->accept();
}                                       //Ende Code
