// MESSAGE ACTUATOR_LIMITS PACKING

#define MAVLINK_MSG_ID_ACTUATOR_LIMITS 132

typedef struct __mavlink_actuator_limits_t
{
 uint64_t timestamp; ///< Onboard time
 float th_min[6]; ///< Minimum thrust of actuators
 float th_start[6]; ///< Start thrust of actuators
 float th_max[6]; ///< Maximum thrust of actuators
 float ang_min[6]; ///< Minimum angle of actuators
 float ang_max[6]; ///< Maximum angle of actuators
 uint8_t valid[6]; ///< Tells wether data is valid
} mavlink_actuator_limits_t;

#define MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN 134
#define MAVLINK_MSG_ID_132_LEN 134

#define MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC 197
#define MAVLINK_MSG_ID_132_CRC 197

#define MAVLINK_MSG_ACTUATOR_LIMITS_FIELD_TH_MIN_LEN 6
#define MAVLINK_MSG_ACTUATOR_LIMITS_FIELD_TH_START_LEN 6
#define MAVLINK_MSG_ACTUATOR_LIMITS_FIELD_TH_MAX_LEN 6
#define MAVLINK_MSG_ACTUATOR_LIMITS_FIELD_ANG_MIN_LEN 6
#define MAVLINK_MSG_ACTUATOR_LIMITS_FIELD_ANG_MAX_LEN 6
#define MAVLINK_MSG_ACTUATOR_LIMITS_FIELD_VALID_LEN 6

#define MAVLINK_MESSAGE_INFO_ACTUATOR_LIMITS { \
	"ACTUATOR_LIMITS", \
	7, \
	{  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_actuator_limits_t, timestamp) }, \
         { "th_min", NULL, MAVLINK_TYPE_FLOAT, 6, 8, offsetof(mavlink_actuator_limits_t, th_min) }, \
         { "th_start", NULL, MAVLINK_TYPE_FLOAT, 6, 32, offsetof(mavlink_actuator_limits_t, th_start) }, \
         { "th_max", NULL, MAVLINK_TYPE_FLOAT, 6, 56, offsetof(mavlink_actuator_limits_t, th_max) }, \
         { "ang_min", NULL, MAVLINK_TYPE_FLOAT, 6, 80, offsetof(mavlink_actuator_limits_t, ang_min) }, \
         { "ang_max", NULL, MAVLINK_TYPE_FLOAT, 6, 104, offsetof(mavlink_actuator_limits_t, ang_max) }, \
         { "valid", NULL, MAVLINK_TYPE_UINT8_T, 6, 128, offsetof(mavlink_actuator_limits_t, valid) }, \
         } \
}


/**
 * @brief Pack a actuator_limits message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp Onboard time
 * @param valid Tells wether data is valid
 * @param th_min Minimum thrust of actuators
 * @param th_start Start thrust of actuators
 * @param th_max Maximum thrust of actuators
 * @param ang_min Minimum angle of actuators
 * @param ang_max Maximum angle of actuators
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuator_limits_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t timestamp, const uint8_t *valid, const float *th_min, const float *th_start, const float *th_max, const float *ang_min, const float *ang_max)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, th_min, 6);
	_mav_put_float_array(buf, 32, th_start, 6);
	_mav_put_float_array(buf, 56, th_max, 6);
	_mav_put_float_array(buf, 80, ang_min, 6);
	_mav_put_float_array(buf, 104, ang_max, 6);
	_mav_put_uint8_t_array(buf, 128, valid, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#else
	mavlink_actuator_limits_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.th_min, th_min, sizeof(float)*6);
	mav_array_memcpy(packet.th_start, th_start, sizeof(float)*6);
	mav_array_memcpy(packet.th_max, th_max, sizeof(float)*6);
	mav_array_memcpy(packet.ang_min, ang_min, sizeof(float)*6);
	mav_array_memcpy(packet.ang_max, ang_max, sizeof(float)*6);
	mav_array_memcpy(packet.valid, valid, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATOR_LIMITS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN, MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
}

/**
 * @brief Pack a actuator_limits message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp Onboard time
 * @param valid Tells wether data is valid
 * @param th_min Minimum thrust of actuators
 * @param th_start Start thrust of actuators
 * @param th_max Maximum thrust of actuators
 * @param ang_min Minimum angle of actuators
 * @param ang_max Maximum angle of actuators
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuator_limits_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t timestamp,const uint8_t *valid,const float *th_min,const float *th_start,const float *th_max,const float *ang_min,const float *ang_max)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, th_min, 6);
	_mav_put_float_array(buf, 32, th_start, 6);
	_mav_put_float_array(buf, 56, th_max, 6);
	_mav_put_float_array(buf, 80, ang_min, 6);
	_mav_put_float_array(buf, 104, ang_max, 6);
	_mav_put_uint8_t_array(buf, 128, valid, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#else
	mavlink_actuator_limits_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.th_min, th_min, sizeof(float)*6);
	mav_array_memcpy(packet.th_start, th_start, sizeof(float)*6);
	mav_array_memcpy(packet.th_max, th_max, sizeof(float)*6);
	mav_array_memcpy(packet.ang_min, ang_min, sizeof(float)*6);
	mav_array_memcpy(packet.ang_max, ang_max, sizeof(float)*6);
	mav_array_memcpy(packet.valid, valid, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATOR_LIMITS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN, MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
}

/**
 * @brief Encode a actuator_limits struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param actuator_limits C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuator_limits_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_actuator_limits_t* actuator_limits)
{
	return mavlink_msg_actuator_limits_pack(system_id, component_id, msg, actuator_limits->timestamp, actuator_limits->valid, actuator_limits->th_min, actuator_limits->th_start, actuator_limits->th_max, actuator_limits->ang_min, actuator_limits->ang_max);
}

/**
 * @brief Encode a actuator_limits struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param actuator_limits C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuator_limits_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_actuator_limits_t* actuator_limits)
{
	return mavlink_msg_actuator_limits_pack_chan(system_id, component_id, chan, msg, actuator_limits->timestamp, actuator_limits->valid, actuator_limits->th_min, actuator_limits->th_start, actuator_limits->th_max, actuator_limits->ang_min, actuator_limits->ang_max);
}

/**
 * @brief Send a actuator_limits message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp Onboard time
 * @param valid Tells wether data is valid
 * @param th_min Minimum thrust of actuators
 * @param th_start Start thrust of actuators
 * @param th_max Maximum thrust of actuators
 * @param ang_min Minimum angle of actuators
 * @param ang_max Maximum angle of actuators
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_actuator_limits_send(mavlink_channel_t chan, uint64_t timestamp, const uint8_t *valid, const float *th_min, const float *th_start, const float *th_max, const float *ang_min, const float *ang_max)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, th_min, 6);
	_mav_put_float_array(buf, 32, th_start, 6);
	_mav_put_float_array(buf, 56, th_max, 6);
	_mav_put_float_array(buf, 80, ang_min, 6);
	_mav_put_float_array(buf, 104, ang_max, 6);
	_mav_put_uint8_t_array(buf, 128, valid, 6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, buf, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN, MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, buf, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
#else
	mavlink_actuator_limits_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.th_min, th_min, sizeof(float)*6);
	mav_array_memcpy(packet.th_start, th_start, sizeof(float)*6);
	mav_array_memcpy(packet.th_max, th_max, sizeof(float)*6);
	mav_array_memcpy(packet.ang_min, ang_min, sizeof(float)*6);
	mav_array_memcpy(packet.ang_max, ang_max, sizeof(float)*6);
	mav_array_memcpy(packet.valid, valid, sizeof(uint8_t)*6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, (const char *)&packet, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN, MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, (const char *)&packet, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_actuator_limits_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, const uint8_t *valid, const float *th_min, const float *th_start, const float *th_max, const float *ang_min, const float *ang_max)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, th_min, 6);
	_mav_put_float_array(buf, 32, th_start, 6);
	_mav_put_float_array(buf, 56, th_max, 6);
	_mav_put_float_array(buf, 80, ang_min, 6);
	_mav_put_float_array(buf, 104, ang_max, 6);
	_mav_put_uint8_t_array(buf, 128, valid, 6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, buf, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN, MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, buf, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
#else
	mavlink_actuator_limits_t *packet = (mavlink_actuator_limits_t *)msgbuf;
	packet->timestamp = timestamp;
	mav_array_memcpy(packet->th_min, th_min, sizeof(float)*6);
	mav_array_memcpy(packet->th_start, th_start, sizeof(float)*6);
	mav_array_memcpy(packet->th_max, th_max, sizeof(float)*6);
	mav_array_memcpy(packet->ang_min, ang_min, sizeof(float)*6);
	mav_array_memcpy(packet->ang_max, ang_max, sizeof(float)*6);
	mav_array_memcpy(packet->valid, valid, sizeof(uint8_t)*6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, (const char *)packet, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN, MAVLINK_MSG_ID_ACTUATOR_LIMITS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATOR_LIMITS, (const char *)packet, MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ACTUATOR_LIMITS UNPACKING


/**
 * @brief Get field timestamp from actuator_limits message
 *
 * @return Onboard time
 */
static inline uint64_t mavlink_msg_actuator_limits_get_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field valid from actuator_limits message
 *
 * @return Tells wether data is valid
 */
static inline uint16_t mavlink_msg_actuator_limits_get_valid(const mavlink_message_t* msg, uint8_t *valid)
{
	return _MAV_RETURN_uint8_t_array(msg, valid, 6,  128);
}

/**
 * @brief Get field th_min from actuator_limits message
 *
 * @return Minimum thrust of actuators
 */
static inline uint16_t mavlink_msg_actuator_limits_get_th_min(const mavlink_message_t* msg, float *th_min)
{
	return _MAV_RETURN_float_array(msg, th_min, 6,  8);
}

/**
 * @brief Get field th_start from actuator_limits message
 *
 * @return Start thrust of actuators
 */
static inline uint16_t mavlink_msg_actuator_limits_get_th_start(const mavlink_message_t* msg, float *th_start)
{
	return _MAV_RETURN_float_array(msg, th_start, 6,  32);
}

/**
 * @brief Get field th_max from actuator_limits message
 *
 * @return Maximum thrust of actuators
 */
static inline uint16_t mavlink_msg_actuator_limits_get_th_max(const mavlink_message_t* msg, float *th_max)
{
	return _MAV_RETURN_float_array(msg, th_max, 6,  56);
}

/**
 * @brief Get field ang_min from actuator_limits message
 *
 * @return Minimum angle of actuators
 */
static inline uint16_t mavlink_msg_actuator_limits_get_ang_min(const mavlink_message_t* msg, float *ang_min)
{
	return _MAV_RETURN_float_array(msg, ang_min, 6,  80);
}

/**
 * @brief Get field ang_max from actuator_limits message
 *
 * @return Maximum angle of actuators
 */
static inline uint16_t mavlink_msg_actuator_limits_get_ang_max(const mavlink_message_t* msg, float *ang_max)
{
	return _MAV_RETURN_float_array(msg, ang_max, 6,  104);
}

/**
 * @brief Decode a actuator_limits message into a struct
 *
 * @param msg The message to decode
 * @param actuator_limits C-struct to decode the message contents into
 */
static inline void mavlink_msg_actuator_limits_decode(const mavlink_message_t* msg, mavlink_actuator_limits_t* actuator_limits)
{
#if MAVLINK_NEED_BYTE_SWAP
	actuator_limits->timestamp = mavlink_msg_actuator_limits_get_timestamp(msg);
	mavlink_msg_actuator_limits_get_th_min(msg, actuator_limits->th_min);
	mavlink_msg_actuator_limits_get_th_start(msg, actuator_limits->th_start);
	mavlink_msg_actuator_limits_get_th_max(msg, actuator_limits->th_max);
	mavlink_msg_actuator_limits_get_ang_min(msg, actuator_limits->ang_min);
	mavlink_msg_actuator_limits_get_ang_max(msg, actuator_limits->ang_max);
	mavlink_msg_actuator_limits_get_valid(msg, actuator_limits->valid);
#else
	memcpy(actuator_limits, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACTUATOR_LIMITS_LEN);
#endif
}
