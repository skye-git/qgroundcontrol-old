#ifndef QGCTABBEDINFOVIEW_H
#define QGCTABBEDINFOVIEW_H

#include <QWidget>
#include "ui_QGCTabbedInfoView.h"
#include "MAVLinkDecoder.h"
#include "QGCMessageView.h"
#include "UASActionsWidget.h"
#include "UASQuickView.h"
#include "UASRawStatusView.h"
#include "UASSkyeControlAdvancedWidget.h"
#include "ledControl/LedControlWidget.h"

class QGCTabbedInfoView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QGCTabbedInfoView(QWidget *parent = 0);
    ~QGCTabbedInfoView();
    void addSource(MAVLinkDecoder *decoder);

    UASSkyeControlAdvancedWidget *advancedWidget;       ///< sub widget containing advanced settings
    LedControlWidget *ledWidget;                        ///< sub widget for led control

private:
    MAVLinkDecoder *m_decoder;
    Ui::QGCTabbedInfoView ui;
    QGCMessageView *messageView;
    UASActionsWidget *actionsWidget;
    UASQuickView *quickView;
    UASRawStatusView *rawView;

};

#endif // QGCTABBEDINFOVIEW_H
