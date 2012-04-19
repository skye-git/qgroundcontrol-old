#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QDebug>
#include <QMetaObject>
#include <QMetaEnum>
#include "SkyeCameraReconfigure.h"
#include "ui_SkyeCameraReconfigure.h"
#include "QGC.h"
#include "SkyeMAV.h"
#include "UASManager.h"
#include "BluefoxReconfigure.h"

SkyeCameraReconfigure::SkyeCameraReconfigure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkyeCameraReconfigure),
    activeCamId(MAV_CAM_ID_PROSILICA),
    msgId(MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_PROSILICA_SETTINGS),
    uasId(0)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(ui->groupBoxVerticalLayout);
    ui->scrollArea->setMinimumSize(300, 400);
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setUAS(UASInterface*)));
    setUAS(UASManager::instance()->getActiveUAS());
    connect(ui->cameraComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(activeCameraChanged(QString)));
    updateAvailableCameras();

    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

SkyeCameraReconfigure::~SkyeCameraReconfigure()
{
    delete ui;
}

void SkyeCameraReconfigure::setUAS(UASInterface* uas)
{
#ifdef MAVLINK_ENABLED_SKYE
    if (uasId!= 0)
    {
        UASInterface* oldUAS = UASManager::instance()->getUASForId(this->uasId);
        SkyeMAV *oldMAV = dynamic_cast<SkyeMAV*>(oldUAS);
        if (oldMAV)
        {
            disconnect(this, SIGNAL(sendBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t*)), oldMAV, SLOT(sendBluefoxReconfigureCommand(mavlink_skye_cam_reconfigure_bluefox_settings_t*)));
            disconnect(oldMAV, SIGNAL(bluefoxSettingsChanged(mavlink_skye_cam_reconfigure_bluefox_settings_t*)), this, SLOT(updateBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t*)));
            disconnect(oldMAV, SIGNAL(reportUDPLinkFailed(QString)), ui->lastActionLabel, SLOT(setText(QString)));
            uasId = 0;
        }
    }
    SkyeMAV *mav = dynamic_cast<SkyeMAV*>(uas);
    if (mav)
    {
        connect(this, SIGNAL(sendBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t*)), mav, SLOT(sendBluefoxReconfigureCommand(mavlink_skye_cam_reconfigure_bluefox_settings_t*)));
        connect(mav, SIGNAL(bluefoxSettingsChanged(mavlink_skye_cam_reconfigure_bluefox_settings_t*)), this, SLOT(updateBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t*)));
        connect(mav, SIGNAL(reportUDPLinkFailed(QString)), ui->lastActionLabel, SLOT(setText(QString)));
//        connect(ui->getButton, SIGNAL(clicked()), this, SLOT())
        ui->lastActionLabel->setText(tr("Connected to ") + uas->getUASName());
        uasId = uas->getUASID();
    }

#endif // MAVLINK_ENABLED_SKYE
}

void SkyeCameraReconfigure::updateAvailableCameras()
{
    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_ID") );

    for(int x=0;x<metaEnum.keyCount()-1;++x)
    {
        QString keyName = metaEnum.key(x);
//        qDebug() << keyName;
        if (keyName != "MAV_CAM_ID_ALL")
        {
            ui->cameraComboBox->insertItem(metaEnum.value(x), metaEnum.key(x));
        }
    }
}

void SkyeCameraReconfigure::activeCameraChanged(QString camName)
{
    // Check whether camera has changed
    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_ID") );
    if (metaEnum.key(activeCamId) != camName)
    {

        deleteOldWidgets();

        if (camName == "MAV_CAM_ID_PROSILICA")
        {
            activeCamId = MAV_CAM_ID_PROSILICA;
            msgId = MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_PROSILICA_SETTINGS;
            createWidgetsForMessage(msgId);
        }
        else if (camName == "MAV_CAM_ID_BLUEFOX_LEFT" )
        {
            activeCamId = MAV_CAM_ID_BLUEFOX_LEFT;
            msgId = MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS;
            createWidgetsForMessage(msgId);
        }
        else if (camName == "MAV_CAM_ID_BLUEFOX_RIGHT" )
        {
            activeCamId = MAV_CAM_ID_BLUEFOX_RIGHT;
            msgId = MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS;
            createWidgetsForMessage(msgId);
        }
    }
}

void SkyeCameraReconfigure::createWidgetsForMessage(uint8_t msgId)
{
    valueMap = QMap<unsigned int, QWidget*>();
    valueMap.clear();
    labelMap = QMap<unsigned int, QLabel*>();
    labelMap.clear();

    mavlink_message_info_t msg[256] = MAVLINK_MESSAGE_INFO;
    memcpy(messageInfo, msg, sizeof(mavlink_message_info_t)*256);
    for (unsigned int i = 0; i < messageInfo[msgId].num_fields; ++i)
    {
        QString name;
        name = messageInfo[msgId].fields[i].name;
        qDebug() << name << " is name of this field";
        QHBoxLayout* hBox = new QHBoxLayout();

        if ( name == "target_system" || name == "cam_id")
        {
            // Do nothing
            qDebug() << "but here we don't create any input widget..";
            QWidget* widget = new QWidget();
            valueMap.insert(i, widget);
        }
        else
        {
            QLabel* labelWidget = new QLabel(name);
            hBox->addWidget(labelWidget);
            labelMap.insert(i, labelWidget);

            switch (messageInfo[msgId].fields[i].type)
            {
            // Type of field is uint8
            case MAVLINK_TYPE_UINT8_T:
            {
                bool widgetAdded = false;
                if (!widgetAdded && name == "pixel_clock")
                {
                    widgetAdded = true;
                    QComboBox* valueWidget = new QComboBox();
                    valueMap.insert(i, valueWidget);
//                    QStringList ret;
                    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
                    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_RECONFIG_PIXEL_CLOCK") );

                    for(int x=0;x<metaEnum.keyCount()-1;++x)
                    {
//                        ret.append(metaEnum.key(x));
                        valueWidget->insertItem(metaEnum.value(x), metaEnum.key(x));
                    }
//                    qDebug() << ret;
                    hBox->addWidget(valueWidget);
                }
                //  COLOR_CODING
                if (!widgetAdded && name == "color_coding")
                {
                    widgetAdded = true;
                    QComboBox* valueWidget = new QComboBox();
                    valueMap.insert(i, valueWidget);

                    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
                    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_RECONFIG_COLOR_CODING") );

                    for(int x=0;x<metaEnum.keyCount()-1;++x)
                    {
                        valueWidget->insertItem(metaEnum.value(x), metaEnum.key(x));
                    }
                    hBox->addWidget(valueWidget);

                }
                //  BAYER_METHOD
                if (!widgetAdded && name == "bayer_method")
                {
                    widgetAdded = true;
                    QComboBox* valueWidget = new QComboBox();
                    valueMap.insert(i, valueWidget);

                    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
                    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_RECONFIG_BAYER_METHOD") );

                    for(int x=0;x<metaEnum.keyCount()-1;++x)
                    {
                        valueWidget->insertItem(metaEnum.value(x), metaEnum.key(x));
                    }
                    hBox->addWidget(valueWidget);
                }

                //  AUTO_CONTROL_SPEED
                if (!widgetAdded && name == "auto_control_speed")
                {
                    widgetAdded = true;
                    QComboBox* valueWidget = new QComboBox();
                    valueMap.insert(i, valueWidget);

                    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
                    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED") );

                    for(int x=0;x<metaEnum.keyCount()-1;++x)
                    {
                        valueWidget->insertItem(metaEnum.value(x), metaEnum.key(x));
                    }
                    hBox->addWidget(valueWidget);
                }

                //  HDR_MODE
                if (!widgetAdded && name == "hdr_mode")
                {
                    widgetAdded = true;
                    QComboBox* valueWidget = new QComboBox();
                    valueMap.insert(i, valueWidget);

                    QMetaObject metaObject = BluefoxReconfigure::staticMetaObject;
                    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("MAV_CAM_RECONFIG_HDR_MODE") );

                    for(int x=0;x<metaEnum.keyCount()-1;++x)
                    {
                        valueWidget->insertItem(metaEnum.value(x), metaEnum.key(x));
                    }
                    hBox->addWidget(valueWidget);
                }

                //  BOOLEAN
                QStringList booleanList;
                booleanList << "shutter_auto" << "gain_auto" << "auto_query_values" << "use_ros_time";
                if ( booleanList.contains(name) )
                {
                    widgetAdded = true;
                    QCheckBox* valueWidget = new QCheckBox();
                    valueMap.insert(i, valueWidget);
                    valueWidget->setText(name);
                    hBox->addWidget(valueWidget);
                }
                // Default uint8
                if (!widgetAdded)
                {
                    widgetAdded = true;
                    //qDebug() << "Type is UINT8_T";
                    QSpinBox* valueWidget = new QSpinBox();
                    valueMap.insert(i, valueWidget);
                    valueWidget->setRange(0,255);
                    hBox->addWidget(valueWidget);

                    if ( name == "binning_x" || name == "binning_y" )
                    {
                        valueWidget->setRange(0,4);
                    }
                    if ( name == "gain_auto_min" || name == "gain_auto_max" || name == "gain" )
                    {
                        valueWidget->setRange(0, 12);
                    }
                }
                break;
            }

            case MAVLINK_TYPE_UINT16_T:
            {
                QSpinBox* valueWidget = new QSpinBox();
                valueMap.insert(i, valueWidget);
                valueWidget->setRange(0,65535);
                hBox->addWidget(valueWidget);

                if ( name == "roi_width" || name == "roi_height" || name == "x_offset" || name == "y_offset" )
                {
                    valueWidget->setRange(0,5000);
                }
                break;
            }

            // Type of field is char
            case MAVLINK_TYPE_CHAR:
            {
                QLineEdit* valueWidget = new QLineEdit();
                valueMap.insert(i, valueWidget);
                hBox->addWidget(valueWidget);
                qDebug() << "THE NEW QLineEdit WAS NAMED: " << valueWidget->accessibleName();
                break;
            }

            // Type of field is float
            case MAVLINK_TYPE_FLOAT:
            {
                QDoubleSpinBox* valueWidget = new QDoubleSpinBox();
                valueMap.insert(i, valueWidget);
                hBox->addWidget(valueWidget);

                if ( name.contains("shutter"))
                {
                    valueWidget->setRange(0, 0.1);
                }
                break;
            }

            default:   // unknown type
            {
                QLabel* valueWidget = new QLabel("Unknown Type");
                valueMap.insert(i, valueWidget);
                hBox->addWidget(valueWidget);
                break;
            }
            }

            hBox->setMargin(0);
            ui->groupBoxVerticalLayout->addLayout(hBox);
        }

        // Last entry: Set now size for all widgets
        if (i == messageInfo[msgId].num_fields - 1)
        {
            qDebug() << "We created" << valueMap.count() << "entries..";
            foreach (QWidget* child, valueMap)
            {
                if (dynamic_cast<QLabel*>(child) == 0)
                {
                    child->setMaximumWidth(200);
                    hBox->setAlignment(child, Qt::AlignRight);
                }
            }
        }
    }
}

void SkyeCameraReconfigure::deleteOldWidgets()
{
    foreach(QWidget* w, valueMap)
    {
        delete w;
    }
    foreach(QLabel* l, labelMap)
    {
        delete l;
    }
    labelMap.clear();
}

void SkyeCameraReconfigure::accept()
{
    qDebug() << "Klicked accept button";
    if (uasId)
    {
        mavlink_message_info_t msg[256] = MAVLINK_MESSAGE_INFO;
        memcpy(messageInfo, msg, sizeof(mavlink_message_info_t)*256);

        switch (msgId)
        {
        case MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS:
        {
            mavlink_skye_cam_reconfigure_bluefox_settings_t bluefox;
            for (unsigned int i = 0; i < messageInfo[msgId].num_fields; ++i)
            {
                QWidget *valueWidget = valueMap.value(i);

                qDebug() << i << "............" << messageInfo[msgId].fields[i].type << messageInfo[msgId].fields[i].name;

                QString name;
                name = messageInfo[msgId].fields[i].name;

                if ( name == "target_system" )
                {
                    bluefox.target_system = (uint8_t)uasId;
                }
                if ( name == "cam_id" )
                {
                    bluefox.cam_id = activeCamId;
                }
                if ( name == "frame_id")
                {
                    QLineEdit* valWgt = dynamic_cast<QLineEdit*>(valueWidget);
                    QString str = valWgt->displayText();
                    QByteArray ba = str.toLocal8Bit();
                    strcpy(bluefox.frame_id, ba.data());
                }
                if ( name == "pixel_clock")
                {
                    QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
                    if (!valWgt) qDebug() << "Sorry, this is no QComboBox"; else
                    bluefox.pixel_clock = (uint8_t)valWgt->currentIndex();
                }
                if ( name == "frame_rate")
                {
                    QDoubleSpinBox* valWgt = dynamic_cast<QDoubleSpinBox*>(valueWidget);
                    if (!valWgt) qDebug() << "Sorry, this is no QDoubleSpinBox"; else
                    bluefox.frame_rate = (float)valWgt->value();
                }
                if ( name == "camera_info_url")
                {
                    QLineEdit* valWgt = dynamic_cast<QLineEdit*>(valueWidget);
                    QString str = valWgt->displayText();
                    QByteArray ba = str.toLocal8Bit();
                    strcpy(bluefox.camera_info_url, ba.data());
                }
                if ( name == "binning_x" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.binning_x = (uint8_t)valWgt->value();
                }
                if ( name == "binning_y" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.binning_y = (uint8_t)valWgt->value();
                }
                if ( name == "roi_width" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.roi_width = (uint16_t)valWgt->value();
                }
                if ( name == "roi_height" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.roi_height = (uint16_t)valWgt->value();
                }
                if ( name == "x_offset" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.x_offset = (uint16_t)valWgt->value();
                }
                if ( name == "y_offset" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.y_offset = (uint16_t)valWgt->value();
                }
                if ( name == "color_coding")
                {
                    QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
                    bluefox.color_coding = (uint8_t)valWgt->currentIndex();
                }
                if ( name == "bayer_method")
                {
                    QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
                    bluefox.bayer_method = (uint8_t)valWgt->currentIndex();
                }
                if ( name == "exposure" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.exposure = (uint8_t)valWgt->value();
                }
                if ( name == "shutter_auto" )
                {
                    QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
                    bluefox.shutter_auto = (uint8_t)valWgt->isChecked();
                }
                if ( name == "shutter_auto_max")
                {
                    QDoubleSpinBox* valWgt = dynamic_cast<QDoubleSpinBox*>(valueWidget);
                    bluefox.shutter_auto_max = (float)valWgt->value();
                }
                if ( name == "shutter")
                {
                    QDoubleSpinBox* valWgt = dynamic_cast<QDoubleSpinBox*>(valueWidget);
                    bluefox.shutter = (float)valWgt->value();
                }
                if ( name == "gain_auto" )
                {
                    QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
                    bluefox.gain_auto = (uint8_t)valWgt->isChecked();
                }
                if ( name == "gain_auto_min" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.gain_auto_min = (uint8_t)valWgt->value();
                }
                if ( name == "gain_auto_max" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.gain_auto_max = (uint8_t)valWgt->value();
                }
                if ( name == "gain" )
                {
                    QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
                    bluefox.gain = (uint8_t)valWgt->value();
                }
                if ( name == "auto_control_speed")
                {
                    QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
                    bluefox.auto_control_speed = (uint8_t)valWgt->currentIndex();
                }
                if ( name == "auto_query_values" )
                {
                    QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
                    bluefox.auto_query_values = (uint8_t)valWgt->isChecked();
                }
                if ( name == "hdr_mode")
                {
                    QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
                    bluefox.hdr_mode = (uint8_t)valWgt->currentIndex();
                }
                if ( name == "use_ros_time" )
                {
                    QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
                    bluefox.use_ros_time = (uint8_t)valWgt->isChecked();
                }

                if (i+1 == messageInfo[msgId].num_fields)
                {
                    ui->lastActionLabel->setText("Sent data to Bluefox");
                    emit sendBluefoxSettings(&bluefox);
                }

        }
        }break;

        case MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_PROSILICA_SETTINGS:
        {
            ui->lastActionLabel->setText("Code not ready for Prosilica yet");
        }break;
        default:
        break;
        }
    }
    else
    {
        ui->lastActionLabel->setText("No skye UAS connected");
    }
}

void SkyeCameraReconfigure::updateBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t* bluefox)
{
    // TODO: Check wheter uasId, cam_id is correct

    ui->lastActionLabel->setText("Received Bluefox settings");
    ui->cameraComboBox->setCurrentIndex(bluefox->cam_id);

    mavlink_message_info_t msg[256] = MAVLINK_MESSAGE_INFO;
    memcpy(messageInfo, msg, sizeof(mavlink_message_info_t)*256);
    for (unsigned int i = 0; i < messageInfo[MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS].num_fields; ++i)
    {
        QWidget *valueWidget = valueMap.value(i);

        qDebug() << i << "............" << messageInfo[msgId].fields[i].type << messageInfo[msgId].fields[i].name;

        QString name;
        name = messageInfo[msgId].fields[i].name;

        if ( name == "frame_id")
        {
            QLineEdit* valWgt = dynamic_cast<QLineEdit*>(valueWidget);
            valWgt->setText(bluefox->frame_id);
        }
        if ( name == "pixel_clock")
        {
            QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
            valWgt->setCurrentIndex((int)bluefox->pixel_clock);
        }
        if ( name == "frame_rate")
        {
            QDoubleSpinBox* valWgt = dynamic_cast<QDoubleSpinBox*>(valueWidget);
            valWgt->setValue((double)bluefox->frame_rate);
        }
        if ( name == "camera_info_url")
        {
            QLineEdit* valWgt = dynamic_cast<QLineEdit*>(valueWidget);
            valWgt->setText(bluefox->camera_info_url);
        }
        if ( name == "binning_x" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->binning_x);
        }
        if ( name == "binning_y" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->binning_y);
        }
        if ( name == "roi_width" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->roi_width);
        }
        if ( name == "roi_height" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->roi_height);
        }
        if ( name == "x_offset" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->x_offset);
        }
        if ( name == "y_offset" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->y_offset);
        }
        if ( name == "color_coding")
        {
            QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
            valWgt->setCurrentIndex((int)bluefox->color_coding);
        }
        if ( name == "bayer_method")
        {
            QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
            valWgt->setCurrentIndex((int)bluefox->bayer_method);
        }
        if ( name == "exposure" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->exposure);
        }
        if ( name == "shutter_auto" )
        {
            QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
            valWgt->setChecked((bool)bluefox->shutter_auto);
        }
        if ( name == "shutter_auto_max")
        {
            QDoubleSpinBox* valWgt = dynamic_cast<QDoubleSpinBox*>(valueWidget);
            valWgt->setValue((double)bluefox->shutter_auto_max);
        }
        if ( name == "shutter")
        {
            QDoubleSpinBox* valWgt = dynamic_cast<QDoubleSpinBox*>(valueWidget);
            valWgt->setValue((double)bluefox->shutter);
        }
        if ( name == "gain_auto" )
        {
            QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
            valWgt->setChecked((bool)bluefox->gain_auto);
        }
        if ( name == "gain_auto_min" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->gain_auto_min);
        }
        if ( name == "gain_auto_max" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->gain_auto_max);
        }
        if ( name == "gain" )
        {
            QSpinBox* valWgt = dynamic_cast<QSpinBox*>(valueWidget);
            valWgt->setValue((int)bluefox->gain);
        }
        if ( name == "auto_control_speed")
        {
            QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
            valWgt->setCurrentIndex((int)bluefox->auto_control_speed);
        }
        if ( name == "auto_query_values" )
        {
            QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
            valWgt->setChecked((bool)bluefox->auto_query_values);
        }
        if ( name == "hdr_mode")
        {
            QComboBox* valWgt = dynamic_cast<QComboBox*>(valueWidget);
            valWgt->setCurrentIndex((int)bluefox->hdr_mode);
        }
        if ( name == "use_ros_time" )
        {
            QCheckBox* valWgt = dynamic_cast<QCheckBox*>(valueWidget);
            valWgt->setChecked((bool)bluefox->use_ros_time);
        }
    }
    ui->lastActionLabel->setText("Got current settings from camera.");

}


