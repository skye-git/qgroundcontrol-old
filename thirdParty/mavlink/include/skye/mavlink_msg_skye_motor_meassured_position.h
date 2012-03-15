// MESSAGE SKYE_MOTOR_MEASSURED_POSITION PACKING

#define MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION 159

typedef struct __mavlink_skye_motor_meassured_position_t
{
 uint32_t time_usec; ///< Timestamp (since UNIX epoch or microseconds since system boot)
 uint16_t thrust1_raw; ///< Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 uint16_t thrust2_raw; ///< Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 uint16_t thrust3_raw; ///< Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 uint16_t thrust4_raw; ///< Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
} mavlink_skye_motor_meassured_position_t;

#define MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION_LEN 12
#define MAVLINK_MSG_ID_159_LEN 12



#define MAVLINK_MESSAGE_INFO_SKYE_MOTOR_MEASSURED_POSITION { \
	"SKYE_MOTOR_MEASSURED_POSITION", \
	5, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_skye_motor_meassured_position_t, time_usec) }, \
         { "thrust1_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_skye_motor_meassured_position_t, thrust1_raw) }, \
         { "thrust2_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_skye_motor_meassured_position_t, thrust2_raw) }, \
         { "thrust3_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_skye_motor_meassured_position_t, thrust3_raw) }, \
         { "thrust4_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_skye_motor_meassured_position_t, thrust4_raw) }, \
         } \
}


/**
 * @brief Pack a skye_motor_meassured_position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust2_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust3_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust4_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, uint16_t thrust1_raw, uint16_t thrust2_raw, uint16_t thrust3_raw, uint16_t thrust4_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[12];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 12);
#else
	mavlink_skye_motor_meassured_position_t packet;
	packet.time_usec = time_usec;
	packet.thrust1_raw = thrust1_raw;
	packet.thrust2_raw = thrust2_raw;
	packet.thrust3_raw = thrust3_raw;
	packet.thrust4_raw = thrust4_raw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 12);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION;
	return mavlink_finalize_message(msg, system_id, component_id, 12, 173);
}

/**
 * @brief Pack a skye_motor_meassured_position message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust2_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust3_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust4_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,uint16_t thrust1_raw,uint16_t thrust2_raw,uint16_t thrust3_raw,uint16_t thrust4_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[12];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 12);
#else
	mavlink_skye_motor_meassured_position_t packet;
	packet.time_usec = time_usec;
	packet.thrust1_raw = thrust1_raw;
	packet.thrust2_raw = thrust2_raw;
	packet.thrust3_raw = thrust3_raw;
	packet.thrust4_raw = thrust4_raw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 12);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 12, 173);
}

/**
 * @brief Encode a skye_motor_meassured_position struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_motor_meassured_position C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_motor_meassured_position_t* skye_motor_meassured_position)
{
	return mavlink_msg_skye_motor_meassured_position_pack(system_id, component_id, msg, skye_motor_meassured_position->time_usec, skye_motor_meassured_position->thrust1_raw, skye_motor_meassured_position->thrust2_raw, skye_motor_meassured_position->thrust3_raw, skye_motor_meassured_position->thrust4_raw);
}

/**
 * @brief Send a skye_motor_meassured_position message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust2_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust3_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 * @param thrust4_raw Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_motor_meassured_position_send(mavlink_channel_t chan, uint32_t time_usec, uint16_t thrust1_raw, uint16_t thrust2_raw, uint16_t thrust3_raw, uint16_t thrust4_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[12];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION, buf, 12, 173);
#else
	mavlink_skye_motor_meassured_position_t packet;
	packet.time_usec = time_usec;
	packet.thrust1_raw = thrust1_raw;
	packet.thrust2_raw = thrust2_raw;
	packet.thrust3_raw = thrust3_raw;
	packet.thrust4_raw = thrust4_raw;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_MOTOR_MEASSURED_POSITION, (const char *)&packet, 12, 173);
#endif
}

#endif

// MESSAGE SKYE_MOTOR_MEASSURED_POSITION UNPACKING


/**
 * @brief Get field time_usec from skye_motor_meassured_position message
 *
 * @return Timestamp (since UNIX epoch or microseconds since system boot)
 */
static inline uint32_t mavlink_msg_skye_motor_meassured_position_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field thrust1_raw from skye_motor_meassured_position message
 *
 * @return Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_get_thrust1_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field thrust2_raw from skye_motor_meassured_position message
 *
 * @return Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_get_thrust2_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field thrust3_raw from skye_motor_meassured_position message
 *
 * @return Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_get_thrust3_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field thrust4_raw from skye_motor_meassured_position message
 *
 * @return Meassureed orientation motor 1 (Homing position: 0, 360deg: 36000)
 */
static inline uint16_t mavlink_msg_skye_motor_meassured_position_get_thrust4_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Decode a skye_motor_meassured_position message into a struct
 *
 * @param msg The message to decode
 * @param skye_motor_meassured_position C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_motor_meassured_position_decode(const mavlink_message_t* msg, mavlink_skye_motor_meassured_position_t* skye_motor_meassured_position)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_motor_meassured_position->time_usec = mavlink_msg_skye_motor_meassured_position_get_time_usec(msg);
	skye_motor_meassured_position->thrust1_raw = mavlink_msg_skye_motor_meassured_position_get_thrust1_raw(msg);
	skye_motor_meassured_position->thrust2_raw = mavlink_msg_skye_motor_meassured_position_get_thrust2_raw(msg);
	skye_motor_meassured_position->thrust3_raw = mavlink_msg_skye_motor_meassured_position_get_thrust3_raw(msg);
	skye_motor_meassured_position->thrust4_raw = mavlink_msg_skye_motor_meassured_position_get_thrust4_raw(msg);
#else
	memcpy(skye_motor_meassured_position, _MAV_PAYLOAD(msg), 12);
#endif
}
