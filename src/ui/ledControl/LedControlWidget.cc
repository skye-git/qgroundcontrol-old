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

#include <QStringList>

#define COLOR_DEPTH 255   // 16bit
#define COLOR_DEPTH_RATIO 1

LedControlWidget::LedControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LedControlWidget),
    uasId(0),
    red(0),
    green(0),
    blue(0),
    mode(LED_CONTROL_MODE_CONSTANT),
    frequency(0.0),
    enabled(false),
    dialog(new QColorDialog)
//    dialogVisible(false)
{
    ui->setupUi(this);

    buttonColors[0].setRgb(255,255,255);
    buttonColors[1].setRgb(255,  0,  0);
    buttonColors[2].setRgb(  0,255,  0);
    buttonColors[3].setRgb(  0,  0,255);
    for (int i=0; i<QGC_LED_COLOR_BUTTONS_MAX; i++) {
       QString colorStr;
       colorStr.sprintf("QWidget { background-color: #%02X%02X%02X; }", buttonColors[i].red(), buttonColors[i].green(), buttonColors[i].blue());
       colorButtons[i].setStyleSheet(colorStr);
       ui->colorLayout->addWidget(&colorButtons[i]);
       colorButtons[i].setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
       colorButtons[i].setMinimumSize(QSize(19, 19));
       colorButtons[i].setMaximumSize(QSize(20, 20));
    }
    // TODO: Find better way to assign color to buttons
    connect(&colorButtons[0], SIGNAL(clicked(bool)), this, SLOT(colorButton0Clicked(bool)));
    connect(&colorButtons[1], SIGNAL(clicked(bool)), this, SLOT(colorButton1Clicked(bool)));
    connect(&colorButtons[2], SIGNAL(clicked(bool)), this, SLOT(colorButton2Clicked(bool)));
    connect(&colorButtons[3], SIGNAL(clicked(bool)), this, SLOT(colorButton3Clicked(bool)));


    // connect active uas
    this->setUAS(UASManager::instance()->getActiveUAS());
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));

    // connect color dialog
    connect(ui->ledColorButton, SIGNAL(pressed()), this, SLOT(changeColorDialogVisibility()));
    connect(dialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(changeColor(QColor)));
    dialog->setOption(QColorDialog::NoButtons);
    this->layout()->addWidget(dialog);
    dialog->close();

    // connect color spinboxes
    connect(this, SIGNAL(redColorChanged(int)), ui->spinBoxRed, SLOT(setValue(int)));
    connect(this, SIGNAL(greenColorChanged(int)), ui->spinBoxGreen, SLOT(setValue(int)));
    connect(this, SIGNAL(blueColorChanged(int)), ui->spinBoxBlue, SLOT(setValue(int)));
    connect(ui->spinBoxRed, SIGNAL(valueChanged(int)), this, SLOT(changeColorRed(int)));
    connect(ui->spinBoxGreen, SIGNAL(valueChanged(int)), this, SLOT(changeColorGreen(int)));
    connect(ui->spinBoxBlue, SIGNAL(valueChanged(int)), this, SLOT(changeColorBlue(int)));

    // set range of color spinboxes
    ui->spinBoxRed->setRange(0,COLOR_DEPTH);
    ui->spinBoxGreen->setRange(0,COLOR_DEPTH);
    ui->spinBoxBlue->setRange(0,COLOR_DEPTH);

    // set default value of color spinboxes
    ui->spinBoxRed->setValue(COLOR_DEPTH);
    ui->spinBoxGreen->setValue(COLOR_DEPTH);
    ui->spinBoxBlue->setValue(COLOR_DEPTH);

    // offer mode settings according to LED_CONTROL_MODE enumerator
    // ui->comboBoxMode->insertItems(0, QStringList() << "CONSTANT" << "BLINK" << "PULS" << "RAINBOW" << "DISCO");
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_CONSTANT, GetNameForLedColorMode(LED_CONTROL_MODE_CONSTANT));
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_BLINK, GetNameForLedColorMode(LED_CONTROL_MODE_BLINK));
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_PULS, GetNameForLedColorMode(LED_CONTROL_MODE_PULS));
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_RAINBOW, GetNameForLedColorMode(LED_CONTROL_MODE_RAINBOW));
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_DISCO, GetNameForLedColorMode(LED_CONTROL_MODE_DISCO));
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_POWER, GetNameForLedColorMode(LED_CONTROL_MODE_POWER));
    ui->comboBoxMode->insertItem(LED_CONTROL_MODE_SPEED, GetNameForLedColorMode(LED_CONTROL_MODE_SPEED));
    connect(ui->comboBoxMode, SIGNAL(activated(int)), this, SLOT(changeMode(int)));

    // initialize frequency spinbox
    ui->doubleSpinBoxFrequency->setRange(0.0, 100.0);
    ui->doubleSpinBoxFrequency->setSingleStep(0.1);
    ui->doubleSpinBoxFrequency->setValue(1.0);
    connect(ui->doubleSpinBoxFrequency, SIGNAL(valueChanged(double)), this, SLOT(changeFrequency(double)));

    // connect on/off switch and do initial update
    connect(ui->checkBoxOnOff, SIGNAL(toggled(bool)), this, SLOT(setLedEnabled(bool)));
    ui->checkBoxOnOff->setChecked(enabled);

}

LedControlWidget::~LedControlWidget()
{
    delete ui;
}

void LedControlWidget::setUAS(UASInterface* uas)
{
    qDebug() << "setUAS (LED)";
    if (this->uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        this->uasId = 0;
        SkyeUAS* mav = dynamic_cast<SkyeUAS*>(oldUAS);
        if (mav)
        {
            // disconnect skye
            disconnect(this, SIGNAL(transmitColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)),
                    mav, SLOT(sendLedColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)));
        }
    }


    SkyeUAS* mav = dynamic_cast<SkyeUAS*>(uas);
    if (mav)
    {
        qDebug() << "Connected LED CONTROL";
        this->uasId = mav->getUASID();

        // start timer and initial submit
        updateValues();
        timeOfSubmit.start();
        emit transmitColor(0, (uint8_t)red, (uint8_t)green, (uint8_t)blue, mode, (float)frequency);

        // connect color submit
        connect(this, SIGNAL(transmitColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)),
                mav, SLOT(sendLedColor(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float)));
    }

}

void LedControlWidget::changeColorDialogVisibility()
{
    if (!dialog->isVisible()) {
        dialog->show();
    }
//    if (dialogVisible)
//    {
//        dialog->close();
//        ui->ledColorButton->setText("Show colors");
//    } else {
//        dialog->open();
//        ui->ledColorButton->setText("Hide colors");
//    }
//    dialogVisible = !dialogVisible;
}

void LedControlWidget::changeColor(QColor newColor)
{
    if (color != newColor)
    {
        color = newColor;
        red = color.red();
        green = color.green();
        blue = color.blue();
        emit redColorChanged(red);
        emit greenColorChanged(green);
        emit blueColorChanged(blue);

        sendColor();
    }

}

void LedControlWidget::changeColorRed(int newRed)
{
    if (red != newRed)
    {
        red = newRed;
        color.setRed(newRed);
        sendColor();
    }
}

void LedControlWidget::changeColorGreen(int newGreen)
{
    if (green != newGreen)
    {
        green = newGreen;
        color.setGreen(newGreen);
        sendColor();
    }
}

void LedControlWidget::changeColorBlue(int newBlue)
{
    if (blue != newBlue)
    {
        blue = newBlue;
        color.setBlue(newBlue);
        sendColor();
    }
}

void LedControlWidget::changeMode(int newMode)
{
    mode = (LED_CONTROL_MODE)newMode;
    sendColor();
}

void LedControlWidget::changeFrequency(double newFrequency)
{
    frequency = newFrequency;
    sendColor();
}

void LedControlWidget::sendColor()
{
    if (this->uasId)
    {
        // rate limit transmission to 10ms (100Hz)
        if (timeOfSubmit.elapsed() > 10)
        {
            if (enabled) {
                updateValues();
                timeOfSubmit.restart();
                emit transmitColor(0, (uint8_t)red, (uint8_t)green, (uint8_t)blue, mode, (float)frequency);
            } else {
                qDebug() << "Changed color, but LED are disabled";
            }
        }
    }
}

void LedControlWidget::updateValues()
{
    red = ui->spinBoxRed->value();
    green = ui->spinBoxGreen->value();
    blue = ui->spinBoxBlue->value();
    frequency = ui->doubleSpinBoxFrequency->value();
    mode = (LED_CONTROL_MODE)ui->comboBoxMode->currentIndex();
}

void LedControlWidget::updateWidget()
{
}

QString LedControlWidget::GetNameForLedColorMode(LED_CONTROL_MODE m)
{
    QString modeName;
    switch(m)
    {
    case LED_CONTROL_MODE_CONSTANT:
        modeName = "CONSTANT";
        break;
    case LED_CONTROL_MODE_BLINK:
        modeName = "BLINK";
        break;
    case LED_CONTROL_MODE_PULS:
        modeName = "PULS";
        break;
    case LED_CONTROL_MODE_RAINBOW:
        modeName = "RAINBOW";
        break;
    case LED_CONTROL_MODE_DISCO:
        modeName = "DISCO";
        break;
    case LED_CONTROL_MODE_POWER:
        modeName = "POWER";
        break;
    case LED_CONTROL_MODE_SPEED:
        modeName = "SPEED";
        break;
    default:
        modeName = "unsupported";
        break;
    }
    return modeName;
}

void LedControlWidget::setLedEnabled(bool checked)
{
    enabled = checked;

    if (enabled == true) {
        // update to current color and mode
        updateValues();
        timeOfSubmit.restart();
        emit transmitColor(0, (uint8_t)red, (uint8_t)green, (uint8_t)blue, mode, (float)frequency);
    } else {
        // black is off
        timeOfSubmit.restart();
        emit transmitColor(0, (uint8_t)0, (uint8_t)0, (uint8_t)0, LED_CONTROL_MODE_CONSTANT, 0.0f);
    }
}

void LedControlWidget::colorButton0Clicked(bool checked)
{
    Q_UNUSED(checked);
    changeColor(buttonColors[0]);
}

void LedControlWidget::colorButton1Clicked(bool checked)
{
    Q_UNUSED(checked);
    changeColor(buttonColors[1]);
}

void LedControlWidget::colorButton2Clicked(bool checked)
{
    Q_UNUSED(checked);
    changeColor(buttonColors[2]);
}

void LedControlWidget::colorButton3Clicked(bool checked)
{
    Q_UNUSED(checked);
    changeColor(buttonColors[3]);
}
