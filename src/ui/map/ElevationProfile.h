#ifndef ELEVATIONPROFILE_H
#define ELEVATIONPROFILE_H

#include <QWidget>
#include "UASInterface.h"

namespace Ui {
class ElevationProfile;
}

class ElevationProfile : public QWidget
{
    Q_OBJECT
    
public:
    explicit ElevationProfile(QWidget *parent = NULL, UASInterface* uas=NULL);
    ~ElevationProfile();

    UASInterface*uas;

public slots:
    void updateStatusLabel(const QString &string);
    

private:
    Ui::ElevationProfile *ui;
};

#endif // ELEVATIONPROFILE_H
