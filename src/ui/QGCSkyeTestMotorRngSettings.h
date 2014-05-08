#ifndef QGCSKYETESTMOTORRNGSETTINGS_H
#define QGCSKYETESTMOTORRNGSETTINGS_H

#include <QWidget>

namespace Ui {
class QGCSkyeTestMotorRngSettings;
}

class QGCSkyeTestMotorRngSettings : public QWidget
{
	Q_OBJECT
	
public:
	explicit QGCSkyeTestMotorRngSettings(QWidget *parent = 0);
	~QGCSkyeTestMotorRngSettings();
	double getFMean() const;
	double getFStd() const;
	double getAFrom() const;
	double getATo() const;
private:
	Ui::QGCSkyeTestMotorRngSettings *ui;
};

#endif // QGCSKYETESTMOTORRNGSETTINGS_H
