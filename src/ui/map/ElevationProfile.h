#ifndef ELEVATIONPROFILE_H
#define ELEVATIONPROFILE_H

#include <QWidget>

namespace Ui {
class ElevationProfile;
}

class ElevationProfile : public QWidget
{
    Q_OBJECT
    
public:
    explicit ElevationProfile(QWidget *parent = 0);
    ~ElevationProfile();
    
private:
    Ui::ElevationProfile *ui;
};

#endif // ELEVATIONPROFILE_H
