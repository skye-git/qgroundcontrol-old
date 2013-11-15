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

    /** @brief Emit request to fly with new AU configuration */
    /** @param disabledAU: AU number to switch off (0 for all actions active) */
    void requestAUConfiguration(int);

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
    /** @brief Request to fly with all (4) AUs */
    void clickedAllAURadioButton();
    /** @brief Request to fly without AU 1 */
    void clickedWoAU1RadioButton();
    /** @brief Request to fly without AU 2 */
    void clickedWoAU2RadioButton();
    /** @brief Request to fly without AU 3 */
    void clickedWoAU3RadioButton();
    /** @brief Request to fly without AU 4 */
    void clickedWoAU4RadioButton();

};

#endif // UASSKYECONTROLADVANCEDWIDGET_H
