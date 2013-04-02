#include "UASCurrentInfoWidget.h"
#include "ui_UASCurrentInfoWidget.h"

UASCurrentInfoWidget::UASCurrentInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UASCurrentInfoWidget)
{
    ui->setupUi(this);

    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));

    boxLayout = new QHBoxLayout;
    setLayout(boxLayout);

    for (int i=0; i<N_CURR; i++)
    {
        boxLayout->addWidget(&labelCurrent[i]);
        labelCurrent[i].setText("--A");
        labelCurrent[i].setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
}

UASCurrentInfoWidget::~UASCurrentInfoWidget()
{
    delete ui;
}

void UASCurrentInfoWidget::setActiveUAS(UASInterface *uas)
{
    // Disconnect old Skye UAS
    if (this->uasId != 0)
    {
        SkyeMAV* mav = dynamic_cast<SkyeMAV*>(UASManager::instance()->getUASForId(uasId));
        if (mav)
        {
            disconnect(mav, SIGNAL(currentInfoChanged(mavlink_actuation_current_t*)), this, SLOT(changeCurrentInfo(mavlink_actuation_current_t*)));
        }
    }

    // Connect Skye UAS
    SkyeMAV* mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        uasId = mav->getUASID();
        connect(mav, SIGNAL(currentInfoChanged(mavlink_actuation_current_t*)), this, SLOT(changeCurrentInfo(mavlink_actuation_current_t*)));
    }
}

void UASCurrentInfoWidget::changeCurrentInfo(mavlink_actuation_current_t *info)
{
    QString currentText;
    for (int i=0; i<N_CURR; i++)
    {
        switch (i)
        {
        case 0: current[i] = info->current_1 / 100.0f;
            break;
        case 1: current[i] = info->current_2 / 100.0f;
            break;
        case 2: current[i] = info->current_3 / 100.0f;
            break;
        case 3: current[i] = info->current_4 / 100.0f;
            break;
        }
        if (current[i] > 0.0f)
        {
            currentText.setNum(current[i], 'g', 3);
            currentText.append(" A");
            labelCurrent[i].setText(currentText);
        } else {
            labelCurrent[i].hide();
        }
    }
}
