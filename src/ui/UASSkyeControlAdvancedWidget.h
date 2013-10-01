#ifndef UASSKYECONTROLADVANCEDWIDGET_H
#define UASSKYECONTROLADVANCEDWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class UASSkyeControlAdvancedWidget;
}

class UASSkyeControlAdvancedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UASSkyeControlAdvancedWidget(QWidget *parent = 0);
    ~UASSkyeControlAdvancedWidget();

signals:
    void transSliderValueChanged(double);
    void rotSliderValueChanged(double);
    void liftSliderValueChanged(double);

public slots:
    void setSliderValues(double transValue, double rotValue, double liftValue);

private:
    Ui::UASSkyeControlAdvancedWidget *ui;
    QString getStyleString(double value);

private slots:
    void changeTransValue(double value);
    void changeRotValue(double value);
    void changeLiftValue(double value);
};

#endif // UASSKYECONTROLADVANCEDWIDGET_H
