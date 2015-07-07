#include "QGCTabbedInfoView.h"

QGCTabbedInfoView::QGCTabbedInfoView(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    messageView = new UASMessageViewWidget(this);
    //actionsWidget = new UASActionsWidget(this);
    quickView = new UASQuickView(this);
    //rawView = new UASRawStatusView(this);
    ui.tabWidget->addTab(quickView,"Quick");
    //ui.tabWidget->addTab(actionsWidget,"Actions");
    //ui.tabWidget->addTab(rawView,"Status");
    ui.tabWidget->addTab(messageView,"Messages");

#ifdef QGC_USE_SKYE_MESSAGES
    advancedControl = new UASSkyeControlAdvancedWidget(this);
    ledControl = new LedControlWidget(this);
    ui.tabWidget->addTab(advancedControl,"Advanced");
    ui.tabWidget->addTab(ledControl,"LED color");
    // set tooltips
    ui.tabWidget->setTabToolTip(ui.tabWidget->indexOf(advancedControl), "Set advanced settings");
    ui.tabWidget->setTabToolTip(ui.tabWidget->indexOf(ledControl), "Control LED color");
    // show default tab
    ui.tabWidget->setCurrentWidget(advancedControl);
#endif //QGC_USE_SKYE_MESSAGES
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
