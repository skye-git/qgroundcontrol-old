#ifndef UASSKYEALERTWIDGET_H
#define UASSKYEALERTWIDGET_H

#include <QWidget>

namespace Ui {
class UASSkyeAlertWidget;
}

class UASSkyeAlertWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeAlertWidget(QWidget *parent = 0);
    ~UASSkyeAlertWidget();

public slots:
    /** @brief Battery is low. Blink to alert user */
    void batteryLow(double voltage, bool isLow, unsigned int ms);

private:
    Ui::UASSkyeAlertWidget *ui;
};

#endif // UASSKYEALERTWIDGET_H
