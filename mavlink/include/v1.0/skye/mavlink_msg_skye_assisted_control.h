// MESSAGE SKYE_ASSISTED_CONTROL PACKING

#define MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL 155

typedef struct __mavlink_skye_assisted_control_t
{
 float translation_lat; ///< Translation (velocity) in Inertial Frame latitude, range [-1,1]
 float translation_long; ///< Translation (velocity) in Inertial Frame longitude, range [-1,1]
 float translation_alt; ///< Translation (velocity) in Inertial Frame altitude, range [-1,1]
 float rotation_x; ///< Roll, range [-1,1]
 float rotation_y; ///< Pitch, range [-1,1]
 float rotation_z; ///< Yaw, range [-1,1]
 uint8_t target_system; ///< System ID
} mavlink_skye_assisted_control_t;

#define MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL_LEN 25
#define MAVLINK_MSG_ID_155_LEN 25



#define MAVLINK_MESSAGE_INFO_SKYE_ASSISTED_CONTROL { \
	"SKYE_ASSISTED_CONTROL", \
	7, \
	{  { "translation_lat", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_skye_assisted_control_t, translation_lat) }, \
         { "translation_long", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_skye_assisted_control_t, translation_long) }, \
         { "translation_alt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_skye_assisted_control_t, translation_alt) }, \
         { "rotation_x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_assisted_control_t, rotation_x) }, \
         { "rotation_y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_assisted_control_t, rotation_y) }, \
         { "rotation_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_skye_assisted_control_t, rotation_z) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_skye_assisted_control_t, target_system) }, \
         } \
}


/**
 * @brief Pack a skye_assisted_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param translation_lat Translation (velocity) in Inertial Frame latitude, range [-1,1]
 * @param translation_long Translation (velocity) in Inertial Frame longitude, range [-1,1]
 * @param translation_alt Translation (velocity) in Inertial Frame altitude, range [-1,1]
 * @param rotation_x Roll, range [-1,1]
 * @param rotation_y Pitch, range [-1,1]
 * @param rotation_z Yaw, range [-1,1]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_assisted_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, float translation_lat, float translation_long, float translation_alt, float rotation_x, float rotation_y, float rotation_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[25];
	_mav_put_float(buf, 0, translation_lat);
	_mav_put_float(buf, 4, translation_long);
	_mav_put_float(buf, 8, translation_alt);
	_mav_put_float(buf, 12, rotation_x);
	_mav_put_float(buf, 16, rotation_y);
	_mav_put_float(buf, 20, rotation_z);
	_mav_put_uint8_t(buf, 24, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 25);
#else
	mavlink_skye_assisted_control_t packet;
	packet.translation_lat = translation_lat;
	packet.translation_long = translation_long;
	packet.translation_alt = translation_alt;
	packet.rotation_x = rotation_x;
	packet.rotation_y = rotation_y;
	packet.rotation_z = rotation_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 25);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL;
	return mavlink_finalize_message(msg, system_id, component_id, 25, 171);
}

/**
 * @brief Pack a skye_assisted_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param translation_lat Translation (velocity) in Inertial Frame latitude, range [-1,1]
 * @param translation_long Translation (velocity) in Inertial Frame longitude, range [-1,1]
 * @param translation_alt Translation (velocity) in Inertial Frame altitude, range [-1,1]
 * @param rotation_x Roll, range [-1,1]
 * @param rotation_y Pitch, range [-1,1]
 * @param rotation_z Yaw, range [-1,1]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_assisted_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,float translation_lat,float translation_long,float translation_alt,float rotation_x,float rotation_y,float rotation_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[25];
	_mav_put_float(buf, 0, translation_lat);
	_mav_put_float(buf, 4, translation_long);
	_mav_put_float(buf, 8, translation_alt);
	_mav_put_float(buf, 12, rotation_x);
	_mav_put_float(buf, 16, rotation_y);
	_mav_put_float(buf, 20, rotation_z);
	_mav_put_uint8_t(buf, 24, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 25);
#else
	mavlink_skye_assisted_control_t packet;
	packet.translation_lat = translation_lat;
	packet.translation_long = translation_long;
	packet.translation_alt = translation_alt;
	packet.rotation_x = rotation_x;
	packet.rotation_y = rotation_y;
	packet.rotation_z = rotation_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 25);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 25, 171);
}

/**
 * @brief Encode a skye_assisted_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_assisted_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_assisted_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_assisted_control_t* skye_assisted_control)
{
	return mavlink_msg_skye_assisted_control_pack(system_id, component_id, msg, skye_assisted_control->target_system, skye_assisted_control->translation_lat, skye_assisted_control->translation_long, skye_assisted_control->translation_alt, skye_assisted_control->rotation_x, skye_assisted_control->rotation_y, skye_assisted_control->rotation_z);
}

/**
 * @brief Send a skye_assisted_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param translation_lat Translation (velocity) in Inertial Frame latitude, range [-1,1]
 * @param translation_long Translation (velocity) in Inertial Frame longitude, range [-1,1]
 * @param translation_alt Translation (velocity) in Inertial Frame altitude, range [-1,1]
 * @param rotation_x Roll, range [-1,1]
 * @param rotation_y Pitch, range [-1,1]
 * @param rotation_z Yaw, range [-1,1]
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_assisted_control_send(mavlink_channel_t chan, uint8_t target_system, float translation_lat, float translation_long, float translation_alt, float rotation_x, float rotation_y, float rotation_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[25];
	_mav_put_float(buf, 0, translation_lat);
	_mav_put_float(buf, 4, translation_long);
	_mav_put_float(buf, 8, translation_alt);
	_mav_put_float(buf, 12, rotation_x);
	_mav_put_float(buf, 16, rotation_y);
	_mav_put_float(buf, 20, rotation_z);
	_mav_put_uint8_t(buf, 24, target_system);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL, buf, 25, 171);
#else
	mavlink_skye_assisted_control_t packet;
	packet.translation_lat = translation_lat;
	packet.translation_long = translation_long;
	packet.translation_alt = translation_alt;
	packet.rotation_x = rotation_x;
	packet.rotation_y = rotation_y;
	packet.rotation_z = rotation_z;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_ASSISTED_CONTROL, (const char *)&packet, 25, 171);
#endif
}

#endif

// MESSAGE SKYE_ASSISTED_CONTROL UNPACKING


/**
 * @brief Get field target_system from skye_assisted_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_assisted_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field translation_lat from skye_assisted_control message
 *
 * @return Translation (velocity) in Inertial Frame latitude, range [-1,1]
 */
static inline float mavlink_msg_skye_assisted_control_get_translation_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field translation_long from skye_assisted_control message
 *
 * @return Translation (velocity) in Inertial Frame longitude, range [-1,1]
 */
static inline float mavlink_msg_skye_assisted_control_get_translation_long(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field translation_alt from skye_assisted_control message
 *
 * @return Translation (velocity) in Inertial Frame altitude, range [-1,1]
 */
static inline float mavlink_msg_skye_assisted_control_get_translation_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field rotation_x from skye_assisted_control message
 *
 * @return Roll, range [-1,1]
 */
static inline float mavlink_msg_skye_assisted_control_get_rotation_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field rotation_y from skye_assisted_control message
 *
 * @return Pitch, range [-1,1]
 */
static inline float mavlink_msg_skye_assisted_control_get_rotation_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field rotation_z from skye_assisted_control message
 *
 * @return Yaw, range [-1,1]
 */
static inline float mavlink_msg_skye_assisted_control_get_rotation_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a skye_assisted_control message into a struct
 *
 * @param msg The message to decode
 * @param skye_assisted_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_assisted_control_decode(const mavlink_message_t* msg, mavlink_skye_assisted_control_t* skye_assisted_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_assisted_control->translation_lat = mavlink_msg_skye_assisted_control_get_translation_lat(msg);
	skye_assisted_control->translation_long = mavlink_msg_skye_assisted_control_get_translation_long(msg);
	skye_assisted_control->translation_alt = mavlink_msg_skye_assisted_control_get_translation_alt(msg);
	skye_assisted_control->rotation_x = mavlink_msg_skye_assisted_control_get_rotation_x(msg);
	skye_assisted_control->rotation_y = mavlink_msg_skye_assisted_control_get_rotation_y(msg);
	skye_assisted_control->rotation_z = mavlink_msg_skye_assisted_control_get_rotation_z(msg);
	skye_assisted_control->target_system = mavlink_msg_skye_assisted_control_get_target_system(msg);
#else
	memcpy(skye_assisted_control, _MAV_PAYLOAD(msg), 25);
#endif
}
