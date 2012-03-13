// MESSAGE SKYE_CAM_HANDLE_SAVE_IMAGE PACKING

#define MAVLINK_MSG_ID_SKYE_CAM_HANDLE_SAVE_IMAGE 162

typedef struct __mavlink_skye_cam_handle_save_image_t
{
 uint8_t target_system; ///< System ID
 uint8_t cam_id; ///< ID of camera, see ENUM MAV_CAM_ID
 uint8_t save_image; ///< Boolean, true: image stream is saved as specified in fields below
 uint8_t save_percent; ///< Percentage of shot images that are stored
 uint8_t format; ///< Format of saved image, see ENUM MAV_CAM_IMAGE_FORMAT
 uint8_t png_level; ///< Compression level for png save format (no compr:1, full compr:9)
 uint8_t jpeg_quality; ///< Compression quality for jpeg save format (lowest quality: 0, highest quality: 100)
 char frame_name[8]; ///< Frame name, max. 8 characters
 char path[32]; ///< Path, where images on SKYE should saved to, max. 32 characters
 uint8_t send_image; ///< Boolean, true: image stream is sent to GS as specified in fields below
 uint8_t send_percent; ///< Percentage of shot images that are sent
 uint8_t format2; ///< Format of sent image, see ENUM MAV_CAM_IMAGE_FORMAT
 uint8_t png_level2; ///< Compression level for png send format (no compr:1, full compr:9)
 uint8_t jpeg_quality2; ///< Compression quality for jpeg send format (lowest quality: 0, highest quality: 100)
 uint8_t keep_old_modus; ///< Boolean, true: new image handle modus is added to previous (image is saved/sent more than once), false: only save/send with new configuration
} mavlink_skye_cam_handle_save_image_t;

#define MAVLINK_MSG_ID_SKYE_CAM_HANDLE_SAVE_IMAGE_LEN 53
#define MAVLINK_MSG_ID_162_LEN 53

#define MAVLINK_MSG_SKYE_CAM_HANDLE_SAVE_IMAGE_FIELD_FRAME_NAME_LEN 8
#define MAVLINK_MSG_SKYE_CAM_HANDLE_SAVE_IMAGE_FIELD_PATH_LEN 32

#define MAVLINK_MESSAGE_INFO_SKYE_CAM_HANDLE_SAVE_IMAGE { \
	"SKYE_CAM_HANDLE_SAVE_IMAGE", \
	15, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_skye_cam_handle_save_image_t, target_system) }, \
         { "cam_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_skye_cam_handle_save_image_t, cam_id) }, \
         { "save_image", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_skye_cam_handle_save_image_t, save_image) }, \
         { "save_percent", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_skye_cam_handle_save_image_t, save_percent) }, \
         { "format", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_skye_cam_handle_save_image_t, format) }, \
         { "png_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_skye_cam_handle_save_image_t, png_level) }, \
         { "jpeg_quality", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_skye_cam_handle_save_image_t, jpeg_quality) }, \
         { "frame_name", NULL, MAVLINK_TYPE_CHAR, 8, 7, offsetof(mavlink_skye_cam_handle_save_image_t, frame_name) }, \
         { "path", NULL, MAVLINK_TYPE_CHAR, 32, 15, offsetof(mavlink_skye_cam_handle_save_image_t, path) }, \
         { "send_image", NULL, MAVLINK_TYPE_UINT8_T, 0, 47, offsetof(mavlink_skye_cam_handle_save_image_t, send_image) }, \
         { "send_percent", NULL, MAVLINK_TYPE_UINT8_T, 0, 48, offsetof(mavlink_skye_cam_handle_save_image_t, send_percent) }, \
         { "format2", NULL, MAVLINK_TYPE_UINT8_T, 0, 49, offsetof(mavlink_skye_cam_handle_save_image_t, format2) }, \
         { "png_level2", NULL, MAVLINK_TYPE_UINT8_T, 0, 50, offsetof(mavlink_skye_cam_handle_save_image_t, png_level2) }, \
         { "jpeg_quality2", NULL, MAVLINK_TYPE_UINT8_T, 0, 51, offsetof(mavlink_skye_cam_handle_save_image_t, jpeg_quality2) }, \
         { "keep_old_modus", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_skye_cam_handle_save_image_t, keep_old_modus) }, \
         } \
}


/**
 * @brief Pack a skye_cam_handle_save_image message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param save_image Boolean, true: image stream is saved as specified in fields below
 * @param save_percent Percentage of shot images that are stored
 * @param format Format of saved image, see ENUM MAV_CAM_IMAGE_FORMAT
 * @param png_level Compression level for png save format (no compr:1, full compr:9)
 * @param jpeg_quality Compression quality for jpeg save format (lowest quality: 0, highest quality: 100)
 * @param frame_name Frame name, max. 8 characters
 * @param path Path, where images on SKYE should saved to, max. 32 characters
 * @param send_image Boolean, true: image stream is sent to GS as specified in fields below
 * @param send_percent Percentage of shot images that are sent
 * @param format2 Format of sent image, see ENUM MAV_CAM_IMAGE_FORMAT
 * @param png_level2 Compression level for png send format (no compr:1, full compr:9)
 * @param jpeg_quality2 Compression quality for jpeg send format (lowest quality: 0, highest quality: 100)
 * @param keep_old_modus Boolean, true: new image handle modus is added to previous (image is saved/sent more than once), false: only save/send with new configuration
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_handle_save_image_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t cam_id, uint8_t save_image, uint8_t save_percent, uint8_t format, uint8_t png_level, uint8_t jpeg_quality, const char *frame_name, const char *path, uint8_t send_image, uint8_t send_percent, uint8_t format2, uint8_t png_level2, uint8_t jpeg_quality2, uint8_t keep_old_modus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[53];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);
	_mav_put_uint8_t(buf, 2, save_image);
	_mav_put_uint8_t(buf, 3, save_percent);
	_mav_put_uint8_t(buf, 4, format);
	_mav_put_uint8_t(buf, 5, png_level);
	_mav_put_uint8_t(buf, 6, jpeg_quality);
	_mav_put_uint8_t(buf, 47, send_image);
	_mav_put_uint8_t(buf, 48, send_percent);
	_mav_put_uint8_t(buf, 49, format2);
	_mav_put_uint8_t(buf, 50, png_level2);
	_mav_put_uint8_t(buf, 51, jpeg_quality2);
	_mav_put_uint8_t(buf, 52, keep_old_modus);
	_mav_put_char_array(buf, 7, frame_name, 8);
	_mav_put_char_array(buf, 15, path, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 53);
#else
	mavlink_skye_cam_handle_save_image_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.save_image = save_image;
	packet.save_percent = save_percent;
	packet.format = format;
	packet.png_level = png_level;
	packet.jpeg_quality = jpeg_quality;
	packet.send_image = send_image;
	packet.send_percent = send_percent;
	packet.format2 = format2;
	packet.png_level2 = png_level2;
	packet.jpeg_quality2 = jpeg_quality2;
	packet.keep_old_modus = keep_old_modus;
	mav_array_memcpy(packet.frame_name, frame_name, sizeof(char)*8);
	mav_array_memcpy(packet.path, path, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 53);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_HANDLE_SAVE_IMAGE;
	return mavlink_finalize_message(msg, system_id, component_id, 53, 154);
}

/**
 * @brief Pack a skye_cam_handle_save_image message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param save_image Boolean, true: image stream is saved as specified in fields below
 * @param save_percent Percentage of shot images that are stored
 * @param format Format of saved image, see ENUM MAV_CAM_IMAGE_FORMAT
 * @param png_level Compression level for png save format (no compr:1, full compr:9)
 * @param jpeg_quality Compression quality for jpeg save format (lowest quality: 0, highest quality: 100)
 * @param frame_name Frame name, max. 8 characters
 * @param path Path, where images on SKYE should saved to, max. 32 characters
 * @param send_image Boolean, true: image stream is sent to GS as specified in fields below
 * @param send_percent Percentage of shot images that are sent
 * @param format2 Format of sent image, see ENUM MAV_CAM_IMAGE_FORMAT
 * @param png_level2 Compression level for png send format (no compr:1, full compr:9)
 * @param jpeg_quality2 Compression quality for jpeg send format (lowest quality: 0, highest quality: 100)
 * @param keep_old_modus Boolean, true: new image handle modus is added to previous (image is saved/sent more than once), false: only save/send with new configuration
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_handle_save_image_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t cam_id,uint8_t save_image,uint8_t save_percent,uint8_t format,uint8_t png_level,uint8_t jpeg_quality,const char *frame_name,const char *path,uint8_t send_image,uint8_t send_percent,uint8_t format2,uint8_t png_level2,uint8_t jpeg_quality2,uint8_t keep_old_modus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[53];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);
	_mav_put_uint8_t(buf, 2, save_image);
	_mav_put_uint8_t(buf, 3, save_percent);
	_mav_put_uint8_t(buf, 4, format);
	_mav_put_uint8_t(buf, 5, png_level);
	_mav_put_uint8_t(buf, 6, jpeg_quality);
	_mav_put_uint8_t(buf, 47, send_image);
	_mav_put_uint8_t(buf, 48, send_percent);
	_mav_put_uint8_t(buf, 49, format2);
	_mav_put_uint8_t(buf, 50, png_level2);
	_mav_put_uint8_t(buf, 51, jpeg_quality2);
	_mav_put_uint8_t(buf, 52, keep_old_modus);
	_mav_put_char_array(buf, 7, frame_name, 8);
	_mav_put_char_array(buf, 15, path, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 53);
#else
	mavlink_skye_cam_handle_save_image_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.save_image = save_image;
	packet.save_percent = save_percent;
	packet.format = format;
	packet.png_level = png_level;
	packet.jpeg_quality = jpeg_quality;
	packet.send_image = send_image;
	packet.send_percent = send_percent;
	packet.format2 = format2;
	packet.png_level2 = png_level2;
	packet.jpeg_quality2 = jpeg_quality2;
	packet.keep_old_modus = keep_old_modus;
	mav_array_memcpy(packet.frame_name, frame_name, sizeof(char)*8);
	mav_array_memcpy(packet.path, path, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 53);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_HANDLE_SAVE_IMAGE;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 53, 154);
}

/**
 * @brief Encode a skye_cam_handle_save_image struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_cam_handle_save_image C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_cam_handle_save_image_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_cam_handle_save_image_t* skye_cam_handle_save_image)
{
	return mavlink_msg_skye_cam_handle_save_image_pack(system_id, component_id, msg, skye_cam_handle_save_image->target_system, skye_cam_handle_save_image->cam_id, skye_cam_handle_save_image->save_image, skye_cam_handle_save_image->save_percent, skye_cam_handle_save_image->format, skye_cam_handle_save_image->png_level, skye_cam_handle_save_image->jpeg_quality, skye_cam_handle_save_image->frame_name, skye_cam_handle_save_image->path, skye_cam_handle_save_image->send_image, skye_cam_handle_save_image->send_percent, skye_cam_handle_save_image->format2, skye_cam_handle_save_image->png_level2, skye_cam_handle_save_image->jpeg_quality2, skye_cam_handle_save_image->keep_old_modus);
}

/**
 * @brief Send a skye_cam_handle_save_image message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param save_image Boolean, true: image stream is saved as specified in fields below
 * @param save_percent Percentage of shot images that are stored
 * @param format Format of saved image, see ENUM MAV_CAM_IMAGE_FORMAT
 * @param png_level Compression level for png save format (no compr:1, full compr:9)
 * @param jpeg_quality Compression quality for jpeg save format (lowest quality: 0, highest quality: 100)
 * @param frame_name Frame name, max. 8 characters
 * @param path Path, where images on SKYE should saved to, max. 32 characters
 * @param send_image Boolean, true: image stream is sent to GS as specified in fields below
 * @param send_percent Percentage of shot images that are sent
 * @param format2 Format of sent image, see ENUM MAV_CAM_IMAGE_FORMAT
 * @param png_level2 Compression level for png send format (no compr:1, full compr:9)
 * @param jpeg_quality2 Compression quality for jpeg send format (lowest quality: 0, highest quality: 100)
 * @param keep_old_modus Boolean, true: new image handle modus is added to previous (image is saved/sent more than once), false: only save/send with new configuration
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_cam_handle_save_image_send(mavlink_channel_t chan, uint8_t target_system, uint8_t cam_id, uint8_t save_image, uint8_t save_percent, uint8_t format, uint8_t png_level, uint8_t jpeg_quality, const char *frame_name, const char *path, uint8_t send_image, uint8_t send_percent, uint8_t format2, uint8_t png_level2, uint8_t jpeg_quality2, uint8_t keep_old_modus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[53];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, cam_id);
	_mav_put_uint8_t(buf, 2, save_image);
	_mav_put_uint8_t(buf, 3, save_percent);
	_mav_put_uint8_t(buf, 4, format);
	_mav_put_uint8_t(buf, 5, png_level);
	_mav_put_uint8_t(buf, 6, jpeg_quality);
	_mav_put_uint8_t(buf, 47, send_image);
	_mav_put_uint8_t(buf, 48, send_percent);
	_mav_put_uint8_t(buf, 49, format2);
	_mav_put_uint8_t(buf, 50, png_level2);
	_mav_put_uint8_t(buf, 51, jpeg_quality2);
	_mav_put_uint8_t(buf, 52, keep_old_modus);
	_mav_put_char_array(buf, 7, frame_name, 8);
	_mav_put_char_array(buf, 15, path, 32);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_HANDLE_SAVE_IMAGE, buf, 53, 154);
#else
	mavlink_skye_cam_handle_save_image_t packet;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.save_image = save_image;
	packet.save_percent = save_percent;
	packet.format = format;
	packet.png_level = png_level;
	packet.jpeg_quality = jpeg_quality;
	packet.send_image = send_image;
	packet.send_percent = send_percent;
	packet.format2 = format2;
	packet.png_level2 = png_level2;
	packet.jpeg_quality2 = jpeg_quality2;
	packet.keep_old_modus = keep_old_modus;
	mav_array_memcpy(packet.frame_name, frame_name, sizeof(char)*8);
	mav_array_memcpy(packet.path, path, sizeof(char)*32);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_HANDLE_SAVE_IMAGE, (const char *)&packet, 53, 154);
#endif
}

#endif

// MESSAGE SKYE_CAM_HANDLE_SAVE_IMAGE UNPACKING


/**
 * @brief Get field target_system from skye_cam_handle_save_image message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field cam_id from skye_cam_handle_save_image message
 *
 * @return ID of camera, see ENUM MAV_CAM_ID
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_cam_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field save_image from skye_cam_handle_save_image message
 *
 * @return Boolean, true: image stream is saved as specified in fields below
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_save_image(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field save_percent from skye_cam_handle_save_image message
 *
 * @return Percentage of shot images that are stored
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_save_percent(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field format from skye_cam_handle_save_image message
 *
 * @return Format of saved image, see ENUM MAV_CAM_IMAGE_FORMAT
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_format(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field png_level from skye_cam_handle_save_image message
 *
 * @return Compression level for png save format (no compr:1, full compr:9)
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_png_level(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field jpeg_quality from skye_cam_handle_save_image message
 *
 * @return Compression quality for jpeg save format (lowest quality: 0, highest quality: 100)
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_jpeg_quality(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field frame_name from skye_cam_handle_save_image message
 *
 * @return Frame name, max. 8 characters
 */
static inline uint16_t mavlink_msg_skye_cam_handle_save_image_get_frame_name(const mavlink_message_t* msg, char *frame_name)
{
	return _MAV_RETURN_char_array(msg, frame_name, 8,  7);
}

/**
 * @brief Get field path from skye_cam_handle_save_image message
 *
 * @return Path, where images on SKYE should saved to, max. 32 characters
 */
static inline uint16_t mavlink_msg_skye_cam_handle_save_image_get_path(const mavlink_message_t* msg, char *path)
{
	return _MAV_RETURN_char_array(msg, path, 32,  15);
}

/**
 * @brief Get field send_image from skye_cam_handle_save_image message
 *
 * @return Boolean, true: image stream is sent to GS as specified in fields below
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_send_image(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  47);
}

/**
 * @brief Get field send_percent from skye_cam_handle_save_image message
 *
 * @return Percentage of shot images that are sent
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_send_percent(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  48);
}

/**
 * @brief Get field format2 from skye_cam_handle_save_image message
 *
 * @return Format of sent image, see ENUM MAV_CAM_IMAGE_FORMAT
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_format2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  49);
}

/**
 * @brief Get field png_level2 from skye_cam_handle_save_image message
 *
 * @return Compression level for png send format (no compr:1, full compr:9)
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_png_level2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  50);
}

/**
 * @brief Get field jpeg_quality2 from skye_cam_handle_save_image message
 *
 * @return Compression quality for jpeg send format (lowest quality: 0, highest quality: 100)
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_jpeg_quality2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  51);
}

/**
 * @brief Get field keep_old_modus from skye_cam_handle_save_image message
 *
 * @return Boolean, true: new image handle modus is added to previous (image is saved/sent more than once), false: only save/send with new configuration
 */
static inline uint8_t mavlink_msg_skye_cam_handle_save_image_get_keep_old_modus(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  52);
}

/**
 * @brief Decode a skye_cam_handle_save_image message into a struct
 *
 * @param msg The message to decode
 * @param skye_cam_handle_save_image C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_cam_handle_save_image_decode(const mavlink_message_t* msg, mavlink_skye_cam_handle_save_image_t* skye_cam_handle_save_image)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_cam_handle_save_image->target_system = mavlink_msg_skye_cam_handle_save_image_get_target_system(msg);
	skye_cam_handle_save_image->cam_id = mavlink_msg_skye_cam_handle_save_image_get_cam_id(msg);
	skye_cam_handle_save_image->save_image = mavlink_msg_skye_cam_handle_save_image_get_save_image(msg);
	skye_cam_handle_save_image->save_percent = mavlink_msg_skye_cam_handle_save_image_get_save_percent(msg);
	skye_cam_handle_save_image->format = mavlink_msg_skye_cam_handle_save_image_get_format(msg);
	skye_cam_handle_save_image->png_level = mavlink_msg_skye_cam_handle_save_image_get_png_level(msg);
	skye_cam_handle_save_image->jpeg_quality = mavlink_msg_skye_cam_handle_save_image_get_jpeg_quality(msg);
	mavlink_msg_skye_cam_handle_save_image_get_frame_name(msg, skye_cam_handle_save_image->frame_name);
	mavlink_msg_skye_cam_handle_save_image_get_path(msg, skye_cam_handle_save_image->path);
	skye_cam_handle_save_image->send_image = mavlink_msg_skye_cam_handle_save_image_get_send_image(msg);
	skye_cam_handle_save_image->send_percent = mavlink_msg_skye_cam_handle_save_image_get_send_percent(msg);
	skye_cam_handle_save_image->format2 = mavlink_msg_skye_cam_handle_save_image_get_format2(msg);
	skye_cam_handle_save_image->png_level2 = mavlink_msg_skye_cam_handle_save_image_get_png_level2(msg);
	skye_cam_handle_save_image->jpeg_quality2 = mavlink_msg_skye_cam_handle_save_image_get_jpeg_quality2(msg);
	skye_cam_handle_save_image->keep_old_modus = mavlink_msg_skye_cam_handle_save_image_get_keep_old_modus(msg);
#else
	memcpy(skye_cam_handle_save_image, _MAV_PAYLOAD(msg), 53);
#endif
}
