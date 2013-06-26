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
*   @brief Implementation of simulated system link
*
*   @author Lorenz Meier <mavteam@student.ethz.ch>
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
#include "MAVLinkSimulationLink.h"
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
MAVLinkSimulationLink::MAVLinkSimulationLink(QString readFile, QString writeFile, int rate, QObject* parent) : LinkInterface(parent),
    readyBytes(0),
    timeOffset(0),
    time_boot(0),
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
    homing(0)
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

MAVLinkSimulationLink::~MAVLinkSimulationLink()
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

void MAVLinkSimulationLink::run()
{
    status.voltage_battery = 0;
    status.errors_comm = 0;

    system.base_mode = MAV_MODE_PREFLIGHT;
    system.custom_mode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
#ifdef QGC_USE_SKYE_INTERFACE
    system.type = MAV_TYPE_AIRSHIP;
#else
    system.custom_mode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
#endif // MAVLINK ENABLED SKYE
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

void MAVLinkSimulationLink::sendMAVLinkMessage(const mavlink_message_t* msg)
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

void MAVLinkSimulationLink::enqueue(uint8_t* stream, uint8_t* index, mavlink_message_t* msg)
{
    // Allocate buffer with packet data
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    unsigned int bufferlength = mavlink_msg_to_send_buffer(buf, msg);
    //add data into datastream
    memcpy(stream+(*index),buf, bufferlength);
    (*index) += bufferlength;
}

void MAVLinkSimulationLink::mainloop()
{

    // Test for encoding / decoding packets

    // Test data stream
    streampointer = 0;

    // Fake system values

    static float fullVoltage = 4.2f * 6.0f - 4.0f;
    static float emptyVoltage = 3.35f * 6.0f;
    static float voltage = fullVoltage;
    static float drainRate = 0.025f; // x.xx% of the capacity is linearly drained per second

    mavlink_attitude_t attitude;
    memset(&attitude, 0, sizeof(mavlink_attitude_t));
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

    // Image transmition sequence number
    static uint16_t seqnr = 0;


    // 50 HZ TASKS
    if (rate50hzCounter == 1000 / rate / 40)
    {

        // ATTITUDE
        attitude.roll = this->roll;          // Beginn Code MA (13.03.2012)
        attitude.pitch = this->pitch;
        attitude.yaw = this->yaw;
        attitude.rollspeed = this->speedRoll;
        attitude.pitchspeed = this->speedPitch;
        attitude.yawspeed = this->speedYaw;                  // Ende Code MA

        attitude.time_boot_ms = time_boot/1000;
        // Pack message and get size of encoded byte string
        mavlink_msg_attitude_encode(systemId, componentId, &msg, &attitude);
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        mavlink_nanotron_skye_node_0_raw_t nano_0;
        nano_0.distance_1 = 4.321f;
        nano_0.distance_2 = 3.21f;
        nano_0.distance_3 = 2.1f;
        nano_0.distance_4 = 1.234f;
        nano_0.distance_5 = 0.0f;
        nano_0.distance_6 = 0.0f;
        mavlink_msg_nanotron_skye_node_0_raw_encode(systemId, MAV_COMP_ID_IMU, &msg, &nano_0);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


        rate50hzCounter = 1;
//        time_boot += 20;
////        qDebug() << "Time since boot: " << time_boot;
    }


    // 10 HZ TASKS
    if (rate10hzCounter == 1000 / rate / 9) {
        rate10hzCounter = 1;

        // Send back new setpoint
        mavlink_message_t ret;
        mavlink_msg_local_position_setpoint_pack(systemId, componentId, &ret, MAV_FRAME_LOCAL_NED, spX, spY, spZ, speedYaw); // spYaw/180.0*M_PI);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // Send back new position
        mavlink_msg_local_position_ned_pack(systemId, componentId, &ret, 0, x, y, -fabs(z), speedX, speedY, speedZ);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // GLOBAL POSITION
        mavlink_msg_global_position_int_pack(systemId, componentId, &ret, 0, (473774.15+(x))*1E3, (85466.12+(y))*1E3, (z)*1000.0,/* (z+550.0)*1000.0*/-1, speedX, speedY, speedZ, yaw);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


#ifdef QGC_USE_SKYE_INTERFACE
        // RETURN 6 DOF CONTROL MSG
        mavlink_setpoint_6dof_t manual;
        manual.trans_x = thrustX;
        manual.trans_y = thrustY;
        manual.trans_z = thrustZ;
        manual.rot_x = momentX;
        manual.rot_y = momentY;
        manual.rot_z = momentZ;
        manual.target_system = systemId;
        mavlink_msg_setpoint_6dof_encode(systemId, MAV_COMP_ID_IMU, &msg, &manual);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // RETURN MANUAL 8DOF COMMAND (Testphase)
        mavlink_setpoint_8dof_t manual_8dof;
        manual_8dof.val1 = thrust1;
        manual_8dof.val2 = thrust2;
        manual_8dof.val3 = thrust3;
        manual_8dof.val4 = thrust4;
        manual_8dof.val5 = orientation1;
        manual_8dof.val6 = orientation2;
        manual_8dof.val7 = orientation3;
        manual_8dof.val8 = orientation4;
        manual_8dof.target_system = systemId;
        mavlink_msg_setpoint_8dof_encode(systemId, MAV_COMP_ID_IMU, &msg, &manual_8dof);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        mavlink_battery_voltage_t volt;
        volt.id = 2;
        volt.voltage_1 = 1010;
        volt.voltage_2 = 1010;
        volt.voltage_3 = 1010;
        volt.voltage_4 = 0;
        volt.battery_remaining = -1;
        mavlink_msg_battery_voltage_encode(systemId, MAV_COMP_ID_IMU, &msg, &volt);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        mavlink_actuation_current_t curr;
        curr.id = 0;
        curr.current_1 = 1010;
        curr.current_2 = 1010;
        curr.current_3 = 1010;
        curr.current_4 = 1010;
        mavlink_msg_actuation_current_encode(systemId, MAV_COMP_ID_IMU, &msg, &curr);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


#endif


    }

    // 1 HZ TASKS
    if (rate1hzCounter == 1000 / rate / 1) {

        status.voltage_battery = voltage * 1000; // millivolts
        status.load = 0;

        // Pack message and get size of encoded byte string
//        messageSize = mavlink_msg_sys_status_encode(systemId, componentId, &msg, &status);

//        // Allocate buffer with packet data
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

        // HEARTBEAT

        // Pack message and get size of encoded byte string
#ifdef QGC_USE_SKYE_INTERFACE                                         // Begin Code MA (24.02.2012)
        messageSize = mavlink_msg_heartbeat_pack(systemId, componentId, &msg, system.type, MAV_AUTOPILOT_PX4, system.base_mode, system.custom_mode, system.system_status);
#else                                                               // Ende Code MA
        messageSize = mavlink_msg_heartbeat_pack(systemId, componentId, &msg, system.type, MAV_AUTOPILOT_ARDUPILOTMEGA, system.base_mode, system.custom_mode, system.system_status);
#endif
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // Vary values

        // VOLTAGE
        // The battery is drained constantly
        voltage = voltage - ((fullVoltage - emptyVoltage) * drainRate / rate);
    //    if (voltage < 3.550f * 3.0f) voltage = 3.550f * 3.0f;

        battery_pack_id = 0;//(int)(0.5*sin(time_boot*0.001)+1);
        mavlink_battery_status_t battery;
        battery.accu_id = battery_pack_id;
        battery.voltage_cell_1 = 1000*voltage;//1000*(3 + sin(time_boot*0.002));
        battery.voltage_cell_2 = 1000*voltage;//1000*(3 + cos(time_boot*0.002));
        battery.voltage_cell_3 = 1000*voltage;//1000*(3 - sin(time_boot*0.002));
        battery.voltage_cell_4 = 0;
        battery.voltage_cell_5 = 0;
        battery.voltage_cell_6 = 0;
        battery.current_battery = 100*2.12;
        battery.battery_remaining = -1;//(int8_t)floor((float)(100 - 0.0005*time_boot));
        mavlink_msg_battery_status_encode(systemId, MAV_COMP_ID_IMU, &msg, &battery);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


        rate1hzCounter = 1;
        seqnr = 0;
    }

    // 20 HZ TASKS
    if (rate20hzCounter == 1000 / rate / 20) {

#ifdef TEMP_QGC_USE_SKYE_INTERFACE
        seqnr++;
        if (seqnr <= 16)
        {
            uint8_t data[253];

//            if (seqnr == 1);
//            {
//                tmpImage.clear();
//                tmpImage.append(tmpFile.readAll());
//            }


            for (int pix=0; pix<253; pix++)
            {
//                data[pix] = tmpImage.remove(0,1).toUInt();
                data[pix] = (uint8_t)(pix*seqnr/4)*sin((double)(time_boot*pix/10));
            }
            // SEND ENCAPSULATED IMAGE
            mavlink_msg_encapsulated_data_pack(systemId, MAV_COMP_ID_CAMERA, &msg, seqnr, data);
            // Allocate buffer with packet data
            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//            qDebug() << "Send package sequence" << seqnr << ":" << data;
            //add data into datastream
            memcpy(stream+streampointer,buffer, bufferlength);
            streampointer += bufferlength;
        }
#endif

        rate20hzCounter = 1;
    }


    // FULL RATE TASKS
    // Default is 50 H


    readyBufferMutex.lock();
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


qint64 MAVLinkSimulationLink::bytesAvailable()
{
    readyBufferMutex.lock();
    qint64 size = readyBuffer.size();
    readyBufferMutex.unlock();
    return size;
}

void MAVLinkSimulationLink::writeBytes(const char* data, qint64 size)
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

#ifdef QGC_USE_SKYE_INTERFACE                             // Beginn Code MA (13.03.2012)
                if ((system.base_mode & MAV_MODE_FLAG_SAFETY_ARMED) &&
                    (mode.base_mode & MAV_MODE_FLAG_SAFETY_ARMED))
                {
                    system.base_mode = mode.base_mode;
                    system.system_status = MAV_STATE_ACTIVE;
                }
                else
                {
                    system.system_status = MAV_STATE_STANDBY;
                    system.base_mode = MAV_MODE_PREFLIGHT;
                }

#endif                                                  // Ende Code MA
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
                bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
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

                // FIXME MAVLINKV10PORTINGNEEDED
//                switch (action.action) {
//                case MAV_ACTION_LAUNCH:
//                    status.status = MAV_STATE_ACTIVE;
//                    status.mode = MAV_MODE_AUTO;
//                    break;
//                case MAV_ACTION_RETURN:
//                    status.status = MAV_STATE_ACTIVE;
//                    break;
//                case MAV_ACTION_MOTORS_START:
//                    status.status = MAV_STATE_ACTIVE;
//                    status.mode = MAV_MODE_LOCKED;
//                    break;
//                case MAV_ACTION_MOTORS_STOP:
//                    status.status = MAV_STATE_STANDBY;
//                    status.mode = MAV_MODE_LOCKED;
//                    break;
//                case MAV_ACTION_EMCY_KILL:
//                    status.status = MAV_STATE_EMERGENCY;
//                    status.mode = MAV_MODE_MANUAL;
//                    break;
//                case MAV_ACTION_SHUTDOWN:
//                    status.status = MAV_STATE_POWEROFF;
//                    status.mode = MAV_MODE_LOCKED;
//                    break;
//                }
            }
            break;
#ifdef MAVLINK_ENABLED_PIXHAWK
            case MAVLINK_MSG_ID_MANUAL_CONTROL: {
                mavlink_manual_control_t control;
                mavlink_msg_manual_control_decode(&msg, &control);
                qDebug() << "\n" << "ROLL:" << control.x << "PITCH:" << control.y;
            }
            break;
#endif
//            case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
//            {
//                qDebug() << "GCS REQUESTED PARAM LIST FROM SIMULATION";
//                mavlink_param_request_list_t read;
//               mavlink_msg_param_request_list_decode(&msg, &read);
//                if (read.target_system == systemId)
//                {
//                    // Output all params
//                    // Iterate through all components, through all parameters and emit them
//                    QMap<QString, float>::iterator i;
//                    // Iterate through all components / subsystems
//                    int j = 0;
//                    for (i = onboardParams.begin(); i != onboardParams.end(); ++i) {
//                        if (j != 5) {
//                            // Pack message and get size of encoded byte string
//                            mavlink_msg_param_value_pack(read.target_system, componentId, &msg, i.key().toStdString().c_str(), i.value(), MAV_PARAM_TYPE_REAL32, onboardParams.size(), j);
//                            // Allocate buffer with packet data
//                            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                            //add data into datastream
//                            memcpy(stream+streampointer,buffer, bufferlength);
//                            streampointer+=bufferlength;
//                        }
//                        j++;
//                    }

//                    qDebug() << "SIMULATION SENT PARAMETERS TO GCS";
//                }
//            }
//                break;
//            case MAVLINK_MSG_ID_PARAM_SET:
//            {
//                // Drop on even milliseconds
//                if (QGC::groundTimeMilliseconds() % 2 == 0)
//                {
//                    qDebug() << "SIMULATION RECEIVED COMMAND TO SET PARAMETER";
//                    mavlink_param_set_t set;
//                    mavlink_msg_param_set_decode(&msg, &set);
//                    //                    if (set.target_system == systemId)
//                    //                    {
//                    QString key = QString((char*)set.param_id);
//                    if (onboardParams.contains(key))
//                    {
//                        onboardParams.remove(key);
//                        onboardParams.insert(key, set.param_value);

//                        // Pack message and get size of encoded byte string
//                        mavlink_msg_param_value_pack(set.target_system, componentId, &msg, key.toStdString().c_str(), set.param_value, MAV_PARAM_TYPE_REAL32, onboardParams.size(), onboardParams.keys().indexOf(key));
//                        // Allocate buffer with packet data
//                        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                        //add data into datastream
//                        memcpy(stream+streampointer,buffer, bufferlength);
//                        streampointer+=bufferlength;
//                    }
//                    //                    }
//                }
//            }
//            break;
//            case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
//            {
//                qDebug() << "SIMULATION RECEIVED COMMAND TO SEND PARAMETER";
//                mavlink_param_request_read_t read;
//                mavlink_msg_param_request_read_decode(&msg, &read);
//                QByteArray bytes((char*)read.param_id, MAVLINK_MSG_PARAM_REQUEST_READ_FIELD_PARAM_ID_LEN);
//                QString key = QString(bytes);
//                if (onboardParams.contains(key))
//                {
//                    float paramValue = onboardParams.value(key);

//                    // Pack message and get size of encoded byte string
//                    mavlink_msg_param_value_pack(read.target_system, componentId, &msg, key.toStdString().c_str(), paramValue, MAV_PARAM_TYPE_REAL32, onboardParams.size(), onboardParams.keys().indexOf(key));
//                    // Allocate buffer with packet data
//                    bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                    //add data into datastream
//                    memcpy(stream+streampointer,buffer, bufferlength);
//                    streampointer+=bufferlength;
//                    //qDebug() << "Sending PARAM" << key;
//                }
//                else if (read.param_index >= 0 && read.param_index < onboardParams.keys().size())
//                {
//                    key = onboardParams.keys().at(read.param_index);
//                    float paramValue = onboardParams.value(key);

//                    // Pack message and get size of encoded byte string
//                    mavlink_msg_param_value_pack(read.target_system, componentId, &msg, key.toStdString().c_str(), paramValue, MAV_PARAM_TYPE_REAL32, onboardParams.size(), onboardParams.keys().indexOf(key));
//                    // Allocate buffer with packet data
//                    bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                    //add data into datastream
//                    memcpy(stream+streampointer,buffer, bufferlength);
//                    streampointer+=bufferlength;
//                    //qDebug() << "Sending PARAM #ID" << (read.param_index) << "KEY:" << key;
//                }
//            }
//            break;

            // Beginn Code MA (09.03.2012)
            case MAVLINK_MSG_ID_SETPOINT_6DOF: {
                mavlink_setpoint_6dof_t m6c;
                mavlink_msg_setpoint_6dof_decode(&msg, &m6c);
                if (m6c.target_system == this->systemId) {
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
            }
            break;      // Ende Code MA (09.03.2012)
            }
        }
        unsigned char v=data[i];
        fprintf(stderr,"%02x ", v);
    }
    fprintf(stderr,"\n");

    readyBufferMutex.lock();
    for (int i = 0; i < streampointer; i++)
    {
        readyBuffer.enqueue(*(stream + i));
    }
    readyBufferMutex.unlock();

    // Update comm status
    status.errors_comm = comm.packet_rx_drop_count;
}


void MAVLinkSimulationLink::readBytes()
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
bool MAVLinkSimulationLink::disconnect()
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
bool MAVLinkSimulationLink::connect()
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
void MAVLinkSimulationLink::connectLink()
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
bool MAVLinkSimulationLink::connectLink(bool connect)
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
bool MAVLinkSimulationLink::isConnected()
{
    return _isConnected;
}

int MAVLinkSimulationLink::getId()
{
    return id;
}

QString MAVLinkSimulationLink::getName()
{
    return name;
}

qint64 MAVLinkSimulationLink::getNominalDataRate()
{
    /* 100 Mbit is reasonable fast and sufficient for all embedded applications */
    return 100000000;
}

qint64 MAVLinkSimulationLink::getTotalUpstream()
{
    return 0;
    //TODO Add functionality here
    // @todo Add functionality here
}

qint64 MAVLinkSimulationLink::getShortTermUpstream()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getCurrentUpstream()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getMaxUpstream()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getBitsSent()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getBitsReceived()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getTotalDownstream()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getShortTermDownstream()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getCurrentDownstream()
{
    return 0;
}

qint64 MAVLinkSimulationLink::getMaxDownstream()
{
    return 0;
}

bool MAVLinkSimulationLink::isFullDuplex()
{
    /* Full duplex is no problem when running in pure software, but this is a serial simulation */
    return false;
}

int MAVLinkSimulationLink::getLinkQuality()
{
    /* The Link quality is always perfect when running in software */
    return 100;
}

