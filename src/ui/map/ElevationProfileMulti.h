#ifndef ELEVATIONPROFILEMULTI_H
#define ELEVATIONPROFILEMULTI_H

#include <QWidget>

#include "ElevationProfile.h"
#include "UASInterface.h"

namespace Ui
{
class ElevationProfileMulti;
}

class ElevationProfileMulti : public QWidget
{
    Q_OBJECT
    
public:
    explicit ElevationProfileMulti(QWidget *parent = 0);
    ~ElevationProfileMulti();

public slots:
    void systemDeleted(QObject* uas);
    void systemCreated(UASInterface* uas);
    void systemSetActive(int uas);

protected:
    quint16 offline_uas_id;
    void changeEvent(QEvent *e);
    QMap<int, ElevationProfile*> lists;

private:
    Ui::ElevationProfileMulti *ui;
};

#endif // ELEVATIONPROFILEMULTI_H
