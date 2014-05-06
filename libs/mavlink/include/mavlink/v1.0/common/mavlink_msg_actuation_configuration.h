// MESSAGE ACTUATION_CONFIGURATION PACKING

#define MAVLINK_MSG_ID_ACTUATION_CONFIGURATION 133

typedef struct __mavlink_actuation_configuration_t
{
 float quat_au1[4]; ///< Quaternion q_BM that describes rotation of AU 1 towards UAV
 float quat_au2[4]; ///< Quaternion q_BM that describes rotation of AU 2 towards UAV
 float quat_au3[4]; ///< Quaternion q_BM that describes rotation of AU 3 towards UAV
 float quat_au4[4]; ///< Quaternion q_BM that describes rotation of AU 4 towards UAV
 float quat_au5[4]; ///< Quaternion q_BM that describes rotation of AU 5 towards UAV
 float quat_au6[4]; ///< Quaternion q_BM that describes rotation of AU 6 towards UAV
} mavlink_actuation_configuration_t;

#define MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN 96
#define MAVLINK_MSG_ID_133_LEN 96

#define MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC 50
#define MAVLINK_MSG_ID_133_CRC 50

#define MAVLINK_MSG_ACTUATION_CONFIGURATION_FIELD_QUAT_AU1_LEN 4
#define MAVLINK_MSG_ACTUATION_CONFIGURATION_FIELD_QUAT_AU2_LEN 4
#define MAVLINK_MSG_ACTUATION_CONFIGURATION_FIELD_QUAT_AU3_LEN 4
#define MAVLINK_MSG_ACTUATION_CONFIGURATION_FIELD_QUAT_AU4_LEN 4
#define MAVLINK_MSG_ACTUATION_CONFIGURATION_FIELD_QUAT_AU5_LEN 4
#define MAVLINK_MSG_ACTUATION_CONFIGURATION_FIELD_QUAT_AU6_LEN 4

#define MAVLINK_MESSAGE_INFO_ACTUATION_CONFIGURATION { \
	"ACTUATION_CONFIGURATION", \
	6, \
	{  { "quat_au1", NULL, MAVLINK_TYPE_FLOAT, 4, 0, offsetof(mavlink_actuation_configuration_t, quat_au1) }, \
         { "quat_au2", NULL, MAVLINK_TYPE_FLOAT, 4, 16, offsetof(mavlink_actuation_configuration_t, quat_au2) }, \
         { "quat_au3", NULL, MAVLINK_TYPE_FLOAT, 4, 32, offsetof(mavlink_actuation_configuration_t, quat_au3) }, \
         { "quat_au4", NULL, MAVLINK_TYPE_FLOAT, 4, 48, offsetof(mavlink_actuation_configuration_t, quat_au4) }, \
         { "quat_au5", NULL, MAVLINK_TYPE_FLOAT, 4, 64, offsetof(mavlink_actuation_configuration_t, quat_au5) }, \
         { "quat_au6", NULL, MAVLINK_TYPE_FLOAT, 4, 80, offsetof(mavlink_actuation_configuration_t, quat_au6) }, \
         } \
}


/**
 * @brief Pack a actuation_configuration message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param quat_au1 Quaternion q_BM that describes rotation of AU 1 towards UAV
 * @param quat_au2 Quaternion q_BM that describes rotation of AU 2 towards UAV
 * @param quat_au3 Quaternion q_BM that describes rotation of AU 3 towards UAV
 * @param quat_au4 Quaternion q_BM that describes rotation of AU 4 towards UAV
 * @param quat_au5 Quaternion q_BM that describes rotation of AU 5 towards UAV
 * @param quat_au6 Quaternion q_BM that describes rotation of AU 6 towards UAV
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_configuration_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const float *quat_au1, const float *quat_au2, const float *quat_au3, const float *quat_au4, const float *quat_au5, const float *quat_au6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN];

	_mav_put_float_array(buf, 0, quat_au1, 4);
	_mav_put_float_array(buf, 16, quat_au2, 4);
	_mav_put_float_array(buf, 32, quat_au3, 4);
	_mav_put_float_array(buf, 48, quat_au4, 4);
	_mav_put_float_array(buf, 64, quat_au5, 4);
	_mav_put_float_array(buf, 80, quat_au6, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#else
	mavlink_actuation_configuration_t packet;

	mav_array_memcpy(packet.quat_au1, quat_au1, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au2, quat_au2, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au3, quat_au3, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au4, quat_au4, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au5, quat_au5, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au6, quat_au6, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_CONFIGURATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
}

/**
 * @brief Pack a actuation_configuration message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param quat_au1 Quaternion q_BM that describes rotation of AU 1 towards UAV
 * @param quat_au2 Quaternion q_BM that describes rotation of AU 2 towards UAV
 * @param quat_au3 Quaternion q_BM that describes rotation of AU 3 towards UAV
 * @param quat_au4 Quaternion q_BM that describes rotation of AU 4 towards UAV
 * @param quat_au5 Quaternion q_BM that describes rotation of AU 5 towards UAV
 * @param quat_au6 Quaternion q_BM that describes rotation of AU 6 towards UAV
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_configuration_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const float *quat_au1,const float *quat_au2,const float *quat_au3,const float *quat_au4,const float *quat_au5,const float *quat_au6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN];

	_mav_put_float_array(buf, 0, quat_au1, 4);
	_mav_put_float_array(buf, 16, quat_au2, 4);
	_mav_put_float_array(buf, 32, quat_au3, 4);
	_mav_put_float_array(buf, 48, quat_au4, 4);
	_mav_put_float_array(buf, 64, quat_au5, 4);
	_mav_put_float_array(buf, 80, quat_au6, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#else
	mavlink_actuation_configuration_t packet;

	mav_array_memcpy(packet.quat_au1, quat_au1, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au2, quat_au2, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au3, quat_au3, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au4, quat_au4, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au5, quat_au5, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au6, quat_au6, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_CONFIGURATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
}

/**
 * @brief Encode a actuation_configuration struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param actuation_configuration C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_configuration_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_actuation_configuration_t* actuation_configuration)
{
	return mavlink_msg_actuation_configuration_pack(system_id, component_id, msg, actuation_configuration->quat_au1, actuation_configuration->quat_au2, actuation_configuration->quat_au3, actuation_configuration->quat_au4, actuation_configuration->quat_au5, actuation_configuration->quat_au6);
}

/**
 * @brief Encode a actuation_configuration struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param actuation_configuration C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_configuration_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_actuation_configuration_t* actuation_configuration)
{
	return mavlink_msg_actuation_configuration_pack_chan(system_id, component_id, chan, msg, actuation_configuration->quat_au1, actuation_configuration->quat_au2, actuation_configuration->quat_au3, actuation_configuration->quat_au4, actuation_configuration->quat_au5, actuation_configuration->quat_au6);
}

/**
 * @brief Send a actuation_configuration message
 * @param chan MAVLink channel to send the message
 *
 * @param quat_au1 Quaternion q_BM that describes rotation of AU 1 towards UAV
 * @param quat_au2 Quaternion q_BM that describes rotation of AU 2 towards UAV
 * @param quat_au3 Quaternion q_BM that describes rotation of AU 3 towards UAV
 * @param quat_au4 Quaternion q_BM that describes rotation of AU 4 towards UAV
 * @param quat_au5 Quaternion q_BM that describes rotation of AU 5 towards UAV
 * @param quat_au6 Quaternion q_BM that describes rotation of AU 6 towards UAV
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_actuation_configuration_send(mavlink_channel_t chan, const float *quat_au1, const float *quat_au2, const float *quat_au3, const float *quat_au4, const float *quat_au5, const float *quat_au6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN];

	_mav_put_float_array(buf, 0, quat_au1, 4);
	_mav_put_float_array(buf, 16, quat_au2, 4);
	_mav_put_float_array(buf, 32, quat_au3, 4);
	_mav_put_float_array(buf, 48, quat_au4, 4);
	_mav_put_float_array(buf, 64, quat_au5, 4);
	_mav_put_float_array(buf, 80, quat_au6, 4);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, buf, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, buf, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
#else
	mavlink_actuation_configuration_t packet;

	mav_array_memcpy(packet.quat_au1, quat_au1, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au2, quat_au2, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au3, quat_au3, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au4, quat_au4, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au5, quat_au5, sizeof(float)*4);
	mav_array_memcpy(packet.quat_au6, quat_au6, sizeof(float)*4);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_actuation_configuration_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *quat_au1, const float *quat_au2, const float *quat_au3, const float *quat_au4, const float *quat_au5, const float *quat_au6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;

	_mav_put_float_array(buf, 0, quat_au1, 4);
	_mav_put_float_array(buf, 16, quat_au2, 4);
	_mav_put_float_array(buf, 32, quat_au3, 4);
	_mav_put_float_array(buf, 48, quat_au4, 4);
	_mav_put_float_array(buf, 64, quat_au5, 4);
	_mav_put_float_array(buf, 80, quat_au6, 4);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, buf, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, buf, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
#else
	mavlink_actuation_configuration_t *packet = (mavlink_actuation_configuration_t *)msgbuf;

	mav_array_memcpy(packet->quat_au1, quat_au1, sizeof(float)*4);
	mav_array_memcpy(packet->quat_au2, quat_au2, sizeof(float)*4);
	mav_array_memcpy(packet->quat_au3, quat_au3, sizeof(float)*4);
	mav_array_memcpy(packet->quat_au4, quat_au4, sizeof(float)*4);
	mav_array_memcpy(packet->quat_au5, quat_au5, sizeof(float)*4);
	mav_array_memcpy(packet->quat_au6, quat_au6, sizeof(float)*4);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, (const char *)packet, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION, (const char *)packet, MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ACTUATION_CONFIGURATION UNPACKING


/**
 * @brief Get field quat_au1 from actuation_configuration message
 *
 * @return Quaternion q_BM that describes rotation of AU 1 towards UAV
 */
static inline uint16_t mavlink_msg_actuation_configuration_get_quat_au1(const mavlink_message_t* msg, float *quat_au1)
{
	return _MAV_RETURN_float_array(msg, quat_au1, 4,  0);
}

/**
 * @brief Get field quat_au2 from actuation_configuration message
 *
 * @return Quaternion q_BM that describes rotation of AU 2 towards UAV
 */
static inline uint16_t mavlink_msg_actuation_configuration_get_quat_au2(const mavlink_message_t* msg, float *quat_au2)
{
	return _MAV_RETURN_float_array(msg, quat_au2, 4,  16);
}

/**
 * @brief Get field quat_au3 from actuation_configuration message
 *
 * @return Quaternion q_BM that describes rotation of AU 3 towards UAV
 */
static inline uint16_t mavlink_msg_actuation_configuration_get_quat_au3(const mavlink_message_t* msg, float *quat_au3)
{
	return _MAV_RETURN_float_array(msg, quat_au3, 4,  32);
}

/**
 * @brief Get field quat_au4 from actuation_configuration message
 *
 * @return Quaternion q_BM that describes rotation of AU 4 towards UAV
 */
static inline uint16_t mavlink_msg_actuation_configuration_get_quat_au4(const mavlink_message_t* msg, float *quat_au4)
{
	return _MAV_RETURN_float_array(msg, quat_au4, 4,  48);
}

/**
 * @brief Get field quat_au5 from actuation_configuration message
 *
 * @return Quaternion q_BM that describes rotation of AU 5 towards UAV
 */
static inline uint16_t mavlink_msg_actuation_configuration_get_quat_au5(const mavlink_message_t* msg, float *quat_au5)
{
	return _MAV_RETURN_float_array(msg, quat_au5, 4,  64);
}

/**
 * @brief Get field quat_au6 from actuation_configuration message
 *
 * @return Quaternion q_BM that describes rotation of AU 6 towards UAV
 */
static inline uint16_t mavlink_msg_actuation_configuration_get_quat_au6(const mavlink_message_t* msg, float *quat_au6)
{
	return _MAV_RETURN_float_array(msg, quat_au6, 4,  80);
}

/**
 * @brief Decode a actuation_configuration message into a struct
 *
 * @param msg The message to decode
 * @param actuation_configuration C-struct to decode the message contents into
 */
static inline void mavlink_msg_actuation_configuration_decode(const mavlink_message_t* msg, mavlink_actuation_configuration_t* actuation_configuration)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_actuation_configuration_get_quat_au1(msg, actuation_configuration->quat_au1);
	mavlink_msg_actuation_configuration_get_quat_au2(msg, actuation_configuration->quat_au2);
	mavlink_msg_actuation_configuration_get_quat_au3(msg, actuation_configuration->quat_au3);
	mavlink_msg_actuation_configuration_get_quat_au4(msg, actuation_configuration->quat_au4);
	mavlink_msg_actuation_configuration_get_quat_au5(msg, actuation_configuration->quat_au5);
	mavlink_msg_actuation_configuration_get_quat_au6(msg, actuation_configuration->quat_au6);
#else
	memcpy(actuation_configuration, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACTUATION_CONFIGURATION_LEN);
#endif
}
