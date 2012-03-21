#ifndef SKYECAMERARECONFIGURE_H
#define SKYECAMERARECONFIGURE_H

#include <QDialog>
#include <QMap>
#include <QLayout>
#include <QVBoxLayout>
#include "QGCMAVLink.h"

namespace Ui {
    class SkyeCameraReconfigure;
}

class SkyeCameraReconfigure : public QDialog
{
    Q_OBJECT
    Q_ENUMS(MAV_CAM_RECONFIG_PIXEL_CLOCK)
    Q_ENUMS(MAV_CAM_RECONFIG_COLOR_CODING)
    Q_ENUMS(MAV_CAM_RECONFIG_BAYER_METHOD)
    Q_ENUMS(MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED)
    Q_ENUMS(MAV_CAM_RECONFIG_HDR_MODE)
    Q_ENUMS(MAV_CAM_ID)

public:
    /* This is kind of a ugly hack to get the enums registered with Q_ENUMS for displaying their keys the QComboBox of SkyeCameraReconfigure Widget
     * The enums are hard copied from skye.h on 21.03.2012 */

    /** @brief Camera Reconfigure parameter "color_coding" */
    enum MAV_CAM_RECONFIG_PIXEL_CLOCK
    {
            MAV_CAM_RECONFIG_PIXEL_CLOCK_6M=6, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_8M=8, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_10M=10, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_13M5=13, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_20M=20, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_24M=24, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_27M6=27, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_32M=32, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_37M=37, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_40M=40, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_50M=50, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_57M6=57, /*  | */
            MAV_CAM_RECONFIG_PIXEL_CLOCK_ENUM_END=58, /*  | */
    };

    /** @brief Camera Reconfigure parameter "color_coding" */
    enum MAV_CAM_RECONFIG_COLOR_CODING
    {
            MAV_CAM_RECONFIG_COLOR_CODING_AUTO=0, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_MONO8=1, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_MONO16=2, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_RAW8=3, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_BGR8=4, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_BGRA8=5, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_BGR16=6, /*  | */
            MAV_CAM_RECONFIG_COLOR_CODING_ENUM_END=7, /*  | */
    };

    /** @brief Camera Reconfigure parameter "bayer_method" */
    enum MAV_CAM_RECONFIG_BAYER_METHOD
    {
            MAV_CAM_RECONFIG_BAYER_METHOD_IMAGE_PROC=0, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_DOWNSAMPLE=1, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_SIMPLE=2, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_BILINEAR=3, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_HQ=4, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_VNG=5, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_AHD=6, /*  | */
            MAV_CAM_RECONFIG_BAYER_METHOD_ENUM_END=7, /*  | */
    };

    /** @brief Camera Reconfigure parameter "auto_control_speed" */
    enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
    {
            MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ACS_MEDIUM=0, /* Medium | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ACS_SLOW=1, /* Slow | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ACS_FAST=2, /* Fast | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ENUM_END=3, /*  | */
    };

    /** @brief Camera Reconfigure parameter "hdr_mode" */
    enum MAV_CAM_RECONFIG_HDR_MODE
    {
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_OFF=0, /* Off | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED0=1, /* Fixed0 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED1=2, /* Fixed1 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED2=3, /* Fixed2 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED3=4, /* Fixed3 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED4=5, /* Fixed4 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED5=6, /* Fixed5 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED6=7, /* Fixed6 | */
            MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_USER=8, /* User | */
            MAV_CAM_RECONFIG_HDR_MODE_ENUM_END=9, /*  | */
    };

    /** @brief Camera ID */
    enum MAV_CAM_ID
    {
            MAV_CAM_ID_ALL=0, /* Off | */
            MAV_CAM_ID_PROSILICA=1, /* High resolution AVT prosilica camera | */
            MAV_CAM_ID_BLUEFOX_LEFT=2, /* Low resolution matrix-vision bluefox camera, position left | */
            MAV_CAM_ID_BLUEFOX_RIGHT=3, /* Low resolution matrix-vision bluefox camera, position right | */
            MAV_CAM_ID_ENUM_END=4, /*  | */
    };


    explicit SkyeCameraReconfigure(QWidget *parent = 0);
    ~SkyeCameraReconfigure();

private:
    Ui::SkyeCameraReconfigure *ui;
    MAV_CAM_ID activeCamId;             ///< Id of current chosen cam

private slots:
    void activeCameraChanged(QString camName);

protected:
    /** @brief Look for available cameras */
    void updateAvailableCameras();
    /** @brief Load widgets specific for message fields */
    void createWidgetsForMessage(uint8_t msgId);
    /** @brief Delete old widgets (Destructor) */
    void deleteOldWidgets();

    mavlink_message_info_t messageInfo[256];
    QMap<unsigned int, QWidget*> object;

};

#endif // SKYECAMERARECONFIGURE_H
