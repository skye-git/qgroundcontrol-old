#include <QDebug>
#include <qmath.h>
#include "SkyeMAV.h"
#include "UDPLink.h"

// Use exponential gain
#ifndef QGC_SKYE_USE_SQUARE_OUT
#define QGC_SKYE_USE_SQUARE_OUT
#endif

#ifndef QGC_EARTH_RADIUS
#define QGC_EARTH_RADIUS 6367449.0
#endif

#ifndef QGC_COS_LATITUDE
#define QGC_COS_LATITUDE 0.67716
#endif

#define QGC_SKYE_MAX_VEL_NORM 1.0
#define QGC_SKYE_LOOKAHEAD 2.0

SkyeMAV::SkyeMAV(MAVLinkProtocol* mavlink, int id) :
UAS(mavlink, id),
airframe(QGC_AIRFRAME_SKYE),
manual1Thrust(0),
manual2Thrust(0),
manual3Thrust(0),
manual4Thrust(0),
manual1Orientation(0),
manual2Orientation(0),
manual3Orientation(0),
manual4Orientation(0),
manualXThrust(0),
manualYThrust(0),
manualZThrust(0),
manualXMoment(0),
manualYMoment(0),
manualZMoment(0),
manualXVel(0),
manualYVel(0),
manualZVel(0),
manualXRot(0),
manualYRot(0),
manualZRot(0),
sensitivityFactorTrans(0),
sensitivityFactorRot(0),
currentTrajectoryStamp(0)
{
    imagePacketsArrived = 0;
    this->setUASName("SKYE");
    connect(&trajectoryTimer, SIGNAL(timeout()), this, SLOT(followTrajectory()));
    trajectoryTimer.start(100);
}

SkyeMAV::~SkyeMAV(void)
{
}

void SkyeMAV::receiveMessage(LinkInterface *link, mavlink_message_t message)
{
#ifdef MAVLINK_ENABLED_SKYE
    if (message.sysid == uasId)  // make sure the message is for the right UAV
    {
        if (!link) return;
        switch (message.msgid)
        {
        case MAVLINK_MSG_ID_SKYE_BATTERY_STATUS:
        {
            mavlink_skye_battery_status_t battery;
            mavlink_msg_skye_battery_status_decode(&message, &battery);

            emit batteryPackChanged(&battery);
        }
        break;
        case MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED:
        {
        // Copied from PxQuadMAV.cc
            // FIXME Kind of a hack to load data from disk
            mavlink_skye_cam_image_triggered_t img;
            mavlink_msg_skye_cam_image_triggered_decode(&message, &img);
            emit imageStarted(img.timestamp);
        }
        break;
        case MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE:
        {
            //qDebug() << "RECIEVED ACK TO GET IMAGE";
            mavlink_data_transmission_handshake_t p;
            mavlink_msg_data_transmission_handshake_decode(&message, &p);
            imageSize = p.size;
            imagePackets = p.packets;
            imagePayload = p.payload;
            imageQuality = p.jpg_quality;
            imageType = p.type;
            imageWidth = p.width;
            imageHeight = p.height;
            imageStart = QGC::groundTimeMilliseconds();

            // Reset arrived packages
            imagePacketsArrived = 0;
        }
            break;

        case MAVLINK_MSG_ID_ENCAPSULATED_DATA:
        {
            mavlink_encapsulated_data_t img;
            mavlink_msg_encapsulated_data_decode(&message, &img);
            int seq = img.seqnr;
            int pos = seq * imagePayload;

//            qDebug() << "Seqnr" << img.seqnr;

            // Check if we have a valid transaction
            if (imagePackets == 0)
            {
                // NO VALID TRANSACTION - ABORT
                // Restart statemachine
                imagePacketsArrived = 0;
            }

            for (int i = 0; i < imagePayload; ++i)
            {
                if (pos <= imageSize) {
                    imageRecBuffer[pos] = img.data[i];
                }
                ++pos;
            }
//            qDebug() << "RECIEVED ENCAPSULATED IMAGE, imagePackets:" << imagePackets << "imagePacketsArrived:" << imagePacketsArrived;

            ++imagePacketsArrived;

            // emit signal if all packets arrived
            if ((imagePacketsArrived >= imagePackets))
            {
                // Restart statemachine
                imagePacketsArrived = 0;
                emit imageReady(this);
//                qDebug() << "SKYE imageReady emitted. all packets arrived";
            }
        }
        break;
        case MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE:
        {
            // Save scaled pressure
        }
        case MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS:
        {
        mavlink_skye_cam_reconfigure_bluefox_settings_t bluefox;
        mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(&message, &bluefox);

        emit bluefoxSettingsChanged(&bluefox);

        }
        // Ignore these messages
        case MAVLINK_MSG_ID_SKYE_TEST_MOTORS:
        case MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL:
        case MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL:
//        case MAVLINK_MSG_ID_SKYE_ASSISTED_RC_CONTROL:
        case MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL:
        case MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION:
        case MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT:
        case MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_PROSILICA_SETTINGS:
        case MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_IMAGE_HANDLER:
        case MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT:
        case MAVLINK_MSG_ID_SKYE_HOME_MAXON:
        case MAVLINK_MSG_ID_SKYE_THREAD_COUNTS:
        case MAVLINK_MSG_ID_SKYE_THREAD_USLEEP:
            break;

        default:
        {
            // Let UAS handle the default message set
            UAS::receiveMessage(link, message);
            break;
            }
        }
    }
#else
    // Let UAS handle the default message set
    UAS::receiveMessage(link, message);
    Q_UNUSED(link);
    Q_UNUSED(message);
#endif // MAVLINK_ENABLED_SKYE
}


void SkyeMAV::setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4)
{
#ifdef MAVLINK_ENABLED_SKYE

    sendTestphaseControlCommands(Thrust1, Thrust2, Thrust3, Thrust4, Orientation1, Orientation2, Orientation3, Orientation4);
    qDebug() << "sendTestphaseControlCommands aufgerufen " << Thrust1;

#else
    Q_UNUSED(Thrust1);
    Q_UNUSED(Thrust2);
    Q_UNUSED(Thrust3);
    Q_UNUSED(Thrust4);
    Q_UNUSED(Orientation1);
    Q_UNUSED(Orientation2);
    Q_UNUSED(Orientation3);
    Q_UNUSED(Orientation4);

#endif // MAVLINK_ENABLED_SKYE
}

void SkyeMAV::setManualControlCommands6DoF(double x , double y , double z , double a , double b, double c)
{
#ifdef MAVLINK_ENABLED_SKYE
//    qDebug() << "Recent Mode: " << mode << ": " << getShortModeTextFor(mode);

#ifdef QGC_SKYE_USE_SQUARE_OUT
    x = qPow(x, 3);
    y = qPow(y, 3);
    z = qPow(z, 3);
    a = qPow(a, 3);
    b = qPow(b, 3);
    c = qPow(c, 3);
#endif

    //if (mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY)
    {
        if ((mode == MAV_MODE_DIRECT_CONTROL_DISARMED) || (mode == MAV_MODE_DIRECT_CONTROL_ARMED))
        {
            sendDirectControlCommands(x, y, z, a, b, c);
            qDebug() << "SkyeMAV.cc l.190, sendDirectControlCommands(x,y,z,a,b,c): "<< x <<":"<< y <<":" << z <<":" << a <<":" << b <<":" << c;
        }else if ((mode == MAV_MODE_ASSISTED_CONTROL_DISARMED) || (mode == MAV_MODE_ASSISTED_CONTROL_ARMED))
        {
            sendAssistedControlCommands(x, y, z, a, b, c);
        }else if ((mode == MAV_MODE_HALF_AUTOMATIC_DISARMED) || (mode == MAV_MODE_HALF_AUTOMATIC_ARMED))
        {
            qDebug() << "set Rotation for HAC" << a << b << c;
            manualZVel = z;
            manualXRot = a;
            manualYRot = b;
            manualZRot = c;
        }else
        {
            qDebug() << "6DOF MANUAL CONTROL: IGNORING COMMANDS: Set mode to MANUAL and CUSTOM to send 6 DoF Mouse commands!";
        }
    }

#else
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);
    Q_UNUSED(a);
    Q_UNUSED(b);
    Q_UNUSED(c);
#endif // MAVLINK_ENABLED_SKYE
}

//AL (06.03.12)
void SkyeMAV::sendTestphaseControlCommands(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 )
{
#ifdef MAVLINK_ENABLED_SKYE
    // Scale values (The Testphase widget is designed that no scaling is needed from UI to the machine the value shouldn't change)
    //double thrustScaling = 1.0f;
    //double orientationScaling = 1.0f;

    manual1Thrust = Thrust1;//*thrustScaling;
    manual2Thrust = Thrust2;//*thrustScaling;
    manual3Thrust = Thrust3;//*thrustScaling;
    manual4Thrust = Thrust4;//*thrustScaling;
    manual1Orientation = Orientation1;//*orientationScaling;
    manual2Orientation = Orientation2;//*orientationScaling;
    manual3Orientation = Orientation3;//*orientationScaling;
    manual4Orientation = Orientation4;//*orientationScaling;

    mavlink_message_t message;

    mavlink_msg_skye_test_motors_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (int)manual1Thrust, (int)manual2Thrust, (int)manual3Thrust,(int)manual4Thrust, (int)manual1Orientation, (int)manual2Orientation, (int)manual3Orientation,(int)manual4Orientation);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT TESTPHASE CONTROL MESSAGE: 1Thrust" << manual1Thrust << " 2Thrust: " << manual2Thrust << " 3Thrust: " << manual3Thrust << " 4Thrust: " << manual4Thrust << " 1Orientation: " << manual1Orientation << " 2Orientation: " << manual2Orientation << " 3Orientation: " << manual3Orientation << " 4Orientation: " << manual4Orientation;

    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());


#endif // MAVLINK_ENABLED_SKYE
}

//AL (06.03.12)

void SkyeMAV::sendDirectControlCommands(double xThrust, double yThrust, double zThrust, double xMoment, double yMoment, double zMoment)
{
#ifdef MAVLINK_ENABLED_SKYE
    // Scale values
    float thrustScaling = sensitivityFactorTrans;
    float momentScaling = sensitivityFactorRot;
    
    manualXThrust = xThrust * thrustScaling;
    manualYThrust = yThrust * thrustScaling;
    manualZThrust = zThrust * thrustScaling;
    manualXMoment = xMoment * momentScaling;
    manualYMoment = yMoment * momentScaling;
    manualZMoment = zMoment * momentScaling;
    
    mavlink_message_t message;
    
    mavlink_msg_skye_direct_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)manualXThrust, (float)manualYThrust, (float)manualZThrust, (float)manualXMoment, (float)manualYMoment, (float)manualZMoment);
    sendMessage(message);
//    qDebug() << __FILE__ << __LINE__ << ": SENT DIRECT CONTROL MESSAGE: xThrust" << manualXThrust << " yThrust: " << manualYThrust << " zThrust: " << manualZThrust << " xMoment: " << manualXMoment << " yMoment: " << manualYMoment << " zMoment: " << manualZMoment;
    
    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());
    
#endif // MAVLINK_ENABLED_SKYE
}


void SkyeMAV::sendAssistedControlCommands(double xVel, double yVel, double zVel, double xRot, double yRot, double zRot)
{
#ifdef MAVLINK_ENABLED_SKYE
    // Scale values
    float velScaling = sensitivityFactorTrans;
    float rotScaling = sensitivityFactorRot;
//    qDebug() << rotScaling << "ROTSCALING";
    manualXVel = xVel * velScaling;
    manualYVel = yVel * velScaling;
    manualZVel = zVel * velScaling;
    manualXRot = xRot * rotScaling;
    manualYRot = yRot * rotScaling;
    manualZRot = zRot * rotScaling;
    
    mavlink_message_t message;
    
    mavlink_msg_skye_assisted_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)manualXVel, (float)manualYVel, (float)manualZVel, (float)manualXRot, (float)manualYRot, (float)manualZRot);
    sendMessage(message);
//    qDebug() << __FILE__ << __LINE__ << ": SENT ASSISTED CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
    
    //emit attitudeThrustSetPointChanged(this, roll, pitch, yaw, thrust, MG::TIME::getGroundTimeNow());
    
#endif // MAVLINK_ENABLED_SKYE
}

void SkyeMAV::takeImageShot(MAV_CAM_ID cam)
{
#ifdef MAVLINK_ENABLED_SKYE
    mavlink_message_t message;
    mavlink_msg_skye_cam_take_shot_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, cam, true);
    sendMessage(message);
#endif // MAVLINK_ENABLED_SKYE
}

QImage SkyeMAV::getImage()          // Function copied from UAS.cc (pixhawk)
{
#ifdef MAVLINK_ENABLED_SKYE

    //qDebug() << "getImage: IMAGE TYPE:" << imageType;

    // RAW greyscale
    if (imageType == MAVLINK_DATA_STREAM_IMG_RAW8U)
    {
        // TODO FIXME
        int imgColors = 255;//imageSize/(imageWidth*imageHeight);
        //const int headerSize = 15;

        // Construct PGM header
        QString header("P5\n%1 %2\n%3\n");
        header = header.arg(imageWidth).arg(imageHeight).arg(imgColors);

        QByteArray tmpImage(header.toStdString().c_str(), header.toStdString().size());
        tmpImage.append(imageRecBuffer);

//        qDebug() << "IMAGE SIZE:" << tmpImage.size() << "HEADER SIZE: (15):" << header.size() << "HEADER: " << header;

        if (imageRecBuffer.isNull())
        {
            qDebug()<< "could not convertToPGM()";
            return QImage();
        }
//        qDebug() << "imageRecBuffer (QByteArray):" << imageRecBuffer.toUInt(NULL, 8);
//        qDebug() << "tmpImage (QByteArray):" << tmpImage;
        if (!image.loadFromData(tmpImage, "PGM"))   // PGM: Portable Graymap
        {
            qDebug()<< "could not create extracted image";
            return QImage();
        }

    }
    // BMP with header
    else if (imageType == MAVLINK_DATA_STREAM_IMG_BMP ||
             imageType == MAVLINK_DATA_STREAM_IMG_JPEG ||
             imageType == MAVLINK_DATA_STREAM_IMG_PGM ||
             imageType == MAVLINK_DATA_STREAM_IMG_PNG)
    {
        if (!image.loadFromData(imageRecBuffer))
        {
            qDebug() << "Loading data from skye image buffer failed!";
        }
    }
    // Restart statemachine
    imagePacketsArrived = 0;
    //imageRecBuffer.clear();
    return image;
#else
    return QImage();
#endif

}

void SkyeMAV::sendHomingCommand()
{
#ifdef MAVLINK_ENABLED_SKYE
    mavlink_message_t message;
    uint8_t homing = 1;

    mavlink_msg_skye_home_maxon_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, homing);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT HOMING COMMAND MESSAGE";
#endif // MAVLINK_ENABLED_SKYE
}

void SkyeMAV::sendBluefoxReconfigureCommand(mavlink_skye_cam_reconfigure_bluefox_settings_t* bluefox)
{
    int sentViaUDP = 0;
    foreach (LinkInterface* link, *links)
    {
        if ( dynamic_cast<UDPLink*>(link) )
        {
        mavlink_message_t message;
        mavlink_msg_skye_cam_reconfigure_bluefox_settings_encode(mavlink->getSystemId(), mavlink->getComponentId(), &message, bluefox);
        sendMessage(link, message);
        sentViaUDP++;
        qDebug() << "Sent Bluefox Reconfigure Command to" << name << "via UDPlink";
        }
    }
    if (!sentViaUDP)
    {
        qDebug() << "Sending via UDP failed";
        emit reportUDPLinkFailed("Sending via UDP failed. Not connected.");
    }
}

void SkyeMAV::requestBluefoxSettings()
{
    int sentViaUDP = 0;
    foreach (LinkInterface* link, *links)
    {
        if ( dynamic_cast<UDPLink*>(link) )
        {
            // TODO
//        mavlink_message_t message;
//        mavlink_msg_skye_request_cam_reconfigure_settings_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, bluefox);
//        sendMessage(link, message);
//        sentViaUDP++;
//        qDebug() << "Requested Bluefox Configureations to" << name << "via UDPlink";
        }
    }
    if (!sentViaUDP)
    {
        qDebug() << "Sending via UDP failed";
        emit reportUDPLinkFailed("Sending via UDP failed. Not connected.");
    }
}

uint8_t SkyeMAV::getMode()
{
    return this->mode;
}

void SkyeMAV::followTrajectory()
{
    if (mode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED) // Half or Full Automatic Control
    {
        qDebug() << "SkyeMAV::followTrajectory";
        QVector<double> trajX;
        QVector<double> trajY;
        QVector<double> trajZ;
        waypointManager.getEditableTrajectory()->getVector(trajX, trajY, trajZ);
//if (!(waypointManager.getEditableTrajectory()->getVector(trajX, trajY, trajZ)));
//        {
//            qDebug() << "SkyeMAV: Trajectory empty or not valid";
//            return;
//        }
        if (trajX.isEmpty()){
            return;
        }
        if (trajX.size() <= currentTrajectoryStamp && currentTrajectoryStamp > 0)
        {
            currentTrajectoryStamp = trajX.size() - 1;
        }

        deltaLatLngAlt[0] = trajX.value(currentTrajectoryStamp) - latitude;
        deltaLatLngAlt[1] = trajY.value(currentTrajectoryStamp) - longitude;
        deltaLatLngAlt[2] = trajZ.value(currentTrajectoryStamp) - altitude;

        // Translate to local coordinates
        deltaXYZ[0] = deltaLatLngAlt[0] * 3.141592 / 180.0 * QGC_EARTH_RADIUS * QGC_COS_LATITUDE;
        deltaXYZ[1] = deltaLatLngAlt[1] * 3.141592 / 180.0 * QGC_EARTH_RADIUS;
        deltaXYZ[2] = deltaLatLngAlt[2];

        deltaNorm = qSqrt(deltaXYZ[0]*deltaXYZ[0] + deltaXYZ[1]*deltaXYZ[1] + deltaXYZ[2]+deltaXYZ[2]);
        deltaNorm2D = qSqrt(deltaXYZ[0]*deltaXYZ[0] + deltaXYZ[1]*deltaXYZ[1]);
        //        qDebug() << "Follows point" << currentTrajectoryStamp << "deltaLat" << deltaLatLngAlt[0] << "deltaLng" << deltaLatLngAlt[1] << "deltaAlt" << deltaLatLngAlt[2]<< "altitude" << altitude;
        qDebug() << "deltaX" << deltaXYZ[0] << "deltaY" << deltaXYZ[1] << "deltaZ" << deltaXYZ[2] << "deltaNorm" << deltaNorm;

        InertialToCamera(deltaXYZ, deltaCam);
        qDebug() << "DeltaCam" << deltaCam[0] << deltaCam[1] << deltaCam[2];

        if (mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY /*&& !qIsNaN(deltaCam[0]) && !qIsNaN(deltaCam[1]) && !qIsNaN(deltaCam[2])*/)
        {
            if (mode & MAV_MODE_FLAG_DECODE_POSITION_AUTO) // FULL AUTOMATIC CONTROL
            {
                if ((sensitivityFactorTrans * deltaNorm) < QGC_SKYE_MAX_VEL_NORM)
                {
                    qDebug() << "Send original Assisted Control for FAC";
                    sendAssistedControlCommands(sensitivityFactorTrans * deltaCam[0],
                                                sensitivityFactorTrans * deltaCam[1],
                                                sensitivityFactorTrans * deltaCam[2],
                                                sensitivityFactorRot * manualXRot,
                                                sensitivityFactorRot * manualYRot,
                                                sensitivityFactorRot * manualZRot);
                } else {
                    qDebug() << "Send reduced Assisted Control";
                    sendAssistedControlCommands(sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[0],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[1],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[2],
                                                sensitivityFactorRot * manualXRot,
                                                sensitivityFactorRot * manualYRot,
                                                sensitivityFactorRot * manualZRot);
                }
                if ( deltaNorm < QGC_SKYE_LOOKAHEAD )
                {
                    qDebug() << "REACHED POINT" << currentTrajectoryStamp << "OF TRAJECTORY";
                    if (trajX.size() > currentTrajectoryStamp + 1)
                        currentTrajectoryStamp++;
                }
            }
            else
            {
                if ((sensitivityFactorTrans * deltaNorm2D) < QGC_SKYE_MAX_VEL_NORM)
                {
                    qDebug() << "Send original Assisted Control for FAC";
                    sendAssistedControlCommands(sensitivityFactorTrans * deltaCam[0],
                                                sensitivityFactorTrans * deltaCam[1],
                                                sensitivityFactorTrans * manualZVel,
                                                sensitivityFactorRot * manualXRot,
                                                sensitivityFactorRot * manualYRot,
                                                sensitivityFactorRot * manualZRot);
                } else {
                    qDebug() << "Send reduced Assisted Control";
                    sendAssistedControlCommands(sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm2D * deltaCam[0],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm2D * deltaCam[1],
                                                sensitivityFactorTrans * manualZVel,
                                                sensitivityFactorRot * manualXRot,
                                                sensitivityFactorRot * manualYRot,
                                                sensitivityFactorRot * manualZRot);
                }
                if ( deltaNorm2D < QGC_SKYE_LOOKAHEAD )
                {
                    qDebug() << "REACHED POINT" << currentTrajectoryStamp << "OF TRAJECTORY";
                    if (trajX.size() > currentTrajectoryStamp + 1)
                        currentTrajectoryStamp++;
                }



            }
//            if ((sensitivityFactorTrans * deltaNorm) < 0.2)
//            {
//                sendDirectControlCommands(deltaCam[0],
//                                          deltaCam[1],
//                                          deltaCam[2],
//                                          manualXRot, manualYRot, manualZRot);
//            } else {
//                qDebug() << "Send reduced Direct Control";
//                sendDirectControlCommands(0.2 / ((double)sensitivityFactorTrans * deltaNorm) * deltaCam[0],
//                                          0.2 / ((double)sensitivityFactorTrans * deltaNorm) * deltaCam[1],
//                                          0.2 / ((double)sensitivityFactorTrans * deltaNorm) * deltaCam[2],
//                                          manualXRot, manualYRot, manualZRot);
//            }
        }


    }
}

void SkyeMAV::InertialToCamera(const double inertFrame[3], double camFrame[3])
{
    updateTrigonometry();
    int i = 0;
    int k = 0;
    for (i = 0; i<3; i++)
    {
        camFrame[i] = 0;
        for (k = 0; k<3; k++)
        {
            camFrame[i] += fromItoC[i*3 + k] * inertFrame[k];
        }
    }
}

void SkyeMAV::updateTrigonometry()
{
    cosPhi = qCos(roll);
    sinPhi = qSin(roll);
    cosTheta = qCos(pitch);
    sinTheta = qSin(pitch);
    cosPsi = qCos(yaw);
    sinPsi = qSin(yaw);
    fromItoC[0] = cosTheta*cosPsi;
    fromItoC[1] = cosTheta*sinPsi;
    fromItoC[2] = -sinTheta;
    fromItoC[3] = sinPhi*sinTheta*cosPsi - cosPhi*sinPsi;
    fromItoC[4] = sinPhi*sinTheta*sinPsi + cosPhi*cosPsi;;
    fromItoC[5] = sinPhi*cosTheta;
    fromItoC[6] = cosPhi*sinTheta*cosPsi + sinPhi*sinPsi;
    fromItoC[7] = cosPhi*sinTheta*sinPsi - sinPhi*cosPsi;
    fromItoC[8] = cosPhi*cosTheta;
    qDebug() << "I to C" << fromItoC[0] << fromItoC[1] << fromItoC[2] << fromItoC[3] << fromItoC[4] << fromItoC[5] << fromItoC[6] << fromItoC[7] << fromItoC[8];
}
