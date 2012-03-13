// MESSAGE SKYE_CAM_TAKE_SHOT PACKING

#define MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT 163

typedef struct __mavlink_skye_cam_take_shot_t
{
 uint8_t target_system; ///< System ID
 uint8_t cam_id; ///< ID of camera, see ENUM MAV_CAM_ID
 uint8_t take_shot; ///< Boolean, true: send recent image (save settings) to GS
} mavlink_skye_cam_take_shot_t;

#define MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT_LEN 3
#define MAVLINK_MSG_ID_163_LEN 3



#define MAVLINK_MESSAGE_INFO_SKYE_CAM_TAKE_SHOT { \
	"SKYE_CAM_TAKE_SHOT", \
	3, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_skye_cam_take_shot_t, target_system) }, \
         { "cam_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_skye_cam_take_shot_t, cam_id) }, \
         { "take_shot", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_skye_cam_take_shot_t, take_shot) }, \
         } \
}


/**
 * @brief Pack a skye_cam_take_shot message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param take_shot Boolean, true: send recent image (save settings) to GS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_take_shot_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t cam_id, uint8_t take_shot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[3];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);
	_mav_put_uint8_t(buf, 2, take_shot);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 3);
#else
	mavlink_skye_cam_take_shot_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.take_shot = take_shot;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 3);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT;
	return mavlink_finalize_message(msg, system_id, component_id, 3, 124);
}

/**
 * @brief Pack a skye_cam_take_shot message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param take_shot Boolean, true: send recent image (save settings) to GS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_take_shot_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t cam_id,uint8_t take_shot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[3];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);
	_mav_put_uint8_t(buf, 2, take_shot);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 3);
#else
	mavlink_skye_cam_take_shot_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.take_shot = take_shot;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 3);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 3, 124);
}

/**
 * @brief Encode a skye_cam_take_shot struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_cam_take_shot C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_cam_take_shot_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_cam_take_shot_t* skye_cam_take_shot)
{
	return mavlink_msg_skye_cam_take_shot_pack(system_id, component_id, msg, skye_cam_take_shot->target_system, skye_cam_take_shot->cam_id, skye_cam_take_shot->take_shot);
}

/**
 * @brief Send a skye_cam_take_shot message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param take_shot Boolean, true: send recent image (save settings) to GS
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_cam_take_shot_send(mavlink_channel_t chan, uint8_t target_system, uint8_t cam_id, uint8_t take_shot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[3];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);
	_mav_put_uint8_t(buf, 2, take_shot);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT, buf, 3, 124);
#else
	mavlink_skye_cam_take_shot_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.take_shot = take_shot;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_TAKE_SHOT, (const char *)&packet, 3, 124);
#endif
}

#endif

// MESSAGE SKYE_CAM_TAKE_SHOT UNPACKING


/**
 * @brief Get field target_system from skye_cam_take_shot message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_cam_take_shot_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field cam_id from skye_cam_take_shot message
 *
 * @return ID of camera, see ENUM MAV_CAM_ID
 */
static inline uint8_t mavlink_msg_skye_cam_take_shot_get_cam_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field take_shot from skye_cam_take_shot message
 *
 * @return Boolean, true: send recent image (save settings) to GS
 */
static inline uint8_t mavlink_msg_skye_cam_take_shot_get_take_shot(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a skye_cam_take_shot message into a struct
 *
 * @param msg The message to decode
 * @param skye_cam_take_shot C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_cam_take_shot_decode(const mavlink_message_t* msg, mavlink_skye_cam_take_shot_t* skye_cam_take_shot)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_cam_take_shot->target_system = mavlink_msg_skye_cam_take_shot_get_target_system(msg);
	skye_cam_take_shot->cam_id = mavlink_msg_skye_cam_take_shot_get_cam_id(msg);
	skye_cam_take_shot->take_shot = mavlink_msg_skye_cam_take_shot_get_take_shot(msg);
#else
	memcpy(skye_cam_take_shot, _MAV_PAYLOAD(msg), 3);
#endif
}
