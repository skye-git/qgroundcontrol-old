#include "ElevationProfile.h"
#include "ui_ElevationProfile.h"

ElevationProfile::ElevationProfile(QWidget *parent, UASInterface* uas) :
    QWidget(parent),
    ui(new Ui::ElevationProfile),
    uas(uas)
{
    ui->setupUi(this);
}

ElevationProfile::~ElevationProfile()
{
    delete ui;
}
