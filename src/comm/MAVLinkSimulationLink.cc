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
#ifdef MAVLINK_ENABLED_SKYE
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

    static float fullVoltage = 4.2f * 3.0f;
    static float emptyVoltage = 3.35f * 3.0f;
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
    static unsigned int circleCounter = 0;

    // Image transmition sequence number
    static uint16_t seqnr = 0;

    // Vary values

    // VOLTAGE
    // The battery is drained constantly
    voltage = voltage - ((fullVoltage - emptyVoltage) * drainRate / rate);
    if (voltage < 3.550f * 3.0f) voltage = 3.550f * 3.0f;

//    static int state = 0;

//    if (state == 0)
//    {
//        state++;
//    }


    // 50 HZ TASKS
    if (rate50hzCounter == 1000 / rate / 40)
    {
//        if (simulationFile->isOpen())
//        {
//            if (simulationFile->atEnd()) {
//                // We reached the end of the file, start from scratch
//                simulationFile->reset();
//                simulationHeader = simulationFile->readLine();
//            }

//            // Data was made available, read one line
//            // first entry is the timestamp
//            QString values = QString(simulationFile->readLine());
//            QStringList parts = values.split("\t");
//            QStringList keys = simulationHeader.split("\t");
//            //qDebug() << simulationHeader;
//            //qDebug() << values;
//            bool ok;
//            static quint64 lastTime = 0;
//            static quint64 baseTime = 0;
//            quint64 time = QString(parts.first()).toLongLong(&ok, 10);
//            // FIXME Remove multiplicaton by 1000
//            time *= 1000;

//            if (ok) {
//                if (timeOffset == 0) {
//                    timeOffset = time;
//                    baseTime = time;
//                }

//                if (lastTime > time) {
//                    // We have wrapped around in the logfile
//                    // Add the measurement time interval to the base time
//                    baseTime += lastTime - timeOffset;
//                }
//                lastTime = time;

//                time = time - timeOffset + baseTime;

//                // Gather individual measurement values
//                for (int i = 1; i < (parts.size() - 1); ++i) {
//                    // Get one data field
//                    bool res;
//                    double d = QString(parts.at(i)).toDouble(&res);
//                    if (!res) d = 0;

//                    if (keys.value(i, "") == "Accel._X") {
//                        rawImuValues.xacc = d;
//                    }

//                    if (keys.value(i, "") == "Accel._Y") {
//                        rawImuValues.yacc = d;
//                    }

//                    if (keys.value(i, "") == "Accel._Z") {
//                        rawImuValues.zacc = d;
//                    }
//                    if (keys.value(i, "") == "Gyro_Phi") {
//                        rawImuValues.xgyro = d;
//                        attitude.rollspeed = ((d-29.000)/15000.0)*2.7-2.7-2.65;
//                    }

//                    if (keys.value(i, "") == "Gyro_Theta") {
//                        rawImuValues.ygyro = d;
//                        attitude.pitchspeed = ((d-29.000)/15000.0)*2.7-2.7-2.65;
//                    }

//                    if (keys.value(i, "") == "Gyro_Psi") {
//                        rawImuValues.zgyro = d;
//                        attitude.yawspeed = ((d-29.000)/3000.0)*2.7-2.7-2.65;
//                    }
//#ifdef MAVLINK_ENABLED_PIXHAWK
//                    if (keys.value(i, "") == "Pressure") {
//                        rawAuxValues.baro = d;
//                    }

//                    if (keys.value(i, "") == "Battery") {
//                        rawAuxValues.vbat = d;
//                    }
//#endif
//                    if (keys.value(i, "") == "roll_IMU") {
//                        attitude.roll = d;
//                    }

//                    if (keys.value(i, "") == "pitch_IMU") {
//                        attitude.pitch = d;
//                    }

//                    if (keys.value(i, "") == "yaw_IMU") {
//                        attitude.yaw = d;
//                    }

//                    //Accel._X	Accel._Y	Accel._Z	Battery	Bottom_Rotor	CPU_Load	Ground_Dist.	Gyro_Phi	Gyro_Psi	Gyro_Theta	Left_Servo	Mag._X	Mag._Y	Mag._Z	Pressure	Right_Servo	Temperature	Top_Rotor	pitch_IMU	roll_IMU	yaw_IMU

//                }
//                // Send out packets


//                // ATTITUDE

//                attitude.time_boot_ms = time/1000;
//                // Pack message and get size of encoded byte string
//                mavlink_msg_attitude_encode(systemId, componentId, &msg, &attitude);
//                // Allocate buffer with packet data
//                bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                //add data into datastream
//                memcpy(stream+streampointer,buffer, bufferlength);
//                streampointer += bufferlength;

//                // IMU
//                rawImuValues.time_usec = time;
//                rawImuValues.xmag = 0;
//                rawImuValues.ymag = 0;
//                rawImuValues.zmag = 0;
//                // Pack message and get size of encoded byte string
//                mavlink_msg_raw_imu_encode(systemId, componentId, &msg, &rawImuValues);
//                // Allocate buffer with packet data
//                bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//                //add data into datastream
//                memcpy(stream+streampointer,buffer, bufferlength);
//                streampointer += bufferlength;

//                //qDebug() << "ATTITUDE" << "BUF LEN" << bufferlength << "POINTER" << streampointer;

//                //qDebug() << "REALTIME" << QGC::groundTimeMilliseconds() << "ONBOARDTIME" << attitude.msec << "ROLL" << attitude.roll;

//            }

//        }

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


        rate50hzCounter = 1;
        time_boot += 20;
//        qDebug() << "Time since boot: " << time_boot;
    }


    // 10 HZ TASKS
    if (rate10hzCounter == 1000 / rate / 9) {
        rate10hzCounter = 1;

//        double lastX = x;
//        double lastY = y;
//        double lastZ = z;
//        double hackDt = 0.1f; // 100 ms

//        // Move X Position
//        x = 7.0*sin(((double)circleCounter)/200.0);
//        y = 5.0*cos(((double)circleCounter)/200.0);
//        z = 1.8 + 1.2*sin(((double)circleCounter)/200.0);

//        double xSpeed = (x - lastX)/hackDt;
//        double ySpeed = (y - lastY)/hackDt;
//        double zSpeed = (z - lastZ)/hackDt;

        circleCounter++;


//        x = (x > 5.0f) ? 5.0f : x;
//        y = (y > 5.0f) ? 5.0f : y;
//        z = (z > 3.0f) ? 3.0f : z;

//        x = (x < -5.0f) ? -5.0f : x;
//        y = (y < -5.0f) ? -5.0f : y;
//        z = (z < -3.0f) ? -3.0f : z;

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

//        // GPS RAW
//        mavlink_msg_gps_raw_pack(systemId, componentId, &ret, 0, 3, 47.376417+(x*0.00001), 8.548103+(y*0.00001), z, 0, 0, 2.5f, 0.1f);
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

        // GLOBAL POSITION
        mavlink_msg_global_position_int_pack(systemId, componentId, &ret, 0, (473780.28137103+(x))*1E3, (85489.9892510421+(y))*1E3, (z+550.0)*1000.0, (z+550.0)*1000.0-1, speedX, speedY, speedZ, yaw);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

//        // GLOBAL POSITION VEHICLE 2
//        mavlink_msg_global_position_int_pack(systemId+1, componentId+1, &ret, 0, (473780.28137103+(x+0.00001))*1E3, (85489.9892510421+((y/2)+0.00001))*1E3, (z+550.0)*1000.0, (z+550.0)*1000.0-1, xSpeed, ySpeed, zSpeed, yaw);
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

//        // ATTITUDE VEHICLE 2
//        mavlink_msg_attitude_pack(54, MAV_COMP_ID_IMU, &ret, 0, 0, 0, atan2((y/2)+0.3, (x+0.002)), 0, 0, 0);
//        sendMAVLinkMessage(&ret);


//        // GLOBAL POSITION VEHICLE 3
//        mavlink_msg_global_position_int_pack(60, componentId, &ret, 0, (473780.28137103+(x/2+0.002))*1E3, (85489.9892510421+((y*2)+0.3))*1E3, (z+590.0)*1000.0, 0*100.0, 0*100.0, 0*100.0);
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &ret);
//        //add data into datastream
//        memcpy(stream+streampointer,buffer, bufferlength);
//        streampointer += bufferlength;

        static int rcCounter = 0;
        if (rcCounter == 2) {
            mavlink_rc_channels_raw_t chan;
            chan.time_boot_ms = 0;
            chan.port = 0;
            chan.chan1_raw = 1000 + ((int)(fabs(x) * 1000) % 2000);
            chan.chan2_raw = 1000 + ((int)(fabs(y) * 1000) % 2000);
            chan.chan3_raw = 1000 + ((int)(fabs(z) * 1000) % 2000);
            chan.chan4_raw = (chan.chan1_raw + chan.chan2_raw) / 2.0f;
            chan.chan5_raw = (chan.chan3_raw + chan.chan4_raw) / 2.0f;
            chan.chan6_raw = (chan.chan3_raw + chan.chan2_raw) / 2.0f;
            chan.chan7_raw = (chan.chan4_raw + chan.chan2_raw) / 2.0f;
            chan.chan8_raw = 0;
            chan.rssi = 100;
            messageSize = mavlink_msg_rc_channels_raw_encode(systemId, componentId, &msg, &chan);
            // Allocate buffer with packet data
            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
            //add data into datastream
            memcpy(stream+streampointer,buffer, bufferlength);
            streampointer += bufferlength;
            rcCounter = 0;
        }
        rcCounter++;

#ifdef MAVLINK_ENABLED_SKYE
        // RETURN DIRECT CONTROL MESSAGE
        mavlink_skye_direct_control_t direct;
        direct.thrust_x = thrustX;
        direct.thrust_y = thrustY;
        direct.thrust_z = thrustZ;
        direct.moment_x = momentX;
        direct.moment_y = momentY;
        direct.moment_z = momentZ;
        direct.target_system = systemId;
        mavlink_msg_skye_direct_control_encode(systemId, MAV_COMP_ID_IMU, &msg, &direct);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // RETURN ASSISTED CONTROL MESSAGE
        mavlink_skye_assisted_control_t assisted;
        assisted.translation_lat = transX;
        assisted.translation_long = transY;
        assisted.translation_alt = transZ;
        assisted.rotation_x = rotX;
        assisted.rotation_y = rotY;
        assisted.rotation_z = rotZ;
        assisted.target_system = systemId;
        mavlink_msg_skye_assisted_control_encode(systemId, MAV_COMP_ID_IMU, &msg, &assisted);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

        // RETURN TESTPHASE CONTROL MESSAGE
        mavlink_skye_test_motors_t testmotors;
        testmotors.thrust_1 = thrust1;
        testmotors.thrust_2 = thrust2;
        testmotors.thrust_3 = thrust3;
        testmotors.thrust_4 = thrust4;
        testmotors.direct_1  = orientation1;
        testmotors.direct_2 = orientation2;
        testmotors.direct_3 = orientation3;
        testmotors.direct_4 = orientation4;
        testmotors.target_system = systemId;
        mavlink_msg_skye_test_motors_encode(systemId, MAV_COMP_ID_IMU, &msg, &testmotors);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;
        //qDebug() << "Return Testphase control message";
        //qDebug() << "testmotors.thrust_1"<< testmotors.thrust_1;

        battery_pack_id++;
        if (battery_pack_id >= 4){
            battery_pack_id = 0;
        }
        mavlink_skye_battery_status_t battery;
        battery.accu_id = battery_pack_id;
        battery.voltage_cell_1 = 1000*(3 + sin(time_boot*0.01));
        battery.voltage_cell_2 = 1000*(3 + cos(time_boot*0.01));
        battery.voltage_cell_3 = 1000*(3 - sin(time_boot*0.01));
        battery.voltage_cell_4 = 1000*(3 + cos(time_boot*0.01));
        battery.current_battery = 100*2.12;
        battery.battery_remaining = (int8_t)round(100 - 0.0005*time_boot);
        mavlink_msg_skye_battery_status_encode(systemId, MAV_COMP_ID_IMU, &msg, &battery);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

//        qDebug() << "Sent battery status message...";

        // RETURN HOME_MAXON MESSAGE
        mavlink_skye_home_maxon_t homemaxon;
        homemaxon.homing = homing;
        mavlink_msg_skye_home_maxon_encode(systemId, MAV_COMP_ID_IMU, &msg, &homemaxon);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer, buffer, bufferlength);
        streampointer += bufferlength;

        //qDebug() << "Sent HOME_MAXON message....";

        mavlink_skye_cam_image_triggered_t image;
        image.timestamp = (uint64_t)(battery_pack_id);
        image.lat = (473780.28137103+(x))*1E3;
        image.lon = (85489.9892510421+(y))*1E3;
        image.alt = (z+550.0)*1000.0;
        image.roll = roll;
        image.pitch = pitch;
        image.yaw = yaw;
        mavlink_msg_skye_cam_image_triggered_encode(systemId, MAV_COMP_ID_IMU, &msg, &image);
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

#endif


    }

    // 1 HZ TASKS
    if (rate1hzCounter == 1000 / rate / 1) {
        // STATE
//        static int statusCounter = 0;
//        if (statusCounter == 100) {
//            system.base_mode = (system.base_mode + 1) % MAV_MODE_ENUM_END;
//            statusCounter = 0;
//        }
//        statusCounter++;

        static int detectionCounter = 6;
        if (detectionCounter % 10 == 0) {
#ifdef MAVLINK_ENABLED_PIXHAWK
            mavlink_pattern_detected_t detected;
            detected.confidence = 5.0f;

            if (detectionCounter == 10) {
                char fileName[] = "patterns/face5.png";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 0; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 20) {
                char fileName[] = "7";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 1; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 30) {
                char fileName[] = "patterns/einstein.bmp";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 0; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 40) {
                char fileName[] = "F";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 1; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 50) {
                char fileName[] = "patterns/face2.png";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 0; // 0: Pattern, 1: Letter
            } else if (detectionCounter == 60) {
                char fileName[] = "H";
                memcpy(detected.file, fileName, sizeof(fileName));
                detected.type = 1; // 0: Pattern, 1: Letter
                detectionCounter = 0;
            }
            detected.detected = 1;
            messageSize = mavlink_msg_pattern_detected_encode(systemId, componentId, &msg, &detected);
            // Allocate buffer with packet data
            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
            //add data into datastream
            memcpy(stream+streampointer,buffer, bufferlength);
            streampointer += bufferlength;
            //detectionCounter = 0;
#endif
        }
        detectionCounter++;



        status.voltage_battery = voltage * 1000; // millivolts
        status.load = 33 * detectionCounter % 1000;

        // Pack message and get size of encoded byte string
        messageSize = mavlink_msg_sys_status_encode(systemId, componentId, &msg, &status);

        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;

//        // Pack debug text message
//        mavlink_statustext_t text;
//        text.severity = 0;
//        strcpy((char*)(text.text), "Text message from system 32");
//        mavlink_msg_statustext_encode(systemId, componentId, &msg, &text);
//        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
//        memcpy(stream+streampointer, buffer, bufferlength);
//        streampointer += bufferlength;

        /*
        // Pack message and get size of encoded byte string
        messageSize = mavlink_msg_boot_pack(systemId, componentId, &msg, version);
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;*/

        // HEARTBEAT

        // Pack message and get size of encoded byte string
#ifdef MAVLINK_ENABLED_SKYE                                         // Begin Code MA (24.02.2012)
        messageSize = mavlink_msg_heartbeat_pack(systemId, componentId, &msg, system.type, MAV_AUTOPILOT_SKYE, system.base_mode, system.custom_mode, system.system_status);
#else                                                               // Ende Code MA
        messageSize = mavlink_msg_heartbeat_pack(systemId, componentId, &msg, system.type, MAV_AUTOPILOT_ARDUPILOTMEGA, system.base_mode, system.custom_mode, system.system_status);
#endif
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //qDebug() << "CRC:" << msg.ck_a << msg.ck_b;
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


        mavlink_msg_data_transmission_handshake_pack(systemId, componentId, &msg, DATA_TYPE_RAW_IMAGE, 1012, 46, 22, 4, 253, 0);
        // Allocate buffer with packet data
        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
        //qDebug() << "CRC:" << msg.ck_a << msg.ck_b;
        //add data into datastream
        memcpy(stream+streampointer,buffer, bufferlength);
        streampointer += bufferlength;


        rate1hzCounter = 1;
        seqnr = 0;
    }

    // 20 HZ TASKS
    if (rate20hzCounter == 1000 / rate / 20) {
        seqnr++;
        switch (seqnr)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        {
            uint8_t data[253];
            for (int pix=0; pix<253; pix++)
            {
                data[pix] = (uint8_t)(pix*seqnr/4);
            }
            // SEND ENCAPSULATED IMAGE
            mavlink_msg_encapsulated_data_pack(systemId, MAV_COMP_ID_CAMERA, &msg, seqnr, data);
            // Allocate buffer with packet data
            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
            qDebug() << "Send package sequence" << seqnr << ":" << data;
            //add data into datastream
            memcpy(stream+streampointer,buffer, bufferlength);
            streampointer += bufferlength;
        }
        break;
        default:
            break;
        }
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
            qDebug() << "SIMULATION LINK RECEIVED MESSAGE!";
            emit messageReceived(msg);

            switch (msg.msgid)
            {
                // SET THE SYSTEM MODE
            case MAVLINK_MSG_ID_SET_MODE:
            {
                mavlink_set_mode_t mode;
                mavlink_msg_set_mode_decode(&msg, &mode);
                // Set mode indepent of mode.target
                system.base_mode = mode.base_mode;
#ifdef MAVLINK_ENABLED_SKYE                             // Beginn Code MA (13.03.2012)
                if (system.base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY)
                {
                    system.system_status = MAV_STATE_ACTIVE;
                }
                else
                {
                    system.system_status = MAV_STATE_STANDBY;
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
                qDebug() << "\n" << "ROLL:" << control.roll << "PITCH:" << control.pitch;
            }
            break;
#endif
            case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
            {
                qDebug() << "GCS REQUESTED PARAM LIST FROM SIMULATION";
                mavlink_param_request_list_t read;
                mavlink_msg_param_request_list_decode(&msg, &read);
                if (read.target_system == systemId)
                {
                    // Output all params
                    // Iterate through all components, through all parameters and emit them
                    QMap<QString, float>::iterator i;
                    // Iterate through all components / subsystems
                    int j = 0;
                    for (i = onboardParams.begin(); i != onboardParams.end(); ++i) {
                        if (j != 5) {
                            // Pack message and get size of encoded byte string
                            mavlink_msg_param_value_pack(read.target_system, componentId, &msg, i.key().toStdString().c_str(), i.value(), MAVLINK_TYPE_FLOAT, onboardParams.size(), j);
                            // Allocate buffer with packet data
                            bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                            //add data into datastream
                            memcpy(stream+streampointer,buffer, bufferlength);
                            streampointer+=bufferlength;
                        }
                        j++;
                    }

                    qDebug() << "SIMULATION SENT PARAMETERS TO GCS";
                }
            }
                break;
            case MAVLINK_MSG_ID_PARAM_SET:
            {
                // Drop on even milliseconds
                if (QGC::groundTimeMilliseconds() % 2 == 0)
                {
                    qDebug() << "SIMULATION RECEIVED COMMAND TO SET PARAMETER";
                    mavlink_param_set_t set;
                    mavlink_msg_param_set_decode(&msg, &set);
                    //                    if (set.target_system == systemId)
                    //                    {
                    QString key = QString((char*)set.param_id);
                    if (onboardParams.contains(key))
                    {
                        onboardParams.remove(key);
                        onboardParams.insert(key, set.param_value);

                        // Pack message and get size of encoded byte string
                        mavlink_msg_param_value_pack(set.target_system, componentId, &msg, key.toStdString().c_str(), set.param_value, MAVLINK_TYPE_FLOAT, onboardParams.size(), onboardParams.keys().indexOf(key));
                        // Allocate buffer with packet data
                        bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                        //add data into datastream
                        memcpy(stream+streampointer,buffer, bufferlength);
                        streampointer+=bufferlength;
                    }
                    //                    }
                }
            }
            break;
            case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
            {
                qDebug() << "SIMULATION RECEIVED COMMAND TO SEND PARAMETER";
                mavlink_param_request_read_t read;
                mavlink_msg_param_request_read_decode(&msg, &read);
                QByteArray bytes((char*)read.param_id, MAVLINK_MSG_PARAM_REQUEST_READ_FIELD_PARAM_ID_LEN);
                QString key = QString(bytes);
                if (onboardParams.contains(key))
                {
                    float paramValue = onboardParams.value(key);

                    // Pack message and get size of encoded byte string
                    mavlink_msg_param_value_pack(read.target_system, componentId, &msg, key.toStdString().c_str(), paramValue, MAVLINK_TYPE_FLOAT, onboardParams.size(), onboardParams.keys().indexOf(key));
                    // Allocate buffer with packet data
                    bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                    //add data into datastream
                    memcpy(stream+streampointer,buffer, bufferlength);
                    streampointer+=bufferlength;
                    //qDebug() << "Sending PARAM" << key;
                }
                else if (read.param_index >= 0 && read.param_index < onboardParams.keys().size())
                {
                    key = onboardParams.keys().at(read.param_index);
                    float paramValue = onboardParams.value(key);

                    // Pack message and get size of encoded byte string
                    mavlink_msg_param_value_pack(read.target_system, componentId, &msg, key.toStdString().c_str(), paramValue, MAVLINK_TYPE_FLOAT, onboardParams.size(), onboardParams.keys().indexOf(key));
                    // Allocate buffer with packet data
                    bufferlength = mavlink_msg_to_send_buffer(buffer, &msg);
                    //add data into datastream
                    memcpy(stream+streampointer,buffer, bufferlength);
                    streampointer+=bufferlength;
                    //qDebug() << "Sending PARAM #ID" << (read.param_index) << "KEY:" << key;
                }
            }
            break;

            // Beginn Code MA (09.03.2012)
            case MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL: {
                mavlink_skye_direct_control_t dc;
                mavlink_msg_skye_direct_control_decode(&msg, &dc);
                if (dc.target_system == this->systemId) {
                    qDebug() << "thrust x: " << dc.thrust_x << "------------------------------------------";
                    thrustX = dc.thrust_x;
                    thrustY = dc.thrust_y;
                    thrustZ = dc.thrust_z;
                    momentX = dc.moment_x;
                    momentY = dc.moment_y;
                    momentZ = dc.moment_z;
                    // thrustX = 42;
                    // Set ATTITUDE also with direct control
                    float lastRoll = roll;
                    float lastPitch = pitch;
                    float lastYaw = yaw;
                    float lastX = x;
                    float lastY = y;
                    float lastZ = z;

                    speedRoll = -1.5*dc.moment_x;
                    speedPitch = 1.5*dc.moment_y;
                    speedYaw = 1.5*dc.moment_z;
                    speedX = 10*dc.thrust_x;
                    speedY = 10*dc.thrust_y;
                    speedZ = 10*dc.thrust_z;

                    float dTime = 0.01;
                    roll = lastRoll + speedRoll*dTime;
                    pitch = lastPitch + speedPitch*dTime;
                    yaw = lastYaw + speedYaw*dTime;
                    x = lastX + cos(yaw)*speedX*dTime - sin(yaw)*speedY*dTime;
                    y = lastY + sin(yaw)*speedX*dTime + cos(yaw)*speedY*dTime;
                    z = lastZ + speedZ*dTime;
                }
            }
            break;
            case MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL: {
                mavlink_skye_assisted_control_t ac;
                mavlink_msg_skye_assisted_control_decode(&msg, &ac);
                if (ac.target_system == this->systemId) {
                    transX = ac.translation_lat;
                    transY = ac.translation_long;
                    transZ = ac.translation_alt;
                    rotX = ac.rotation_x;
                    rotY = ac.rotation_y;
                    rotZ = ac.rotation_z;

                    // Set ATTITUDE also with direct control
                    float lastRoll = roll;
                    float lastPitch = pitch;
                    float lastYaw = yaw;

                    roll = -3.14159*ac.rotation_x;
                    pitch = 3.14159*ac.rotation_y;
                    yaw = 3.14159*ac.rotation_z;

                    float dTime = 0.01;
                    speedRoll = (roll - lastRoll)/dTime;
                    speedPitch = (pitch - lastPitch)/dTime;
                    speedYaw = (yaw - lastYaw)/dTime;
                }
            }
            break;
            case MAVLINK_MSG_ID_SKYE_TEST_MOTORS: {
                mavlink_skye_test_motors_t tm;
                mavlink_msg_skye_test_motors_decode(&msg, &tm);
                if (tm.target_system == this->systemId) {
                    thrust1 = tm.thrust_1;        //Testphase Control
                    thrust2 = tm.thrust_2;
                    thrust3 = tm.thrust_3;
                    thrust4 = tm.thrust_4;
                    orientation1 = tm.direct_1;
                    orientation2 =tm.direct_2;
                    orientation3 = tm.direct_3;
                    orientation4 = tm.direct_4;
                }
            }
            break;      // Ende Code MA (09.03.2012)
            case MAVLINK_MSG_ID_SKYE_HOME_MAXON: {
                mavlink_skye_home_maxon_t hm;
                mavlink_msg_skye_home_maxon_decode(&msg, &hm);
                if (hm.target_system == this->systemId) {
                    homing = hm.homing;
                }
            }
            break;      // Ende Code AL (19.03.2012)
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
