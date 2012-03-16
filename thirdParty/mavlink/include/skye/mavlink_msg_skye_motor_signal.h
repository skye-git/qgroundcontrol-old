// MESSAGE SKYE_MOTOR_SIGNAL PACKING

#define MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL 158

typedef struct __mavlink_skye_motor_signal_t
{
 uint32_t time_usec; ///< Timestamp (since UNIX epoch or microseconds since system boot)
 uint16_t thrust1_raw; ///< Thrust output thruster 1 FIXME: VALUES
 uint16_t thrust2_raw; ///< Thrust output thruster 2 FIXME: VALUES
 uint16_t thrust3_raw; ///< Thrust output thruster 3 FIXME: VALUES
 uint16_t thrust4_raw; ///< Thrust output thruster 4 FIXME: VALUES
 uint16_t position1_raw; ///< Orientation output position motor 1 FIXME: VALUES
 uint16_t position2_raw; ///< Orientation output position motor 2 FIXME: VALUES
 uint16_t position3_raw; ///< Orientation output position motor 3 FIXME: VALUES
 uint16_t position4_raw; ///< Orientation output position motor 4 FIXME: VALUES
} mavlink_skye_motor_signal_t;

#define MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL_LEN 20
#define MAVLINK_MSG_ID_158_LEN 20



#define MAVLINK_MESSAGE_INFO_SKYE_MOTOR_SIGNAL { \
	"SKYE_MOTOR_SIGNAL", \
	9, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_skye_motor_signal_t, time_usec) }, \
         { "thrust1_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_skye_motor_signal_t, thrust1_raw) }, \
         { "thrust2_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_skye_motor_signal_t, thrust2_raw) }, \
         { "thrust3_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_skye_motor_signal_t, thrust3_raw) }, \
         { "thrust4_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_skye_motor_signal_t, thrust4_raw) }, \
         { "position1_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_skye_motor_signal_t, position1_raw) }, \
         { "position2_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_skye_motor_signal_t, position2_raw) }, \
         { "position3_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_skye_motor_signal_t, position3_raw) }, \
         { "position4_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_skye_motor_signal_t, position4_raw) }, \
         } \
}


/**
 * @brief Pack a skye_motor_signal message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Thrust output thruster 1 FIXME: VALUES
 * @param thrust2_raw Thrust output thruster 2 FIXME: VALUES
 * @param thrust3_raw Thrust output thruster 3 FIXME: VALUES
 * @param thrust4_raw Thrust output thruster 4 FIXME: VALUES
 * @param position1_raw Orientation output position motor 1 FIXME: VALUES
 * @param position2_raw Orientation output position motor 2 FIXME: VALUES
 * @param position3_raw Orientation output position motor 3 FIXME: VALUES
 * @param position4_raw Orientation output position motor 4 FIXME: VALUES
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_motor_signal_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, uint16_t thrust1_raw, uint16_t thrust2_raw, uint16_t thrust3_raw, uint16_t thrust4_raw, uint16_t position1_raw, uint16_t position2_raw, uint16_t position3_raw, uint16_t position4_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[20];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);
	_mav_put_uint16_t(buf, 12, position1_raw);
	_mav_put_uint16_t(buf, 14, position2_raw);
	_mav_put_uint16_t(buf, 16, position3_raw);
	_mav_put_uint16_t(buf, 18, position4_raw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 20);
#else
	mavlink_skye_motor_signal_t packet;
	packet.time_usec = time_usec;
	packet.thrust1_raw = thrust1_raw;
	packet.thrust2_raw = thrust2_raw;
	packet.thrust3_raw = thrust3_raw;
	packet.thrust4_raw = thrust4_raw;
	packet.position1_raw = position1_raw;
	packet.position2_raw = position2_raw;
	packet.position3_raw = position3_raw;
	packet.position4_raw = position4_raw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 20);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL;
	return mavlink_finalize_message(msg, system_id, component_id, 20, 215);
}

/**
 * @brief Pack a skye_motor_signal message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Thrust output thruster 1 FIXME: VALUES
 * @param thrust2_raw Thrust output thruster 2 FIXME: VALUES
 * @param thrust3_raw Thrust output thruster 3 FIXME: VALUES
 * @param thrust4_raw Thrust output thruster 4 FIXME: VALUES
 * @param position1_raw Orientation output position motor 1 FIXME: VALUES
 * @param position2_raw Orientation output position motor 2 FIXME: VALUES
 * @param position3_raw Orientation output position motor 3 FIXME: VALUES
 * @param position4_raw Orientation output position motor 4 FIXME: VALUES
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_motor_signal_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,uint16_t thrust1_raw,uint16_t thrust2_raw,uint16_t thrust3_raw,uint16_t thrust4_raw,uint16_t position1_raw,uint16_t position2_raw,uint16_t position3_raw,uint16_t position4_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[20];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);
	_mav_put_uint16_t(buf, 12, position1_raw);
	_mav_put_uint16_t(buf, 14, position2_raw);
	_mav_put_uint16_t(buf, 16, position3_raw);
	_mav_put_uint16_t(buf, 18, position4_raw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 20);
#else
	mavlink_skye_motor_signal_t packet;
	packet.time_usec = time_usec;
	packet.thrust1_raw = thrust1_raw;
	packet.thrust2_raw = thrust2_raw;
	packet.thrust3_raw = thrust3_raw;
	packet.thrust4_raw = thrust4_raw;
	packet.position1_raw = position1_raw;
	packet.position2_raw = position2_raw;
	packet.position3_raw = position3_raw;
	packet.position4_raw = position4_raw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 20);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 20, 215);
}

/**
 * @brief Encode a skye_motor_signal struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_motor_signal C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_motor_signal_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_motor_signal_t* skye_motor_signal)
{
	return mavlink_msg_skye_motor_signal_pack(system_id, component_id, msg, skye_motor_signal->time_usec, skye_motor_signal->thrust1_raw, skye_motor_signal->thrust2_raw, skye_motor_signal->thrust3_raw, skye_motor_signal->thrust4_raw, skye_motor_signal->position1_raw, skye_motor_signal->position2_raw, skye_motor_signal->position3_raw, skye_motor_signal->position4_raw);
}

/**
 * @brief Send a skye_motor_signal message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Thrust output thruster 1 FIXME: VALUES
 * @param thrust2_raw Thrust output thruster 2 FIXME: VALUES
 * @param thrust3_raw Thrust output thruster 3 FIXME: VALUES
 * @param thrust4_raw Thrust output thruster 4 FIXME: VALUES
 * @param position1_raw Orientation output position motor 1 FIXME: VALUES
 * @param position2_raw Orientation output position motor 2 FIXME: VALUES
 * @param position3_raw Orientation output position motor 3 FIXME: VALUES
 * @param position4_raw Orientation output position motor 4 FIXME: VALUES
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_motor_signal_send(mavlink_channel_t chan, uint32_t time_usec, uint16_t thrust1_raw, uint16_t thrust2_raw, uint16_t thrust3_raw, uint16_t thrust4_raw, uint16_t position1_raw, uint16_t position2_raw, uint16_t position3_raw, uint16_t position4_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[20];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);
	_mav_put_uint16_t(buf, 12, position1_raw);
	_mav_put_uint16_t(buf, 14, position2_raw);
	_mav_put_uint16_t(buf, 16, position3_raw);
	_mav_put_uint16_t(buf, 18, position4_raw);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL, buf, 20, 215);
#else
	mavlink_skye_motor_signal_t packet;
	packet.time_usec = time_usec;
	packet.thrust1_raw = thrust1_raw;
	packet.thrust2_raw = thrust2_raw;
	packet.thrust3_raw = thrust3_raw;
	packet.thrust4_raw = thrust4_raw;
	packet.position1_raw = position1_raw;
	packet.position2_raw = position2_raw;
	packet.position3_raw = position3_raw;
	packet.position4_raw = position4_raw;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL, (const char *)&packet, 20, 215);
#endif
}

#endif

// MESSAGE SKYE_MOTOR_SIGNAL UNPACKING


/**
 * @brief Get field time_usec from skye_motor_signal message
 *
 * @return Timestamp (since UNIX epoch or microseconds since system boot)
 */
static inline uint32_t mavlink_msg_skye_motor_signal_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field thrust1_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 1 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust1_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field thrust2_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 2 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust2_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field thrust3_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 3 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust3_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field thrust4_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 4 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust4_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field position1_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 1 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position1_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field position2_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 2 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position2_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field position3_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 3 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position3_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field position4_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 4 FIXME: VALUES
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position4_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Decode a skye_motor_signal message into a struct
 *
 * @param msg The message to decode
 * @param skye_motor_signal C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_motor_signal_decode(const mavlink_message_t* msg, mavlink_skye_motor_signal_t* skye_motor_signal)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_motor_signal->time_usec = mavlink_msg_skye_motor_signal_get_time_usec(msg);
	skye_motor_signal->thrust1_raw = mavlink_msg_skye_motor_signal_get_thrust1_raw(msg);
	skye_motor_signal->thrust2_raw = mavlink_msg_skye_motor_signal_get_thrust2_raw(msg);
	skye_motor_signal->thrust3_raw = mavlink_msg_skye_motor_signal_get_thrust3_raw(msg);
	skye_motor_signal->thrust4_raw = mavlink_msg_skye_motor_signal_get_thrust4_raw(msg);
	skye_motor_signal->position1_raw = mavlink_msg_skye_motor_signal_get_position1_raw(msg);
	skye_motor_signal->position2_raw = mavlink_msg_skye_motor_signal_get_position2_raw(msg);
	skye_motor_signal->position3_raw = mavlink_msg_skye_motor_signal_get_position3_raw(msg);
	skye_motor_signal->position4_raw = mavlink_msg_skye_motor_signal_get_position4_raw(msg);
#else
	memcpy(skye_motor_signal, _MAV_PAYLOAD(msg), 20);
#endif
}
