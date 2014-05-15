#ifndef SKYEAUSTATUSSETTINGSDIALOG_H
#define SKYEAUSTATUSSETTINGSDIALOG_H

#include <QDialog>
#include <QList>
#include <QStringList>
#include <QFileInfo>

#define SKYE_AU_COUNT_MAX 6
#define SKYE_AU_PARAM_MAX 4

namespace Ui {
class SkyeAUStatusSettingsDialog;
}

class SkyeAUStatusSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkyeAUStatusSettingsDialog(QWidget *parent = 0);
    ~SkyeAUStatusSettingsDialog();

private slots:
    void openFileDialog();
    void readFromFile();
    void readFromFile(QString filename);
    void readFromTable();
    void updateTable();

private:
    Ui::SkyeAUStatusSettingsDialog *ui;

    void loadSettings();
    void storeSettings();
    bool quaternionFromQStringList(double *quaternion, QStringList stringList);
    double quaternions[SKYE_AU_PARAM_MAX][SKYE_AU_COUNT_MAX];
    QFileInfo fileInfo;
};

#endif // SKYEAUSTATUSSETTINGSDIALOG_H
