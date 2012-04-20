// MESSAGE SKYE_DIRECT_CONTROL PACKING

#define MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL 154

typedef struct __mavlink_skye_direct_control_t
{
 float thrust_x; ///< Resulting thrust in Body Frame x, in Newton
 float thrust_y; ///< Resulting thrust in Body Frame y, in Newton
 float thrust_z; ///< Resulting thrust in Body Frame z, in Newton
 float moment_x; ///< Resulting moment in Body Frame x (roll), in Newtonmeter
 float moment_y; ///< Resulting moment in Body Frame y (pitch), in Newtonmeter
 float moment_z; ///< Resulting moment in Body Frame z (yaw), in Newtonmeter
 uint8_t target_system; ///< System ID
} mavlink_skye_direct_control_t;

#define MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL_LEN 25
#define MAVLINK_MSG_ID_154_LEN 25



#define MAVLINK_MESSAGE_INFO_SKYE_DIRECT_CONTROL { \
	"SKYE_DIRECT_CONTROL", \
	7, \
	{  { "thrust_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_skye_direct_control_t, thrust_x) }, \
         { "thrust_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_skye_direct_control_t, thrust_y) }, \
         { "thrust_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_skye_direct_control_t, thrust_z) }, \
         { "moment_x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_direct_control_t, moment_x) }, \
         { "moment_y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_direct_control_t, moment_y) }, \
         { "moment_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_skye_direct_control_t, moment_z) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_skye_direct_control_t, target_system) }, \
         } \
}


/**
 * @brief Pack a skye_direct_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param thrust_x Resulting thrust in Body Frame x, in Newton
 * @param thrust_y Resulting thrust in Body Frame y, in Newton
 * @param thrust_z Resulting thrust in Body Frame z, in Newton
 * @param moment_x Resulting moment in Body Frame x (roll), in Newtonmeter
 * @param moment_y Resulting moment in Body Frame y (pitch), in Newtonmeter
 * @param moment_z Resulting moment in Body Frame z (yaw), in Newtonmeter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_direct_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, float thrust_x, float thrust_y, float thrust_z, float moment_x, float moment_y, float moment_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[25];
	_mav_put_float(buf, 0, thrust_x);
	_mav_put_float(buf, 4, thrust_y);
	_mav_put_float(buf, 8, thrust_z);
	_mav_put_float(buf, 12, moment_x);
	_mav_put_float(buf, 16, moment_y);
	_mav_put_float(buf, 20, moment_z);
	_mav_put_uint8_t(buf, 24, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 25);
#else
	mavlink_skye_direct_control_t packet;
	packet.thrust_x = thrust_x;
	packet.thrust_y = thrust_y;
	packet.thrust_z = thrust_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 25);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL;
	return mavlink_finalize_message(msg, system_id, component_id, 25, 175);
}

/**
 * @brief Pack a skye_direct_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param thrust_x Resulting thrust in Body Frame x, in Newton
 * @param thrust_y Resulting thrust in Body Frame y, in Newton
 * @param thrust_z Resulting thrust in Body Frame z, in Newton
 * @param moment_x Resulting moment in Body Frame x (roll), in Newtonmeter
 * @param moment_y Resulting moment in Body Frame y (pitch), in Newtonmeter
 * @param moment_z Resulting moment in Body Frame z (yaw), in Newtonmeter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_direct_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,float thrust_x,float thrust_y,float thrust_z,float moment_x,float moment_y,float moment_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[25];
	_mav_put_float(buf, 0, thrust_x);
	_mav_put_float(buf, 4, thrust_y);
	_mav_put_float(buf, 8, thrust_z);
	_mav_put_float(buf, 12, moment_x);
	_mav_put_float(buf, 16, moment_y);
	_mav_put_float(buf, 20, moment_z);
	_mav_put_uint8_t(buf, 24, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 25);
#else
	mavlink_skye_direct_control_t packet;
	packet.thrust_x = thrust_x;
	packet.thrust_y = thrust_y;
	packet.thrust_z = thrust_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 25);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 25, 175);
}

/**
 * @brief Encode a skye_direct_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_direct_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_direct_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_direct_control_t* skye_direct_control)
{
	return mavlink_msg_skye_direct_control_pack(system_id, component_id, msg, skye_direct_control->target_system, skye_direct_control->thrust_x, skye_direct_control->thrust_y, skye_direct_control->thrust_z, skye_direct_control->moment_x, skye_direct_control->moment_y, skye_direct_control->moment_z);
}

/**
 * @brief Send a skye_direct_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param thrust_x Resulting thrust in Body Frame x, in Newton
 * @param thrust_y Resulting thrust in Body Frame y, in Newton
 * @param thrust_z Resulting thrust in Body Frame z, in Newton
 * @param moment_x Resulting moment in Body Frame x (roll), in Newtonmeter
 * @param moment_y Resulting moment in Body Frame y (pitch), in Newtonmeter
 * @param moment_z Resulting moment in Body Frame z (yaw), in Newtonmeter
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_direct_control_send(mavlink_channel_t chan, uint8_t target_system, float thrust_x, float thrust_y, float thrust_z, float moment_x, float moment_y, float moment_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[25];
	_mav_put_float(buf, 0, thrust_x);
	_mav_put_float(buf, 4, thrust_y);
	_mav_put_float(buf, 8, thrust_z);
	_mav_put_float(buf, 12, moment_x);
	_mav_put_float(buf, 16, moment_y);
	_mav_put_float(buf, 20, moment_z);
	_mav_put_uint8_t(buf, 24, target_system);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL, buf, 25, 175);
#else
	mavlink_skye_direct_control_t packet;
	packet.thrust_x = thrust_x;
	packet.thrust_y = thrust_y;
	packet.thrust_z = thrust_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_DIRECT_CONTROL, (const char *)&packet, 25, 175);
#endif
}

#endif

// MESSAGE SKYE_DIRECT_CONTROL UNPACKING


/**
 * @brief Get field target_system from skye_direct_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_direct_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field thrust_x from skye_direct_control message
 *
 * @return Resulting thrust in Body Frame x, in Newton
 */
static inline float mavlink_msg_skye_direct_control_get_thrust_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field thrust_y from skye_direct_control message
 *
 * @return Resulting thrust in Body Frame y, in Newton
 */
static inline float mavlink_msg_skye_direct_control_get_thrust_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field thrust_z from skye_direct_control message
 *
 * @return Resulting thrust in Body Frame z, in Newton
 */
static inline float mavlink_msg_skye_direct_control_get_thrust_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field moment_x from skye_direct_control message
 *
 * @return Resulting moment in Body Frame x (roll), in Newtonmeter
 */
static inline float mavlink_msg_skye_direct_control_get_moment_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field moment_y from skye_direct_control message
 *
 * @return Resulting moment in Body Frame y (pitch), in Newtonmeter
 */
static inline float mavlink_msg_skye_direct_control_get_moment_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field moment_z from skye_direct_control message
 *
 * @return Resulting moment in Body Frame z (yaw), in Newtonmeter
 */
static inline float mavlink_msg_skye_direct_control_get_moment_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a skye_direct_control message into a struct
 *
 * @param msg The message to decode
 * @param skye_direct_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_direct_control_decode(const mavlink_message_t* msg, mavlink_skye_direct_control_t* skye_direct_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_direct_control->thrust_x = mavlink_msg_skye_direct_control_get_thrust_x(msg);
	skye_direct_control->thrust_y = mavlink_msg_skye_direct_control_get_thrust_y(msg);
	skye_direct_control->thrust_z = mavlink_msg_skye_direct_control_get_thrust_z(msg);
	skye_direct_control->moment_x = mavlink_msg_skye_direct_control_get_moment_x(msg);
	skye_direct_control->moment_y = mavlink_msg_skye_direct_control_get_moment_y(msg);
	skye_direct_control->moment_z = mavlink_msg_skye_direct_control_get_moment_z(msg);
	skye_direct_control->target_system = mavlink_msg_skye_direct_control_get_target_system(msg);
#else
	memcpy(skye_direct_control, _MAV_PAYLOAD(msg), 25);
#endif
}
