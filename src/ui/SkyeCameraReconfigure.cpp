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

SkyeCameraReconfigure::SkyeCameraReconfigure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkyeCameraReconfigure)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(ui->groupBoxVerticalLayout);
    updateAvailableCameras();
    createWidgetsForMessage(MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS);

}

SkyeCameraReconfigure::~SkyeCameraReconfigure()
{
    delete ui;
}

void SkyeCameraReconfigure::updateAvailableCameras()
{
    QMetaObject metaObject = SkyeCameraReconfigure::staticMetaObject;
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

void SkyeCameraReconfigure::createWidgetsForMessage(uint8_t msgId)
{
    object = QMap<unsigned int, QWidget*>();

    mavlink_message_info_t msg[256] = MAVLINK_MESSAGE_INFO;
    memcpy(messageInfo, msg, sizeof(mavlink_message_info_t)*256);
    for (unsigned int i = 0; i < messageInfo[msgId].num_fields; ++i)
    {
        if ( messageInfo[msgId].fields[i].name != "target_system" )
        {
            QString name;
            name = messageInfo[msgId].fields[i].name;
            QWidget* widget = new QWidget();
            QLabel* labelWidget = new QLabel(name, widget);
            QHBoxLayout* hBox = new QHBoxLayout(widget);
            hBox->addWidget(labelWidget);
            object.insert(i, widget);
            ui->groupBoxVerticalLayout->addWidget(object.value(i));

            qDebug() << "switch" << messageInfo[msgId].fields[i].type;

            switch (messageInfo[msgId].fields[i].type)
            {
            // Type of field is uint8
            case MAVLINK_TYPE_UINT8_T:
            {
                bool widgetAdded = false;

                qDebug() << name << " is name of this field";

                if (!widgetAdded && name == "pixel_clock")
                {
                    widgetAdded = true;
                    QComboBox* valueWidget = new QComboBox(widget);

//                    QStringList ret;
                    QMetaObject metaObject = SkyeCameraReconfigure::staticMetaObject;
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
                    QComboBox* valueWidget = new QComboBox(widget);

                    QMetaObject metaObject = SkyeCameraReconfigure::staticMetaObject;
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
                    QComboBox* valueWidget = new QComboBox(widget);

                    QMetaObject metaObject = SkyeCameraReconfigure::staticMetaObject;
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
                    QComboBox* valueWidget = new QComboBox(widget);

                    QMetaObject metaObject = SkyeCameraReconfigure::staticMetaObject;
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
                    QComboBox* valueWidget = new QComboBox(widget);

                    QMetaObject metaObject = SkyeCameraReconfigure::staticMetaObject;
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
                    QCheckBox* valueWidget = new QCheckBox(widget);
                    valueWidget->setText(name);
                    hBox->addWidget(valueWidget);
                }
                // Default uint8
                if (!widgetAdded)
                {
                    widgetAdded = true;
                    //qDebug() << "Type is UINT8_T";
                    QSpinBox* valueWidget = new QSpinBox(widget);
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
                QSpinBox* valueWidget = new QSpinBox(widget);
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
                QLineEdit* valueWidget = new QLineEdit(widget);
                hBox->addWidget(valueWidget);
                break;
            }

            // Type of field is float
            case MAVLINK_TYPE_FLOAT:
            {
                QDoubleSpinBox* valueWidget = new QDoubleSpinBox(widget);
                hBox->addWidget(valueWidget);

                if ( name.contains("shutter"))
                {
                    valueWidget->setRange(0, 0.1);
                }
                break;
            }


            default:   // unknown type
            {
                QLabel* valueWidget = new QLabel("Unknown Type", widget);
                hBox->addWidget(valueWidget);
                break;
            }
            }
            QList<QWidget *> childWidgets = widget->findChildren<QWidget *>();
            qDebug() << "We found " << childWidgets.count() << " children..";
            foreach (QWidget* child , childWidgets)
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
    foreach(QWidget* w, object)
    {
        delete w;
    }
    object.clear();
}
