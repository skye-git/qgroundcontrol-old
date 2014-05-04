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
*   @brief Implementation of simulated system link, slightly modified from MAVLinkSkyeSimulationLink
*
*
*/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <QTime>
#include <QImage>
#include <QDebug>
#include <QFileInfo>
#include "LinkManager.h"
#include "MAVLinkProtocol.h"
#include "MAVLinkSkyeSimulationLink.h"
#include "QGCMAVLink.h"
#include "QGC.h"
#include "MAVLinkSimulationMAV.h"

/**
* Create a simulated link. This link is connected to an input and output file.
* The link sends one line at a time at the specified sendrate. The timing of
* the sendrate is free of drift, which means it is stable on the long run.
* However, small deviations are mixed in to vary the sendrate slightly
* in order to simulate disturbances on a real communication link.
*
* @param readFile The file with the messages to read (must be in ASCII format, line breaks can be Unix or Windows style)
* @param writeFile The received messages are written to that file
* @param rate The rate at which the messages are sent (in intervals of milliseconds)
**/
MAVLinkSkyeSimulationLink::MAVLinkSkyeSimulationLink(QString readFile, QString writeFile, int rate, QObject* parent) :
    readyBytes(0),
    timeOffset(0),
    roll(0),            // Attitude
    pitch(0),
    yaw(0),
    speedRoll(0),
    speedPitch(0),
    speedYaw(0),
    x(0),
    y(0),
    z(0),
    speedX(0),
    speedY(0),
    speedZ(0),
    thrustX(0),         // Direct Control
    thrustY(0),
    thrustZ(0),
    momentX(0),
    momentY(0),
    momentZ(0),
    transX(0),          // Assisted Control
    transY(0),
    transZ(0),
    rotX(0),
    rotY(0),
    rotZ(0),
    thrust1(0),        //Testphase Control
    thrust2(0),
    thrust3(0),
    thrust4(0),
    orientation1(0),
    orientation2(0),
    orientation3(0),
    orientation4(0),
    battery_pack_id(0),
    homing(0),
    time_boot(0)
{
    this->rate = rate;
    _isConnected = false;

    onboardParams = QMap<QString, float>();
    onboardParams.insert("PID_ROLL_K_P", 0.5f);
    onboardParams.insert("PID_PITCH_K_P", 0.5f);
    onboardParams.insert("PID_YAW_K_P", 0.5f);
    onboardParams.insert("PID_XY_K_P", 100.0f);
    onboardParams.insert("PID_ALT_K_P", 0.5f);
    onboardParams.insert("SYS_TYPE", 1);
    onboardParams.insert("SYS_ID", systemId);
    onboardParams.insert("RC4_REV", 0);
    onboardParams.insert("RC5_REV", 1);
    onboardParams.insert("HDNG2RLL_P", 0.7f);
    onboardParams.insert("HDNG2RLL_I", 0.01f);
    onboardParams.insert("HDNG2RLL_D", 0.02f);
    onboardParams.insert("HDNG2RLL_IMAX", 500.0f);
    onboardParams.insert("RLL2SRV_P", 0.4f);
    onboardParams.insert("RLL2SRV_I", 0.0f);
    onboardParams.insert("RLL2SRV_D", 0.0f);
    onboardParams.insert("RLL2SRV_IMAX", 500.0f);

    // Comments on the variables can be found in the header file

    simulationFile = new QFile(readFile, this);
    if (simulationFile->exists() && simulationFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        simulationHeader = simulationFile->readLine();
    }
    receiveFile = new QFile(writeFile, this);
    lastSent = QGC::groundTimeMilliseconds();

    if (simulationFile->exists())
    {
        this->name = "Simulation: " + QFileInfo(simulationFile->fileName()).fileName();
    }
    else
    {
        this->name = "MAVLink simulation link";
    }



    // Initialize the pseudo-random number generator
    srand(QTime::currentTime().msec());
    maxTimeNoise = 0;
    this->id = getNextLinkId();
    LinkManager::instance()->add(this);
    QObject::connect(this, SIGNAL(destroyed(QObject*)), LinkManager::instance(), SLOT(removeLink(QObject*)));
}

MAVLinkSkyeSimulationLink::~MAVLinkSkyeSimulationLink()
{
    //TODO Check destructor
    //    fileStream->flush();
    //    outStream->flush();
    // Force termination, there is no
    // need for cleanup since
    // this thread is not manipulating
    // any relevant data
    terminate();
    delete simulationFile;
}

void MAVLinkSkyeSimulationLink::run()
{
    status.voltage_battery = 0;
    status.errors_comm = 0;

    system.base_mode = MAV_MODE_PREFLIGHT;
    system.custom_mode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
    system.type = MAV_TYPE_AIRSHIP;
    system.system_status = MAV_STATE_UNINIT;

    forever
    {
        static quint64 last = 0;

        if (QGC::groundTimeMilliseconds() - last >= rate)
        {
            if (_isConnected)
            {
                mainloop();
                readBytes();
            }
            else
            {
                // Sleep for substantially longer
                // if not connected
                QGC::SLEEP::msleep(500);
            }
            last = QGC::groundTimeMilliseconds();
        }
        QGC::SLEEP::msleep(3);
    }
}

void MAVLinkSkyeSimulationLink::sendMAVLinkMessage(const mavlink_message_t* msg)
{
    // Allocate buffer with packet data
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    unsigned int bufferlength = mavlink_msg_to_send_buffer(buf, msg);

    // Pack to link buffer
    readyBufferMutex.lock();
    for (unsigned int i = 0; i < bufferlength; i++)
    {
        readyBuffer.enqueue(*(buf + i));
    }
    readyBufferMutex.unlock();
}

void MAVLinkSkyeSimulationLink::enqueue(uint8_t* stream, uint8_t* index, mavlink_message_t* msg)
{
    // Allocate buffer with packet data
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    unsigned int bufferlength = mavlink_msg_to_send_buffer(buf, msg);
    //add data into datastream
    memcpy(stream+(*index),buf, bufferlength);
    (*index) += bufferlength;
}

void MAVLinkSkyeSimulationLink::mainloop()
{

    // Test for encoding / decoding packets

    // Test data stream
    streampointer = 0;

    // Fake system values

    static float fullVoltage = 4.2f * 1.0f - 2.11f/6.0f;
    static float emptyVoltage = 3.35f * 1.0f;
    static float voltage = fullVoltage;
    static float drainRate = 0.025f; // x.xx% of the capacity is linearly drained per second

#ifdef MAVLINK_ENABLED_PIXHAWK
    mavlink_raw_aux_t rawAuxValues;
    memset(&rawAuxValues, 0, sizeof(mavlink_raw_aux_t));
#endif
    mavlink_raw_imu_t rawImuValues;
    memset(&rawImuValues, 0, sizeof(mavlink_raw_imu_t));

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int bufferlength;
    int messageSize;
    mavlink_message_t msg;

    // Timers
    static unsigned int rate1hzCounter = 1;
    static unsigned int rate10hzCounter = 1;
    static unsigned int rate20hzCounter = 1;
    static unsigned int rate50hzCounter = 1;

    // 1 HZ TASKS
    if (rate1hzCounter == 1000 / rate / 1) {

        // Vary values
        if (++battery_pack_id >= 4) battery_pack_id = 0;
        voltage = voltage - ((fullVoltage - emptyVoltage) * drainRate / rate);
        status.voltage_battery = voltage * 6 * 1000; // millivolts
        status.load = 0;

        sendMsgBatteryCellsStatus(voltage);
        sendMsgBatteryStatus(voltage);
        sendMsgActuationStatus();
        sendMsgAllocationControllerRaw();
        sendMsgSysStatus();
        sendMsgHeartbeat();
        sendMsgStatustext();

        rate1hzCounter = 1;
    }

    // 10 HZ TASKS
    if (rate10hzCounter == 1000 / rate / 10) {
        rate10hzCounter = 1;

        sendMsgGlobalPositionInt();
    }


    // 20 HZ TASKS
    if (rate20hzCounter == 1000 / rate / 20) {

        rate20hzCounter = 1;
    }

    // 50 HZ TASKS
    if (rate50hzCounter == 1000 / rate / 50)
    {

        sendMsgAttitude();

        rate50hzCounter = 1;
        time_boot += 20;
//        qDebug() << "Time since boot: " << time_boot;
    }

    readyBufferMutex.lock();
    qDebug() << "[mainloop] locked mutex. Streampointer is" << streampointer << ".";
    for (unsigned int i = 0; i < streampointer; i++) {
        readyBuffer.enqueue(*(stream + i));
    }
    readyBufferMutex.unlock();

    // Increment counters after full main loop
    rate1hzCounter++;
    rate10hzCounter++;
    rate20hzCounter++;
    rate50hzCounter++;
}


qint64 MAVLinkSkyeSimulationLink::bytesAvailable()
{
    readyBufferMutex.lock();
    qint64 size = readyBuffer.size();
    readyBufferMutex.unlock();
    return size;
}

void MAVLinkSkyeSimulationLink::writeBytes(const char* data, qint64 size)
{
    // Parse bytes
    mavlink_message_t msg;
    mavlink_status_t comm;

    uint8_t stream[2048];
    int streampointer = 0;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int bufferlength = 0;

    // Output all bytes as hex digits
    for (int i=0; i<size; i++)
    {
        if (mavlink_parse_char(this->id, data[i], &msg, &comm))
        {
            // MESSAGE RECEIVED!
//            qDebug() << "SIMULATION LINK RECEIVED MESSAGE!";
            emit messageReceived(msg);

            switch (msg.msgid)
            {
                // SET THE SYSTEM MODE
            case MAVLINK_MSG_ID_SET_MODE:
            {
                mavlink_set_mode_t mode;
                mavlink_msg_set_mode_decode(&msg, &mode);
                // Set mode indepent of mode.target

                // Beginn Code MA (13.03.2012)
                if (mode.base_mode & MAV_MODE_FLAG_SAFETY_ARMED)
                {
                    system.base_mode = mode.base_mode;
                    system.system_status = MAV_STATE_ACTIVE;
                }
                else
                {
                    system.system_status = MAV_STATE_STANDBY;
                    system.base_mode = MAV_MODE_PREFLIGHT;
                }

               // Ende Code MA
            }
            break;

            case MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT:
            {
                mavlink_set_local_position_setpoint_t set;
                mavlink_msg_set_local_position_setpoint_decode(&msg, &set);
                spX = set.x;
                spY = set.y;
                spZ = set.z;
                spYaw = set.yaw;

                // Send back new setpoint
                mavlink_message_t ret;
                mavlink_msg_local_position_setpoint_pack(systemId, componentId, &ret, MAV_FRAME_LOCAL_NED, spX, spY, spZ, spYaw);
                bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
                //add data into datastream
                memcpy(stream+streampointer,buffer, bufferlength);
                streampointer += bufferlength;
            }
            break;
            // EXECUTE OPERATOR ACTIONS
            case MAVLINK_MSG_ID_COMMAND_LONG:
            {
                mavlink_command_long_t action;
                mavlink_msg_command_long_decode(&msg, &action);

                qDebug() << "SIM" << "received action" << action.command << "for system" << action.target_system;

                if (action.command == MAV_CMD_DO_SET_MODE)
                {
                    if ((int)action.param1 & MAV_MODE_FLAG_DECODE_POSITION_SAFETY)
                    {
                        system.base_mode = (int)action.param1;
                        system.system_status = MAV_STATE_ACTIVE;
                    }
                    else
                    {
                        system.system_status = MAV_STATE_STANDBY;
                        system.base_mode = MAV_MODE_PREFLIGHT;
                    }
                }
            }
            break;

            // Beginn Code MA (09.03.2012)
            case MAVLINK_MSG_ID_SETPOINT_6DOF: {
                mavlink_setpoint_6dof_t m6c;
                mavlink_msg_setpoint_6dof_decode(&msg, &m6c);
                // qDebug() << "Simulation received 6dof message" << m6c.trans_x << m6c.rot_x;
                //if (m6c.target_system == this->systemId)
                {
                    thrustX = m6c.trans_x;
                    thrustY = m6c.trans_y;
                    thrustZ = m6c.trans_z;
                    momentX = m6c.rot_x;
                    momentY = m6c.rot_y;
                    momentZ = m6c.rot_z;
                    // thrustX = 42;
                    // Set ATTITUDE also with direct control
                    float lastRoll = roll;
                    float lastPitch = pitch;
                    float lastYaw = yaw;
                    float lastX = x;
                    float lastY = y;
                    float lastZ = z;

                    speedRoll = 3.5*m6c.rot_x;
                    speedPitch = 3.5*m6c.rot_y;
                    speedYaw = 3.5*m6c.rot_z;
                    speedX = 10*m6c.trans_x;
                    speedY = 10*m6c.trans_y;
                    speedZ = 10*m6c.trans_z;

                    float dTime = 0.01;
                    roll = lastRoll + speedRoll*dTime;
                    pitch = lastPitch + speedPitch*dTime;
                    yaw = lastYaw + speedYaw*dTime;

                    x = lastX + qCos(yaw)*speedX*dTime - qSin(yaw)*speedY*dTime;
                    y = lastY + qSin(yaw)*speedX*dTime + qCos(yaw)*speedY*dTime;
                    z = lastZ + speedZ*dTime;
               }
                qDebug() << "Skye Simulation received 6dof setpoint.";
                // Send back new setpoint
                mavlink_message_t ret;
                mavlink_msg_setpoint_6dof_pack(systemId, componentId, &ret, m6c.target_system, m6c.trans_x, m6c.trans_y, m6c.trans_z, m6c.rot_x, m6c.rot_y, m6c.rot_z);
                bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
                //add data into datastream
                memcpy(stream+streampointer,buffer, bufferlength);
                streampointer += bufferlength;
            }
            break;

            case MAVLINK_MSG_ID_SETPOINT_8DOF: {
                mavlink_setpoint_8dof_t m8c;
                mavlink_msg_setpoint_8dof_decode(&msg, &m8c);
                if (m8c.target_system == this->systemId) {
                    thrust1 = m8c.val1;        //Testphase Control
                    thrust2 = m8c.val2;
                    thrust3 = m8c.val3;
                    thrust4 = m8c.val4;
                    orientation1 = m8c.val5;
                    orientation2 = m8c.val6;
                    orientation3 = m8c.val7;
                    orientation4 = m8c.val8;
                }
                qDebug() << "Skye Simulation received 8 DOF setpoint.";
                // Send back new setpoint
                mavlink_message_t ret;
                mavlink_msg_setpoint_8dof_pack(systemId, componentId, &ret, m8c.target_system, m8c.val1, m8c.val2, m8c.val3, m8c.val4, m8c.val5, m8c.val6, m8c.val7, m8c.val8);
                bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
                //add data into datastream
                memcpy(stream+streampointer,buffer, bufferlength);
                streampointer += bufferlength;
            }
            break;      // Ende Code MA (09.03.2012)

            }
        }
        unsigned char v=data[i];
        //fprintf(stderr,"%02x ", v);
    }
    //fprintf(stderr,"\n");

    readyBufferMutex.lock();
    qDebug() << "[writeBytes] locked mutex. Streampointer is" << streampointer << ".";
    for (int i = 0; i < streampointer; i++)
    {
        readyBuffer.enqueue(*(stream + i));
    }
    readyBufferMutex.unlock();

    if (streampointer > 0)
        readBytes();

    // Update comm status
    status.errors_comm = comm.packet_rx_drop_count;
}


void MAVLinkSkyeSimulationLink::readBytes()
{
    // Lock concurrent resource readyBuffer
    readyBufferMutex.lock();
    const qint64 maxLength = 2048;
    char data[maxLength];
    qint64 len = qMin((qint64)readyBuffer.size(), maxLength);

    for (unsigned int i = 0; i < len; i++) {
        *(data + i) = readyBuffer.takeFirst();
    }

    QByteArray b(data, len);
    emit bytesReceived(this, b);

    readyBufferMutex.unlock();

//    if (len > 0)
//    {
//        qDebug() << "Simulation sent " << len << " bytes to groundstation: ";

//        /* Increase write counter */
//        //bitsSentTotal += size * 8;

//        //Output all bytes as hex digits
//        int i;
//        for (i=0; i<len; i++)
//        {
//            unsigned int v=data[i];
//            fprintf(stderr,"%02x ", v);
//        }
//        fprintf(stderr,"\n");
//    }
}

/**
* Disconnect the connection.
*
* @return True if connection has been disconnected, false if connection
* couldn't be disconnected.
**/
bool MAVLinkSkyeSimulationLink::disconnect()
{

    if(isConnected())
    {
        //        timer->stop();

        _isConnected = false;

        emit disconnected();
        emit connected(false);

        //exit();
    }

    return true;
}

/**
* Connect the link.
*
* @return True if connection has been established, false if connection
* couldn't be established.
**/
bool MAVLinkSkyeSimulationLink::connect()
{
    _isConnected = true;
    emit connected();
    emit connected(true);

    start(LowPriority);
//    MAVLinkSimulationSKYE* skyemav = new MAVLinkSimulationSKYE;
//    MAVLinkSimulationMAV* mav1 = new MAVLinkSimulationMAV(this, 1, 37.480391, -122.282883);
//    Q_UNUSED(mav1);
//    MAVLinkSimulationMAV* mav2 = new MAVLinkSimulationMAV(this, 2, 47.375, 8.548, 1);
//    Q_UNUSED(mav2);
    //    timer->start(rate);
    return true;
}

/**
* Connect the link.
*
* @param connect true connects the link, false disconnects it
* @return True if connection has been established, false if connection
* couldn't be established.
**/
void MAVLinkSkyeSimulationLink::connectLink()
{
    this->connect();
}

/**
* Connect the link.
*
* @param connect true connects the link, false disconnects it
* @return True if connection has been established, false if connection
* couldn't be established.
**/
bool MAVLinkSkyeSimulationLink::connectLink(bool connect)
{
    _isConnected = connect;

    if(connect) {
        this->connect();
    }

    return true;
}

/**
* Check if connection is active.
*
* @return True if link is connected, false otherwise.
**/
bool MAVLinkSkyeSimulationLink::isConnected() const
{
    return _isConnected;
}

int MAVLinkSkyeSimulationLink::getId() const
{
    return id;
}

QString MAVLinkSkyeSimulationLink::getName() const
{
    return name;
}

qint64 MAVLinkSkyeSimulationLink::getTotalUpstream()
{
    return 0;
    //TODO Add functionality here
    // @todo Add functionality here
}

qint64 MAVLinkSkyeSimulationLink::getShortTermUpstream()
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getCurrentUpstream()
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getMaxUpstream()
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getBitsSent() const
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getBitsReceived() const
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getConnectionSpeed() const
{
    /* 100 Mbit is reasonable fast and sufficient for all embedded applications */
    return 100000000;
}

qint64 MAVLinkSkyeSimulationLink::getTotalDownstream()
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getShortTermDownstream()
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getCurrentDownstream()
{
    return 0;
}

qint64 MAVLinkSkyeSimulationLink::getMaxDownstream()
{
    return 0;
}

bool MAVLinkSkyeSimulationLink::isFullDuplex() const
{
    /* Full duplex is no problem when running in pure software, but this is a serial simulation */
    return false;
}

int MAVLinkSkyeSimulationLink::getLinkQuality() const
{
    /* The Link quality is always perfect when running in software */
    return 100;
}

void MAVLinkSkyeSimulationLink::sendMsgBatteryCellsStatus(float voltage) {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    cells.accu_id = battery_pack_id;
    cells.voltage_cell_1 = 1000*(3.88 + sin(3.14159*time_boot/1000.0/10.0)); //(uint16_t)(1000*voltage);
    cells.voltage_cell_2 = (uint16_t)(1000*voltage);  //1000*(3 + cos(time_boot*0.002));
    cells.voltage_cell_3 = (uint16_t)(1000*voltage);  //1000*(3 - sin(time_boot*0.002));
    cells.voltage_cell_4 = (uint16_t)(1000*voltage+05);  //1000*(3 - sin(time_boot*0.002));
    cells.voltage_cell_5 = (uint16_t)(1000*voltage+10);
    cells.voltage_cell_6 = (uint16_t)(1000*voltage-20);

    mavlink_msg_battery_cells_status_encode(systemId, componentId, &msg, &cells);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgBatteryStatus(float voltage) {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    battery.accu_id = battery_pack_id;
    battery.voltage = 6*voltage*1000;
    battery.current = 2120;
    battery.energy = 999;
    if (battery_pack_id == 2) battery.status = (int8_t)time_boot;
    else                      battery.status = BATTERY_STATUS_BIT_ATTACHED | BATTERY_STATUS_BIT_FULL;
    battery.charge = time_boot*0.002;
    battery.time = 200; // seconds

    mavlink_msg_battery_status_encode(systemId, componentId, &msg, &battery);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgAllocationControllerRaw() {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_allocation_controller_raw_t alloc;
    alloc.thrust_1 = 100;
    alloc.thrust_2 = 200;
    alloc.thrust_3 = 300;
    alloc.thrust_4 = 400;
    alloc.pos_1 = 0;
    alloc.pos_2 = 0;
    alloc.pos_3 = 0;
    alloc.pos_4 = 0;
    mavlink_msg_allocation_controller_raw_encode(systemId, componentId, &msg, &alloc);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgActuationStatus() {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_actuation_status_t au_status;
    au_status.au_id = battery_pack_id;
    au_status.status = MAV_ACTUATION_UNIT_STATUS_READY;
    if (battery_pack_id == 1)
        au_status.status = MAV_ACTUATION_UNIT_STATUS_READY;
    if (battery_pack_id == 0)
        au_status.status = MAV_ACTUATION_UNIT_STATUS_READY;
    mavlink_msg_actuation_status_encode(systemId, componentId, &msg, &au_status);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgSysStatus() {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    // Pack message and get size of encoded byte string
    mavlink_msg_sys_status_encode(systemId, componentId, &msg, &status);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgHeartbeat() {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    // Pack message and get size of encoded byte string
    mavlink_msg_heartbeat_pack(systemId, componentId, &msg, system.type, MAV_AUTOPILOT_PX4, system.base_mode, system.custom_mode, system.system_status);
    // Allocate buffer with packet data
    uint16_t bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgStatustext() {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_statustext_t text;
    text.severity = 0;
    QString str = QString("Text message from system %1").arg(systemId);
    strcpy((char*)(text.text), str.toAscii().constData());
    mavlink_msg_statustext_encode(systemId, componentId, &msg, &text);

    this->enqueue(stream, &streampointer, &msg);
}

void MAVLinkSkyeSimulationLink::sendMsgGlobalPositionInt() {
    mavlink_message_t msg;

    // GLOBAL POSITION
    mavlink_msg_global_position_int_pack(systemId, componentId, &msg, 0, (473774.15+(x))*1E3, (85466.12+(y))*1E3, (z)*1000.0,/* (z+550.0)*1000.0*/-1, speedX, speedY, speedZ, yaw);

    this->enqueue(stream, &streampointer, &msg);

}

void MAVLinkSkyeSimulationLink::sendMsgAttitude() {
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_attitude_t attitude;
    attitude.roll = this->roll;
    attitude.pitch = this->pitch;
    attitude.yaw = this->yaw;
    attitude.rollspeed = this->speedRoll;
    attitude.pitchspeed = this->speedPitch;
    attitude.yawspeed = this->speedYaw;

    attitude.time_boot_ms = time_boot/1000;
    // Pack message and get size of encoded byte string
    mavlink_msg_attitude_encode(systemId, componentId, &msg, &attitude);

    this->enqueue(stream, &streampointer, &msg);
}
