#include "QGCMapTool.h"
#include "ui_QGCMapTool.h"
#include <QAction>
#include <QMenu>

QGCMapTool::QGCMapTool(QWidget *parent) :
    QWidget(parent),
    uasId(0),
    uasMode(0),
    touchInputvisib(false),
    touchInputModeSet(false),
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

    connect(ui->Ring, SIGNAL(xValuechanged(double)), ui->doubleSpinBox_x, SLOT(setValue(double)));//Code AL (25.03.12)
    connect(ui->Ring, SIGNAL(yValuechanged(double)), ui->doubleSpinBox_y, SLOT(setValue(double)));
    connect(ui->Ring, SIGNAL(zValuechanged(double)), ui->doubleSpinBox_z, SLOT(setValue(double)));
    connect(ui->Ring, SIGNAL(valueMapRingChanged(double,double,double)),this,SLOT(transmitMapRingvalues(double,double,double)));//Ende

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));//Code MA (23.04.2012)

}

void QGCMapTool::setUAS(UASInterface* uas)
{
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(oldUAS);
        if (mav)
        {
            disconnect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        }
    }

    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        connect(mav, SIGNAL(modeChanged(int,int)), this, SLOT(updateMode(int,int)));
        updateMode(mav->getUASID(), mav->getUASMode());
    }
}

void QGCMapTool::updateMode(int uas,int mode)
{
    if ((uasId == uas) && ((int)uasMode != mode))
    {
        uasMode = (unsigned int)mode;
        // Check for touchring visibility
        setRingvisible(touchInputModeSet);
    }
}


void QGCMapTool::setZoom(int zoom)
{
    if (ui->zoomSlider->value() != zoom)
    {
        ui->zoomSlider->setValue(zoom);
    }
}

void QGCMapTool::setRingvisible(bool visib) // Beginn Code AL (26.03.12) Mod MA
{
    touchInputModeSet = visib;
    touchInputvisib = (visib && !(uasMode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED));
    ui->Ring->setVisible(touchInputvisib);
}                                           // Ende Code AL, Mod MA

void QGCMapTool::transmitMapRingvalues(double x, double y, double z) // Beginn Code AL (11.04.12)
{
    if(touchInputvisib)
    {
        emit valueTouchInputChangedMap(x, y, z);
    }

}                                           // Ende Code AL

QGCMapTool::~QGCMapTool()
{
    delete ui;
}

void QGCMapTool::resizeEvent(QResizeEvent *event) //Beginn Code AL (18.03.12)
{
    ui->Ring->resize(event->size());
    event->accept();
}                                       //Ende Code
