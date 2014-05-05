#include "SkyeAUStatusSettingsDialog.h"
#include "ui_SkyeAUStatusSettingsDialog.h"

SkyeAUStatusSettingsDialog::SkyeAUStatusSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkyeAUStatusSettingsDialog)
{
    ui->setupUi(this);
}

SkyeAUStatusSettingsDialog::~SkyeAUStatusSettingsDialog()
{
    delete ui;
}
