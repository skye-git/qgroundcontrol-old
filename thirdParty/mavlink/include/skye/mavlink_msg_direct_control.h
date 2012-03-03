// MESSAGE DIRECT_CONTROL PACKING

#define MAVLINK_MSG_ID_DIRECT_CONTROL 152

typedef struct __mavlink_direct_control_t
{
 float thrust_x; ///< Resulting thrust in Body Frame x, range [-1,1]
 float thrust_y; ///< Resulting thrust in Body Frame y, range [-1,1]
 float thrust_z; ///< Resulting thrust in Body Frame z, range [-1,1]
 float moment_x; ///< Resulting moment in Body Frame x (roll), range [-1,1]
 float moment_y; ///< Resulting moment in Body Frame y (pitch), range [-1,1]
 float moment_z; ///< Resulting moment in Body Frame z (yaw), range [-1,1]
 uint8_t target_system; ///< System ID
} mavlink_direct_control_t;

#define MAVLINK_MSG_ID_DIRECT_CONTROL_LEN 25
#define MAVLINK_MSG_ID_152_LEN 25



#define MAVLINK_MESSAGE_INFO_DIRECT_CONTROL { \
	"DIRECT_CONTROL", \
	7, \
	{  { "thrust_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_direct_control_t, thrust_x) }, \
         { "thrust_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_direct_control_t, thrust_y) }, \
         { "thrust_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_direct_control_t, thrust_z) }, \
         { "moment_x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_direct_control_t, moment_x) }, \
         { "moment_y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_direct_control_t, moment_y) }, \
         { "moment_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_direct_control_t, moment_z) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_direct_control_t, target_system) }, \
         } \
}


/**
 * @brief Pack a direct_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param thrust_x Resulting thrust in Body Frame x, range [-1,1]
 * @param thrust_y Resulting thrust in Body Frame y, range [-1,1]
 * @param thrust_z Resulting thrust in Body Frame z, range [-1,1]
 * @param moment_x Resulting moment in Body Frame x (roll), range [-1,1]
 * @param moment_y Resulting moment in Body Frame y (pitch), range [-1,1]
 * @param moment_z Resulting moment in Body Frame z (yaw), range [-1,1]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_direct_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
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
	mavlink_direct_control_t packet;
	packet.thrust_x = thrust_x;
	packet.thrust_y = thrust_y;
	packet.thrust_z = thrust_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 25);
#endif

	msg->msgid = MAVLINK_MSG_ID_DIRECT_CONTROL;
	return mavlink_finalize_message(msg, system_id, component_id, 25, 79);
}

/**
 * @brief Pack a direct_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param thrust_x Resulting thrust in Body Frame x, range [-1,1]
 * @param thrust_y Resulting thrust in Body Frame y, range [-1,1]
 * @param thrust_z Resulting thrust in Body Frame z, range [-1,1]
 * @param moment_x Resulting moment in Body Frame x (roll), range [-1,1]
 * @param moment_y Resulting moment in Body Frame y (pitch), range [-1,1]
 * @param moment_z Resulting moment in Body Frame z (yaw), range [-1,1]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_direct_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
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
	mavlink_direct_control_t packet;
	packet.thrust_x = thrust_x;
	packet.thrust_y = thrust_y;
	packet.thrust_z = thrust_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 25);
#endif

	msg->msgid = MAVLINK_MSG_ID_DIRECT_CONTROL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 25, 79);
}

/**
 * @brief Encode a direct_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param direct_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_direct_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_direct_control_t* direct_control)
{
	return mavlink_msg_direct_control_pack(system_id, component_id, msg, direct_control->target_system, direct_control->thrust_x, direct_control->thrust_y, direct_control->thrust_z, direct_control->moment_x, direct_control->moment_y, direct_control->moment_z);
}

/**
 * @brief Send a direct_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param thrust_x Resulting thrust in Body Frame x, range [-1,1]
 * @param thrust_y Resulting thrust in Body Frame y, range [-1,1]
 * @param thrust_z Resulting thrust in Body Frame z, range [-1,1]
 * @param moment_x Resulting moment in Body Frame x (roll), range [-1,1]
 * @param moment_y Resulting moment in Body Frame y (pitch), range [-1,1]
 * @param moment_z Resulting moment in Body Frame z (yaw), range [-1,1]
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_direct_control_send(mavlink_channel_t chan, uint8_t target_system, float thrust_x, float thrust_y, float thrust_z, float moment_x, float moment_y, float moment_z)
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

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DIRECT_CONTROL, buf, 25, 79);
#else
	mavlink_direct_control_t packet;
	packet.thrust_x = thrust_x;
	packet.thrust_y = thrust_y;
	packet.thrust_z = thrust_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DIRECT_CONTROL, (const char *)&packet, 25, 79);
#endif
}

#endif

// MESSAGE DIRECT_CONTROL UNPACKING


/**
 * @brief Get field target_system from direct_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_direct_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field thrust_x from direct_control message
 *
 * @return Resulting thrust in Body Frame x, range [-1,1]
 */
static inline float mavlink_msg_direct_control_get_thrust_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field thrust_y from direct_control message
 *
 * @return Resulting thrust in Body Frame y, range [-1,1]
 */
static inline float mavlink_msg_direct_control_get_thrust_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field thrust_z from direct_control message
 *
 * @return Resulting thrust in Body Frame z, range [-1,1]
 */
static inline float mavlink_msg_direct_control_get_thrust_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field moment_x from direct_control message
 *
 * @return Resulting moment in Body Frame x (roll), range [-1,1]
 */
static inline float mavlink_msg_direct_control_get_moment_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field moment_y from direct_control message
 *
 * @return Resulting moment in Body Frame y (pitch), range [-1,1]
 */
static inline float mavlink_msg_direct_control_get_moment_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field moment_z from direct_control message
 *
 * @return Resulting moment in Body Frame z (yaw), range [-1,1]
 */
static inline float mavlink_msg_direct_control_get_moment_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a direct_control message into a struct
 *
 * @param msg The message to decode
 * @param direct_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_direct_control_decode(const mavlink_message_t* msg, mavlink_direct_control_t* direct_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	direct_control->thrust_x = mavlink_msg_direct_control_get_thrust_x(msg);
	direct_control->thrust_y = mavlink_msg_direct_control_get_thrust_y(msg);
	direct_control->thrust_z = mavlink_msg_direct_control_get_thrust_z(msg);
	direct_control->moment_x = mavlink_msg_direct_control_get_moment_x(msg);
	direct_control->moment_y = mavlink_msg_direct_control_get_moment_y(msg);
	direct_control->moment_z = mavlink_msg_direct_control_get_moment_z(msg);
	direct_control->target_system = mavlink_msg_direct_control_get_target_system(msg);
#else
	memcpy(direct_control, _MAV_PAYLOAD(msg), 25);
#endif
}
