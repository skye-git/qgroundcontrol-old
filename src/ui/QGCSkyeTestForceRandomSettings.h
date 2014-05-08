#ifndef QGCSKYETESTFORCERANDOMSETTINGS_H
#define QGCSKYETESTFORCERANDOMSETTINGS_H

#include <QWidget>

namespace Ui {
class QGCSkyeTestForceRandomSettings;
}

class QGCSkyeTestForceRandomSettings : public QWidget
{
	Q_OBJECT
	
public:
	explicit QGCSkyeTestForceRandomSettings(QWidget *parent = 0);
	~QGCSkyeTestForceRandomSettings();
	
	double getMStd() const;
	double getFStd() const;
private:
	Ui::QGCSkyeTestForceRandomSettings *ui;
};

#endif // QGCSKYETESTFORCERANDOMSETTINGS_H
