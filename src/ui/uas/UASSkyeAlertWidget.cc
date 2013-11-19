#include "UASSkyeAlertWidget.h"
#include "ui_UASSkyeAlertWidget.h"

UASSkyeAlertWidget::UASSkyeAlertWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASSkyeAlertWidget)
{
    ui->setupUi(this);

}

UASSkyeAlertWidget::~UASSkyeAlertWidget()
{
    delete ui;
}

void UASSkyeAlertWidget::batteryLow(double voltage, bool isLow, unsigned int ms)
{
    // set alert label visible
    if (isLow)
    {
        ui->labelAlert->setVisible(true);

        // Alternate colors to increase visibility
        if ((ms / 1000) % 2 == 0)
        {
            ui->labelAlert->setStyleSheet(QString("QLabel {color: #000; background-color: #FF0037; font-size: 15pt;}"));
        }
        else
        {
            ui->labelAlert->setStyleSheet(QString("QLabel {color: #FFF; background-color: #6B0017; font-size: 15pt;}"));
        }
        ui->labelAlert->setText(tr("BATTERY LOW: %1 V (%2 s)").arg(voltage, 2, 'f', 1, ' ').arg(ms / 1000.0f, 2, 'f', 1, ' '));
    }
    else
    {
        // hide label
        if (ui->labelAlert->isVisible())
        {
            ui->labelAlert->setVisible(false);
        }
    }

}
