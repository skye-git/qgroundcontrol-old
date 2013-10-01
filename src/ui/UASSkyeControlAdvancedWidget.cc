#include "UASSkyeControlAdvancedWidget.h"
#include "ui_UASSkyeControlAdvancedWidget.h"

UASSkyeControlAdvancedWidget::UASSkyeControlAdvancedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSkyeControlAdvancedWidget)
{
    ui->setupUi(this);

    connect(ui->doubleSpinBoxTranslation, SIGNAL(valueChanged(double)), this, SLOT(changeTransValue(double)));
    connect(ui->doubleSpinBoxRotation, SIGNAL(valueChanged(double)), this, SLOT(changeRotValue(double)));
    connect(ui->doubleSpinBoxLift, SIGNAL(valueChanged(double)), this, SLOT(changeLiftValue(double)));

}

UASSkyeControlAdvancedWidget::~UASSkyeControlAdvancedWidget()
{
    delete ui;
}

void UASSkyeControlAdvancedWidget::setSliderValues(double transValue, double rotValue, double liftValue)
{
    ui->doubleSpinBoxTranslation->setValue(transValue);
    ui->doubleSpinBoxRotation->setValue(rotValue);
    ui->doubleSpinBoxLift->setValue(liftValue);
}

void UASSkyeControlAdvancedWidget::changeTransValue(double value)
{
    ui->doubleSpinBoxTranslation->setStyleSheet(getStyleString(value));

    emit transSliderValueChanged(value);
}

void UASSkyeControlAdvancedWidget::changeRotValue(double value)
{
    ui->doubleSpinBoxRotation->setStyleSheet(getStyleString(value));

    emit rotSliderValueChanged(value);
}

void UASSkyeControlAdvancedWidget::changeLiftValue(double value)
{
    ui->doubleSpinBoxLift->setStyleSheet(getStyleString(value));

    emit liftSliderValueChanged(value);
}

QString UASSkyeControlAdvancedWidget::getStyleString(double val)
{
    int red = 16*16;
    int green = 16;
    int blue = 1;
    int colorStart = (int)(( 1+10*val ) * red + (  10*(1-val)) * green + 6 * blue);
    int colorEnd =   (int)(( 1+14*val ) * red + (  14*(1-val)) * green + 6 * blue);
    QString style = QString("QSlider::sub-page:horizontal {border: 1px solid #bbb; border-radius: 4px; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #%1, stop: 1 #%2); }").arg(colorStart, 1, 16).arg(colorEnd, 1, 16);

    return style;
}
