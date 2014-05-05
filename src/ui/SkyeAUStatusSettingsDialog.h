#ifndef SKYEAUSTATUSSETTINGSDIALOG_H
#define SKYEAUSTATUSSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SkyeAUStatusSettingsDialog;
}

class SkyeAUStatusSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkyeAUStatusSettingsDialog(QWidget *parent = 0);
    ~SkyeAUStatusSettingsDialog();

private:
    Ui::SkyeAUStatusSettingsDialog *ui;
};

#endif // SKYEAUSTATUSSETTINGSDIALOG_H
