#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDebug>
#include "SkyeCameraReconfigure.h"
#include "ui_SkyeCameraReconfigure.h"

SkyeCameraReconfigure::SkyeCameraReconfigure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkyeCameraReconfigure)
{
    ui->setupUi(this);

    mainVLayout = new QVBoxLayout;
    object = QMap<unsigned int, QLayout*>();
//    QPushButton* aButton = new QPushButton;
//    mainVLayout->addWidget(aButton);
//    setLayout(mainVLayout);

    mavlink_message_info_t msg[256] = MAVLINK_MESSAGE_INFO;
    memcpy(messageInfo, msg, sizeof(mavlink_message_info_t)*256);
    for (unsigned int i = 0; i < messageInfo[MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS].num_fields; ++i)
    {
        qDebug() << "KREBS KREBS KREBS switch" << messageInfo[MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS].fields[i].type;
        switch (messageInfo[MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS].fields[i].type)
        {
        case MAVLINK_TYPE_UINT8_T:
            {
                qDebug() << "Type is UINT8_T";
                QString name;
                name.append(messageInfo[MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS].fields[i].name);
                QLabel* label = new QLabel(name);
                QSpinBox* spin = new QSpinBox;
                QHBoxLayout* hBox = new QHBoxLayout;
                hBox->addWidget(label);
                hBox->addWidget(spin);
                object.insert(i, hBox);
                mainVLayout->addLayout(object.value(i));
            }

            break;
        }

    }
    setLayout(mainVLayout);
}

SkyeCameraReconfigure::~SkyeCameraReconfigure()
{
    delete ui;
}
