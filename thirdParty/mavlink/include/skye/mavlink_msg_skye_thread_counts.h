// MESSAGE SKYE_THREAD_COUNTS PACKING

#define MAVLINK_MSG_ID_SKYE_THREAD_COUNTS 167

typedef struct __mavlink_skye_thread_counts_t
{
 uint64_t heartbeatloop_count; ///< Counter of heartbeatloop
 uint64_t receiveloop_count; ///< Counter of receiveloop
 uint64_t telemetryloop_count; ///< Counter of telemetryloop
 uint64_t gyroaccloop_count; ///< Counter of gyroaccloop
 uint64_t controlloop_count; ///< Counter of controlloop
 uint64_t stateestimation_count; ///< Counter of stateestimation
 uint32_t time_usec; ///< Timestamp (since UNIX epoch or microseconds since system boot)
 uint8_t running_threads; ///< Number of running threads
} mavlink_skye_thread_counts_t;

#define MAVLINK_MSG_ID_SKYE_THREAD_COUNTS_LEN 53
#define MAVLINK_MSG_ID_167_LEN 53



#define MAVLINK_MESSAGE_INFO_SKYE_THREAD_COUNTS { \
	"SKYE_THREAD_COUNTS", \
	8, \
	{  { "heartbeatloop_count", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_skye_thread_counts_t, heartbeatloop_count) }, \
         { "receiveloop_count", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_skye_thread_counts_t, receiveloop_count) }, \
         { "telemetryloop_count", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_skye_thread_counts_t, telemetryloop_count) }, \
         { "gyroaccloop_count", NULL, MAVLINK_TYPE_UINT64_T, 0, 24, offsetof(mavlink_skye_thread_counts_t, gyroaccloop_count) }, \
         { "controlloop_count", NULL, MAVLINK_TYPE_UINT64_T, 0, 32, offsetof(mavlink_skye_thread_counts_t, controlloop_count) }, \
         { "stateestimation_count", NULL, MAVLINK_TYPE_UINT64_T, 0, 40, offsetof(mavlink_skye_thread_counts_t, stateestimation_count) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 48, offsetof(mavlink_skye_thread_counts_t, time_usec) }, \
         { "running_threads", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_skye_thread_counts_t, running_threads) }, \
         } \
}


/**
 * @brief Pack a skye_thread_counts message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param running_threads Number of running threads
 * @param heartbeatloop_count Counter of heartbeatloop
 * @param receiveloop_count Counter of receiveloop
 * @param telemetryloop_count Counter of telemetryloop
 * @param gyroaccloop_count Counter of gyroaccloop
 * @param controlloop_count Counter of controlloop
 * @param stateestimation_count Counter of stateestimation
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_thread_counts_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, uint8_t running_threads, uint64_t heartbeatloop_count, uint64_t receiveloop_count, uint64_t telemetryloop_count, uint64_t gyroaccloop_count, uint64_t controlloop_count, uint64_t stateestimation_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[53];
	_mav_put_uint64_t(buf, 0, heartbeatloop_count);
	_mav_put_uint64_t(buf, 8, receiveloop_count);
	_mav_put_uint64_t(buf, 16, telemetryloop_count);
	_mav_put_uint64_t(buf, 24, gyroaccloop_count);
	_mav_put_uint64_t(buf, 32, controlloop_count);
	_mav_put_uint64_t(buf, 40, stateestimation_count);
	_mav_put_uint32_t(buf, 48, time_usec);
	_mav_put_uint8_t(buf, 52, running_threads);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 53);
#else
	mavlink_skye_thread_counts_t packet;
	packet.heartbeatloop_count = heartbeatloop_count;
	packet.receiveloop_count = receiveloop_count;
	packet.telemetryloop_count = telemetryloop_count;
	packet.gyroaccloop_count = gyroaccloop_count;
	packet.controlloop_count = controlloop_count;
	packet.stateestimation_count = stateestimation_count;
	packet.time_usec = time_usec;
	packet.running_threads = running_threads;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 53);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_THREAD_COUNTS;
	return mavlink_finalize_message(msg, system_id, component_id, 53, 78);
}

/**
 * @brief Pack a skye_thread_counts message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param running_threads Number of running threads
 * @param heartbeatloop_count Counter of heartbeatloop
 * @param receiveloop_count Counter of receiveloop
 * @param telemetryloop_count Counter of telemetryloop
 * @param gyroaccloop_count Counter of gyroaccloop
 * @param controlloop_count Counter of controlloop
 * @param stateestimation_count Counter of stateestimation
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_thread_counts_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,uint8_t running_threads,uint64_t heartbeatloop_count,uint64_t receiveloop_count,uint64_t telemetryloop_count,uint64_t gyroaccloop_count,uint64_t controlloop_count,uint64_t stateestimation_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[53];
	_mav_put_uint64_t(buf, 0, heartbeatloop_count);
	_mav_put_uint64_t(buf, 8, receiveloop_count);
	_mav_put_uint64_t(buf, 16, telemetryloop_count);
	_mav_put_uint64_t(buf, 24, gyroaccloop_count);
	_mav_put_uint64_t(buf, 32, controlloop_count);
	_mav_put_uint64_t(buf, 40, stateestimation_count);
	_mav_put_uint32_t(buf, 48, time_usec);
	_mav_put_uint8_t(buf, 52, running_threads);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 53);
#else
	mavlink_skye_thread_counts_t packet;
	packet.heartbeatloop_count = heartbeatloop_count;
	packet.receiveloop_count = receiveloop_count;
	packet.telemetryloop_count = telemetryloop_count;
	packet.gyroaccloop_count = gyroaccloop_count;
	packet.controlloop_count = controlloop_count;
	packet.stateestimation_count = stateestimation_count;
	packet.time_usec = time_usec;
	packet.running_threads = running_threads;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 53);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_THREAD_COUNTS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 53, 78);
}

/**
 * @brief Encode a skye_thread_counts struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_thread_counts C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_thread_counts_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_thread_counts_t* skye_thread_counts)
{
	return mavlink_msg_skye_thread_counts_pack(system_id, component_id, msg, skye_thread_counts->time_usec, skye_thread_counts->running_threads, skye_thread_counts->heartbeatloop_count, skye_thread_counts->receiveloop_count, skye_thread_counts->telemetryloop_count, skye_thread_counts->gyroaccloop_count, skye_thread_counts->controlloop_count, skye_thread_counts->stateestimation_count);
}

/**
 * @brief Send a skye_thread_counts message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param running_threads Number of running threads
 * @param heartbeatloop_count Counter of heartbeatloop
 * @param receiveloop_count Counter of receiveloop
 * @param telemetryloop_count Counter of telemetryloop
 * @param gyroaccloop_count Counter of gyroaccloop
 * @param controlloop_count Counter of controlloop
 * @param stateestimation_count Counter of stateestimation
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_thread_counts_send(mavlink_channel_t chan, uint32_t time_usec, uint8_t running_threads, uint64_t heartbeatloop_count, uint64_t receiveloop_count, uint64_t telemetryloop_count, uint64_t gyroaccloop_count, uint64_t controlloop_count, uint64_t stateestimation_count)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[53];
	_mav_put_uint64_t(buf, 0, heartbeatloop_count);
	_mav_put_uint64_t(buf, 8, receiveloop_count);
	_mav_put_uint64_t(buf, 16, telemetryloop_count);
	_mav_put_uint64_t(buf, 24, gyroaccloop_count);
	_mav_put_uint64_t(buf, 32, controlloop_count);
	_mav_put_uint64_t(buf, 40, stateestimation_count);
	_mav_put_uint32_t(buf, 48, time_usec);
	_mav_put_uint8_t(buf, 52, running_threads);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_THREAD_COUNTS, buf, 53, 78);
#else
	mavlink_skye_thread_counts_t packet;
	packet.heartbeatloop_count = heartbeatloop_count;
	packet.receiveloop_count = receiveloop_count;
	packet.telemetryloop_count = telemetryloop_count;
	packet.gyroaccloop_count = gyroaccloop_count;
	packet.controlloop_count = controlloop_count;
	packet.stateestimation_count = stateestimation_count;
	packet.time_usec = time_usec;
	packet.running_threads = running_threads;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_THREAD_COUNTS, (const char *)&packet, 53, 78);
#endif
}

#endif

// MESSAGE SKYE_THREAD_COUNTS UNPACKING


/**
 * @brief Get field time_usec from skye_thread_counts message
 *
 * @return Timestamp (since UNIX epoch or microseconds since system boot)
 */
static inline uint32_t mavlink_msg_skye_thread_counts_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  48);
}

/**
 * @brief Get field running_threads from skye_thread_counts message
 *
 * @return Number of running threads
 */
static inline uint8_t mavlink_msg_skye_thread_counts_get_running_threads(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  52);
}

/**
 * @brief Get field heartbeatloop_count from skye_thread_counts message
 *
 * @return Counter of heartbeatloop
 */
static inline uint64_t mavlink_msg_skye_thread_counts_get_heartbeatloop_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field receiveloop_count from skye_thread_counts message
 *
 * @return Counter of receiveloop
 */
static inline uint64_t mavlink_msg_skye_thread_counts_get_receiveloop_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field telemetryloop_count from skye_thread_counts message
 *
 * @return Counter of telemetryloop
 */
static inline uint64_t mavlink_msg_skye_thread_counts_get_telemetryloop_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field gyroaccloop_count from skye_thread_counts message
 *
 * @return Counter of gyroaccloop
 */
static inline uint64_t mavlink_msg_skye_thread_counts_get_gyroaccloop_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  24);
}

/**
 * @brief Get field controlloop_count from skye_thread_counts message
 *
 * @return Counter of controlloop
 */
static inline uint64_t mavlink_msg_skye_thread_counts_get_controlloop_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  32);
}

/**
 * @brief Get field stateestimation_count from skye_thread_counts message
 *
 * @return Counter of stateestimation
 */
static inline uint64_t mavlink_msg_skye_thread_counts_get_stateestimation_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  40);
}

/**
 * @brief Decode a skye_thread_counts message into a struct
 *
 * @param msg The message to decode
 * @param skye_thread_counts C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_thread_counts_decode(const mavlink_message_t* msg, mavlink_skye_thread_counts_t* skye_thread_counts)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_thread_counts->heartbeatloop_count = mavlink_msg_skye_thread_counts_get_heartbeatloop_count(msg);
	skye_thread_counts->receiveloop_count = mavlink_msg_skye_thread_counts_get_receiveloop_count(msg);
	skye_thread_counts->telemetryloop_count = mavlink_msg_skye_thread_counts_get_telemetryloop_count(msg);
	skye_thread_counts->gyroaccloop_count = mavlink_msg_skye_thread_counts_get_gyroaccloop_count(msg);
	skye_thread_counts->controlloop_count = mavlink_msg_skye_thread_counts_get_controlloop_count(msg);
	skye_thread_counts->stateestimation_count = mavlink_msg_skye_thread_counts_get_stateestimation_count(msg);
	skye_thread_counts->time_usec = mavlink_msg_skye_thread_counts_get_time_usec(msg);
	skye_thread_counts->running_threads = mavlink_msg_skye_thread_counts_get_running_threads(msg);
#else
	memcpy(skye_thread_counts, _MAV_PAYLOAD(msg), 53);
#endif
}
