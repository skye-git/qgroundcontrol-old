#ifndef UASCURRENTINFOWIDGET_H
#define UASCURRENTINFOWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include "UASInterface.h"
#include "UASManager.h"
#include "SkyeMAV.h"

#define N_CURR 3

namespace Ui {
class UASCurrentInfoWidget;
}

class UASCurrentInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit UASCurrentInfoWidget(QWidget *parent = 0);
    ~UASCurrentInfoWidget();
    
    Ui::UASCurrentInfoWidget *ui;
    int uasId;
    QHBoxLayout *boxLayout;
    QLabel labelCurrent[N_CURR];
    float current[N_CURR];

public slots:
    void setActiveUAS(UASInterface *uas);
    void changeCurrentInfo(mavlink_actuation_current_t *info);
};

#endif // UASCURRENTINFOWIDGET_H
