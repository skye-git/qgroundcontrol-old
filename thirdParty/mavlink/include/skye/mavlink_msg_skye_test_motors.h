// MESSAGE SKYE_TEST_MOTORS PACKING

#define MAVLINK_MSG_ID_SKYE_TEST_MOTORS 153

typedef struct __mavlink_skye_test_motors_t
{
 int16_t direct_1; ///< Direction of direction motor 1, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 int16_t direct_2; ///< Direction of direction motor 2, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 int16_t direct_3; ///< Direction of direction motor 3, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 int16_t direct_4; ///< Direction of direction motor 4, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 uint8_t target_system; ///< System ID
 uint8_t thrust_1; ///< Thrust of motor 1, range [0,200]
 uint8_t thrust_2; ///< Thrust of motor 2, range [0,200]
 uint8_t thrust_3; ///< Thrust of motor 3, range [0,200]
 uint8_t thrust_4; ///< Thrust of motor 4, range [0,200]
} mavlink_skye_test_motors_t;

#define MAVLINK_MSG_ID_SKYE_TEST_MOTORS_LEN 13
#define MAVLINK_MSG_ID_153_LEN 13



#define MAVLINK_MESSAGE_INFO_SKYE_TEST_MOTORS { \
	"SKYE_TEST_MOTORS", \
	9, \
	{  { "direct_1", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_skye_test_motors_t, direct_1) }, \
         { "direct_2", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_skye_test_motors_t, direct_2) }, \
         { "direct_3", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_skye_test_motors_t, direct_3) }, \
         { "direct_4", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_skye_test_motors_t, direct_4) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_skye_test_motors_t, target_system) }, \
         { "thrust_1", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_skye_test_motors_t, thrust_1) }, \
         { "thrust_2", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_skye_test_motors_t, thrust_2) }, \
         { "thrust_3", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_skye_test_motors_t, thrust_3) }, \
         { "thrust_4", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_skye_test_motors_t, thrust_4) }, \
         } \
}


/**
 * @brief Pack a skye_test_motors message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param thrust_1 Thrust of motor 1, range [0,200]
 * @param thrust_2 Thrust of motor 2, range [0,200]
 * @param thrust_3 Thrust of motor 3, range [0,200]
 * @param thrust_4 Thrust of motor 4, range [0,200]
 * @param direct_1 Direction of direction motor 1, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_2 Direction of direction motor 2, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_3 Direction of direction motor 3, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_4 Direction of direction motor 4, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_test_motors_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t thrust_1, uint8_t thrust_2, uint8_t thrust_3, uint8_t thrust_4, int16_t direct_1, int16_t direct_2, int16_t direct_3, int16_t direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_int16_t(buf, 0, direct_1);
	_mav_put_int16_t(buf, 2, direct_2);
	_mav_put_int16_t(buf, 4, direct_3);
	_mav_put_int16_t(buf, 6, direct_4);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, thrust_1);
	_mav_put_uint8_t(buf, 10, thrust_2);
	_mav_put_uint8_t(buf, 11, thrust_3);
	_mav_put_uint8_t(buf, 12, thrust_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 13);
#else
	mavlink_skye_test_motors_t packet;
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.target_system = target_system;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 13);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_TEST_MOTORS;
	return mavlink_finalize_message(msg, system_id, component_id, 13, 204);
}

/**
 * @brief Pack a skye_test_motors message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param thrust_1 Thrust of motor 1, range [0,200]
 * @param thrust_2 Thrust of motor 2, range [0,200]
 * @param thrust_3 Thrust of motor 3, range [0,200]
 * @param thrust_4 Thrust of motor 4, range [0,200]
 * @param direct_1 Direction of direction motor 1, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_2 Direction of direction motor 2, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_3 Direction of direction motor 3, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_4 Direction of direction motor 4, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_test_motors_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t thrust_1,uint8_t thrust_2,uint8_t thrust_3,uint8_t thrust_4,int16_t direct_1,int16_t direct_2,int16_t direct_3,int16_t direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_int16_t(buf, 0, direct_1);
	_mav_put_int16_t(buf, 2, direct_2);
	_mav_put_int16_t(buf, 4, direct_3);
	_mav_put_int16_t(buf, 6, direct_4);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, thrust_1);
	_mav_put_uint8_t(buf, 10, thrust_2);
	_mav_put_uint8_t(buf, 11, thrust_3);
	_mav_put_uint8_t(buf, 12, thrust_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 13);
#else
	mavlink_skye_test_motors_t packet;
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.target_system = target_system;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 13);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_TEST_MOTORS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 13, 204);
}

/**
 * @brief Encode a skye_test_motors struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_test_motors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_test_motors_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_test_motors_t* skye_test_motors)
{
	return mavlink_msg_skye_test_motors_pack(system_id, component_id, msg, skye_test_motors->target_system, skye_test_motors->thrust_1, skye_test_motors->thrust_2, skye_test_motors->thrust_3, skye_test_motors->thrust_4, skye_test_motors->direct_1, skye_test_motors->direct_2, skye_test_motors->direct_3, skye_test_motors->direct_4);
}

/**
 * @brief Send a skye_test_motors message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param thrust_1 Thrust of motor 1, range [0,200]
 * @param thrust_2 Thrust of motor 2, range [0,200]
 * @param thrust_3 Thrust of motor 3, range [0,200]
 * @param thrust_4 Thrust of motor 4, range [0,200]
 * @param direct_1 Direction of direction motor 1, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_2 Direction of direction motor 2, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_3 Direction of direction motor 3, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 * @param direct_4 Direction of direction motor 4, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_test_motors_send(mavlink_channel_t chan, uint8_t target_system, uint8_t thrust_1, uint8_t thrust_2, uint8_t thrust_3, uint8_t thrust_4, int16_t direct_1, int16_t direct_2, int16_t direct_3, int16_t direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_int16_t(buf, 0, direct_1);
	_mav_put_int16_t(buf, 2, direct_2);
	_mav_put_int16_t(buf, 4, direct_3);
	_mav_put_int16_t(buf, 6, direct_4);
	_mav_put_uint8_t(buf, 8, target_system);
	_mav_put_uint8_t(buf, 9, thrust_1);
	_mav_put_uint8_t(buf, 10, thrust_2);
	_mav_put_uint8_t(buf, 11, thrust_3);
	_mav_put_uint8_t(buf, 12, thrust_4);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_TEST_MOTORS, buf, 13, 204);
#else
	mavlink_skye_test_motors_t packet;
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.target_system = target_system;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_TEST_MOTORS, (const char *)&packet, 13, 204);
#endif
}

#endif

// MESSAGE SKYE_TEST_MOTORS UNPACKING


/**
 * @brief Get field target_system from skye_test_motors message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_test_motors_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field thrust_1 from skye_test_motors message
 *
 * @return Thrust of motor 1, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_test_motors_get_thrust_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field thrust_2 from skye_test_motors message
 *
 * @return Thrust of motor 2, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_test_motors_get_thrust_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field thrust_3 from skye_test_motors message
 *
 * @return Thrust of motor 3, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_test_motors_get_thrust_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field thrust_4 from skye_test_motors message
 *
 * @return Thrust of motor 4, range [0,200]
 */
static inline uint8_t mavlink_msg_skye_test_motors_get_thrust_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field direct_1 from skye_test_motors message
 *
 * @return Direction of direction motor 1, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 */
static inline int16_t mavlink_msg_skye_test_motors_get_direct_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field direct_2 from skye_test_motors message
 *
 * @return Direction of direction motor 2, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 */
static inline int16_t mavlink_msg_skye_test_motors_get_direct_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field direct_3 from skye_test_motors message
 *
 * @return Direction of direction motor 3, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 */
static inline int16_t mavlink_msg_skye_test_motors_get_direct_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field direct_4 from skye_test_motors message
 *
 * @return Direction of direction motor 4, in 0.1 degrees [-360deg: -3600, 360deg: 3600] 
 */
static inline int16_t mavlink_msg_skye_test_motors_get_direct_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Decode a skye_test_motors message into a struct
 *
 * @param msg The message to decode
 * @param skye_test_motors C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_test_motors_decode(const mavlink_message_t* msg, mavlink_skye_test_motors_t* skye_test_motors)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_test_motors->direct_1 = mavlink_msg_skye_test_motors_get_direct_1(msg);
	skye_test_motors->direct_2 = mavlink_msg_skye_test_motors_get_direct_2(msg);
	skye_test_motors->direct_3 = mavlink_msg_skye_test_motors_get_direct_3(msg);
	skye_test_motors->direct_4 = mavlink_msg_skye_test_motors_get_direct_4(msg);
	skye_test_motors->target_system = mavlink_msg_skye_test_motors_get_target_system(msg);
	skye_test_motors->thrust_1 = mavlink_msg_skye_test_motors_get_thrust_1(msg);
	skye_test_motors->thrust_2 = mavlink_msg_skye_test_motors_get_thrust_2(msg);
	skye_test_motors->thrust_3 = mavlink_msg_skye_test_motors_get_thrust_3(msg);
	skye_test_motors->thrust_4 = mavlink_msg_skye_test_motors_get_thrust_4(msg);
#else
	memcpy(skye_test_motors, _MAV_PAYLOAD(msg), 13);
#endif
}
