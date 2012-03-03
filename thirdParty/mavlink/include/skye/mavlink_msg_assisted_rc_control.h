// MESSAGE ASSISTED_RC_CONTROL PACKING

#define MAVLINK_MSG_ID_ASSISTED_RC_CONTROL 154

typedef struct __mavlink_assisted_rc_control_t
{
 float translation_x; ///< Translation x [-1,1]
 float rotation_x; ///< Roll, range [-1,1]
 float rotation_y; ///< Pitch, range [-1,1]
 float rotation_z; ///< Yaw, range [-1,1]
 uint8_t target_system; ///< System ID
} mavlink_assisted_rc_control_t;

#define MAVLINK_MSG_ID_ASSISTED_RC_CONTROL_LEN 17
#define MAVLINK_MSG_ID_154_LEN 17



#define MAVLINK_MESSAGE_INFO_ASSISTED_RC_CONTROL { \
	"ASSISTED_RC_CONTROL", \
	5, \
	{  { "translation_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_assisted_rc_control_t, translation_x) }, \
         { "rotation_x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_assisted_rc_control_t, rotation_x) }, \
         { "rotation_y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_assisted_rc_control_t, rotation_y) }, \
         { "rotation_z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_assisted_rc_control_t, rotation_z) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_assisted_rc_control_t, target_system) }, \
         } \
}


/**
 * @brief Pack a assisted_rc_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param translation_x Translation x [-1,1]
 * @param rotation_x Roll, range [-1,1]
 * @param rotation_y Pitch, range [-1,1]
 * @param rotation_z Yaw, range [-1,1]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_assisted_rc_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, float translation_x, float rotation_x, float rotation_y, float rotation_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[17];
	_mav_put_float(buf, 0, translation_x);
	_mav_put_float(buf, 4, rotation_x);
	_mav_put_float(buf, 8, rotation_y);
	_mav_put_float(buf, 12, rotation_z);
	_mav_put_uint8_t(buf, 16, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 17);
#else
	mavlink_assisted_rc_control_t packet;
	packet.translation_x = translation_x;
	packet.rotation_x = rotation_x;
	packet.rotation_y = rotation_y;
	packet.rotation_z = rotation_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 17);
#endif

	msg->msgid = MAVLINK_MSG_ID_ASSISTED_RC_CONTROL;
	return mavlink_finalize_message(msg, system_id, component_id, 17, 85);
}

/**
 * @brief Pack a assisted_rc_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param translation_x Translation x [-1,1]
 * @param rotation_x Roll, range [-1,1]
 * @param rotation_y Pitch, range [-1,1]
 * @param rotation_z Yaw, range [-1,1]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_assisted_rc_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,float translation_x,float rotation_x,float rotation_y,float rotation_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[17];
	_mav_put_float(buf, 0, translation_x);
	_mav_put_float(buf, 4, rotation_x);
	_mav_put_float(buf, 8, rotation_y);
	_mav_put_float(buf, 12, rotation_z);
	_mav_put_uint8_t(buf, 16, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 17);
#else
	mavlink_assisted_rc_control_t packet;
	packet.translation_x = translation_x;
	packet.rotation_x = rotation_x;
	packet.rotation_y = rotation_y;
	packet.rotation_z = rotation_z;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 17);
#endif

	msg->msgid = MAVLINK_MSG_ID_ASSISTED_RC_CONTROL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 17, 85);
}

/**
 * @brief Encode a assisted_rc_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param assisted_rc_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_assisted_rc_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_assisted_rc_control_t* assisted_rc_control)
{
	return mavlink_msg_assisted_rc_control_pack(system_id, component_id, msg, assisted_rc_control->target_system, assisted_rc_control->translation_x, assisted_rc_control->rotation_x, assisted_rc_control->rotation_y, assisted_rc_control->rotation_z);
}

/**
 * @brief Send a assisted_rc_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param translation_x Translation x [-1,1]
 * @param rotation_x Roll, range [-1,1]
 * @param rotation_y Pitch, range [-1,1]
 * @param rotation_z Yaw, range [-1,1]
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_assisted_rc_control_send(mavlink_channel_t chan, uint8_t target_system, float translation_x, float rotation_x, float rotation_y, float rotation_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[17];
	_mav_put_float(buf, 0, translation_x);
	_mav_put_float(buf, 4, rotation_x);
	_mav_put_float(buf, 8, rotation_y);
	_mav_put_float(buf, 12, rotation_z);
	_mav_put_uint8_t(buf, 16, target_system);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ASSISTED_RC_CONTROL, buf, 17, 85);
#else
	mavlink_assisted_rc_control_t packet;
	packet.translation_x = translation_x;
	packet.rotation_x = rotation_x;
	packet.rotation_y = rotation_y;
	packet.rotation_z = rotation_z;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ASSISTED_RC_CONTROL, (const char *)&packet, 17, 85);
#endif
}

#endif

// MESSAGE ASSISTED_RC_CONTROL UNPACKING


/**
 * @brief Get field target_system from assisted_rc_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_assisted_rc_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field translation_x from assisted_rc_control message
 *
 * @return Translation x [-1,1]
 */
static inline float mavlink_msg_assisted_rc_control_get_translation_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field rotation_x from assisted_rc_control message
 *
 * @return Roll, range [-1,1]
 */
static inline float mavlink_msg_assisted_rc_control_get_rotation_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field rotation_y from assisted_rc_control message
 *
 * @return Pitch, range [-1,1]
 */
static inline float mavlink_msg_assisted_rc_control_get_rotation_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field rotation_z from assisted_rc_control message
 *
 * @return Yaw, range [-1,1]
 */
static inline float mavlink_msg_assisted_rc_control_get_rotation_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a assisted_rc_control message into a struct
 *
 * @param msg The message to decode
 * @param assisted_rc_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_assisted_rc_control_decode(const mavlink_message_t* msg, mavlink_assisted_rc_control_t* assisted_rc_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	assisted_rc_control->translation_x = mavlink_msg_assisted_rc_control_get_translation_x(msg);
	assisted_rc_control->rotation_x = mavlink_msg_assisted_rc_control_get_rotation_x(msg);
	assisted_rc_control->rotation_y = mavlink_msg_assisted_rc_control_get_rotation_y(msg);
	assisted_rc_control->rotation_z = mavlink_msg_assisted_rc_control_get_rotation_z(msg);
	assisted_rc_control->target_system = mavlink_msg_assisted_rc_control_get_target_system(msg);
#else
	memcpy(assisted_rc_control, _MAV_PAYLOAD(msg), 17);
#endif
}
