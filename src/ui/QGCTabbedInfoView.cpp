#include "QGCTabbedInfoView.h"

QGCTabbedInfoView::QGCTabbedInfoView(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    messageView = new QGCMessageView(this);
    //actionsWidget = new UASActionsWidget(this);
    //quickView = new UASQuickView(this);
    //rawView = new UASRawStatusView(this);

    advancedWidget = new UASSkyeControlAdvancedWidget(this);
    ledWidget = new LedControlWidget(this);
    //ui.tabWidget->addTab(quickView,"Quick");
    //ui.tabWidget->addTab(actionsWidget,"Actions");
    //ui.tabWidget->addTab(rawView,"Status");
    ui.tabWidget->addTab(messageView,"Messages");
    ui.tabWidget->addTab(advancedWidget,"Settings");
    ui.tabWidget->addTab(ledWidget,"LED color");

    // set tooltips
    ui.tabWidget->setTabToolTip(ui.tabWidget->indexOf(messageView), "Messages from UAV");
    ui.tabWidget->setTabToolTip(ui.tabWidget->indexOf(advancedWidget), "Set advanced settings");
    ui.tabWidget->setTabToolTip(ui.tabWidget->indexOf(ledWidget), "Control LED color");

    // show default tab
    ui.tabWidget->setCurrentWidget(advancedWidget);
}
void QGCTabbedInfoView::addSource(MAVLinkDecoder *decoder)
{
    m_decoder = decoder;
    //rawView->addSource(decoder);
    quickView->addSource(decoder);
}

QGCTabbedInfoView::~QGCTabbedInfoView()
{
}
