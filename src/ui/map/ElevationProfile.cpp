#include "ElevationProfile.h"
#include "ui_ElevationProfile.h"

ElevationProfile::ElevationProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElevationProfile)
{
    ui->setupUi(this);
}

ElevationProfile::~ElevationProfile()
{
    delete ui;
}
