#include "QGCViewModeSelection.h"
#include "ui_QGCViewModeSelection.h"
#include "QGC.h"
#include "MainWindow.h"

QGCViewModeSelection::QGCViewModeSelection(QWidget *parent) :
    QWidget(parent),
    selected(false),
    ui(new Ui::QGCViewModeSelection)
{
    ui->setupUi(this);

    // Begin Code Skye
    connect(ui->viewModeSkye, SIGNAL(clicked()), this, SLOT(selectSkye()));
    connect(ui->viewModeSim, SIGNAL(clicked()), this, SLOT(selectSim()));
    // End Code Skye
    connect(ui->viewModeGeneric, SIGNAL(clicked()), this, SLOT(selectGeneric()));
    connect(ui->viewModeAR, SIGNAL(clicked()), this, SLOT(selectWifi()));
    connect(ui->viewModePX4, SIGNAL(clicked()), this, SLOT(selectPX4()));
    connect(ui->viewModeAPM, SIGNAL(clicked()), this, SLOT(selectAPM()));
    connect(ui->notAgainCheckBox, SIGNAL(clicked(bool)), this, SIGNAL(settingsStorageRequested(bool)));

    // Begin Code Skye
    ui->viewModeGeneric->hide();
    ui->viewModeAR->hide();
    ui->viewModePX4->hide();
    ui->viewModeAPM->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    // End Code Skye
}

QGCViewModeSelection::~QGCViewModeSelection()
{
    delete ui;
}

enum MainWindow::CUSTOM_MODE QGCViewModeSelection::waitForInput() {
    while (!selected)
        QGC::SLEEP::msleep(200);

    return mode;
}
// Begin Code Skye
void QGCViewModeSelection::selectSkye() {
    emit customViewModeSelected(MainWindow::CUSTOM_MODE_SKYE);
    mode = MainWindow::CUSTOM_MODE_NONE;
    selected = true;
}

void QGCViewModeSelection::selectSim() {
    emit customViewModeSelected(MainWindow::CUSTOM_MODE_SIM);
    mode = MainWindow::CUSTOM_MODE_SIM;
    selected = true;
}
// End Code Skye

void QGCViewModeSelection::selectGeneric() {
    emit customViewModeSelected(MainWindow::CUSTOM_MODE_NONE);
    mode = MainWindow::CUSTOM_MODE_NONE;
    selected = true;
}

void QGCViewModeSelection::selectWifi() {
    emit customViewModeSelected(MainWindow::CUSTOM_MODE_WIFI);
    mode = MainWindow::CUSTOM_MODE_WIFI;
    selected = true;
}

void QGCViewModeSelection::selectPX4() {
    emit customViewModeSelected(MainWindow::CUSTOM_MODE_PX4);
    mode = MainWindow::CUSTOM_MODE_PX4;
    selected = true;
}

void QGCViewModeSelection::selectAPM() {
    emit customViewModeSelected(MainWindow::CUSTOM_MODE_APM);
    mode = MainWindow::CUSTOM_MODE_APM;
    selected = true;
}
