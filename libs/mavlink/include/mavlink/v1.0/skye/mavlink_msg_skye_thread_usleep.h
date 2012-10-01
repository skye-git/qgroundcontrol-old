// MESSAGE SKYE_THREAD_USLEEP PACKING

#define MAVLINK_MSG_ID_SKYE_THREAD_USLEEP 168

typedef struct __mavlink_skye_thread_usleep_t
{
 int64_t heartbeatloop_usleep; ///< Microseconds heartbeatloop is sleeping
 int64_t receiveloop_timestamp; ///< Microseconds receiveloop is sleeping
 int64_t telemetryloop_usleep; ///< Microseconds telemetryloop is sleeping
 int64_t gyroaccloop_usleep; ///< Microseconds gyroaccloop is sleeping
 int64_t controlloop_usleep; ///< Microseconds controlloop is sleeping
 int64_t stateestimation_usleep; ///< Microseconds stateestimation loop is sleeping
 uint32_t time_usec; ///< Timestamp (since UNIX epoch or microseconds since system boot)
} mavlink_skye_thread_usleep_t;

#define MAVLINK_MSG_ID_SKYE_THREAD_USLEEP_LEN 52
#define MAVLINK_MSG_ID_168_LEN 52



#define MAVLINK_MESSAGE_INFO_SKYE_THREAD_USLEEP { \
	"SKYE_THREAD_USLEEP", \
	7, \
	{  { "heartbeatloop_usleep", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_skye_thread_usleep_t, heartbeatloop_usleep) }, \
         { "receiveloop_timestamp", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_skye_thread_usleep_t, receiveloop_timestamp) }, \
         { "telemetryloop_usleep", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_skye_thread_usleep_t, telemetryloop_usleep) }, \
         { "gyroaccloop_usleep", NULL, MAVLINK_TYPE_INT64_T, 0, 24, offsetof(mavlink_skye_thread_usleep_t, gyroaccloop_usleep) }, \
         { "controlloop_usleep", NULL, MAVLINK_TYPE_INT64_T, 0, 32, offsetof(mavlink_skye_thread_usleep_t, controlloop_usleep) }, \
         { "stateestimation_usleep", NULL, MAVLINK_TYPE_INT64_T, 0, 40, offsetof(mavlink_skye_thread_usleep_t, stateestimation_usleep) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 48, offsetof(mavlink_skye_thread_usleep_t, time_usec) }, \
         } \
}


/**
 * @brief Pack a skye_thread_usleep message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param heartbeatloop_usleep Microseconds heartbeatloop is sleeping
 * @param receiveloop_timestamp Microseconds receiveloop is sleeping
 * @param telemetryloop_usleep Microseconds telemetryloop is sleeping
 * @param gyroaccloop_usleep Microseconds gyroaccloop is sleeping
 * @param controlloop_usleep Microseconds controlloop is sleeping
 * @param stateestimation_usleep Microseconds stateestimation loop is sleeping
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_thread_usleep_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, int64_t heartbeatloop_usleep, int64_t receiveloop_timestamp, int64_t telemetryloop_usleep, int64_t gyroaccloop_usleep, int64_t controlloop_usleep, int64_t stateestimation_usleep)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[52];
	_mav_put_int64_t(buf, 0, heartbeatloop_usleep);
	_mav_put_int64_t(buf, 8, receiveloop_timestamp);
	_mav_put_int64_t(buf, 16, telemetryloop_usleep);
	_mav_put_int64_t(buf, 24, gyroaccloop_usleep);
	_mav_put_int64_t(buf, 32, controlloop_usleep);
	_mav_put_int64_t(buf, 40, stateestimation_usleep);
	_mav_put_uint32_t(buf, 48, time_usec);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 52);
#else
	mavlink_skye_thread_usleep_t packet;
	packet.heartbeatloop_usleep = heartbeatloop_usleep;
	packet.receiveloop_timestamp = receiveloop_timestamp;
	packet.telemetryloop_usleep = telemetryloop_usleep;
	packet.gyroaccloop_usleep = gyroaccloop_usleep;
	packet.controlloop_usleep = controlloop_usleep;
	packet.stateestimation_usleep = stateestimation_usleep;
	packet.time_usec = time_usec;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 52);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_THREAD_USLEEP;
	return mavlink_finalize_message(msg, system_id, component_id, 52, 9);
}

/**
 * @brief Pack a skye_thread_usleep message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param heartbeatloop_usleep Microseconds heartbeatloop is sleeping
 * @param receiveloop_timestamp Microseconds receiveloop is sleeping
 * @param telemetryloop_usleep Microseconds telemetryloop is sleeping
 * @param gyroaccloop_usleep Microseconds gyroaccloop is sleeping
 * @param controlloop_usleep Microseconds controlloop is sleeping
 * @param stateestimation_usleep Microseconds stateestimation loop is sleeping
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_thread_usleep_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,int64_t heartbeatloop_usleep,int64_t receiveloop_timestamp,int64_t telemetryloop_usleep,int64_t gyroaccloop_usleep,int64_t controlloop_usleep,int64_t stateestimation_usleep)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[52];
	_mav_put_int64_t(buf, 0, heartbeatloop_usleep);
	_mav_put_int64_t(buf, 8, receiveloop_timestamp);
	_mav_put_int64_t(buf, 16, telemetryloop_usleep);
	_mav_put_int64_t(buf, 24, gyroaccloop_usleep);
	_mav_put_int64_t(buf, 32, controlloop_usleep);
	_mav_put_int64_t(buf, 40, stateestimation_usleep);
	_mav_put_uint32_t(buf, 48, time_usec);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 52);
#else
	mavlink_skye_thread_usleep_t packet;
	packet.heartbeatloop_usleep = heartbeatloop_usleep;
	packet.receiveloop_timestamp = receiveloop_timestamp;
	packet.telemetryloop_usleep = telemetryloop_usleep;
	packet.gyroaccloop_usleep = gyroaccloop_usleep;
	packet.controlloop_usleep = controlloop_usleep;
	packet.stateestimation_usleep = stateestimation_usleep;
	packet.time_usec = time_usec;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 52);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_THREAD_USLEEP;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 52, 9);
}

/**
 * @brief Encode a skye_thread_usleep struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_thread_usleep C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_thread_usleep_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_thread_usleep_t* skye_thread_usleep)
{
	return mavlink_msg_skye_thread_usleep_pack(system_id, component_id, msg, skye_thread_usleep->time_usec, skye_thread_usleep->heartbeatloop_usleep, skye_thread_usleep->receiveloop_timestamp, skye_thread_usleep->telemetryloop_usleep, skye_thread_usleep->gyroaccloop_usleep, skye_thread_usleep->controlloop_usleep, skye_thread_usleep->stateestimation_usleep);
}

/**
 * @brief Send a skye_thread_usleep message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param heartbeatloop_usleep Microseconds heartbeatloop is sleeping
 * @param receiveloop_timestamp Microseconds receiveloop is sleeping
 * @param telemetryloop_usleep Microseconds telemetryloop is sleeping
 * @param gyroaccloop_usleep Microseconds gyroaccloop is sleeping
 * @param controlloop_usleep Microseconds controlloop is sleeping
 * @param stateestimation_usleep Microseconds stateestimation loop is sleeping
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_thread_usleep_send(mavlink_channel_t chan, uint32_t time_usec, int64_t heartbeatloop_usleep, int64_t receiveloop_timestamp, int64_t telemetryloop_usleep, int64_t gyroaccloop_usleep, int64_t controlloop_usleep, int64_t stateestimation_usleep)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[52];
	_mav_put_int64_t(buf, 0, heartbeatloop_usleep);
	_mav_put_int64_t(buf, 8, receiveloop_timestamp);
	_mav_put_int64_t(buf, 16, telemetryloop_usleep);
	_mav_put_int64_t(buf, 24, gyroaccloop_usleep);
	_mav_put_int64_t(buf, 32, controlloop_usleep);
	_mav_put_int64_t(buf, 40, stateestimation_usleep);
	_mav_put_uint32_t(buf, 48, time_usec);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_THREAD_USLEEP, buf, 52, 9);
#else
	mavlink_skye_thread_usleep_t packet;
	packet.heartbeatloop_usleep = heartbeatloop_usleep;
	packet.receiveloop_timestamp = receiveloop_timestamp;
	packet.telemetryloop_usleep = telemetryloop_usleep;
	packet.gyroaccloop_usleep = gyroaccloop_usleep;
	packet.controlloop_usleep = controlloop_usleep;
	packet.stateestimation_usleep = stateestimation_usleep;
	packet.time_usec = time_usec;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_THREAD_USLEEP, (const char *)&packet, 52, 9);
#endif
}

#endif

// MESSAGE SKYE_THREAD_USLEEP UNPACKING


/**
 * @brief Get field time_usec from skye_thread_usleep message
 *
 * @return Timestamp (since UNIX epoch or microseconds since system boot)
 */
static inline uint32_t mavlink_msg_skye_thread_usleep_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  48);
}

/**
 * @brief Get field heartbeatloop_usleep from skye_thread_usleep message
 *
 * @return Microseconds heartbeatloop is sleeping
 */
static inline int64_t mavlink_msg_skye_thread_usleep_get_heartbeatloop_usleep(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field receiveloop_timestamp from skye_thread_usleep message
 *
 * @return Microseconds receiveloop is sleeping
 */
static inline int64_t mavlink_msg_skye_thread_usleep_get_receiveloop_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field telemetryloop_usleep from skye_thread_usleep message
 *
 * @return Microseconds telemetryloop is sleeping
 */
static inline int64_t mavlink_msg_skye_thread_usleep_get_telemetryloop_usleep(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int64_t(msg,  16);
}

/**
 * @brief Get field gyroaccloop_usleep from skye_thread_usleep message
 *
 * @return Microseconds gyroaccloop is sleeping
 */
static inline int64_t mavlink_msg_skye_thread_usleep_get_gyroaccloop_usleep(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int64_t(msg,  24);
}

/**
 * @brief Get field controlloop_usleep from skye_thread_usleep message
 *
 * @return Microseconds controlloop is sleeping
 */
static inline int64_t mavlink_msg_skye_thread_usleep_get_controlloop_usleep(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int64_t(msg,  32);
}

/**
 * @brief Get field stateestimation_usleep from skye_thread_usleep message
 *
 * @return Microseconds stateestimation loop is sleeping
 */
static inline int64_t mavlink_msg_skye_thread_usleep_get_stateestimation_usleep(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int64_t(msg,  40);
}

/**
 * @brief Decode a skye_thread_usleep message into a struct
 *
 * @param msg The message to decode
 * @param skye_thread_usleep C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_thread_usleep_decode(const mavlink_message_t* msg, mavlink_skye_thread_usleep_t* skye_thread_usleep)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_thread_usleep->heartbeatloop_usleep = mavlink_msg_skye_thread_usleep_get_heartbeatloop_usleep(msg);
	skye_thread_usleep->receiveloop_timestamp = mavlink_msg_skye_thread_usleep_get_receiveloop_timestamp(msg);
	skye_thread_usleep->telemetryloop_usleep = mavlink_msg_skye_thread_usleep_get_telemetryloop_usleep(msg);
	skye_thread_usleep->gyroaccloop_usleep = mavlink_msg_skye_thread_usleep_get_gyroaccloop_usleep(msg);
	skye_thread_usleep->controlloop_usleep = mavlink_msg_skye_thread_usleep_get_controlloop_usleep(msg);
	skye_thread_usleep->stateestimation_usleep = mavlink_msg_skye_thread_usleep_get_stateestimation_usleep(msg);
	skye_thread_usleep->time_usec = mavlink_msg_skye_thread_usleep_get_time_usec(msg);
#else
	memcpy(skye_thread_usleep, _MAV_PAYLOAD(msg), 52);
#endif
}
