#ifndef UASSKYECONTROLADVANCEDWIDGET_H
#define UASSKYECONTROLADVANCEDWIDGET_H

#define QGC_SKYE_DEFAULT_SENS_DIRECT_TRANS 0.5
#define QGC_SKYE_DEFAULT_SENS_DIRECT_ROT 0.5
#define QGC_SKYE_DEFAULT_SENS_ASSIST_TRANS 0.5
#define QGC_SKYE_DEFAULT_SENS_ASSIST_ROT 0.5
#define QGC_SKYE_MAX_SENS_DIRECT_TRANS 1.0
#define QGC_SKYE_MAX_SENS_DIRECT_ROT 1.0
#define QGC_SKYE_MAX_SENS_ASSIST_TRANS 1.0
#define QGC_SKYE_MAX_SENS_ASSIST_ROT 1.0

#include <QWidget>
#include <QString>
#include <QTime>
#include <UASInterface.h>

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
    void linearSliderValueChanged(double);
    void angularSliderValueChanged(double);
    void liftSliderValueChanged(double);
    void rollSliderValueChanged(double);
    void pitchSliderValueChanged(double);
    void yawSliderValueChanged(double);

    /** @brief Emit request to fly with new AU configuration */
    /** @param disabledAU: AU number to switch off (0 for all actions active) */
    void requestAUConfiguration(int);

public slots:
    /** @brief Set the system this widget controls */
    void setUAS(UASInterface* uas);

    void setSliderValues(double transValue, double rotValue, double liftValue);
    void emitSliderValues();
    /** @brief Update allocation case given by UAV */
    void updateAllocCase(int allocCase);


private:
    Ui::UASSkyeControlAdvancedWidget *ui;
    QString getStyleString(double value);

    UASInterface *uas;

    bool addRollEnabled;
    bool addPitchEnabled;
    bool addYawEnabled;

    double liftValue;
    double maxLinearInput;
    double maxAngularInput;

    QTime lastTimeMaxLinearInputChanged;
    QTime lastTimeMaxAngularInputChanged;
    QTime lastTimeLiftValueChanged;

private slots:
    void changeMaxLinearInput(double value);
    void changeMaxAngularInput(double value);
    void changeLiftValue(double value);
    void changeRollValue(double value);
    void changePitchValue(double value);
    void changeYawValue(double value);
    void updateMaxLinearInput(double value);
    void updateMaxAngularInput(double value);
    void updateLiftValue(double value);
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
