// MESSAGE SKYE_MOTOR_SIGNAL PACKING

#define MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL 158

typedef struct __mavlink_skye_motor_signal_t
{
 uint32_t time_usec; ///< Timestamp (since UNIX epoch or microseconds since system boot)
 uint16_t thrust1_raw; ///< Thrust output thruster 1, range [0,200]
 uint16_t thrust2_raw; ///< Thrust output thruster 2, range [0,200]
 uint16_t thrust3_raw; ///< Thrust output thruster 3, range [0,200]
 uint16_t thrust4_raw; ///< Thrust output thruster 4, range [0,200]
 uint16_t position1_raw; ///< Orientation output position motor 1, in 10qc [-360deg: -17614, 360deg: 17614]
 uint16_t position2_raw; ///< Orientation output position motor 2, in 10qc [-360deg: -17614, 360deg: 17614]
 uint16_t position3_raw; ///< Orientation output position motor 3, in 10qc [-360deg: -17614, 360deg: 17614]
 uint16_t position4_raw; ///< Orientation output position motor 4, in 10qc [-360deg: -17614, 360deg: 17614]
 int16_t direct_1; ///< Direction of direction motor 1, in 10qc [-360deg: -17614, 360deg: 17614] 
 int16_t direct_2; ///< Direction of direction motor 2, in 10qc [-360deg: -17614, 360deg: 17614] 
 int16_t direct_3; ///< Direction of direction motor 3, in 10qc [-360deg: -17614, 360deg: 17614] 
 int16_t direct_4; ///< Direction of direction motor 4, in 10qc [-360deg: -17614, 360deg: 17614] 
 uint8_t thrust_1; ///< Thrust of motor 1, range [0,200]
 uint8_t thrust_2; ///< Thrust of motor 2, range [0,200]
 uint8_t thrust_3; ///< Thrust of motor 3, range [0,200]
 uint8_t thrust_4; ///< Thrust of motor 4, range [0,200]
} mavlink_skye_motor_signal_t;

#define MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL_LEN 32
#define MAVLINK_MSG_ID_158_LEN 32



#define MAVLINK_MESSAGE_INFO_SKYE_MOTOR_SIGNAL { \
	"SKYE_MOTOR_SIGNAL", \
	17, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_skye_motor_signal_t, time_usec) }, \
         { "thrust1_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_skye_motor_signal_t, thrust1_raw) }, \
         { "thrust2_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_skye_motor_signal_t, thrust2_raw) }, \
         { "thrust3_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_skye_motor_signal_t, thrust3_raw) }, \
         { "thrust4_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_skye_motor_signal_t, thrust4_raw) }, \
         { "position1_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_skye_motor_signal_t, position1_raw) }, \
         { "position2_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_skye_motor_signal_t, position2_raw) }, \
         { "position3_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_skye_motor_signal_t, position3_raw) }, \
         { "position4_raw", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_skye_motor_signal_t, position4_raw) }, \
         { "direct_1", NULL, MAVLINK_TYPE_INT16_T, 0, 20, offsetof(mavlink_skye_motor_signal_t, direct_1) }, \
         { "direct_2", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_skye_motor_signal_t, direct_2) }, \
         { "direct_3", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_skye_motor_signal_t, direct_3) }, \
         { "direct_4", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_skye_motor_signal_t, direct_4) }, \
         { "thrust_1", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_skye_motor_signal_t, thrust_1) }, \
         { "thrust_2", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_skye_motor_signal_t, thrust_2) }, \
         { "thrust_3", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_skye_motor_signal_t, thrust_3) }, \
         { "thrust_4", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_skye_motor_signal_t, thrust_4) }, \
         } \
}


/**
 * @brief Pack a skye_motor_signal message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Thrust output thruster 1, range [0,200]
 * @param thrust2_raw Thrust output thruster 2, range [0,200]
 * @param thrust3_raw Thrust output thruster 3, range [0,200]
 * @param thrust4_raw Thrust output thruster 4, range [0,200]
 * @param position1_raw Orientation output position motor 1, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position2_raw Orientation output position motor 2, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position3_raw Orientation output position motor 3, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position4_raw Orientation output position motor 4, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param thrust_1 Thrust of motor 1, range [0,200]
 * @param thrust_2 Thrust of motor 2, range [0,200]
 * @param thrust_3 Thrust of motor 3, range [0,200]
 * @param thrust_4 Thrust of motor 4, range [0,200]
 * @param direct_1 Direction of direction motor 1, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_2 Direction of direction motor 2, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_3 Direction of direction motor 3, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_4 Direction of direction motor 4, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_motor_signal_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, uint16_t thrust1_raw, uint16_t thrust2_raw, uint16_t thrust3_raw, uint16_t thrust4_raw, uint16_t position1_raw, uint16_t position2_raw, uint16_t position3_raw, uint16_t position4_raw, uint8_t thrust_1, uint8_t thrust_2, uint8_t thrust_3, uint8_t thrust_4, int16_t direct_1, int16_t direct_2, int16_t direct_3, int16_t direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[32];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);
	_mav_put_uint16_t(buf, 12, position1_raw);
	_mav_put_uint16_t(buf, 14, position2_raw);
	_mav_put_uint16_t(buf, 16, position3_raw);
	_mav_put_uint16_t(buf, 18, position4_raw);
	_mav_put_int16_t(buf, 20, direct_1);
	_mav_put_int16_t(buf, 22, direct_2);
	_mav_put_int16_t(buf, 24, direct_3);
	_mav_put_int16_t(buf, 26, direct_4);
	_mav_put_uint8_t(buf, 28, thrust_1);
	_mav_put_uint8_t(buf, 29, thrust_2);
	_mav_put_uint8_t(buf, 30, thrust_3);
	_mav_put_uint8_t(buf, 31, thrust_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 32);
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
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 32);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL;
	return mavlink_finalize_message(msg, system_id, component_id, 32, 215);
}

/**
 * @brief Pack a skye_motor_signal message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Thrust output thruster 1, range [0,200]
 * @param thrust2_raw Thrust output thruster 2, range [0,200]
 * @param thrust3_raw Thrust output thruster 3, range [0,200]
 * @param thrust4_raw Thrust output thruster 4, range [0,200]
 * @param position1_raw Orientation output position motor 1, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position2_raw Orientation output position motor 2, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position3_raw Orientation output position motor 3, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position4_raw Orientation output position motor 4, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param thrust_1 Thrust of motor 1, range [0,200]
 * @param thrust_2 Thrust of motor 2, range [0,200]
 * @param thrust_3 Thrust of motor 3, range [0,200]
 * @param thrust_4 Thrust of motor 4, range [0,200]
 * @param direct_1 Direction of direction motor 1, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_2 Direction of direction motor 2, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_3 Direction of direction motor 3, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_4 Direction of direction motor 4, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_motor_signal_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,uint16_t thrust1_raw,uint16_t thrust2_raw,uint16_t thrust3_raw,uint16_t thrust4_raw,uint16_t position1_raw,uint16_t position2_raw,uint16_t position3_raw,uint16_t position4_raw,uint8_t thrust_1,uint8_t thrust_2,uint8_t thrust_3,uint8_t thrust_4,int16_t direct_1,int16_t direct_2,int16_t direct_3,int16_t direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[32];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);
	_mav_put_uint16_t(buf, 12, position1_raw);
	_mav_put_uint16_t(buf, 14, position2_raw);
	_mav_put_uint16_t(buf, 16, position3_raw);
	_mav_put_uint16_t(buf, 18, position4_raw);
	_mav_put_int16_t(buf, 20, direct_1);
	_mav_put_int16_t(buf, 22, direct_2);
	_mav_put_int16_t(buf, 24, direct_3);
	_mav_put_int16_t(buf, 26, direct_4);
	_mav_put_uint8_t(buf, 28, thrust_1);
	_mav_put_uint8_t(buf, 29, thrust_2);
	_mav_put_uint8_t(buf, 30, thrust_3);
	_mav_put_uint8_t(buf, 31, thrust_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 32);
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
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 32);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 32, 215);
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
	return mavlink_msg_skye_motor_signal_pack(system_id, component_id, msg, skye_motor_signal->time_usec, skye_motor_signal->thrust1_raw, skye_motor_signal->thrust2_raw, skye_motor_signal->thrust3_raw, skye_motor_signal->thrust4_raw, skye_motor_signal->position1_raw, skye_motor_signal->position2_raw, skye_motor_signal->position3_raw, skye_motor_signal->position4_raw, skye_motor_signal->thrust_1, skye_motor_signal->thrust_2, skye_motor_signal->thrust_3, skye_motor_signal->thrust_4, skye_motor_signal->direct_1, skye_motor_signal->direct_2, skye_motor_signal->direct_3, skye_motor_signal->direct_4);
}

/**
 * @brief Send a skye_motor_signal message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param thrust1_raw Thrust output thruster 1, range [0,200]
 * @param thrust2_raw Thrust output thruster 2, range [0,200]
 * @param thrust3_raw Thrust output thruster 3, range [0,200]
 * @param thrust4_raw Thrust output thruster 4, range [0,200]
 * @param position1_raw Orientation output position motor 1, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position2_raw Orientation output position motor 2, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position3_raw Orientation output position motor 3, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param position4_raw Orientation output position motor 4, in 10qc [-360deg: -17614, 360deg: 17614]
 * @param thrust_1 Thrust of motor 1, range [0,200]
 * @param thrust_2 Thrust of motor 2, range [0,200]
 * @param thrust_3 Thrust of motor 3, range [0,200]
 * @param thrust_4 Thrust of motor 4, range [0,200]
 * @param direct_1 Direction of direction motor 1, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_2 Direction of direction motor 2, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_3 Direction of direction motor 3, in 10qc [-360deg: -17614, 360deg: 17614] 
 * @param direct_4 Direction of direction motor 4, in 10qc [-360deg: -17614, 360deg: 17614] 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_motor_signal_send(mavlink_channel_t chan, uint32_t time_usec, uint16_t thrust1_raw, uint16_t thrust2_raw, uint16_t thrust3_raw, uint16_t thrust4_raw, uint16_t position1_raw, uint16_t position2_raw, uint16_t position3_raw, uint16_t position4_raw, uint8_t thrust_1, uint8_t thrust_2, uint8_t thrust_3, uint8_t thrust_4, int16_t direct_1, int16_t direct_2, int16_t direct_3, int16_t direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[32];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 4, thrust1_raw);
	_mav_put_uint16_t(buf, 6, thrust2_raw);
	_mav_put_uint16_t(buf, 8, thrust3_raw);
	_mav_put_uint16_t(buf, 10, thrust4_raw);
	_mav_put_uint16_t(buf, 12, position1_raw);
	_mav_put_uint16_t(buf, 14, position2_raw);
	_mav_put_uint16_t(buf, 16, position3_raw);
	_mav_put_uint16_t(buf, 18, position4_raw);
	_mav_put_int16_t(buf, 20, direct_1);
	_mav_put_int16_t(buf, 22, direct_2);
	_mav_put_int16_t(buf, 24, direct_3);
	_mav_put_int16_t(buf, 26, direct_4);
	_mav_put_uint8_t(buf, 28, thrust_1);
	_mav_put_uint8_t(buf, 29, thrust_2);
	_mav_put_uint8_t(buf, 30, thrust_3);
	_mav_put_uint8_t(buf, 31, thrust_4);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL, buf, 32, 215);
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
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_MOTOR_SIGNAL, (const char *)&packet, 32, 215);
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
 * @return Thrust output thruster 1, range [0,200]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust1_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field thrust2_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 2, range [0,200]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust2_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field thrust3_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 3, range [0,200]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust3_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field thrust4_raw from skye_motor_signal message
 *
 * @return Thrust output thruster 4, range [0,200]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_thrust4_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field position1_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 1, in 10qc [-360deg: -17614, 360deg: 17614]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position1_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field position2_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 2, in 10qc [-360deg: -17614, 360deg: 17614]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position2_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field position3_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 3, in 10qc [-360deg: -17614, 360deg: 17614]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position3_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field position4_raw from skye_motor_signal message
 *
 * @return Orientation output position motor 4, in 10qc [-360deg: -17614, 360deg: 17614]
 */
static inline uint16_t mavlink_msg_skye_motor_signal_get_position4_raw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field thrust_1 from skye_motor_signal message
 *
 * @return Thrust of motor 1, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_motor_signal_get_thrust_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field thrust_2 from skye_motor_signal message
 *
 * @return Thrust of motor 2, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_motor_signal_get_thrust_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  29);
}

/**
 * @brief Get field thrust_3 from skye_motor_signal message
 *
 * @return Thrust of motor 3, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_motor_signal_get_thrust_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  30);
}

/**
 * @brief Get field thrust_4 from skye_motor_signal message
 *
 * @return Thrust of motor 4, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_motor_signal_get_thrust_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field direct_1 from skye_motor_signal message
 *
 * @return Direction of direction motor 1, in 10qc [-360deg: -17614, 360deg: 17614] 
 */
static inline int16_t mavlink_msg_skye_motor_signal_get_direct_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  20);
}

/**
 * @brief Get field direct_2 from skye_motor_signal message
 *
 * @return Direction of direction motor 2, in 10qc [-360deg: -17614, 360deg: 17614] 
 */
static inline int16_t mavlink_msg_skye_motor_signal_get_direct_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  22);
}

/**
 * @brief Get field direct_3 from skye_motor_signal message
 *
 * @return Direction of direction motor 3, in 10qc [-360deg: -17614, 360deg: 17614] 
 */
static inline int16_t mavlink_msg_skye_motor_signal_get_direct_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Get field direct_4 from skye_motor_signal message
 *
 * @return Direction of direction motor 4, in 10qc [-360deg: -17614, 360deg: 17614] 
 */
static inline int16_t mavlink_msg_skye_motor_signal_get_direct_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  26);
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
	skye_motor_signal->direct_1 = mavlink_msg_skye_motor_signal_get_direct_1(msg);
	skye_motor_signal->direct_2 = mavlink_msg_skye_motor_signal_get_direct_2(msg);
	skye_motor_signal->direct_3 = mavlink_msg_skye_motor_signal_get_direct_3(msg);
	skye_motor_signal->direct_4 = mavlink_msg_skye_motor_signal_get_direct_4(msg);
	skye_motor_signal->thrust_1 = mavlink_msg_skye_motor_signal_get_thrust_1(msg);
	skye_motor_signal->thrust_2 = mavlink_msg_skye_motor_signal_get_thrust_2(msg);
	skye_motor_signal->thrust_3 = mavlink_msg_skye_motor_signal_get_thrust_3(msg);
	skye_motor_signal->thrust_4 = mavlink_msg_skye_motor_signal_get_thrust_4(msg);
#else
	memcpy(skye_motor_signal, _MAV_PAYLOAD(msg), 32);
#endif
}
