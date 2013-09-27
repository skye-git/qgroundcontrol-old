// MESSAGE NANOTRON_SKYE_SENDER_6_RAW PACKING

#define MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_6_RAW 143

typedef struct __mavlink_nanotron_skye_sender_6_raw_t
{
 float distance_1; ///< Distance to Receiver module 1
 float distance_2; ///< Distance to Receiver module 2
 float distance_3; ///< Distance to Receiver module 3
 float distance_4; ///< Distance to Receiver module 4
 float distance_5; ///< Distance to Receiver module 5
 float distance_6; ///< Distance to Receiver module 6
} mavlink_nanotron_skye_sender_6_raw_t;

#define MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_6_RAW_LEN 24
#define MAVLINK_MSG_ID_143_LEN 24



#define MAVLINK_MESSAGE_INFO_NANOTRON_SKYE_SENDER_6_RAW { \
	"NANOTRON_SKYE_SENDER_6_RAW", \
	6, \
	{  { "distance_1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_nanotron_skye_sender_6_raw_t, distance_1) }, \
         { "distance_2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_nanotron_skye_sender_6_raw_t, distance_2) }, \
         { "distance_3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_nanotron_skye_sender_6_raw_t, distance_3) }, \
         { "distance_4", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_nanotron_skye_sender_6_raw_t, distance_4) }, \
         { "distance_5", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_nanotron_skye_sender_6_raw_t, distance_5) }, \
         { "distance_6", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_nanotron_skye_sender_6_raw_t, distance_6) }, \
         } \
}


/**
 * @brief Pack a nanotron_skye_sender_6_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param distance_1 Distance to Receiver module 1
 * @param distance_2 Distance to Receiver module 2
 * @param distance_3 Distance to Receiver module 3
 * @param distance_4 Distance to Receiver module 4
 * @param distance_5 Distance to Receiver module 5
 * @param distance_6 Distance to Receiver module 6
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nanotron_skye_sender_6_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float distance_1, float distance_2, float distance_3, float distance_4, float distance_5, float distance_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[24];
	_mav_put_float(buf, 0, distance_1);
	_mav_put_float(buf, 4, distance_2);
	_mav_put_float(buf, 8, distance_3);
	_mav_put_float(buf, 12, distance_4);
	_mav_put_float(buf, 16, distance_5);
	_mav_put_float(buf, 20, distance_6);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 24);
#else
	mavlink_nanotron_skye_sender_6_raw_t packet;
	packet.distance_1 = distance_1;
	packet.distance_2 = distance_2;
	packet.distance_3 = distance_3;
	packet.distance_4 = distance_4;
	packet.distance_5 = distance_5;
	packet.distance_6 = distance_6;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 24);
#endif

	msg->msgid = MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_6_RAW;
	return mavlink_finalize_message(msg, system_id, component_id, 24, 165);
}

/**
 * @brief Pack a nanotron_skye_sender_6_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param distance_1 Distance to Receiver module 1
 * @param distance_2 Distance to Receiver module 2
 * @param distance_3 Distance to Receiver module 3
 * @param distance_4 Distance to Receiver module 4
 * @param distance_5 Distance to Receiver module 5
 * @param distance_6 Distance to Receiver module 6
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nanotron_skye_sender_6_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float distance_1,float distance_2,float distance_3,float distance_4,float distance_5,float distance_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[24];
	_mav_put_float(buf, 0, distance_1);
	_mav_put_float(buf, 4, distance_2);
	_mav_put_float(buf, 8, distance_3);
	_mav_put_float(buf, 12, distance_4);
	_mav_put_float(buf, 16, distance_5);
	_mav_put_float(buf, 20, distance_6);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 24);
#else
	mavlink_nanotron_skye_sender_6_raw_t packet;
	packet.distance_1 = distance_1;
	packet.distance_2 = distance_2;
	packet.distance_3 = distance_3;
	packet.distance_4 = distance_4;
	packet.distance_5 = distance_5;
	packet.distance_6 = distance_6;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 24);
#endif

	msg->msgid = MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_6_RAW;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 24, 165);
}

/**
 * @brief Encode a nanotron_skye_sender_6_raw struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param nanotron_skye_sender_6_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nanotron_skye_sender_6_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_nanotron_skye_sender_6_raw_t* nanotron_skye_sender_6_raw)
{
	return mavlink_msg_nanotron_skye_sender_6_raw_pack(system_id, component_id, msg, nanotron_skye_sender_6_raw->distance_1, nanotron_skye_sender_6_raw->distance_2, nanotron_skye_sender_6_raw->distance_3, nanotron_skye_sender_6_raw->distance_4, nanotron_skye_sender_6_raw->distance_5, nanotron_skye_sender_6_raw->distance_6);
}

/**
 * @brief Send a nanotron_skye_sender_6_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param distance_1 Distance to Receiver module 1
 * @param distance_2 Distance to Receiver module 2
 * @param distance_3 Distance to Receiver module 3
 * @param distance_4 Distance to Receiver module 4
 * @param distance_5 Distance to Receiver module 5
 * @param distance_6 Distance to Receiver module 6
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_nanotron_skye_sender_6_raw_send(mavlink_channel_t chan, float distance_1, float distance_2, float distance_3, float distance_4, float distance_5, float distance_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[24];
	_mav_put_float(buf, 0, distance_1);
	_mav_put_float(buf, 4, distance_2);
	_mav_put_float(buf, 8, distance_3);
	_mav_put_float(buf, 12, distance_4);
	_mav_put_float(buf, 16, distance_5);
	_mav_put_float(buf, 20, distance_6);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_6_RAW, buf, 24, 165);
#else
	mavlink_nanotron_skye_sender_6_raw_t packet;
	packet.distance_1 = distance_1;
	packet.distance_2 = distance_2;
	packet.distance_3 = distance_3;
	packet.distance_4 = distance_4;
	packet.distance_5 = distance_5;
	packet.distance_6 = distance_6;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NANOTRON_SKYE_SENDER_6_RAW, (const char *)&packet, 24, 165);
#endif
}

#endif

// MESSAGE NANOTRON_SKYE_SENDER_6_RAW UNPACKING


/**
 * @brief Get field distance_1 from nanotron_skye_sender_6_raw message
 *
 * @return Distance to Receiver module 1
 */
static inline float mavlink_msg_nanotron_skye_sender_6_raw_get_distance_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field distance_2 from nanotron_skye_sender_6_raw message
 *
 * @return Distance to Receiver module 2
 */
static inline float mavlink_msg_nanotron_skye_sender_6_raw_get_distance_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field distance_3 from nanotron_skye_sender_6_raw message
 *
 * @return Distance to Receiver module 3
 */
static inline float mavlink_msg_nanotron_skye_sender_6_raw_get_distance_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field distance_4 from nanotron_skye_sender_6_raw message
 *
 * @return Distance to Receiver module 4
 */
static inline float mavlink_msg_nanotron_skye_sender_6_raw_get_distance_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field distance_5 from nanotron_skye_sender_6_raw message
 *
 * @return Distance to Receiver module 5
 */
static inline float mavlink_msg_nanotron_skye_sender_6_raw_get_distance_5(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field distance_6 from nanotron_skye_sender_6_raw message
 *
 * @return Distance to Receiver module 6
 */
static inline float mavlink_msg_nanotron_skye_sender_6_raw_get_distance_6(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a nanotron_skye_sender_6_raw message into a struct
 *
 * @param msg The message to decode
 * @param nanotron_skye_sender_6_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_nanotron_skye_sender_6_raw_decode(const mavlink_message_t* msg, mavlink_nanotron_skye_sender_6_raw_t* nanotron_skye_sender_6_raw)
{
#if MAVLINK_NEED_BYTE_SWAP
	nanotron_skye_sender_6_raw->distance_1 = mavlink_msg_nanotron_skye_sender_6_raw_get_distance_1(msg);
	nanotron_skye_sender_6_raw->distance_2 = mavlink_msg_nanotron_skye_sender_6_raw_get_distance_2(msg);
	nanotron_skye_sender_6_raw->distance_3 = mavlink_msg_nanotron_skye_sender_6_raw_get_distance_3(msg);
	nanotron_skye_sender_6_raw->distance_4 = mavlink_msg_nanotron_skye_sender_6_raw_get_distance_4(msg);
	nanotron_skye_sender_6_raw->distance_5 = mavlink_msg_nanotron_skye_sender_6_raw_get_distance_5(msg);
	nanotron_skye_sender_6_raw->distance_6 = mavlink_msg_nanotron_skye_sender_6_raw_get_distance_6(msg);
#else
	memcpy(nanotron_skye_sender_6_raw, _MAV_PAYLOAD(msg), 24);
#endif
}
