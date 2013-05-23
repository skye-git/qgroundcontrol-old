#include "PrimaryFlightDisplay.h"
#include "UASManager.h"

//#include "ui_primaryflightdisplay.h"
#include <QDebug>
#include <QRectF>
#include <cmath>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
//#include <math.h>
#include <cmath>

/*
 *@TODO:
 * global fixed pens (and painters too?)
 * repaint on demand multiple canvases
 * multi implementation with shared model class
 */
double PrimaryFlightDisplay_round(double value, int digits=0)
{
  return floor(value * pow(10, digits) + 0.5) / pow(10, digits);
}

const int PrimaryFlightDisplay::tickValues[] = {10, 20, 30, 45, 60};
const QString PrimaryFlightDisplay::compassWindNames[] = {
    QString("N"),
    QString("NE"),
    QString("E"),
    QString("SE"),
    QString("S"),
    QString("SW"),
    QString("W"),
    QString("NW")
};

PrimaryFlightDisplay::PrimaryFlightDisplay(int width, int height, QWidget *parent) :
    QWidget(parent),

    roll(0),
    pitch(0),
    //    heading(NAN),
    heading(0),
    aboveASLAltitude(0),
    GPSAltitude(0),
    aboveHomeAltitude(0),
    groundSpeed(0),
    airSpeed(0),

    mode(""),
    state(""),

    load(0),

    font("Bitstream Vera Sans"),
    refreshTimer(new QTimer(this)),
    uas(NULL),
//    energyStatus(tr("??.?V (??m:??s)"))
    batteryVoltage(UNKNOWN_BATTERY),
    batteryCharge(UNKNOWN_BATTERY),

    layout(FEATUREPANELS_IN_CORNERS),
    style(OPAGUE_TAPES),

    whitePen(Qt::white),
    redPen(QColor::fromHsvF(0, 0.6, 0.8)),
    amberPen(QColor::fromHsvF(0.12, 0.6, 1.0)),
    greenPen(QColor::fromHsvF(0.25, 0.8, 0.8)),
    blackPen(QColor::fromHsvF(0, 0, 0.2)),

    instrumentEdgePen(QColor::fromHsvF(0, 0, 0.65, 1.0)),
    instrumentBackground(QColor::fromHsvF(0, 0, 0.3, 0.3)),
    instrumentOpagueBackground(QColor::fromHsvF(0, 0, 0.3, 1.0))
{
    setMinimumSize(120, 80);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Connect with UAS
    connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));
    if (UASManager::instance()->getActiveUAS() != NULL) setActiveUAS(UASManager::instance()->getActiveUAS());

    // Refresh timer
    refreshTimer->setInterval(updateInterval);
    //    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(paintHUD()));
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(update()));
}

PrimaryFlightDisplay::~PrimaryFlightDisplay()
{
    refreshTimer->stop();
}


QSize PrimaryFlightDisplay::sizeHint() const
{
    return QSize(width(), (width()*3.0f)/4);
}

void PrimaryFlightDisplay::showEvent(QShowEvent* event)
{
    // React only to internal (pre-display)
    // events
    QWidget::showEvent(event);
    refreshTimer->start(updateInterval);
    emit visibilityChanged(true);
}

void PrimaryFlightDisplay::hideEvent(QHideEvent* event)
{
    // React only to internal (pre-display)
    // events
    refreshTimer->stop();
    QWidget::hideEvent(event);
    emit visibilityChanged(false);
}

/*
 * Interface against qgroundcontrol
 */


/**
 *
 * @param uas the UAS/MAV to monitor/display with the HUD
 */
void PrimaryFlightDisplay::setActiveUAS(UASInterface* uas)
{
    if (this->uas != NULL) {
        // Disconnect any previously connected active MAV
        disconnect(this->uas, SIGNAL(attitudeChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateAttitude(UASInterface*, double, double, double, quint64)));
        disconnect(this->uas, SIGNAL(attitudeChanged(UASInterface*,int,double,double,double,quint64)), this, SLOT(updateAttitude(UASInterface*,int,double, double, double, quint64)));
        disconnect(this->uas, SIGNAL(batteryChanged(UASInterface*, double, double, double, int)), this, SLOT(updateBattery(UASInterface*, double, double, double, int)));
        disconnect(this->uas, SIGNAL(statusChanged(UASInterface*,QString,QString)), this, SLOT(updateState(UASInterface*,QString)));
        disconnect(this->uas, SIGNAL(modeChanged(int,QString,QString)), this, SLOT(updateMode(int,QString,QString)));
        disconnect(this->uas, SIGNAL(heartbeat(UASInterface*)), this, SLOT(receiveHeartbeat(UASInterface*)));

        //disconnect(this->uas, SIGNAL(localPositionChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateLocalPosition(UASInterface*,double,double,double,quint64)));
        disconnect(this->uas, SIGNAL(globalPositionChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateGlobalPosition(UASInterface*,double,double,double,quint64)));
        disconnect(this->uas, SIGNAL(speedChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateSpeed(UASInterface*,double,double,double,quint64)));
        disconnect(this->uas, SIGNAL(waypointSelected(int,int)), this, SLOT(selectWaypoint(int, int)));
    }

    if (uas) {
        // Now connect the new UAS
        // Setup communication
        connect(uas, SIGNAL(attitudeChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateAttitude(UASInterface*, double, double, double, quint64)));
        connect(uas, SIGNAL(attitudeChanged(UASInterface*,int,double,double,double,quint64)), this, SLOT(updateAttitude(UASInterface*,int,double, double, double, quint64)));
        connect(uas, SIGNAL(batteryChanged(UASInterface*, double, double, double, int)), this, SLOT(updateBattery(UASInterface*, double, double, double, int)));
        connect(uas, SIGNAL(statusChanged(UASInterface*,QString,QString)), this, SLOT(updateState(UASInterface*,QString)));
        connect(uas, SIGNAL(modeChanged(int,QString,QString)), this, SLOT(updateMode(int,QString,QString)));
        connect(uas, SIGNAL(heartbeat(UASInterface*)), this, SLOT(receiveHeartbeat(UASInterface*)));

        //connect(uas, SIGNAL(localPositionChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateLocalPosition(UASInterface*,double,double,double,quint64)));
        connect(uas, SIGNAL(globalPositionChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateGlobalPosition(UASInterface*,double,double,double,quint64)));
        connect(uas, SIGNAL(speedChanged(UASInterface*,double,double,double,quint64)), this, SLOT(updateSpeed(UASInterface*,double,double,double,quint64)));
        connect(uas, SIGNAL(waypointSelected(int,int)), this, SLOT(selectWaypoint(int, int)));

        // Set new UAS
        this->uas = uas;
    }
}

void PrimaryFlightDisplay::updateAttitude(UASInterface* uas, double roll, double pitch, double yaw, quint64 timestamp)
{
    Q_UNUSED(uas);
    Q_UNUSED(timestamp);
    if (!isnan(roll) && !isinf(roll) && !isnan(pitch) && !isinf(pitch) && !isnan(yaw) && !isinf(yaw))
    {
        // TODO: Units conversion? // Called from UAS.cc l. 646
        this->roll = roll * (180.0 / M_PI);
        this->pitch = pitch * (180.0 / M_PI);
        this->heading = yaw * (180.0 / M_PI);
    }
    // TODO: Else-part. We really should have an "attitude bad or unknown" indication instead of just freezing.

    qDebug("r,p,y: %f,%f,%f", roll, pitch, yaw);
}

/*
 * TODO! Implementation or removal of this.
 * Currently a dummy.
 */
void PrimaryFlightDisplay::updateAttitude(UASInterface* uas, int component, double roll, double pitch, double yaw, quint64 timestamp)
{
    Q_UNUSED(uas);
    Q_UNUSED(component);
    Q_UNUSED(roll);
    Q_UNUSED(pitch);
    Q_UNUSED(yaw);
    Q_UNUSED(timestamp);
// Called from UAS.cc l. 616
    if (!isnan(roll) && !isinf(roll) && !isnan(pitch) && !isinf(pitch) && !isnan(yaw) && !isinf(yaw)) {
    this->roll = roll * (180.0 / M_PI);
    this->pitch = pitch * (180.0 / M_PI);
    this->heading = yaw * (180.0 / M_PI);
}
qDebug("(2) r,p,y: %f,%f,%f", roll, pitch, yaw);

}

void PrimaryFlightDisplay::updateBattery(UASInterface* uas, double voltage, double current, double percent, int seconds)
{
    Q_UNUSED(uas);
    Q_UNUSED(seconds);
    /*
    energyStatus = tr("BAT [%1V | %2V%]").arg(voltage, 4, 'f', 1, QChar('0')).arg(percent, 2, 'f', 0, QChar('0'));
    if (percent < 20.0f) {
        fuelColor = warningColor;
    } else if (percent < 10.0f) {
        fuelColor = criticalColor;
    } else {
        fuelColor = infoColor;
    }
    */
    batteryVoltage = voltage;
    batteryCurrent = current;
    batteryCharge = percent;
}

void PrimaryFlightDisplay::receiveHeartbeat(UASInterface*)
{
}

void PrimaryFlightDisplay::updateThrust(UASInterface* uas, double thrust)
{
    Q_UNUSED(uas);
    Q_UNUSED(thrust);
}

/*
 * TODO! Implementation or removal of this.
 * Currently a dummy.
 */
void PrimaryFlightDisplay::updateLocalPosition(UASInterface* uas,double x,double y,double z,quint64 timestamp)
{
    Q_UNUSED(uas);
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);
    Q_UNUSED(timestamp);
}

void PrimaryFlightDisplay::updateGlobalPosition(UASInterface* uas,double lat, double lon, double altitude, quint64 timestamp)
{
    Q_UNUSED(uas);
    Q_UNUSED(lat);
    Q_UNUSED(lon);
    Q_UNUSED(timestamp);

    // TODO: Examine whether this is really the GPS alt or the mix-alt coming in.
    GPSAltitude = altitude;
}

/*
 * TODO! Examine what data comes with this call, should we consider it airspeed, ground speed or
 * should we not consider it at all?
 */
void PrimaryFlightDisplay::updateSpeed(UASInterface* uas,double x,double y,double z,quint64 timestamp)
{
    Q_UNUSED(uas);
    Q_UNUSED(timestamp);
    Q_UNUSED(z);
    /*
    this->xSpeed = x;
    this->ySpeed = y;
    this->zSpeed = z;
    */

    double newTotalSpeed = sqrt(x*x + y*y/*+ zSpeed*zSpeed */);
    // totalAcc = (newTotalSpeed - totalSpeed) / ((double)(lastSpeedUpdate - timestamp)/1000.0);

    // TODO: Change to real data.
    groundSpeed = newTotalSpeed;
    airSpeed = x;
    verticalVelocity = z;
}

void PrimaryFlightDisplay::updateState(UASInterface* uas,QString state)
{
    // Only one UAS is connected at a time
    Q_UNUSED(uas);
    this->state = state;
}

void PrimaryFlightDisplay::updateMode(int id, QString mode, QString description)
{
    // Only one UAS is connected at a time
    Q_UNUSED(id);
    Q_UNUSED(description);
    this->mode = mode;
}

void PrimaryFlightDisplay::updateLoad(UASInterface* uas, double load)
{
    Q_UNUSED(uas);
    this->load = load;
    //updateValue(uas, "load", load, MG::TIME::getGroundTimeNow());
}

void PrimaryFlightDisplay::selectWaypoint(int uasId, int id) {
}

/*
 * Private and such
 */
void PrimaryFlightDisplay::resizeEvent(QResizeEvent *e) {
    QWidget::resizeEvent(e);
    whitePen.setWidthF(LINEWIDTH * e->size().height());
    redPen.setWidthF(LINEWIDTH * e->size().height());
    greenPen.setWidthF(LINEWIDTH * e->size().height());
    instrumentEdgePen.setWidthF(LINEWIDTH * e->size().height());

    if (e->size().height() > e->size().width())
        layout = COMPASS_SEPARATED;
    else if (e->size().height()*4 > e->size().width()*3)
        layout = FEATUREPANELS_AT_BOTTOM;
    else
        layout = FEATUREPANELS_IN_CORNERS;
    qDebug("Width %d height %d decision %d", e->size().width(), e->size().height(), layout);
}

void PrimaryFlightDisplay::paintEvent(QPaintEvent *event)
{
    // Event is not needed
    // the event is ignored as this widget
    // is refreshed automatically
    Q_UNUSED(event);
    //makeDummyData();
    doPaint();
}

void PrimaryFlightDisplay::drawTextCenter (
        QPainter& painter,
        QString text,
        float pixelSize,
        float x,
        float y)
{
    font.setPixelSize(pixelSize);
    painter.setFont(font);

    QFontMetrics metrics = QFontMetrics(font);
    QRect bounds = metrics.boundingRect(text);
    int flags = Qt::AlignCenter |  Qt::TextDontClip; // For some reason the bounds rect is too small!
    painter.drawText(x /*+bounds.x()*/ -bounds.width()/2, y /*+bounds.y()*/ -bounds.height()/2, bounds.width(), bounds.height(), flags, text);
}

void PrimaryFlightDisplay::drawTextLeftCenter (
        QPainter& painter,
        QString text,
        float pixelSize,
        float x,
        float y)
{
    font.setPixelSize(pixelSize);
    painter.setFont(font);

    QFontMetrics metrics = QFontMetrics(font);
    QRect bounds = metrics.boundingRect(text);
    int flags = Qt::AlignLeft | Qt::TextDontClip; // For some reason the bounds rect is too small!
    painter.drawText(x /*+bounds.x()*/, y /*+bounds.y()*/ -bounds.height()/2, bounds.width(), bounds.height(), flags, text);
}

void PrimaryFlightDisplay::drawTextRightCenter (
        QPainter& painter,
        QString text,
        float pixelSize,
        float x,
        float y)
{
    font.setPixelSize(pixelSize);
    painter.setFont(font);

    QFontMetrics metrics = QFontMetrics(font);
    QRect bounds = metrics.boundingRect(text);
    int flags = Qt::AlignRight | Qt::TextDontClip; // For some reason the bounds rect is too small!
    painter.drawText(x /*+bounds.x()*/ -bounds.width(), y /*+bounds.y()*/ -bounds.height()/2, bounds.width(), bounds.height(), flags, text);
}

void PrimaryFlightDisplay::drawTextCenterTop (
        QPainter& painter,
        QString text,
        float pixelSize,
        float x,
        float y)
{
    font.setPixelSize(pixelSize);
    painter.setFont(font);

    QFontMetrics metrics = QFontMetrics(font);
    QRect bounds = metrics.boundingRect(text);
    int flags = Qt::AlignCenter | Qt::TextDontClip; // For some reason the bounds rect is too small!
    painter.drawText(x /*+bounds.x()*/ -bounds.width()/2, y+bounds.height() /*+bounds.y()*/, bounds.width(), bounds.height(), flags, text);
}

void PrimaryFlightDisplay::drawTextCenterBottom (
        QPainter& painter,
        QString text,
        float pixelSize,
        float x,
        float y)
{
    font.setPixelSize(pixelSize);
    painter.setFont(font);

    QFontMetrics metrics = QFontMetrics(font);
    QRect bounds = metrics.boundingRect(text);
    int flags = Qt::AlignCenter;
    painter.drawText(x /*+bounds.x()*/ -bounds.width()/2, y /*+bounds.y()*/, bounds.width(), bounds.height(), flags, text);
}

void PrimaryFlightDisplay::drawInstrumentBackground(QPainter& painter, QRectF edge) {
    painter.setPen(instrumentEdgePen);
    painter.drawRect(edge);
}

void PrimaryFlightDisplay::fillInstrumentBackground(QPainter& painter, QRectF edge) {
    painter.setPen(instrumentEdgePen);
    painter.setBrush(instrumentBackground);
    painter.drawRect(edge);
    painter.setBrush(Qt::NoBrush);
}

void PrimaryFlightDisplay::fillInstrumentOpagueBackground(QPainter& painter, QRectF edge) {
    painter.setPen(instrumentEdgePen);
    painter.setBrush(instrumentOpagueBackground);
    painter.drawRect(edge);
    painter.setBrush(Qt::NoBrush);
}

/*
void PrimaryFlightDisplay::prepareTransform(QPainter& painter, qreal width, qreal height) {
    painter.resetTransform();
    painter.translate(width/2, height/2);
}

void PrimaryFlightDisplay::transformToGlobalSystem(QPainter& painter, qreal width, qreal height, float roll, float pitch) {
    prepareTransform(painter, width, height);
    painter.rotate(roll);
    painter.translate(0, pitch*height/PITCHTRANSLATION);
}
*/

qreal pitchAngleToTranslation(qreal viewHeight, float pitch) {
    return pitch*viewHeight/PITCHTRANSLATION;
}

void PrimaryFlightDisplay::drawAIAirframeFixedFeatures(QPainter& painter, QRectF area) {
    // red line from -7/10 to -5/10 half-width
    // red line from 7/10 to 5/10 half-width
    // red slanted line from -2/10 half-width to 0
    // red slanted line from 2/10 half-width to 0
    // red arrow thing under roll scale
    // prepareTransform(painter, width, height);
    painter.resetTransform();
    painter.translate(area.center());

    qreal w = area.width();
    qreal h = area.height();

    painter.setPen(redPen);
    QPointF start(-0.35*w, 0);
    QPointF end(-0.25*w, 0);
    painter.drawLine(start, end);

    start = QPointF(0.35*w, 0);
    end = QPointF(0.25*w, 0);
    painter.drawLine(start, end);

    start = QPointF(0.0894*w, 0.894*0.05*w);
    end = QPoint(0, 0);
//    end = QPointF(-0.0894*width, -0.894*0.05*width);
    painter.drawLine(start, end);

    start = QPointF(-0.0894*w, 0.894*0.05*w);
    end = QPoint(0, 0);
    // end = QPointF(0.0894*width, -0.894*0.05*width);
    painter.drawLine(start, end);

    painter.setPen(redPen);
//    painter.setBrush(Qt::SolidPattern);

    QPainterPath markerPath(QPointF(0, -h*ROLL_SCALE_RADIUS+1));
    markerPath.lineTo(-h*ROLL_SCALE_MARKERWIDTH/2, -h*(ROLL_SCALE_RADIUS-ROLL_SCALE_MARKERHEIGHT)+1);
    markerPath.lineTo(h*ROLL_SCALE_MARKERWIDTH/2, -h*(ROLL_SCALE_RADIUS-ROLL_SCALE_MARKERHEIGHT)+1);
    markerPath.closeSubpath();
    painter.drawPath(markerPath);
}

void PrimaryFlightDisplay::drawAIGlobalFeatures(
        QPainter& painter,
        QRectF area) {

    painter.resetTransform();
    painter.translate(area.center());

    painter.rotate(roll);
    painter.translate(0, pitchAngleToTranslation(area.height(), pitch));

    qreal w = area.width();
    qreal h = area.height();

    qreal halfsize= 90/PITCHTRANSLATION*h + w*sqrt(2)/2;

    QPainterPath skyPath(QPointF(-w, 0));
    skyPath.lineTo(-halfsize, -halfsize);
    skyPath.lineTo(halfsize, -halfsize);
    skyPath.lineTo(halfsize, 0);
    skyPath.closeSubpath();

    QLinearGradient skyGradient(0, -halfsize, 0, 0);
    skyGradient.setColorAt(0, QColor::fromHsvF(0.6, 1.0, 0.7));
    skyGradient.setColorAt(1, QColor::fromHsvF(0.6, 0.25, 0.9));
    QBrush skyBrush(skyGradient);
    painter.fillPath(skyPath, skyBrush);

    QPainterPath groundPath(QPointF(-halfsize, 0));
    groundPath.lineTo(-halfsize, halfsize);
    groundPath.lineTo(halfsize, halfsize);
    groundPath.lineTo(halfsize, 0);
    groundPath.closeSubpath();

    QLinearGradient groundGradient(0, h, 0, 0);
    groundGradient.setColorAt(0, QColor::fromHsvF(0.25, 1, 0.5));
    groundGradient.setColorAt(1, QColor::fromHsvF(0.25, 0.25, 0.5));
    QBrush groundBrush(groundGradient);
    painter.fillPath(groundPath, groundBrush);

    painter.setPen(greenPen);
    QPointF start(-w, 0);
    QPoint end(w, 0);
    painter.drawLine(start, end);


    if (style == OPAGUE_TAPES) {
        painter.resetTransform();
        drawInstrumentBackground(painter, area);
    }
}

void PrimaryFlightDisplay::drawPitchScale(
        QPainter& painter,
        QRectF area,
        bool drawNumbersLeft,
        bool drawNumbersRight
        ) {

    // We should really do these transforms but they are assumed done by caller.
    // painter.resetTransform();
    // painter.translate(area.center());
    // painter.rotate(roll);

    painter.setPen(whitePen);

    QTransform savedTransform = painter.transform();

    qreal h = area.height();

    // find the mark nearest center
    int snap = round(pitch/PITCH_SCALE_RESOLUTION)*PITCH_SCALE_RESOLUTION;
    int _min = snap-PITCH_SCALE_HALFRANGE;
    int _max = snap+PITCH_SCALE_HALFRANGE;
    for (int degrees=_min; degrees<=_max; degrees+=PITCH_SCALE_RESOLUTION) {
        bool isMajor = degrees % (PITCH_SCALE_RESOLUTION*2) == 0;
        float linewidth =  isMajor ? PITCH_SCALE_MAJORLENGTH : PITCH_SCALE_MINORLENGTH;
        float shift = pitchAngleToTranslation(h, pitch-degrees);
        painter.translate(0, shift);
        QPointF start(-linewidth*h, 0);
        QPointF end(linewidth*h, 0);
        painter.drawLine(start, end);

        if (isMajor && (drawNumbersLeft||drawNumbersRight)) {
            int displayDegrees = degrees;
            if(displayDegrees>90) displayDegrees = 180-displayDegrees;
            else if (displayDegrees<-90) displayDegrees = -180 - displayDegrees;
            if (SHOW_ZERO_ON_SCALES || degrees) {
                QString s_number; //= QString("%d").arg(degrees);
                s_number.sprintf("%d", displayDegrees);
                if (drawNumbersLeft)  drawTextRightCenter(painter, s_number, SCALE_TEXT_SIZE*h, -PITCH_SCALE_MAJORLENGTH * h-10, 0);
                if (drawNumbersRight) drawTextLeftCenter(painter, s_number, SCALE_TEXT_SIZE*h, PITCH_SCALE_MAJORLENGTH * h+10, 0);
            }
        }

        painter.setTransform(savedTransform);
    }
}

void PrimaryFlightDisplay::drawRollScale(
        QPainter& painter,
        QRectF area,
        bool drawTicks,
        bool drawNumbers) {

    qreal h = area.height();

    painter.setPen(whitePen);

    // We should really do these transforms but they are assumed done by caller.
    // painter.resetTransform();
    // painter.translate(area.center());
    // painter.rotate(roll);

    qreal _size = h * ROLL_SCALE_RADIUS*2;

    QRectF arcArea(-_size/2, -h * ROLL_SCALE_RADIUS, _size, _size);
    painter.drawArc(arcArea, (90-ROLL_SCALE_RANGE)*16, ROLL_SCALE_RANGE*2*16);
    if (drawTicks) {
        int length = sizeof(tickValues)/sizeof(int);
        qreal previousRotation = 0;
        for (int i=0; i<length*2+1; i++) {
            int degrees = (i==length) ? 0 : (i>length) ?-tickValues[i-length-1] : tickValues[i];
            //degrees = 180 - degrees;
            painter.rotate(degrees - previousRotation);
            previousRotation = degrees;

            QPointF start(0, -_size/2);
            QPointF end(0, -(1.0+ROLL_SCALE_TICKMARKLENGTH)*_size/2);

            painter.drawLine(start, end);

            QString s_number; //= QString("%d").arg(degrees);
            if (SHOW_ZERO_ON_SCALES || degrees)
                s_number.sprintf("%d", abs(degrees));

            if (drawNumbers) {
                drawTextCenterBottom(painter, s_number, SCALE_TEXT_SIZE*h, 0, -(ROLL_SCALE_RADIUS+ROLL_SCALE_TICKMARKLENGTH*1.7)*h);
            }
        }
    }
}

void PrimaryFlightDisplay::drawAIAttitudeScales(
        QPainter& painter,
        QRectF area
    ) {
    // To save computations, we do these transformations once for both scales:
    painter.resetTransform();
    painter.translate(area.center());
    painter.rotate(roll);
    QTransform saved = painter.transform();

    drawRollScale(painter, area, true, true);

    painter.setTransform(saved);
    drawPitchScale(painter, area, true, true);
}

void PrimaryFlightDisplay::drawCompassDisk(QPainter& painter, QRectF area) {
    float start = heading - COMPASS_DISK2_SPAN/2;
    float end = heading + COMPASS_DISK2_SPAN/2;

    int firstTick = ceil(start / COMPASS_DISK2_RESOLUTION) * COMPASS_DISK2_RESOLUTION;
    int lastTick = floor(end / COMPASS_DISK2_RESOLUTION) * COMPASS_DISK2_RESOLUTION;

    float radius = area.width()/2;
    float innerRadius = radius * 0.96;
    painter.resetTransform();

    float save = instrumentEdgePen.widthF();
    instrumentEdgePen.setWidthF(save/2);
    painter.setPen(instrumentEdgePen);
    if (layout == COMPASS_SEPARATED)
        painter.setBrush(instrumentOpagueBackground);
    else
        painter.setBrush(instrumentBackground);
    painter.drawEllipse(area);
    instrumentEdgePen.setWidthF(save);
    painter.setBrush(Qt::NoBrush);

    blackPen.setWidthF(2);

    for (int tickYaw = firstTick; tickYaw <= lastTick; tickYaw += COMPASS_DISK2_RESOLUTION) {
        int displayTick = tickYaw;
        if (displayTick < 0) displayTick+=360;
        else if (displayTick>=360) displayTick-=360;

        // yaw is in center.
        float off = tickYaw - heading;
        // wrap that to ]-180..180]
        if (off<=-180) off+= 360; else if (off>180) off += 360;

        painter.translate(area.center());
        painter.rotate(off);
        bool drewArrow = false;
        bool isMajor = displayTick % COMPASS_DISK2_MAJORTICK == 0;

        if (displayTick==30 || displayTick==60 ||
            displayTick==120 || displayTick==150 ||
            displayTick==210 || displayTick==240 ||
                displayTick==300 || displayTick==330) {
            // draw a number
            QString s_number;
            s_number.sprintf("%d", displayTick/10);
            painter.setPen(blackPen);
            drawTextCenter(painter, s_number, COMPASS_SCALE_TEXT_SIZE*radius, 0, -innerRadius*0.75);
        } else {
            if (displayTick % COMPASS_DISK2_ARROWTICK == 0) {
                if (displayTick!=0) {
                    QPainterPath markerPath(QPointF(0, -innerRadius*(1-COMPASS_DISK_MARKERHEIGHT/2)));
                    markerPath.lineTo(innerRadius*COMPASS_DISK_MARKERWIDTH/4, -innerRadius);
                    markerPath.lineTo(-innerRadius*COMPASS_DISK_MARKERWIDTH/4, -innerRadius);
                    markerPath.closeSubpath();
                    painter.setPen(blackPen);
                    painter.setBrush(Qt::SolidPattern);
                    painter.drawPath(markerPath);
                    painter.setBrush(Qt::NoBrush);
                    drewArrow = true;
                }
                if (displayTick%90 == 0) {
                    // Also draw a label
             QString name = compassWindNames[displayTick / 45];
             painter.setPen(blackPen);
            drawTextCenter(painter, name, COMPASS_SCALE_TEXT_SIZE*radius*1.2, 0, -innerRadius*0.75);
                }
        }
}
            // draw the scale lines. If an arrow was drawn, stay off from it.

            QPointF p_start = drewArrow ? QPoint(0, -innerRadius*0.94) : QPoint(0, -innerRadius);
            QPoint p_end = isMajor ? QPoint(0, -innerRadius*0.86) : QPoint(0, -innerRadius*0.90);

            painter.setPen(blackPen);
        painter.drawLine(p_start, p_end);
        painter.resetTransform();
    }

    painter.setPen(blackPen);
    //painter.setBrush(Qt::SolidPattern);
    painter.translate(area.center());
    QPainterPath markerPath(QPointF(0, -radius-2));
    markerPath.lineTo(radius*COMPASS_DISK_MARKERWIDTH/2,  -radius-radius*COMPASS_DISK_MARKERHEIGHT-2);
    markerPath.lineTo(-radius*COMPASS_DISK_MARKERWIDTH/2, -radius-radius*COMPASS_DISK_MARKERHEIGHT-2);
    markerPath.closeSubpath();
    painter.drawPath(markerPath);

    QRectF compassRect(-radius/3, -radius*0.52, radius*2/3, radius*0.28);
    painter.setPen(instrumentEdgePen);
    painter.drawRoundedRect(compassRect, instrumentEdgePen.widthF()*2/3, instrumentEdgePen.widthF()*2/3);

    if (heading < 0) heading += 360;
    else if (heading >= 360) heading -= 360;
    /* final safeguard for really stupid systems */
    int yawCompass = static_cast<int>(heading) % 360;

    QString yawAngle;
    yawAngle.sprintf("%03d", yawCompass);

    painter.setPen(whitePen);
    drawTextCenter(painter, yawAngle, COMPASS_SCALE_TEXT_SIZE*radius*1.2, 0, -radius*0.38);
}

#ifdef USE_TAPE_COMPASS
void PrimaryFlightDisplay::drawCompassTape(
        QPainter& painter,
        float heading,
        qreal width,
        qreal y,
        qreal height
        ) {
    float start = heading - COMPASS_TAPE_SPAN/2;
    float end = heading + COMPASS_TAPE_SPAN/2;
    int firstTick = ceil(start / COMPASS_TAPE_RESOLUTION) * COMPASS_TAPE_RESOLUTION;
    int lastTick = floor(end / COMPASS_TAPE_RESOLUTION) * COMPASS_TAPE_RESOLUTION;
    painter.setPen(whitePen);

    for (int tickYaw = firstTick; tickYaw <= lastTick; tickYaw += COMPASS_TAPE_RESOLUTION) {
        int displayTick = tickYaw;
        if (displayTick < 0) displayTick+=360;
        else if (displayTick>=360) displayTick-=360;

        // yaw is in center.
        float off = tickYaw - heading;
        // wrap that to ]-180..180]
        if (off<=-180) off+= 360; else if (off>180) off += 360;

        float x = width/2 + off*width/COMPASS_TAPE_SPAN;

        QPointF p_start = QPointF(x, y-height/2);
        QPointF p_end = QPointF(x, y+height/2);

        if (displayTick % 45 == 0) {
            // draw a wind label
            QString name = compassWindNames[displayTick / 45];
            drawText(painter, name, Qt::AlignLeft | Qt::TextWordWrap, SCALE_TEXT_SIZE, x, y);
            painter.drawPoint(p_start);
            painter.drawPoint(p_end);
        } else {
            QPointF p_start(x, y-height/2);
            QPointF p_endQPointF(x, y+height/2);
            painter.drawLine(p_start, p_end);
        }
    }

    painter.setPen(redPen);
    QPointF p_start(width/2, y-height/2);
    QPointF p_end(width/2, y+height/2);
    painter.drawLine(p_start, p_end);
}
#endif

void PrimaryFlightDisplay::drawAltimeter(
        QPainter& painter,
        QRectF area, // the area where to draw the tape.
//        float width,
//        float height,
        float altitude,
        float maxAltitude,
        float vv
    ) {

    Q_UNUSED(vv)
    Q_UNUSED(maxAltitude)

    painter.resetTransform();
    fillInstrumentBackground(painter, area);

    painter.setPen(whitePen);

    float h = area.height();
    float w = area.width();
    float effectiveHalfHeight = h*0.45;
    float tickmarkLeft = 0.3*w;
    float tickmarkRight = 0.4*w;
    float numbersLeft = 0.42*w;
    float markerHalfHeight = 0.06*h;
    float rightEdge = w-instrumentEdgePen.widthF()*2;
    float markerTip = tickmarkLeft;

    // altitude scale
#ifdef ALTIMETER_PROJECTED
    float range = 1.2;
    float start = altitude - ALTIMETER_PROJECTED_SPAN/2;
    float end = altitude + ALTIMETER_PROJECTED_SPAN/2;
    int firstTick = ceil(start / ALTIMETER_PROJECTED_RESOLUTION) * ALTIMETER_PROJECTED_RESOLUTION;
    int lastTick = floor(end / ALTIMETER_PROJECTED_RESOLUTION) * ALTIMETER_PROJECTED_RESOLUTION;
    for (int tickAlt = firstTick; tickAlt <= lastTick; tickAlt += ALTIMETER_PROJECTED_RESOLUTION) {
        // a number between 0 and 1. Use as radians directly.
        float r = range*(tickAlt-altitude)/(ALTIMETER_PROJECTED_SPAN/2);
        float y = effectiveHalfHeight * sin(r);
        scale = cos(r);
        if (scale<0) scale = -scale;
        bool hasText = tickAlt % ALTIMETER_PROJECTED_MAJOR_RESOLUTION == 0;
#else
    float start = altitude - ALTIMETER_LINEAR_SPAN/2;
    float end = altitude + ALTIMETER_LINEAR_SPAN/2;
    int firstTick = ceil(start / ALTIMETER_LINEAR_RESOLUTION) * ALTIMETER_LINEAR_RESOLUTION;
    int lastTick = floor(end / ALTIMETER_LINEAR_RESOLUTION) * ALTIMETER_LINEAR_RESOLUTION;
    for (int tickAlt = firstTick; tickAlt <= lastTick; tickAlt += ALTIMETER_LINEAR_RESOLUTION) {
        float y = (tickAlt-altitude)*effectiveHalfHeight/(ALTIMETER_LINEAR_SPAN/2);
        bool hasText = tickAlt % ALTIMETER_LINEAR_MAJOR_RESOLUTION == 0;
#endif
        painter.resetTransform();
        painter.translate(area.left(), area.center().y() - y);
        painter.drawLine(tickmarkLeft, 0, tickmarkRight, 0);
        if (hasText) {
            QString s_alt;
            s_alt.sprintf("%d", tickAlt);
            drawTextLeftCenter(painter, s_alt, TAPES_TEXT_SIZE*width(), numbersLeft, 0);
        }
    }

    QPainterPath markerPath(QPoint(markerTip, 0));
    markerPath.lineTo(markerTip+markerHalfHeight, markerHalfHeight);
    markerPath.lineTo(rightEdge, markerHalfHeight);
    markerPath.lineTo(rightEdge, -markerHalfHeight);
    markerPath.lineTo(markerTip+markerHalfHeight, -markerHalfHeight);
    markerPath.closeSubpath();

    painter.resetTransform();
    painter.translate(area.left(), area.center().y());
    painter.setPen(blackPen);
    painter.setBrush(Qt::SolidPattern);
    painter.drawPath(markerPath);
    painter.setBrush(Qt::NoBrush);

    painter.setPen(whitePen);
    QString s_alt;
    s_alt.sprintf("%3.0f", altitude);
    float xCenter = (markerTip+rightEdge)/2;
    drawTextCenter(painter, s_alt, TAPES_TEXT_SIZE*width(), xCenter, 0);
}

void PrimaryFlightDisplay::drawSysStatsPanel (
        QPainter& painter,
        QRectF area) {
    // Timer
    // Battery
    // Armed/not
    QString s_volts("12.4V 21A");
    QString s_arm("Armed");

    painter.resetTransform();

    if (style == OPAGUE_TAPES)
        drawInstrumentBackground(painter, area);

    painter.translate(area.center());

    painter.setPen(amberPen);
    drawTextCenter(painter, s_volts, PANELS_TEXT_SIZE*width(), 0, -area.height()/6);
    painter.setPen(redPen);
    drawTextCenter(painter, s_arm, PANELS_TEXT_SIZE*width(), 0, area.height()/6);
}

void PrimaryFlightDisplay::drawLinkStatsPanel (
        QPainter& painter,
        QRectF area) {
    // UAV Id
    // Droprates up, down
    QString s_linkStat("100%");
    QString s_upTime("01:23:34");

    painter.resetTransform();

    if (style == OPAGUE_TAPES)
        drawInstrumentBackground(painter, area);

    painter.translate(area.center());

    painter.setPen(amberPen);
    drawTextCenter(painter, s_linkStat, PANELS_TEXT_SIZE*width(), 0, -area.height()/6);
    drawTextCenter(painter, s_upTime, PANELS_TEXT_SIZE*width(), 0, area.height()/6);
}

void PrimaryFlightDisplay::drawMissionStatsPanel (
        QPainter& painter,
        QRectF area) {
    // Flight mode
    // next WP
    // next WP dist
    QString s_flightMode("Auto");
    QString s_nextWP("1234m\u21924");

    painter.resetTransform();

    if (style == OPAGUE_TAPES)
        drawInstrumentBackground(painter, area);

    painter.translate(area.center());

    painter.setPen(amberPen);
    drawTextCenter(painter, s_flightMode, PANELS_TEXT_SIZE*width(), 0, -area.height()/6);
    drawTextCenter(painter, s_nextWP, PANELS_TEXT_SIZE*width(), 0, area.height()/6);
}

void PrimaryFlightDisplay::drawSensorsStatsPanel (
        QPainter& painter,
        QRectF area) {
    // GPS fixmode and #sats
    // Home alt.?
    // Groundspeed?
    QString s_GPS("GPS 3D(8)");
    QString s_homealt("H.alt 472m");

    painter.resetTransform();

    if (style == OPAGUE_TAPES)
        drawInstrumentBackground(painter, area);

    painter.translate(area.center());

    painter.setPen(amberPen);
    drawTextCenter(painter, s_GPS, PANELS_TEXT_SIZE*width(), 0, -area.height()/6);
    drawTextCenter(painter, s_homealt, PANELS_TEXT_SIZE*width(), 0, area.height()/6);
}

#define TOP         (1<<0)
#define BOTTOM      (1<<1)
#define LEFT        (1<<2)
#define RIGHT       (1<<3)

#define TOP_2       (1<<4)
#define BOTTOM_2    (1<<5)
#define LEFT_2      (1<<6)
#define RIGHT_2     (1<<7)

void applyMargin(QRectF& area, float margin, int where) {
    if (margin < 0.01) return;

    QRectF save(area);
    qreal consumed;

    if (where & LEFT) {
        area.setX(save.x() + (consumed = margin));
    } else if (where & LEFT_2) {
        area.setX(save.x() + (consumed = margin/2));
    } else {
        consumed = 0;
    }

    if (where & RIGHT) {
        area.setWidth(save.width()-consumed-margin);
    } else if (where & RIGHT_2) {
        area.setWidth(save.width()-consumed-margin/2);
    } else {
        area.setWidth(save.width()-consumed);
    }

    if (where & TOP) {
        area.setY(save.y() + (consumed = margin));
    } else if (where & TOP_2) {
        area.setY(save.y() + (consumed = margin/2));
    } else {
        consumed = 0;
    }

    if (where & BOTTOM) {
        area.setHeight(save.height()-consumed-margin);
    } else if (where & BOTTOM_2) {
        area.setHeight(save.height()-consumed-margin/2);
    } else {
        area.setHeight(save.height()-consumed);
    }
}

void setMarginsForInlineLayout(qreal margin, QRectF& panel1, QRectF& panel2, QRectF& panel3, QRectF& panel4) {
    applyMargin(panel1, margin, BOTTOM|LEFT|RIGHT_2);
    applyMargin(panel2, margin, BOTTOM|LEFT_2|RIGHT_2);
    applyMargin(panel3, margin, BOTTOM|LEFT_2|RIGHT_2);
    applyMargin(panel4, margin, BOTTOM|LEFT_2|RIGHT);
}

void setMarginsForCornerLayout(qreal margin, QRectF& panel1, QRectF& panel2, QRectF& panel3, QRectF& panel4) {
    applyMargin(panel1, margin, BOTTOM|LEFT|RIGHT_2);
    applyMargin(panel2, margin, BOTTOM|LEFT_2|RIGHT_2);
    applyMargin(panel3, margin, BOTTOM|LEFT_2|RIGHT_2);
    applyMargin(panel4, margin, BOTTOM|LEFT_2|RIGHT);
}

inline qreal tapesGaugeWidthFor(qreal containerWidth, qreal preferredAIWidth) {
    qreal result = (containerWidth - preferredAIWidth) / 2.0f;
    qreal minimum = containerWidth / 6.0f;
    if (result < minimum) result = minimum;
    return result;
}

void PrimaryFlightDisplay::doPaint() {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    qreal margin = height()/100.0f;

    QRectF AIArea;
    QRectF compassArea;
    QRectF altimeterArea;
    QRectF velocityMeterArea;
    QRectF sensorsStatsArea;
    QRectF linkStatsArea;
    QRectF sysStatsArea;
    QRectF missionStatsArea;

    painter.fillRect(rect(), Qt::black);
    qreal tapeGaugeWidth;

    switch(layout) {
    case FEATUREPANELS_IN_CORNERS: {
        tapeGaugeWidth = tapesGaugeWidthFor(width(), height());

        // A layout optimal for a container wider than it is high.
        // The AI gets full height and if tapes are transparent, also full width. If tapes are opague, then
        // the AI gets a width to be perfectly square.
        AIArea = QRectF(
                    style == OPAGUE_TAPES ? tapeGaugeWidth : 0,
                    0,
                    style == OPAGUE_TAPES ? width() - tapeGaugeWidth * 2: width(),
                    height());

        // Tape gauges get so much width that the AI area not covered by them is perfectly square.

        qreal sidePanelsHeight = height();

        altimeterArea = QRectF(AIArea.right(), height()/5, tapeGaugeWidth, sidePanelsHeight*3/5);
        velocityMeterArea = QRectF (0, height()/5, tapeGaugeWidth, sidePanelsHeight*3/5);

        sensorsStatsArea = QRectF(0, 0, tapeGaugeWidth, sidePanelsHeight/5);
        linkStatsArea = QRectF(AIArea.right(), 0, tapeGaugeWidth, sidePanelsHeight/5);
        sysStatsArea = QRectF(0, sidePanelsHeight*4/5, tapeGaugeWidth, sidePanelsHeight/5);
        missionStatsArea =QRectF(AIArea.right(), sidePanelsHeight*4/5, tapeGaugeWidth, sidePanelsHeight/5);

        if (style == OPAGUE_TAPES) {
            applyMargin(AIArea, margin, TOP|BOTTOM);
            applyMargin(altimeterArea, margin, TOP|BOTTOM|RIGHT);
            applyMargin(velocityMeterArea, margin, TOP|BOTTOM|LEFT);
            setMarginsForCornerLayout(margin, sensorsStatsArea, linkStatsArea, sysStatsArea, missionStatsArea);
        }

        // Compass is inside the AI ans within its margins also.
        compassArea = QRectF(AIArea.x()+AIArea.width()*0.60, AIArea.y()+AIArea.height()*0.80,
                             AIArea.width()/2, AIArea.height()/2);
        break;
    }

    case FEATUREPANELS_AT_BOTTOM: {
        // A layout for containers with about the same width and height.
        // qreal minor = min(width(), height());
        // qreal major = max(width(), height());

        qreal aiheight = height()*4.0f/5;

        tapeGaugeWidth = tapesGaugeWidthFor(width(), aiheight);

        AIArea = QRectF(
                    style == OPAGUE_TAPES ? tapeGaugeWidth : 0,
                    0,
                    style == OPAGUE_TAPES ? width() - tapeGaugeWidth*2 : width(),
                    aiheight);

        // Tape gauges get so much width that the AI area not covered by them is perfectly square.
        altimeterArea = QRectF(AIArea.right(), 0, tapeGaugeWidth, aiheight);
        velocityMeterArea = QRectF (0, 0, tapeGaugeWidth, aiheight);

        qreal panelsHeight = height() / 5.0f;
        qreal panelsWidth = width() / 4.0f;

        sensorsStatsArea = QRectF(0, AIArea.bottom(), panelsWidth, panelsHeight);
        linkStatsArea = QRectF(panelsWidth, AIArea.bottom(), panelsWidth, panelsHeight);
        sysStatsArea = QRectF(panelsWidth*2, AIArea.bottom(), panelsWidth, panelsHeight);
        missionStatsArea =QRectF(panelsWidth*3, AIArea.bottom(), panelsWidth, panelsHeight);

        if (style == OPAGUE_TAPES) {
            applyMargin(AIArea, margin, TOP|BOTTOM);
            applyMargin(altimeterArea, margin, TOP|BOTTOM|RIGHT);
            applyMargin(velocityMeterArea, margin, TOP|BOTTOM|LEFT);
            setMarginsForInlineLayout(margin, sensorsStatsArea, linkStatsArea, sysStatsArea, missionStatsArea);
        }

        // Compass is inside the AI ans within its margins also.
        compassArea = QRectF(AIArea.x()+AIArea.width()*0.60, AIArea.y()+AIArea.height()*0.80,
                             AIArea.width()/2, AIArea.height()/2);
        break;
    }

    case COMPASS_SEPARATED: {
        // A layout for containers higher than their width.
        tapeGaugeWidth = tapesGaugeWidthFor(width(), width());

        qreal aiheight = height() / 2.0f;
        if (width() > aiheight) aiheight = width()-tapeGaugeWidth*2;

        AIArea = QRectF(
                    style == OPAGUE_TAPES ? tapeGaugeWidth : 0,
                    0,
                    style == OPAGUE_TAPES ? width()-tapeGaugeWidth*2 : width(),
                    aiheight);

        altimeterArea = QRectF(AIArea.right(), 0, tapeGaugeWidth, aiheight);
        velocityMeterArea = QRectF (0, 0, tapeGaugeWidth, aiheight);

        qreal panelsWidth = width() / 4.0f;
        qreal remainingHeight = height() - aiheight;
        qreal panelsHeight = remainingHeight / 5.0f;
        QPoint compassCenter;
        qreal maxCompassRadius;
        if(remainingHeight > width()) {
            // very tall layout, place panels below compass.
            sensorsStatsArea = QRectF(0, height()-panelsHeight, panelsWidth, panelsHeight);
            linkStatsArea = QRectF(panelsWidth, height()-panelsHeight, panelsWidth, panelsHeight);
            sysStatsArea = QRectF(panelsWidth*2, height()-panelsHeight, panelsWidth, panelsHeight);
            missionStatsArea =QRectF(panelsWidth*3, height()-panelsHeight, panelsWidth, panelsHeight);
            if (style == OPAGUE_TAPES) {
                setMarginsForInlineLayout(margin, sensorsStatsArea, linkStatsArea, sysStatsArea, missionStatsArea);
            }
            compassCenter = QPoint(width()/2, (AIArea.bottom()+height()-panelsHeight)/2);
            maxCompassRadius = fmin(width()/2, (height()-AIArea.height()-panelsHeight)/2);
        } else {
            // Remaining part is wider than high; place panels in corners around compass
            sensorsStatsArea = QRectF(0, AIArea.bottom(), panelsWidth, panelsHeight);
            linkStatsArea = QRectF(width()-panelsWidth, AIArea.bottom(), panelsWidth, panelsHeight);
            sysStatsArea = QRectF(0, height()-panelsHeight, panelsWidth, panelsHeight);
            missionStatsArea =QRectF(width()-panelsWidth, height()-panelsHeight, panelsWidth, panelsHeight);
            if (style == OPAGUE_TAPES) {
                setMarginsForCornerLayout(margin, sensorsStatsArea, linkStatsArea, sysStatsArea, missionStatsArea);
            }
            compassCenter = QPoint(width()/2, (AIArea.bottom()+height())/2);
            // diagonal between 2 panel corners
            qreal xd = width()-panelsWidth*2;
            qreal yd = height()-panelsHeight - AIArea.bottom();
            maxCompassRadius = sqrt(xd*xd + yd*yd)/2;
        }

        qreal compassRadius = maxCompassRadius * 0.9;
        compassArea = QRectF(compassCenter.x()-compassRadius, compassCenter.y()-compassRadius, 2*compassRadius, 2*compassRadius);
        break;
    }
    }

    bool hadClip = painter.hasClipping();

    painter.setClipping(true);

    if (layout==COMPASS_SEPARATED)
        painter.setClipRect(rect());
    else
        painter.setClipRect(AIArea);

    drawAIGlobalFeatures(painter, AIArea);
    drawAIAttitudeScales(painter, AIArea);
    drawAIAirframeFixedFeatures(painter, AIArea);

    drawCompassDisk(painter, compassArea);

    painter.setClipping(hadClip);

    // X: To the right of AI and with single margin again. That is, 3 single margins plus width of AI.
    // Y: 1 single margin below above gadget.

    drawAltimeter(painter, altimeterArea, aboveASLAltitude, 1000, 0);
    drawAltimeter(painter, velocityMeterArea, aboveASLAltitude, 1000, 0);

    drawSensorsStatsPanel(painter, sensorsStatsArea);
    drawLinkStatsPanel(painter, linkStatsArea);
    drawSysStatsPanel(painter, sysStatsArea);
    drawMissionStatsPanel(painter, missionStatsArea);

    painter.end();
}

void PrimaryFlightDisplay:: createActions() {}
