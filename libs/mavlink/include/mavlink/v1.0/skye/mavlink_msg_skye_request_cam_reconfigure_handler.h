// MESSAGE SKYE_REQUEST_CAM_RECONFIGURE_HANDLER PACKING

#define MAVLINK_MSG_ID_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER 170

typedef struct __mavlink_skye_request_cam_reconfigure_handler_t
{
 uint8_t target_system; ///< System ID
 uint8_t cam_id; ///< ID of camera, see ENUM MAV_CAM_ID
} mavlink_skye_request_cam_reconfigure_handler_t;

#define MAVLINK_MSG_ID_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER_LEN 2
#define MAVLINK_MSG_ID_170_LEN 2



#define MAVLINK_MESSAGE_INFO_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER { \
	"SKYE_REQUEST_CAM_RECONFIGURE_HANDLER", \
	2, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_skye_request_cam_reconfigure_handler_t, target_system) }, \
         { "cam_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_skye_request_cam_reconfigure_handler_t, cam_id) }, \
         } \
}


/**
 * @brief Pack a skye_request_cam_reconfigure_handler message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_request_cam_reconfigure_handler_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t cam_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 2);
#else
	mavlink_skye_request_cam_reconfigure_handler_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER;
	return mavlink_finalize_message(msg, system_id, component_id, 2, 102);
}

/**
 * @brief Pack a skye_request_cam_reconfigure_handler message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_request_cam_reconfigure_handler_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t cam_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 2);
#else
	mavlink_skye_request_cam_reconfigure_handler_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 2, 102);
}

/**
 * @brief Encode a skye_request_cam_reconfigure_handler struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_request_cam_reconfigure_handler C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_request_cam_reconfigure_handler_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_request_cam_reconfigure_handler_t* skye_request_cam_reconfigure_handler)
{
	return mavlink_msg_skye_request_cam_reconfigure_handler_pack(system_id, component_id, msg, skye_request_cam_reconfigure_handler->target_system, skye_request_cam_reconfigure_handler->cam_id);
}

/**
 * @brief Send a skye_request_cam_reconfigure_handler message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_request_cam_reconfigure_handler_send(mavlink_channel_t chan, uint8_t target_system, uint8_t cam_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER, buf, 2, 102);
#else
	mavlink_skye_request_cam_reconfigure_handler_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_REQUEST_CAM_RECONFIGURE_HANDLER, (const char *)&packet, 2, 102);
#endif
}

#endif

// MESSAGE SKYE_REQUEST_CAM_RECONFIGURE_HANDLER UNPACKING


/**
 * @brief Get field target_system from skye_request_cam_reconfigure_handler message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_request_cam_reconfigure_handler_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field cam_id from skye_request_cam_reconfigure_handler message
 *
 * @return ID of camera, see ENUM MAV_CAM_ID
 */
static inline uint8_t mavlink_msg_skye_request_cam_reconfigure_handler_get_cam_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a skye_request_cam_reconfigure_handler message into a struct
 *
 * @param msg The message to decode
 * @param skye_request_cam_reconfigure_handler C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_request_cam_reconfigure_handler_decode(const mavlink_message_t* msg, mavlink_skye_request_cam_reconfigure_handler_t* skye_request_cam_reconfigure_handler)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_request_cam_reconfigure_handler->target_system = mavlink_msg_skye_request_cam_reconfigure_handler_get_target_system(msg);
	skye_request_cam_reconfigure_handler->cam_id = mavlink_msg_skye_request_cam_reconfigure_handler_get_cam_id(msg);
#else
	memcpy(skye_request_cam_reconfigure_handler, _MAV_PAYLOAD(msg), 2);
#endif
}
