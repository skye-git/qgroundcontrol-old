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

    // connect color spinboxes
    connect(this, SIGNAL(redColorChanged(int)), ui->spinBoxRed, SLOT(setValue(int)));
    connect(this, SIGNAL(greenColorChanged(int)), ui->spinBoxGreen, SLOT(setValue(int)));
    connect(this, SIGNAL(blueColorChanged(int)), ui->spinBoxBlue, SLOT(setValue(int)));

    // set range of color spinboxes
    ui->spinBoxRed->setRange(0,COLOR_DEPTH);
    ui->spinBoxGreen->setRange(0,COLOR_DEPTH);
    ui->spinBoxBlue->setRange(0,COLOR_DEPTH);

}

LedControlWidget::~LedControlWidget()
{
    delete ui;
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

//        sendColor
    }

}

void LedControlWidget::updateWidget()
{

}
