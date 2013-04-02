#include <QDebug>
#include <qmath.h>
#include "SkyeMAV.h"
#include "UDPLink.h"

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
    currentTrajectoryStamp(0),
    inputMode(QGC_INPUT_MODE_TOUCH)
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
#ifdef QGC_USE_SKYE_INTERFACE
    if (message.sysid == uasId)  // make sure the message is for the right UAV
    {
        if (!link) return;
        switch (message.msgid)
        {
        case MAVLINK_MSG_ID_BATTERY_STATUS:
        {
            mavlink_battery_status_t battery;
            mavlink_msg_battery_status_decode(&message, &battery);

            emit batteryPackChanged(&battery);
        }
        break;
#ifdef TEMP_MAVLINK_ENABLE_SKYE
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
#endif

        // Ignore these messages
        case MAVLINK_MSG_ID_SETPOINT_6DOF:
        case MAVLINK_MSG_ID_SETPOINT_8DOF:
            break;

        default:
        {
            // Let UAS handle the default message set
            UAS::receiveMessage(link, message);
        }
        break;
        }
    }
#else
    // Let UAS handle the default message set
    UAS::receiveMessage(link, message);
    Q_UNUSED(link);
    Q_UNUSED(message);
#endif // QGC_USE_SKYE_INTERFACE
}

void SkyeMAV::setManual6DOFControlCommands(double x , double y , double z , double a , double b, double c)
{
#ifdef QGC_USE_SKYE_INTERFACE

    if (mode & MAV_MODE_FLAG_GUIDED_ENABLED)
    {
        manualXRot = a * sensitivityFactorRot;
        manualYRot = b * sensitivityFactorRot;
        manualZRot = c * sensitivityFactorRot;
        qDebug() << "Set manual rotation for FAC" << a << b << c;

    }else if (mode & MAV_MODE_FLAG_AUTO_ENABLED)
    {
        manualZVel = z * sensitivityFactorTrans;
        manualXRot = a * sensitivityFactorRot;
        manualYRot = b * sensitivityFactorRot;
        manualZRot = c * sensitivityFactorRot;
        qDebug() << "Set lift and manual rotation for HAC" << z << a << b << c;

    }else if (mode & MAV_MODE_FLAG_MANUAL_INPUT_ENABLED)
    {
        manualXVel = x * sensitivityFactorTrans;
        manualYVel = y * sensitivityFactorTrans;
        manualZVel = z * sensitivityFactorTrans;
        manualXRot = a * sensitivityFactorRot;
        manualYRot = b * sensitivityFactorRot;
        manualZRot = c * sensitivityFactorRot;
        sendManualControlCommands6DoF(manualXVel, manualYVel, manualZVel, manualXRot, manualYRot, manualZRot);
        //    qDebug() << __FILE__ << __LINE__ << ": SENT 6DOF CONTROL MESSAGE: x velocity" << manualXVel << " y velocity: " << manualYVel << " z velocity: " << manualZVel << " x rotation: " << manualXRot << " y rotation: " << manualYRot << " z rotation: " << manualZRot;
    }

#else
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);
    Q_UNUSED(a);
    Q_UNUSED(b);
    Q_UNUSED(c);
#endif // QGC_USE_SKYE_INTERFACE
}

void SkyeMAV::sendManualControlCommands6DoF(double x, double y, double z, double phi, double theta, double psi)
{
#ifdef QGC_USE_SKYE_INTERFACE

    mavlink_message_t message;
    mavlink_msg_setpoint_6dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId, (float)x, (float)y, (float)z, (float)phi, (float)theta, (float)psi);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT 6DOF CONTROL MESSAGE:" << x << y << z << phi << theta << psi;

#else
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);
    Q_UNUSED(phi);
    Q_UNUSED(theta);
    Q_UNUSED(psi);
#endif // QGC_USE_SKYE_INTERFACE
}

void SkyeMAV::setTestphaseCommandsByWidget(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4)
{
#ifdef QGC_USE_SKYE_INTERFACE

    sendManualControlCommands8DoF(Thrust1, Thrust2, Thrust3, Thrust4, Orientation1, Orientation2, Orientation3, Orientation4);
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

#endif // QGC_USE_SKYE_INTERFACE
}

void SkyeMAV::sendManualControlCommands8DoF(int Thrust1 , int Thrust2 , int Thrust3 , int Thrust4 , int Orientation1 , int Orientation2, int Orientation3, int Orientation4 )
{
#ifdef QGC_USE_SKYE_INTERFACE

    mavlink_message_t message;

    mavlink_msg_setpoint_8dof_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId,
                                         (float)Thrust1,
                                         (float)Thrust2,
                                         (float)Thrust3,
                                         (float)Thrust4,
                                         (float)Orientation1,
                                         (float)Orientation2,
                                         (float)Orientation3,
                                         (float)Orientation4);
    sendMessage(message);
    qDebug() << __FILE__ << __LINE__ << ": SENT 8DOF CONTROL MESSAGE: 1Thrust" << Thrust1 << " 2Thrust: " << Thrust2 << " 3Thrust: " << Thrust3 << " 4Thrust: " << Thrust4 << " 1Orientation: " << Orientation1 << " 2Orientation: " << Orientation2 << " 3Orientation: " << Orientation3 << " 4Orientation: " << Orientation4;

#endif // QGC_USE_SKYE_INTERFACE
}

void SkyeMAV::setModeCommand(int mode)
{
#ifdef QGC_USE_SKYE_INTERFACE
	mavlink_message_t message;

	mavlink_msg_command_long_pack(mavlink->getSystemId(), mavlink->getComponentId(), &message, this->uasId,
								  (uint8_t)MAV_COMP_ID_ALL, MAV_CMD_DO_SET_MODE, 1, mode, 0, 0, 0, 0, 0, 0);

	sendMessage(message);

#endif //QGC_USE_SKYE_INTERFACE
}


QImage SkyeMAV::getImage()          // Function copied from UAS.cc (pixhawk)
{
#ifdef TEMP_QGC_USE_SKYE_INTERFACE

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
                if (deltaNorm < QGC_SKYE_MAX_VEL_NORM / sensitivityFactorTrans)
                {
                    qDebug() << "Send original 6DOF manual control command for FAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * deltaCam[0],
                                                sensitivityFactorTrans * deltaCam[1],
                                                sensitivityFactorTrans * deltaCam[2],
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                } else {
                    qDebug() << "Send original 6DOF manual control command for FAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[0],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[1],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm * deltaCam[2],
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                }
                if ( deltaNorm < QGC_SKYE_LOOKAHEAD )
                {
                    qDebug() << "REACHED POINT" << currentTrajectoryStamp << "OF TRAJECTORY";
                    if (trajX.size() > currentTrajectoryStamp + 1)
                        currentTrajectoryStamp++;
                }
            }
            else        // HALF AUTOMATIC CONTROL
            {
                if (deltaNorm2D < QGC_SKYE_MAX_VEL_NORM / sensitivityFactorTrans)
                {
                    qDebug() << "Send original 6DOF manual control command for HAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * deltaCam[0],
                                                sensitivityFactorTrans * deltaCam[1],
                                                manualZVel,
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                } else {
                    qDebug() << "Send reduced 6DOF manual control command for HAC";
                    sendManualControlCommands6DoF(sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm2D * deltaCam[0],
                                                sensitivityFactorTrans * QGC_SKYE_MAX_VEL_NORM / deltaNorm2D * deltaCam[1],
                                                manualZVel,
                                                manualXRot,
                                                manualYRot,
                                                manualZRot);
                }
                if ( deltaNorm2D < QGC_SKYE_LOOKAHEAD )
                {
                    qDebug() << "REACHED POINT" << currentTrajectoryStamp << "OF TRAJECTORY";
                    if (trajX.size() > currentTrajectoryStamp + 1)
                        currentTrajectoryStamp++;
                }
            }
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
//    qDebug() << "I to C" << fromItoC[0] << fromItoC[1] << fromItoC[2] << fromItoC[3] << fromItoC[4] << fromItoC[5] << fromItoC[6] << fromItoC[7] << fromItoC[8];
}


void SkyeMAV::setInputMode(SkyeMAV::QGC_INPUT_MODE input)
{
    inputMode = input;
    emit inputModeChanged(inputMode);
}

void SkyeMAV::sendLedColor(uint8_t ledId, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency)
{
    mavlink_message_t msg;
    mavlink_msg_led_control_pack(mavlink->getSystemId(), mavlink->getComponentId(), &msg, ledId, red, green, blue, mode, frequency);
    sendMessage(msg);
    qDebug("Sent LED Color Message");
}
