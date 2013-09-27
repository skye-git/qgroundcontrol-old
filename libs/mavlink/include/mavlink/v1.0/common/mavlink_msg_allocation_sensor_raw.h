// MESSAGE ALLOCATION_SENSOR_RAW PACKING

#define MAVLINK_MSG_ID_ALLOCATION_SENSOR_RAW 137

typedef struct __mavlink_allocation_sensor_raw_t
{
 int32_t pos_1; ///< Orientation motor position readout of AU 1
 int32_t pos_2; ///< Orientation motor position readout of AU 2
 int32_t pos_3; ///< Orientation motor position readout of AU 3
 int32_t pos_4; ///< Orientation motor position readout of AU 4
} mavlink_allocation_sensor_raw_t;

#define MAVLINK_MSG_ID_ALLOCATION_SENSOR_RAW_LEN 16
#define MAVLINK_MSG_ID_137_LEN 16



#define MAVLINK_MESSAGE_INFO_ALLOCATION_SENSOR_RAW { \
	"ALLOCATION_SENSOR_RAW", \
	4, \
	{  { "pos_1", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_allocation_sensor_raw_t, pos_1) }, \
         { "pos_2", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_allocation_sensor_raw_t, pos_2) }, \
         { "pos_3", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_allocation_sensor_raw_t, pos_3) }, \
         { "pos_4", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_allocation_sensor_raw_t, pos_4) }, \
         } \
}


/**
 * @brief Pack a allocation_sensor_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_1 Orientation motor position readout of AU 1
 * @param pos_2 Orientation motor position readout of AU 2
 * @param pos_3 Orientation motor position readout of AU 3
 * @param pos_4 Orientation motor position readout of AU 4
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_allocation_sensor_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int32_t pos_1, int32_t pos_2, int32_t pos_3, int32_t pos_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[16];
	_mav_put_int32_t(buf, 0, pos_1);
	_mav_put_int32_t(buf, 4, pos_2);
	_mav_put_int32_t(buf, 8, pos_3);
	_mav_put_int32_t(buf, 12, pos_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 16);
#else
	mavlink_allocation_sensor_raw_t packet;
	packet.pos_1 = pos_1;
	packet.pos_2 = pos_2;
	packet.pos_3 = pos_3;
	packet.pos_4 = pos_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 16);
#endif

	msg->msgid = MAVLINK_MSG_ID_ALLOCATION_SENSOR_RAW;
	return mavlink_finalize_message(msg, system_id, component_id, 16, 212);
}

/**
 * @brief Pack a allocation_sensor_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_1 Orientation motor position readout of AU 1
 * @param pos_2 Orientation motor position readout of AU 2
 * @param pos_3 Orientation motor position readout of AU 3
 * @param pos_4 Orientation motor position readout of AU 4
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_allocation_sensor_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int32_t pos_1,int32_t pos_2,int32_t pos_3,int32_t pos_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[16];
	_mav_put_int32_t(buf, 0, pos_1);
	_mav_put_int32_t(buf, 4, pos_2);
	_mav_put_int32_t(buf, 8, pos_3);
	_mav_put_int32_t(buf, 12, pos_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 16);
#else
	mavlink_allocation_sensor_raw_t packet;
	packet.pos_1 = pos_1;
	packet.pos_2 = pos_2;
	packet.pos_3 = pos_3;
	packet.pos_4 = pos_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 16);
#endif

	msg->msgid = MAVLINK_MSG_ID_ALLOCATION_SENSOR_RAW;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 16, 212);
}

/**
 * @brief Encode a allocation_sensor_raw struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param allocation_sensor_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_allocation_sensor_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_allocation_sensor_raw_t* allocation_sensor_raw)
{
	return mavlink_msg_allocation_sensor_raw_pack(system_id, component_id, msg, allocation_sensor_raw->pos_1, allocation_sensor_raw->pos_2, allocation_sensor_raw->pos_3, allocation_sensor_raw->pos_4);
}

/**
 * @brief Send a allocation_sensor_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_1 Orientation motor position readout of AU 1
 * @param pos_2 Orientation motor position readout of AU 2
 * @param pos_3 Orientation motor position readout of AU 3
 * @param pos_4 Orientation motor position readout of AU 4
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_allocation_sensor_raw_send(mavlink_channel_t chan, int32_t pos_1, int32_t pos_2, int32_t pos_3, int32_t pos_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[16];
	_mav_put_int32_t(buf, 0, pos_1);
	_mav_put_int32_t(buf, 4, pos_2);
	_mav_put_int32_t(buf, 8, pos_3);
	_mav_put_int32_t(buf, 12, pos_4);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ALLOCATION_SENSOR_RAW, buf, 16, 212);
#else
	mavlink_allocation_sensor_raw_t packet;
	packet.pos_1 = pos_1;
	packet.pos_2 = pos_2;
	packet.pos_3 = pos_3;
	packet.pos_4 = pos_4;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ALLOCATION_SENSOR_RAW, (const char *)&packet, 16, 212);
#endif
}

#endif

// MESSAGE ALLOCATION_SENSOR_RAW UNPACKING


/**
 * @brief Get field pos_1 from allocation_sensor_raw message
 *
 * @return Orientation motor position readout of AU 1
 */
static inline int32_t mavlink_msg_allocation_sensor_raw_get_pos_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field pos_2 from allocation_sensor_raw message
 *
 * @return Orientation motor position readout of AU 2
 */
static inline int32_t mavlink_msg_allocation_sensor_raw_get_pos_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field pos_3 from allocation_sensor_raw message
 *
 * @return Orientation motor position readout of AU 3
 */
static inline int32_t mavlink_msg_allocation_sensor_raw_get_pos_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field pos_4 from allocation_sensor_raw message
 *
 * @return Orientation motor position readout of AU 4
 */
static inline int32_t mavlink_msg_allocation_sensor_raw_get_pos_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Decode a allocation_sensor_raw message into a struct
 *
 * @param msg The message to decode
 * @param allocation_sensor_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_allocation_sensor_raw_decode(const mavlink_message_t* msg, mavlink_allocation_sensor_raw_t* allocation_sensor_raw)
{
#if MAVLINK_NEED_BYTE_SWAP
	allocation_sensor_raw->pos_1 = mavlink_msg_allocation_sensor_raw_get_pos_1(msg);
	allocation_sensor_raw->pos_2 = mavlink_msg_allocation_sensor_raw_get_pos_2(msg);
	allocation_sensor_raw->pos_3 = mavlink_msg_allocation_sensor_raw_get_pos_3(msg);
	allocation_sensor_raw->pos_4 = mavlink_msg_allocation_sensor_raw_get_pos_4(msg);
#else
	memcpy(allocation_sensor_raw, _MAV_PAYLOAD(msg), 16);
#endif
}
