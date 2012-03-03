// MESSAGE TEST_MOTORS PACKING

#define MAVLINK_MSG_ID_TEST_MOTORS 151

typedef struct __mavlink_test_motors_t
{
 float thrust_1; ///< Thrust of motor 1, range [-1,1]
 float thrust_2; ///< Thrust of motor 2, range [-1,1]
 float thrust_3; ///< Thrust of motor 3, range [-1,1]
 float thrust_4; ///< Thrust of motor 4, range [-1,1]
 float direct_1; ///< Direction of direction motor 1, in radians
 float direct_2; ///< Direction of direction motor 2, in radians
 float direct_3; ///< Direction of direction motor 3, in radians
 float direct_4; ///< Direction of direction motor 4, in radians
 uint8_t target_system; ///< System ID
} mavlink_test_motors_t;

#define MAVLINK_MSG_ID_TEST_MOTORS_LEN 33
#define MAVLINK_MSG_ID_151_LEN 33



#define MAVLINK_MESSAGE_INFO_TEST_MOTORS { \
	"TEST_MOTORS", \
	9, \
	{  { "thrust_1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_test_motors_t, thrust_1) }, \
         { "thrust_2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_test_motors_t, thrust_2) }, \
         { "thrust_3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_test_motors_t, thrust_3) }, \
         { "thrust_4", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_test_motors_t, thrust_4) }, \
         { "direct_1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_test_motors_t, direct_1) }, \
         { "direct_2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_test_motors_t, direct_2) }, \
         { "direct_3", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_test_motors_t, direct_3) }, \
         { "direct_4", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_test_motors_t, direct_4) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_test_motors_t, target_system) }, \
         } \
}


/**
 * @brief Pack a test_motors message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param thrust_1 Thrust of motor 1, range [-1,1]
 * @param thrust_2 Thrust of motor 2, range [-1,1]
 * @param thrust_3 Thrust of motor 3, range [-1,1]
 * @param thrust_4 Thrust of motor 4, range [-1,1]
 * @param direct_1 Direction of direction motor 1, in radians
 * @param direct_2 Direction of direction motor 2, in radians
 * @param direct_3 Direction of direction motor 3, in radians
 * @param direct_4 Direction of direction motor 4, in radians
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_motors_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, float thrust_1, float thrust_2, float thrust_3, float thrust_4, float direct_1, float direct_2, float direct_3, float direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[33];
	_mav_put_float(buf, 0, thrust_1);
	_mav_put_float(buf, 4, thrust_2);
	_mav_put_float(buf, 8, thrust_3);
	_mav_put_float(buf, 12, thrust_4);
	_mav_put_float(buf, 16, direct_1);
	_mav_put_float(buf, 20, direct_2);
	_mav_put_float(buf, 24, direct_3);
	_mav_put_float(buf, 28, direct_4);
	_mav_put_uint8_t(buf, 32, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 33);
#else
	mavlink_test_motors_t packet;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 33);
#endif

	msg->msgid = MAVLINK_MSG_ID_TEST_MOTORS;
	return mavlink_finalize_message(msg, system_id, component_id, 33, 227);
}

/**
 * @brief Pack a test_motors message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param thrust_1 Thrust of motor 1, range [-1,1]
 * @param thrust_2 Thrust of motor 2, range [-1,1]
 * @param thrust_3 Thrust of motor 3, range [-1,1]
 * @param thrust_4 Thrust of motor 4, range [-1,1]
 * @param direct_1 Direction of direction motor 1, in radians
 * @param direct_2 Direction of direction motor 2, in radians
 * @param direct_3 Direction of direction motor 3, in radians
 * @param direct_4 Direction of direction motor 4, in radians
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_motors_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,float thrust_1,float thrust_2,float thrust_3,float thrust_4,float direct_1,float direct_2,float direct_3,float direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[33];
	_mav_put_float(buf, 0, thrust_1);
	_mav_put_float(buf, 4, thrust_2);
	_mav_put_float(buf, 8, thrust_3);
	_mav_put_float(buf, 12, thrust_4);
	_mav_put_float(buf, 16, direct_1);
	_mav_put_float(buf, 20, direct_2);
	_mav_put_float(buf, 24, direct_3);
	_mav_put_float(buf, 28, direct_4);
	_mav_put_uint8_t(buf, 32, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 33);
#else
	mavlink_test_motors_t packet;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 33);
#endif

	msg->msgid = MAVLINK_MSG_ID_TEST_MOTORS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 33, 227);
}

/**
 * @brief Encode a test_motors struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param test_motors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_motors_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_test_motors_t* test_motors)
{
	return mavlink_msg_test_motors_pack(system_id, component_id, msg, test_motors->target_system, test_motors->thrust_1, test_motors->thrust_2, test_motors->thrust_3, test_motors->thrust_4, test_motors->direct_1, test_motors->direct_2, test_motors->direct_3, test_motors->direct_4);
}

/**
 * @brief Send a test_motors message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param thrust_1 Thrust of motor 1, range [-1,1]
 * @param thrust_2 Thrust of motor 2, range [-1,1]
 * @param thrust_3 Thrust of motor 3, range [-1,1]
 * @param thrust_4 Thrust of motor 4, range [-1,1]
 * @param direct_1 Direction of direction motor 1, in radians
 * @param direct_2 Direction of direction motor 2, in radians
 * @param direct_3 Direction of direction motor 3, in radians
 * @param direct_4 Direction of direction motor 4, in radians
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_test_motors_send(mavlink_channel_t chan, uint8_t target_system, float thrust_1, float thrust_2, float thrust_3, float thrust_4, float direct_1, float direct_2, float direct_3, float direct_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[33];
	_mav_put_float(buf, 0, thrust_1);
	_mav_put_float(buf, 4, thrust_2);
	_mav_put_float(buf, 8, thrust_3);
	_mav_put_float(buf, 12, thrust_4);
	_mav_put_float(buf, 16, direct_1);
	_mav_put_float(buf, 20, direct_2);
	_mav_put_float(buf, 24, direct_3);
	_mav_put_float(buf, 28, direct_4);
	_mav_put_uint8_t(buf, 32, target_system);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_MOTORS, buf, 33, 227);
#else
	mavlink_test_motors_t packet;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;
	packet.direct_1 = direct_1;
	packet.direct_2 = direct_2;
	packet.direct_3 = direct_3;
	packet.direct_4 = direct_4;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST_MOTORS, (const char *)&packet, 33, 227);
#endif
}

#endif

// MESSAGE TEST_MOTORS UNPACKING


/**
 * @brief Get field target_system from test_motors message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_test_motors_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field thrust_1 from test_motors message
 *
 * @return Thrust of motor 1, range [-1,1]
 */
static inline float mavlink_msg_test_motors_get_thrust_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field thrust_2 from test_motors message
 *
 * @return Thrust of motor 2, range [-1,1]
 */
static inline float mavlink_msg_test_motors_get_thrust_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field thrust_3 from test_motors message
 *
 * @return Thrust of motor 3, range [-1,1]
 */
static inline float mavlink_msg_test_motors_get_thrust_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field thrust_4 from test_motors message
 *
 * @return Thrust of motor 4, range [-1,1]
 */
static inline float mavlink_msg_test_motors_get_thrust_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field direct_1 from test_motors message
 *
 * @return Direction of direction motor 1, in radians
 */
static inline float mavlink_msg_test_motors_get_direct_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field direct_2 from test_motors message
 *
 * @return Direction of direction motor 2, in radians
 */
static inline float mavlink_msg_test_motors_get_direct_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field direct_3 from test_motors message
 *
 * @return Direction of direction motor 3, in radians
 */
static inline float mavlink_msg_test_motors_get_direct_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field direct_4 from test_motors message
 *
 * @return Direction of direction motor 4, in radians
 */
static inline float mavlink_msg_test_motors_get_direct_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Decode a test_motors message into a struct
 *
 * @param msg The message to decode
 * @param test_motors C-struct to decode the message contents into
 */
static inline void mavlink_msg_test_motors_decode(const mavlink_message_t* msg, mavlink_test_motors_t* test_motors)
{
#if MAVLINK_NEED_BYTE_SWAP
	test_motors->thrust_1 = mavlink_msg_test_motors_get_thrust_1(msg);
	test_motors->thrust_2 = mavlink_msg_test_motors_get_thrust_2(msg);
	test_motors->thrust_3 = mavlink_msg_test_motors_get_thrust_3(msg);
	test_motors->thrust_4 = mavlink_msg_test_motors_get_thrust_4(msg);
	test_motors->direct_1 = mavlink_msg_test_motors_get_direct_1(msg);
	test_motors->direct_2 = mavlink_msg_test_motors_get_direct_2(msg);
	test_motors->direct_3 = mavlink_msg_test_motors_get_direct_3(msg);
	test_motors->direct_4 = mavlink_msg_test_motors_get_direct_4(msg);
	test_motors->target_system = mavlink_msg_test_motors_get_target_system(msg);
#else
	memcpy(test_motors, _MAV_PAYLOAD(msg), 33);
#endif
}
