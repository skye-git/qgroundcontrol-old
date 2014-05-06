// MESSAGE ATTITUDE_CONTROLLER_RAW PACKING

#define MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW 135

typedef struct __mavlink_attitude_controller_raw_t
{
 float M_x; ///< Moment around x axis [Nm]
 float M_y; ///< Moment around y axis [Nm]
 float M_z; ///< Moment around z axis [Nm]
} mavlink_attitude_controller_raw_t;

#define MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN 12
#define MAVLINK_MSG_ID_135_LEN 12

#define MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC 43
#define MAVLINK_MSG_ID_135_CRC 43



#define MAVLINK_MESSAGE_INFO_ATTITUDE_CONTROLLER_RAW { \
	"ATTITUDE_CONTROLLER_RAW", \
	3, \
	{  { "M_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_attitude_controller_raw_t, M_x) }, \
         { "M_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_attitude_controller_raw_t, M_y) }, \
         { "M_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_attitude_controller_raw_t, M_z) }, \
         } \
}


/**
 * @brief Pack a attitude_controller_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param M_x Moment around x axis [Nm]
 * @param M_y Moment around y axis [Nm]
 * @param M_z Moment around z axis [Nm]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_controller_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float M_x, float M_y, float M_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN];
	_mav_put_float(buf, 0, M_x);
	_mav_put_float(buf, 4, M_y);
	_mav_put_float(buf, 8, M_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#else
	mavlink_attitude_controller_raw_t packet;
	packet.M_x = M_x;
	packet.M_y = M_y;
	packet.M_z = M_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
}

/**
 * @brief Pack a attitude_controller_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param M_x Moment around x axis [Nm]
 * @param M_y Moment around y axis [Nm]
 * @param M_z Moment around z axis [Nm]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_controller_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float M_x,float M_y,float M_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN];
	_mav_put_float(buf, 0, M_x);
	_mav_put_float(buf, 4, M_y);
	_mav_put_float(buf, 8, M_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#else
	mavlink_attitude_controller_raw_t packet;
	packet.M_x = M_x;
	packet.M_y = M_y;
	packet.M_z = M_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
}

/**
 * @brief Encode a attitude_controller_raw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param attitude_controller_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_controller_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_attitude_controller_raw_t* attitude_controller_raw)
{
	return mavlink_msg_attitude_controller_raw_pack(system_id, component_id, msg, attitude_controller_raw->M_x, attitude_controller_raw->M_y, attitude_controller_raw->M_z);
}

/**
 * @brief Encode a attitude_controller_raw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param attitude_controller_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_controller_raw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_attitude_controller_raw_t* attitude_controller_raw)
{
	return mavlink_msg_attitude_controller_raw_pack_chan(system_id, component_id, chan, msg, attitude_controller_raw->M_x, attitude_controller_raw->M_y, attitude_controller_raw->M_z);
}

/**
 * @brief Send a attitude_controller_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param M_x Moment around x axis [Nm]
 * @param M_y Moment around y axis [Nm]
 * @param M_z Moment around z axis [Nm]
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_attitude_controller_raw_send(mavlink_channel_t chan, float M_x, float M_y, float M_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN];
	_mav_put_float(buf, 0, M_x);
	_mav_put_float(buf, 4, M_y);
	_mav_put_float(buf, 8, M_z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, buf, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, buf, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
#else
	mavlink_attitude_controller_raw_t packet;
	packet.M_x = M_x;
	packet.M_y = M_y;
	packet.M_z = M_z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, (const char *)&packet, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, (const char *)&packet, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_attitude_controller_raw_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float M_x, float M_y, float M_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, M_x);
	_mav_put_float(buf, 4, M_y);
	_mav_put_float(buf, 8, M_z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, buf, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, buf, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
#else
	mavlink_attitude_controller_raw_t *packet = (mavlink_attitude_controller_raw_t *)msgbuf;
	packet->M_x = M_x;
	packet->M_y = M_y;
	packet->M_z = M_z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, (const char *)packet, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW, (const char *)packet, MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ATTITUDE_CONTROLLER_RAW UNPACKING


/**
 * @brief Get field M_x from attitude_controller_raw message
 *
 * @return Moment around x axis [Nm]
 */
static inline float mavlink_msg_attitude_controller_raw_get_M_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field M_y from attitude_controller_raw message
 *
 * @return Moment around y axis [Nm]
 */
static inline float mavlink_msg_attitude_controller_raw_get_M_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field M_z from attitude_controller_raw message
 *
 * @return Moment around z axis [Nm]
 */
static inline float mavlink_msg_attitude_controller_raw_get_M_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a attitude_controller_raw message into a struct
 *
 * @param msg The message to decode
 * @param attitude_controller_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_attitude_controller_raw_decode(const mavlink_message_t* msg, mavlink_attitude_controller_raw_t* attitude_controller_raw)
{
#if MAVLINK_NEED_BYTE_SWAP
	attitude_controller_raw->M_x = mavlink_msg_attitude_controller_raw_get_M_x(msg);
	attitude_controller_raw->M_y = mavlink_msg_attitude_controller_raw_get_M_y(msg);
	attitude_controller_raw->M_z = mavlink_msg_attitude_controller_raw_get_M_z(msg);
#else
	memcpy(attitude_controller_raw, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_RAW_LEN);
#endif
}
