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

public:
    explicit SkyeCameraReconfigure(QWidget *parent = 0);
    ~SkyeCameraReconfigure();

private:
    Ui::SkyeCameraReconfigure *ui;

protected:
    QVBoxLayout* mainVLayout;
    mavlink_message_info_t messageInfo[256];
    QMap<unsigned int, QLayout*> object;
};

#endif // SKYECAMERARECONFIGURE_H
