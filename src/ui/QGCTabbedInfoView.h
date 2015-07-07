#ifndef QGCTABBEDINFOVIEW_H
#define QGCTABBEDINFOVIEW_H

#include <QWidget>
#include "ui_QGCTabbedInfoView.h"
#include "MAVLinkDecoder.h"
#include "UASMessageView.h"
#include "UASQuickView.h"
#include "UASRawStatusView.h"

#ifdef QGC_USE_SKYE_MESSAGES
#include "UASSkyeControlAdvancedWidget.h"
#include "ledControl/LedControlWidget.h"
#endif //QGC_USE_SKYE_MESSAGES

class QGCTabbedInfoView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QGCTabbedInfoView(QWidget *parent = 0);
    ~QGCTabbedInfoView();
    void addSource(MAVLinkDecoder *decoder);
private:
    MAVLinkDecoder *m_decoder;
    Ui::QGCTabbedInfoView ui;
    UASMessageViewWidget *messageView;
    UASQuickView *quickView;
    UASRawStatusView *rawView;

#ifdef QGC_USE_SKYE_MESSAGES
    UASSkyeControlAdvancedWidget *advancedControl;
    LedControlWidget *ledControl;
#endif
};

#endif // QGCTABBEDINFOVIEW_H
