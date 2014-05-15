#include "SkyeAUStatusSettingsDialog.h"
#include "ui_SkyeAUStatusSettingsDialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <qmath.h>

SkyeAUStatusSettingsDialog::SkyeAUStatusSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkyeAUStatusSettingsDialog)
{
    ui->setupUi(this);

    // define table size. add 1 row per AU
    ui->tableWidget->setRowCount(SKYE_AU_COUNT_MAX);
    ui->tableWidget->setColumnCount(SKYE_AU_PARAM_MAX);

    // set header labels
    QStringList headerLabels;
    headerLabels << "q0" << "q1" << "q2" << "q3";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    headerLabels.clear();
    for (int i=1; i<SKYE_AU_COUNT_MAX+1; i++) {
        headerLabels << QString("AU %1").arg(i);
    }
    ui->tableWidget->setVerticalHeaderLabels(headerLabels);

//    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString("%1").arg(23.3)));
//    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("QStr"));
//    ui->tableWidget->setItem(2, 3, new QTableWidgetItem("hello"));

    connect(ui->toolButtonBrowseFile, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(ui->pushButtonLoadFile,   SIGNAL(clicked()), this, SLOT(readFromFile()));

    loadSettings();
}

SkyeAUStatusSettingsDialog::~SkyeAUStatusSettingsDialog()
{
    delete ui;
}

void SkyeAUStatusSettingsDialog::openFileDialog()
{
    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open File"), fileInfo.absolutePath());
    fileInfo.setFile(newFileName);
    storeSettings();

    /* update GUI */
    ui->lineEditFilePath->setText(fileInfo.absoluteFilePath());
}

void SkyeAUStatusSettingsDialog::readFromFile()
{
    readFromFile(fileInfo.absoluteFilePath());
}

void SkyeAUStatusSettingsDialog::readFromFile(QString filename)
{
    /* File must be tab seperated and using headers:
     *
     *       q0     q1     q2     q3
     * AU1   XX     XX     XX     XX
     * AU2   XX     XX     XX     XX
     * AU3   XX     XX     XX     XX
     * AU4   XX     XX     XX     XX
     *
     * where XX represents a floating point number
     */

    /* reset quaternion */
    memset(quaternions, 0.0, sizeof(quaternions));

    /* read from file */
    QFile textFile(filename);
    if (!textFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        qDebug() << "File" << filename << "does not exist";
        return;
    }

    qDebug() << "Reading from file:" << filename;

    int i = -1;
    while (!textFile.atEnd())
    {
        QString line;
        QStringList stringList;
        line = textFile.readLine();
        stringList << line.split("\t", QString::SkipEmptyParts);
        /* read header line and data */
        if (i<0)
        {
            // stringList contains now header. Might do something with it..
        } else {
            stringList.removeFirst();       // remove row header
            double q[4];
            if (!quaternionFromQStringList(q, stringList))
            {
                break;
            } else {
                for (int j=0; j<4; j++) {
                    quaternions[j][i] = q[j];
                }
            }
            qDebug() << "[readFromFile] quat" << i << "is" << quaternions[0][i] << quaternions[1][i] << quaternions[2][i] << quaternions[3][i];
        }

        i++;
    }

    textFile.close();

    /* Display values in table */
    updateTable();
}

void SkyeAUStatusSettingsDialog::readFromTable()
{
    /* update quaternion values given by GUI */
    double newQuaternions[SKYE_AU_PARAM_MAX][SKYE_AU_COUNT_MAX];
    bool ok;
    for (int row=0; row<SKYE_AU_COUNT_MAX; row++) {
        for (int col=0; col<SKYE_AU_PARAM_MAX; col++) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem = ui->tableWidget->item(row,col); // quaternions has dimension [4][N]. Table is transposed.
            newItem->text();
            bool ok;
            newQuaternions[col][row] = newItem->text().toDouble(&ok);
            if (ok == false) {
                ui->label->setText(QString("Invalid number in field [%1][%2].").arg(row, col));
                return;
            }
        }
    }

    memcpy(quaternions, newQuaternions, sizeof(quaternions));
    ui->label->setText("Press apply to transmit values.");
}


void SkyeAUStatusSettingsDialog::updateTable()
{
    /* update quaternion values on GUI */
    for (int row=0; row<SKYE_AU_COUNT_MAX; row++) {
        for (int col=0; col<SKYE_AU_PARAM_MAX; col++) {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(quaternions[row][col], 'f', 6));
            ui->tableWidget->setItem(row, col, newItem);
        }
    }
}

void SkyeAUStatusSettingsDialog::loadSettings()
{
    /* load from settigs or use default values */
    QSettings settings;
    settings.beginGroup("QGC_SKYE_AU_SETTINGS");
    fileInfo.setFile( settings.value( "FILE_NAME", "file.txt").toString() );
    settings.endGroup();

    /* update GUI */
    ui->lineEditFilePath->setText( fileInfo.absoluteFilePath() );
    if ( fileInfo.exists() )
    {
        // XXX file exists. we may load the data to the GUI
    }

}

void SkyeAUStatusSettingsDialog::storeSettings()
{
    QSettings settings;
    settings.beginGroup("QGC_SKYE_AU_SETTINGS");
    settings.setValue( "FILE_NAME", fileInfo.absoluteFilePath() );
}

bool SkyeAUStatusSettingsDialog::quaternionFromQStringList(double *quaternion, QStringList stringList)
{
    if (stringList.size() != 4) {
        return false;
    }

    double q[4];
    bool ok;

    /* extract 4 values from stringList */
    for (int i=0; i<4; i++)
    {
        q[i] = stringList.at(i).toDouble(&ok);
        if (!ok) return false;
    }

    /* copy quaternion */
    memcpy(quaternion, q, sizeof(q));
    return true;
}
