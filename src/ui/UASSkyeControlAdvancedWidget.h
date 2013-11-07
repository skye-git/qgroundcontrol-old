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
    void rollSliderValueChanged(double);
    void pitchSliderValueChanged(double);
    void yawSliderValueChanged(double);

public slots:
    void setSliderValues(double transValue, double rotValue, double liftValue);
    void emitSliderValues();

private:
    Ui::UASSkyeControlAdvancedWidget *ui;
    QString getStyleString(double value);

    bool addRollEnabled;
    bool addPitchEnabled;
    bool addYawEnabled;

private slots:
    void changeTransValue(double value);
    void changeRotValue(double value);
    void changeLiftValue(double value);
    void changeRollValue(double value);
    void changePitchValue(double value);
    void changeYawValue(double value);
    void clickedRollCheckBox(bool active);
    void clickedPitchCheckBox(bool active);
    void clickedYawCheckBox(bool active);
};

#endif // UASSKYECONTROLADVANCEDWIDGET_H
