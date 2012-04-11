#ifndef SKYECAMERARECONFIGURE_H
#define SKYECAMERARECONFIGURE_H

#include <QDialog>
#include <QMap>
#include <QLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "QGCMAVLink.h"
#include "UASInterface.h"

namespace Ui {
    class SkyeCameraReconfigure;
}

class SkyeCameraReconfigure : public QDialog
{
    Q_OBJECT

public:
    explicit SkyeCameraReconfigure(QWidget *parent = 0);
    ~SkyeCameraReconfigure();

public slots:
    /** @brief Apply current widgets valus to camera */
    void accept();
    /** @brief Update widget values for bluefox */
    void updateBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t* bluefox);

private:
    Ui::SkyeCameraReconfigure *ui;
    MAV_CAM_ID activeCamId;             ///< Id of current chosen cam
    uint8_t msgId;                      ///< Id of msg suitable for active camera
    int uasId;                          ///< Id of active uas

private slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);
    /** @brief Readjust settings when new camera chosen */
    void activeCameraChanged(QString camName);

signals:
    /** @brief Send Bluefox Camera settings to active (skye) uas */
    void sendBluefoxSettings(mavlink_skye_cam_reconfigure_bluefox_settings_t *bluefox);

protected:
    /** @brief Look for available cameras */
    void updateAvailableCameras();
    /** @brief Load widgets specific for message fields */
    void createWidgetsForMessage(uint8_t msgId);
    /** @brief Delete old widgets (Destructor) */
    void deleteOldWidgets();

    mavlink_message_info_t messageInfo[256];
    QMap<unsigned int, QWidget*> valueMap;
    QMap<unsigned int, QLabel*> labelMap;


};

#endif // SKYECAMERARECONFIGURE_H
