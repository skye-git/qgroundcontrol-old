#include "ElevationProfileMulti.h"
#include "ui_ElevationProfileMulti.h"
#include "UASManager.h"

ElevationProfileMulti::ElevationProfileMulti(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElevationProfileMulti),
    offline_uas_id(0)
{
    ui->setupUi(this);
    setMinimumSize(600, 80);
    connect(UASManager::instance(), SIGNAL(UASCreated(UASInterface*)), this, SLOT(systemCreated(UASInterface*)));
    connect(UASManager::instance(), SIGNAL(activeUASSet(int)), this, SLOT(systemSetActive(int)));

    ElevationProfile* list = new ElevationProfile(ui->stackedWidget, NULL);
    lists.insert(offline_uas_id, list);
    ui->stackedWidget->addWidget(list);
}

void ElevationProfileMulti::systemDeleted(QObject* uas)
{
    UASInterface* mav = dynamic_cast<UASInterface*>(uas);
    if (mav)
    {
        int id = mav->getUASID();
        ElevationProfile* list = lists.value(id, NULL);
        if (list)
        {
            delete list;
            lists.remove(id);
        }
    }
}

void ElevationProfileMulti::systemCreated(UASInterface* uas)
{
    ElevationProfile* list = new ElevationProfile(ui->stackedWidget, uas);
    lists.insert(uas->getUASID(), list);
    ui->stackedWidget->addWidget(list);
    // Ensure widget is deleted when system is deleted
    connect(uas, SIGNAL(destroyed(QObject*)), this, SLOT(systemDeleted(QObject*)));
}

void ElevationProfileMulti::systemSetActive(int uas)
{
    ElevationProfile* list = lists.value(uas, NULL);
    if (list) {
        ui->stackedWidget->setCurrentWidget(list);
    }
}

ElevationProfileMulti::~ElevationProfileMulti()
{
    delete ui;
}

void ElevationProfileMulti::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
