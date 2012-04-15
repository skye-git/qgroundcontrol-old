// MESSAGE SKYE_HOME_MAXON PACKING

#define MAVLINK_MSG_ID_SKYE_HOME_MAXON 166

typedef struct __mavlink_skye_home_maxon_t
{
 uint8_t target_system; ///< System ID
 uint8_t homing; ///< Boolean, true: home maxon motors
} mavlink_skye_home_maxon_t;

#define MAVLINK_MSG_ID_SKYE_HOME_MAXON_LEN 2
#define MAVLINK_MSG_ID_166_LEN 2



#define MAVLINK_MESSAGE_INFO_SKYE_HOME_MAXON { \
	"SKYE_HOME_MAXON", \
	2, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_skye_home_maxon_t, target_system) }, \
         { "homing", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_skye_home_maxon_t, homing) }, \
         } \
}


/**
 * @brief Pack a skye_home_maxon message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param homing Boolean, true: home maxon motors
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_home_maxon_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t homing)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, homing);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 2);
#else
	mavlink_skye_home_maxon_t packet;
	packet.target_system = target_system;
	packet.homing = homing;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_HOME_MAXON;
	return mavlink_finalize_message(msg, system_id, component_id, 2, 219);
}

/**
 * @brief Pack a skye_home_maxon message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param homing Boolean, true: home maxon motors
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_home_maxon_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t homing)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, homing);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 2);
#else
	mavlink_skye_home_maxon_t packet;
	packet.target_system = target_system;
	packet.homing = homing;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_HOME_MAXON;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 2, 219);
}

/**
 * @brief Encode a skye_home_maxon struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_home_maxon C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_home_maxon_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_home_maxon_t* skye_home_maxon)
{
	return mavlink_msg_skye_home_maxon_pack(system_id, component_id, msg, skye_home_maxon->target_system, skye_home_maxon->homing);
}

/**
 * @brief Send a skye_home_maxon message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param homing Boolean, true: home maxon motors
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_home_maxon_send(mavlink_channel_t chan, uint8_t target_system, uint8_t homing)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, homing);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_HOME_MAXON, buf, 2, 219);
#else
	mavlink_skye_home_maxon_t packet;
	packet.target_system = target_system;
	packet.homing = homing;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_HOME_MAXON, (const char *)&packet, 2, 219);
#endif
}

#endif

// MESSAGE SKYE_HOME_MAXON UNPACKING


/**
 * @brief Get field target_system from skye_home_maxon message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_home_maxon_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field homing from skye_home_maxon message
 *
 * @return Boolean, true: home maxon motors
 */
static inline uint8_t mavlink_msg_skye_home_maxon_get_homing(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a skye_home_maxon message into a struct
 *
 * @param msg The message to decode
 * @param skye_home_maxon C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_home_maxon_decode(const mavlink_message_t* msg, mavlink_skye_home_maxon_t* skye_home_maxon)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_home_maxon->target_system = mavlink_msg_skye_home_maxon_get_target_system(msg);
	skye_home_maxon->homing = mavlink_msg_skye_home_maxon_get_homing(msg);
#else
	memcpy(skye_home_maxon, _MAV_PAYLOAD(msg), 2);
#endif
}
