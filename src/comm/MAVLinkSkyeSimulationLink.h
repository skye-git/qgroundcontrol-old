/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of MAVLinkSkyeSimulationLink, slightly modified from MAVLinkSkyeSimulationLink
 *
 *
 */

#ifndef MAVLINKSKYESIMULATIONLINK_H
#define MAVLINKSKYESIMULATIONLINK_H

#include <QFile>
#include <QTimer>
#include <QTextStream>
#include <QQueue>
#include <QMutex>
#include <QMap>
#include <qmath.h>
#include <inttypes.h>
#include "QGCMAVLink.h"

#include "LinkInterface.h"

class MAVLinkSkyeSimulationLink : public LinkInterface
{
    Q_OBJECT
public:
    MAVLinkSkyeSimulationLink(QString readFile="", QString writeFile="", int rate=5, QObject* parent = 0);
    ~MAVLinkSkyeSimulationLink();
    bool isConnected() const;
    qint64 bytesAvailable();

    void run();
    void requestReset() { }
    bool connect();
    bool disconnect();

    /* Extensive statistics for scientific purposes */
    qint64 getNominalDataRate() const;
    qint64 getTotalUpstream();
    qint64 getShortTermUpstream();
    qint64 getCurrentUpstream();
    qint64 getMaxUpstream();
    qint64 getTotalDownstream();
    qint64 getShortTermDownstream();
    qint64 getCurrentDownstream();
    qint64 getMaxDownstream();
    qint64 getBitsSent() const;
    qint64 getBitsReceived() const;

    QString getName() const;
    int getId() const;
    int getBaudRate() const;
    int getBaudRateType() const;
    int getFlowType() const;
    int getParityType() const;
    int getDataBitsType() const;
    int getStopBitsType() const;

    int getLinkQuality() const;
    bool isFullDuplex() const;

public slots:
    void writeBytes(const char* data, qint64 size);
    void readBytes();
    /** @brief Mainloop simulating the mainloop of the MAV */
    virtual void mainloop();
    bool connectLink(bool connect);
    void connectLink();
    void sendMAVLinkMessage(const mavlink_message_t* msg);


protected:

    // UAS properties
    float roll, pitch, yaw;
    float speedRoll, speedPitch, speedYaw;       // Code MA (14.03.2012)
    double x, y, z;
    double spYaw;//    double spX, spY, spZ, spYaw;
    double speedX, speedY, speedZ;      // Code MA (14.03.2012)
    double spX, spY, spZ;
    int battery;

    QTimer* timer;
    /** File which contains the input data (simulated robot messages) **/
    QFile* simulationFile;
    QFile* mavlinkLogFile;
    QString simulationHeader;
    /** File where the commands sent by the groundstation are stored **/
    QFile* receiveFile;
    QTextStream textStream;
    QTextStream* fileStream;
    QTextStream* outStream;
    /** Buffer which can be read from connected protocols through readBytes(). **/
    QMutex readyBufferMutex;
    bool _isConnected;
    quint64 rate;
    int maxTimeNoise;
    quint64 lastSent;
    static const int streamlength = 4096;
    unsigned int streampointer;
    //const int testoffset = 0;
    uint8_t stream[streamlength];

    int readyBytes;
    QQueue<uint8_t> readyBuffer;

    int id;
    QString name;
    qint64 timeOffset;
    mavlink_heartbeat_t system;
    mavlink_sys_status_t status;

    QMap<QString, float> onboardParams;

    void enqueue(uint8_t* stream, uint8_t* index, mavlink_message_t* msg);

    static const uint8_t systemId = 42;
    static const uint8_t componentId = 200;
    static const uint16_t version = 1000;


    // Begin Code MA (09.03.2012) -----------------------
    double thrustX;      // Direct Control input
    double thrustY;
    double thrustZ;
    double momentX;
    double momentY;
    double momentZ;
    double transX;      // Direct Control input
    double transY;
    double transZ;
    double rotX;
    double rotY;
    double rotZ;
    float thrust1;        //Testphase Control
    float thrust2;
    float thrust3;
    float thrust4;
    float orientation1;
    float orientation2;
    float orientation3;
    float orientation4;
    int battery_pack_id;    // Iterator for detailed battery message
    int homing;                 //Value from HOME_MAXON message

    int time_boot;      ///< Time since boot in ms
    // Ende Code MA (09.03.2012) --------------------------


signals:
    void valueChanged(int uasId, QString curve, double value, quint64 usec);
    void messageReceived(const mavlink_message_t& message);

};

#endif // MAVLINKSKYESIMULATIONLINK_H
