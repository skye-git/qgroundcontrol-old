// MESSAGE SKYE_CAM_IMAGE_TRIGGERED PACKING

#define MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED 165

typedef struct __mavlink_skye_cam_image_triggered_t
{
 uint64_t timestamp; ///< Timestamp
 float roll; ///< Roll angle in rad
 float pitch; ///< Pitch angle in rad
 float yaw; ///< Yaw angle in rad
 int32_t lat; ///< Latitude, expressed as * 1E7
 int32_t lon; ///< Longitude, expressed as * 1E7
 int32_t alt; ///< Altitude in meters, expressed as * 1000 (millimeters), above MSL
} mavlink_skye_cam_image_triggered_t;

#define MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED_LEN 32
#define MAVLINK_MSG_ID_165_LEN 32



#define MAVLINK_MESSAGE_INFO_SKYE_CAM_IMAGE_TRIGGERED { \
	"SKYE_CAM_IMAGE_TRIGGERED", \
	7, \
	{  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_skye_cam_image_triggered_t, timestamp) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_skye_cam_image_triggered_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_cam_image_triggered_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_cam_image_triggered_t, yaw) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_skye_cam_image_triggered_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_skye_cam_image_triggered_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_skye_cam_image_triggered_t, alt) }, \
         } \
}


/**
 * @brief Pack a skye_cam_image_triggered message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp Timestamp
 * @param roll Roll angle in rad
 * @param pitch Pitch angle in rad
 * @param yaw Yaw angle in rad
 * @param lat Latitude, expressed as * 1E7
 * @param lon Longitude, expressed as * 1E7
 * @param alt Altitude in meters, expressed as * 1000 (millimeters), above MSL
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_image_triggered_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t timestamp, float roll, float pitch, float yaw, int32_t lat, int32_t lon, int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[32];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float(buf, 8, roll);
	_mav_put_float(buf, 12, pitch);
	_mav_put_float(buf, 16, yaw);
	_mav_put_int32_t(buf, 20, lat);
	_mav_put_int32_t(buf, 24, lon);
	_mav_put_int32_t(buf, 28, alt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 32);
#else
	mavlink_skye_cam_image_triggered_t packet;
	packet.timestamp = timestamp;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 32);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED;
	return mavlink_finalize_message(msg, system_id, component_id, 32, 205);
}

/**
 * @brief Pack a skye_cam_image_triggered message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp Timestamp
 * @param roll Roll angle in rad
 * @param pitch Pitch angle in rad
 * @param yaw Yaw angle in rad
 * @param lat Latitude, expressed as * 1E7
 * @param lon Longitude, expressed as * 1E7
 * @param alt Altitude in meters, expressed as * 1000 (millimeters), above MSL
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_image_triggered_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t timestamp,float roll,float pitch,float yaw,int32_t lat,int32_t lon,int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[32];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float(buf, 8, roll);
	_mav_put_float(buf, 12, pitch);
	_mav_put_float(buf, 16, yaw);
	_mav_put_int32_t(buf, 20, lat);
	_mav_put_int32_t(buf, 24, lon);
	_mav_put_int32_t(buf, 28, alt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 32);
#else
	mavlink_skye_cam_image_triggered_t packet;
	packet.timestamp = timestamp;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 32);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 32, 205);
}

/**
 * @brief Encode a skye_cam_image_triggered struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_cam_image_triggered C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_cam_image_triggered_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_cam_image_triggered_t* skye_cam_image_triggered)
{
	return mavlink_msg_skye_cam_image_triggered_pack(system_id, component_id, msg, skye_cam_image_triggered->timestamp, skye_cam_image_triggered->roll, skye_cam_image_triggered->pitch, skye_cam_image_triggered->yaw, skye_cam_image_triggered->lat, skye_cam_image_triggered->lon, skye_cam_image_triggered->alt);
}

/**
 * @brief Send a skye_cam_image_triggered message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp Timestamp
 * @param roll Roll angle in rad
 * @param pitch Pitch angle in rad
 * @param yaw Yaw angle in rad
 * @param lat Latitude, expressed as * 1E7
 * @param lon Longitude, expressed as * 1E7
 * @param alt Altitude in meters, expressed as * 1000 (millimeters), above MSL
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_cam_image_triggered_send(mavlink_channel_t chan, uint64_t timestamp, float roll, float pitch, float yaw, int32_t lat, int32_t lon, int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[32];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float(buf, 8, roll);
	_mav_put_float(buf, 12, pitch);
	_mav_put_float(buf, 16, yaw);
	_mav_put_int32_t(buf, 20, lat);
	_mav_put_int32_t(buf, 24, lon);
	_mav_put_int32_t(buf, 28, alt);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED, buf, 32, 205);
#else
	mavlink_skye_cam_image_triggered_t packet;
	packet.timestamp = timestamp;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.lat = lat;
	packet.lon = lon;
	packet.alt = alt;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_IMAGE_TRIGGERED, (const char *)&packet, 32, 205);
#endif
}

#endif

// MESSAGE SKYE_CAM_IMAGE_TRIGGERED UNPACKING


/**
 * @brief Get field timestamp from skye_cam_image_triggered message
 *
 * @return Timestamp
 */
static inline uint64_t mavlink_msg_skye_cam_image_triggered_get_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field roll from skye_cam_image_triggered message
 *
 * @return Roll angle in rad
 */
static inline float mavlink_msg_skye_cam_image_triggered_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field pitch from skye_cam_image_triggered message
 *
 * @return Pitch angle in rad
 */
static inline float mavlink_msg_skye_cam_image_triggered_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field yaw from skye_cam_image_triggered message
 *
 * @return Yaw angle in rad
 */
static inline float mavlink_msg_skye_cam_image_triggered_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field lat from skye_cam_image_triggered message
 *
 * @return Latitude, expressed as * 1E7
 */
static inline int32_t mavlink_msg_skye_cam_image_triggered_get_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field lon from skye_cam_image_triggered message
 *
 * @return Longitude, expressed as * 1E7
 */
static inline int32_t mavlink_msg_skye_cam_image_triggered_get_lon(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Get field alt from skye_cam_image_triggered message
 *
 * @return Altitude in meters, expressed as * 1000 (millimeters), above MSL
 */
static inline int32_t mavlink_msg_skye_cam_image_triggered_get_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  28);
}

/**
 * @brief Decode a skye_cam_image_triggered message into a struct
 *
 * @param msg The message to decode
 * @param skye_cam_image_triggered C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_cam_image_triggered_decode(const mavlink_message_t* msg, mavlink_skye_cam_image_triggered_t* skye_cam_image_triggered)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_cam_image_triggered->timestamp = mavlink_msg_skye_cam_image_triggered_get_timestamp(msg);
	skye_cam_image_triggered->roll = mavlink_msg_skye_cam_image_triggered_get_roll(msg);
	skye_cam_image_triggered->pitch = mavlink_msg_skye_cam_image_triggered_get_pitch(msg);
	skye_cam_image_triggered->yaw = mavlink_msg_skye_cam_image_triggered_get_yaw(msg);
	skye_cam_image_triggered->lat = mavlink_msg_skye_cam_image_triggered_get_lat(msg);
	skye_cam_image_triggered->lon = mavlink_msg_skye_cam_image_triggered_get_lon(msg);
	skye_cam_image_triggered->alt = mavlink_msg_skye_cam_image_triggered_get_alt(msg);
#else
	memcpy(skye_cam_image_triggered, _MAV_PAYLOAD(msg), 32);
#endif
}
