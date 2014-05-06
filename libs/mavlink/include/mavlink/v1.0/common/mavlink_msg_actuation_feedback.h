// MESSAGE ACTUATION_FEEDBACK PACKING

#define MAVLINK_MSG_ID_ACTUATION_FEEDBACK 137

typedef struct __mavlink_actuation_feedback_t
{
 uint64_t timestamp; ///< Onboard time
 float thrust[6]; ///< Thrust estimate of actuation units in Newton
 float angle[6]; ///< Orientation readout of actuation units in Degree
} mavlink_actuation_feedback_t;

#define MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN 56
#define MAVLINK_MSG_ID_137_LEN 56

#define MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC 108
#define MAVLINK_MSG_ID_137_CRC 108

#define MAVLINK_MSG_ACTUATION_FEEDBACK_FIELD_THRUST_LEN 6
#define MAVLINK_MSG_ACTUATION_FEEDBACK_FIELD_ANGLE_LEN 6

#define MAVLINK_MESSAGE_INFO_ACTUATION_FEEDBACK { \
	"ACTUATION_FEEDBACK", \
	3, \
	{  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_actuation_feedback_t, timestamp) }, \
         { "thrust", NULL, MAVLINK_TYPE_FLOAT, 6, 8, offsetof(mavlink_actuation_feedback_t, thrust) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 6, 32, offsetof(mavlink_actuation_feedback_t, angle) }, \
         } \
}


/**
 * @brief Pack a actuation_feedback message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp Onboard time
 * @param thrust Thrust estimate of actuation units in Newton
 * @param angle Orientation readout of actuation units in Degree
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_feedback_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t timestamp, const float *thrust, const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, thrust, 6);
	_mav_put_float_array(buf, 32, angle, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#else
	mavlink_actuation_feedback_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet.angle, angle, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_FEEDBACK;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
}

/**
 * @brief Pack a actuation_feedback message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp Onboard time
 * @param thrust Thrust estimate of actuation units in Newton
 * @param angle Orientation readout of actuation units in Degree
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_feedback_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t timestamp,const float *thrust,const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, thrust, 6);
	_mav_put_float_array(buf, 32, angle, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#else
	mavlink_actuation_feedback_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet.angle, angle, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_FEEDBACK;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
}

/**
 * @brief Encode a actuation_feedback struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param actuation_feedback C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_feedback_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_actuation_feedback_t* actuation_feedback)
{
	return mavlink_msg_actuation_feedback_pack(system_id, component_id, msg, actuation_feedback->timestamp, actuation_feedback->thrust, actuation_feedback->angle);
}

/**
 * @brief Encode a actuation_feedback struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param actuation_feedback C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_feedback_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_actuation_feedback_t* actuation_feedback)
{
	return mavlink_msg_actuation_feedback_pack_chan(system_id, component_id, chan, msg, actuation_feedback->timestamp, actuation_feedback->thrust, actuation_feedback->angle);
}

/**
 * @brief Send a actuation_feedback message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp Onboard time
 * @param thrust Thrust estimate of actuation units in Newton
 * @param angle Orientation readout of actuation units in Degree
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_actuation_feedback_send(mavlink_channel_t chan, uint64_t timestamp, const float *thrust, const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, thrust, 6);
	_mav_put_float_array(buf, 32, angle, 6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, buf, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, buf, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
#else
	mavlink_actuation_feedback_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet.angle, angle, sizeof(float)*6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_actuation_feedback_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, const float *thrust, const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, thrust, 6);
	_mav_put_float_array(buf, 32, angle, 6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, buf, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, buf, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
#else
	mavlink_actuation_feedback_t *packet = (mavlink_actuation_feedback_t *)msgbuf;
	packet->timestamp = timestamp;
	mav_array_memcpy(packet->thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet->angle, angle, sizeof(float)*6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, (const char *)packet, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_FEEDBACK, (const char *)packet, MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ACTUATION_FEEDBACK UNPACKING


/**
 * @brief Get field timestamp from actuation_feedback message
 *
 * @return Onboard time
 */
static inline uint64_t mavlink_msg_actuation_feedback_get_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field thrust from actuation_feedback message
 *
 * @return Thrust estimate of actuation units in Newton
 */
static inline uint16_t mavlink_msg_actuation_feedback_get_thrust(const mavlink_message_t* msg, float *thrust)
{
	return _MAV_RETURN_float_array(msg, thrust, 6,  8);
}

/**
 * @brief Get field angle from actuation_feedback message
 *
 * @return Orientation readout of actuation units in Degree
 */
static inline uint16_t mavlink_msg_actuation_feedback_get_angle(const mavlink_message_t* msg, float *angle)
{
	return _MAV_RETURN_float_array(msg, angle, 6,  32);
}

/**
 * @brief Decode a actuation_feedback message into a struct
 *
 * @param msg The message to decode
 * @param actuation_feedback C-struct to decode the message contents into
 */
static inline void mavlink_msg_actuation_feedback_decode(const mavlink_message_t* msg, mavlink_actuation_feedback_t* actuation_feedback)
{
#if MAVLINK_NEED_BYTE_SWAP
	actuation_feedback->timestamp = mavlink_msg_actuation_feedback_get_timestamp(msg);
	mavlink_msg_actuation_feedback_get_thrust(msg, actuation_feedback->thrust);
	mavlink_msg_actuation_feedback_get_angle(msg, actuation_feedback->angle);
#else
	memcpy(actuation_feedback, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACTUATION_FEEDBACK_LEN);
#endif
}
