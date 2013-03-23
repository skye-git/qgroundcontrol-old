/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009, 2010 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

#include "LedControlWidget.h"
#include "ui_LedControlWidget.h"
#include "UASManager.h"
#include "SkyeMAV.h"

#define COLOR_DEPTH 255   // 16bit
#define COLOR_DEPTH_RATIO 1

LedControlWidget::LedControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LedControlWidget),
    uasId(0),
    red(0),
    green(0),
    blue(0),
    dialog(new QColorDialog)
{
    ui->setupUi(this);

    // connect active uas
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    // connect color dialog
    connect(ui->ledColorButton, SIGNAL(pressed()), this, SLOT(openColorDialog()));
    connect(dialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(updateColor(QColor)));
    dialog->setOption(QColorDialog::NoButtons);

    // connect color spinboxes
    connect(this, SIGNAL(redColorChanged(int)), ui->spinBoxRed, SLOT(setValue(int)));
    connect(this, SIGNAL(greenColorChanged(int)), ui->spinBoxGreen, SLOT(setValue(int)));
    connect(this, SIGNAL(blueColorChanged(int)), ui->spinBoxBlue, SLOT(setValue(int)));
    connect(ui->spinBoxRed, SIGNAL(valueChanged(int)), this, SLOT(changedColorRed(int)));
    connect(ui->spinBoxGreen, SIGNAL(valueChanged(int)), this, SLOT(changedColorGreen(int)));
    connect(ui->spinBoxBlue, SIGNAL(valueChanged(int)), this, SLOT(changedColorBlue(int)));

    // set range of color spinboxes
    ui->spinBoxRed->setRange(0,COLOR_DEPTH);
    ui->spinBoxGreen->setRange(0,COLOR_DEPTH);
    ui->spinBoxBlue->setRange(0,COLOR_DEPTH);

}

LedControlWidget::~LedControlWidget()
{
    delete ui;
}

void LedControlWidget::setUAS(UASInterface* uas)
{
#ifdef QGC_USE_SKYE_INTERFACE
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        this->uasId = 0;
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(oldUAS);
        if (mav)
        {
            // disconnect skye
            disconnect(this, SIGNAL(transmitColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)),
                    mav, SLOT(sendLedColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)));
        }
    }


    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        this->uasId = mav->getUASID();

        // connect skye
        connect(this, SIGNAL(transmitColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)),
                mav, SLOT(sendLedColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)));
    }


#endif // QGC_USE_SKYE_INTERFACE
}

void LedControlWidget::openColorDialog()
{
    dialog->open();
}

void LedControlWidget::updateColor(QColor newColor)
{
    if (color != newColor)
    {
        color = newColor;
        red = color.red() * COLOR_DEPTH_RATIO;
        green = color.green() * COLOR_DEPTH_RATIO;
        blue = color.blue() * COLOR_DEPTH_RATIO;
        emit redColorChanged(red);
        emit greenColorChanged(green);
        emit blueColorChanged(blue);

        uint8_t mode = 0;
        float frequency = 0.0f;
        emit transmitColor(0, (uint8_t)red, (uint8_t)green, (uint8_t)blue, mode, frequency );
    }

}

void LedControlWidget::updateWidget()
{

}

void LedControlWidget::changedColorRed(int newRed)
{
    color.setRed(newRed);
    emit colorChanged(color);
}

void LedControlWidget::changedColorGreen(int newGreen)
{
    color.setGreen(newGreen);
    emit colorChanged(color);
}

void LedControlWidget::changedColorBlue(int newBlue)
{
    color.setBlue(newBlue);
    emit colorChanged(color);
}

void LedControlWidget::sendColor(QColor newColor)
{

}
