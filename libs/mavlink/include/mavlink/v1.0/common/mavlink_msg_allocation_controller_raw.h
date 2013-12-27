// MESSAGE ALLOCATION_CONTROLLER_RAW PACKING

#define MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW 136

typedef struct __mavlink_allocation_controller_raw_t
{
 int32_t pos_1; ///< Orientation motor setpoint of AU 1
 int32_t pos_2; ///< Orientation motor setpoint of of AU 2
 int32_t pos_3; ///< Orientation motor setpoint of of AU 3
 int32_t pos_4; ///< Orientation motor setpoint of of AU 4
 uint16_t thrust_1; ///< Thrust motor setpoint of AU 1
 uint16_t thrust_2; ///< Thrust motor setpoint of AU 2
 uint16_t thrust_3; ///< Thrust motor setpoint of AU 3
 uint16_t thrust_4; ///< Thrust motor setpoint of AU 4
} mavlink_allocation_controller_raw_t;

#define MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN 24
#define MAVLINK_MSG_ID_136_LEN 24

#define MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_CRC 200
#define MAVLINK_MSG_ID_136_CRC 200



#define MAVLINK_MESSAGE_INFO_ALLOCATION_CONTROLLER_RAW { \
	"ALLOCATION_CONTROLLER_RAW", \
	8, \
	{  { "pos_1", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_allocation_controller_raw_t, pos_1) }, \
         { "pos_2", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_allocation_controller_raw_t, pos_2) }, \
         { "pos_3", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_allocation_controller_raw_t, pos_3) }, \
         { "pos_4", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_allocation_controller_raw_t, pos_4) }, \
         { "thrust_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_allocation_controller_raw_t, thrust_1) }, \
         { "thrust_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_allocation_controller_raw_t, thrust_2) }, \
         { "thrust_3", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_allocation_controller_raw_t, thrust_3) }, \
         { "thrust_4", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_allocation_controller_raw_t, thrust_4) }, \
         } \
}


/**
 * @brief Pack a allocation_controller_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_1 Orientation motor setpoint of AU 1
 * @param pos_2 Orientation motor setpoint of of AU 2
 * @param pos_3 Orientation motor setpoint of of AU 3
 * @param pos_4 Orientation motor setpoint of of AU 4
 * @param thrust_1 Thrust motor setpoint of AU 1
 * @param thrust_2 Thrust motor setpoint of AU 2
 * @param thrust_3 Thrust motor setpoint of AU 3
 * @param thrust_4 Thrust motor setpoint of AU 4
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int32_t pos_1, int32_t pos_2, int32_t pos_3, int32_t pos_4, uint16_t thrust_1, uint16_t thrust_2, uint16_t thrust_3, uint16_t thrust_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN];
	_mav_put_int32_t(buf, 0, pos_1);
	_mav_put_int32_t(buf, 4, pos_2);
	_mav_put_int32_t(buf, 8, pos_3);
	_mav_put_int32_t(buf, 12, pos_4);
	_mav_put_uint16_t(buf, 16, thrust_1);
	_mav_put_uint16_t(buf, 18, thrust_2);
	_mav_put_uint16_t(buf, 20, thrust_3);
	_mav_put_uint16_t(buf, 22, thrust_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#else
	mavlink_allocation_controller_raw_t packet;
	packet.pos_1 = pos_1;
	packet.pos_2 = pos_2;
	packet.pos_3 = pos_3;
	packet.pos_4 = pos_4;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif
}

/**
 * @brief Pack a allocation_controller_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_1 Orientation motor setpoint of AU 1
 * @param pos_2 Orientation motor setpoint of of AU 2
 * @param pos_3 Orientation motor setpoint of of AU 3
 * @param pos_4 Orientation motor setpoint of of AU 4
 * @param thrust_1 Thrust motor setpoint of AU 1
 * @param thrust_2 Thrust motor setpoint of AU 2
 * @param thrust_3 Thrust motor setpoint of AU 3
 * @param thrust_4 Thrust motor setpoint of AU 4
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int32_t pos_1,int32_t pos_2,int32_t pos_3,int32_t pos_4,uint16_t thrust_1,uint16_t thrust_2,uint16_t thrust_3,uint16_t thrust_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN];
	_mav_put_int32_t(buf, 0, pos_1);
	_mav_put_int32_t(buf, 4, pos_2);
	_mav_put_int32_t(buf, 8, pos_3);
	_mav_put_int32_t(buf, 12, pos_4);
	_mav_put_uint16_t(buf, 16, thrust_1);
	_mav_put_uint16_t(buf, 18, thrust_2);
	_mav_put_uint16_t(buf, 20, thrust_3);
	_mav_put_uint16_t(buf, 22, thrust_4);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#else
	mavlink_allocation_controller_raw_t packet;
	packet.pos_1 = pos_1;
	packet.pos_2 = pos_2;
	packet.pos_3 = pos_3;
	packet.pos_4 = pos_4;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif
}

/**
 * @brief Encode a allocation_controller_raw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param allocation_controller_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_allocation_controller_raw_t* allocation_controller_raw)
{
	return mavlink_msg_allocation_controller_raw_pack(system_id, component_id, msg, allocation_controller_raw->pos_1, allocation_controller_raw->pos_2, allocation_controller_raw->pos_3, allocation_controller_raw->pos_4, allocation_controller_raw->thrust_1, allocation_controller_raw->thrust_2, allocation_controller_raw->thrust_3, allocation_controller_raw->thrust_4);
}

/**
 * @brief Encode a allocation_controller_raw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param allocation_controller_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_allocation_controller_raw_t* allocation_controller_raw)
{
	return mavlink_msg_allocation_controller_raw_pack_chan(system_id, component_id, chan, msg, allocation_controller_raw->pos_1, allocation_controller_raw->pos_2, allocation_controller_raw->pos_3, allocation_controller_raw->pos_4, allocation_controller_raw->thrust_1, allocation_controller_raw->thrust_2, allocation_controller_raw->thrust_3, allocation_controller_raw->thrust_4);
}

/**
 * @brief Send a allocation_controller_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_1 Orientation motor setpoint of AU 1
 * @param pos_2 Orientation motor setpoint of of AU 2
 * @param pos_3 Orientation motor setpoint of of AU 3
 * @param pos_4 Orientation motor setpoint of of AU 4
 * @param thrust_1 Thrust motor setpoint of AU 1
 * @param thrust_2 Thrust motor setpoint of AU 2
 * @param thrust_3 Thrust motor setpoint of AU 3
 * @param thrust_4 Thrust motor setpoint of AU 4
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_allocation_controller_raw_send(mavlink_channel_t chan, int32_t pos_1, int32_t pos_2, int32_t pos_3, int32_t pos_4, uint16_t thrust_1, uint16_t thrust_2, uint16_t thrust_3, uint16_t thrust_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN];
	_mav_put_int32_t(buf, 0, pos_1);
	_mav_put_int32_t(buf, 4, pos_2);
	_mav_put_int32_t(buf, 8, pos_3);
	_mav_put_int32_t(buf, 12, pos_4);
	_mav_put_uint16_t(buf, 16, thrust_1);
	_mav_put_uint16_t(buf, 18, thrust_2);
	_mav_put_uint16_t(buf, 20, thrust_3);
	_mav_put_uint16_t(buf, 22, thrust_4);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW, buf, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW, buf, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif
#else
	mavlink_allocation_controller_raw_t packet;
	packet.pos_1 = pos_1;
	packet.pos_2 = pos_2;
	packet.pos_3 = pos_3;
	packet.pos_4 = pos_4;
	packet.thrust_1 = thrust_1;
	packet.thrust_2 = thrust_2;
	packet.thrust_3 = thrust_3;
	packet.thrust_4 = thrust_4;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW, (const char *)&packet, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW, (const char *)&packet, MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif
#endif
}

#endif

// MESSAGE ALLOCATION_CONTROLLER_RAW UNPACKING


/**
 * @brief Get field pos_1 from allocation_controller_raw message
 *
 * @return Orientation motor setpoint of AU 1
 */
static inline int32_t mavlink_msg_allocation_controller_raw_get_pos_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field pos_2 from allocation_controller_raw message
 *
 * @return Orientation motor setpoint of of AU 2
 */
static inline int32_t mavlink_msg_allocation_controller_raw_get_pos_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field pos_3 from allocation_controller_raw message
 *
 * @return Orientation motor setpoint of of AU 3
 */
static inline int32_t mavlink_msg_allocation_controller_raw_get_pos_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field pos_4 from allocation_controller_raw message
 *
 * @return Orientation motor setpoint of of AU 4
 */
static inline int32_t mavlink_msg_allocation_controller_raw_get_pos_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field thrust_1 from allocation_controller_raw message
 *
 * @return Thrust motor setpoint of AU 1
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_get_thrust_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field thrust_2 from allocation_controller_raw message
 *
 * @return Thrust motor setpoint of AU 2
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_get_thrust_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field thrust_3 from allocation_controller_raw message
 *
 * @return Thrust motor setpoint of AU 3
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_get_thrust_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field thrust_4 from allocation_controller_raw message
 *
 * @return Thrust motor setpoint of AU 4
 */
static inline uint16_t mavlink_msg_allocation_controller_raw_get_thrust_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Decode a allocation_controller_raw message into a struct
 *
 * @param msg The message to decode
 * @param allocation_controller_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_allocation_controller_raw_decode(const mavlink_message_t* msg, mavlink_allocation_controller_raw_t* allocation_controller_raw)
{
#if MAVLINK_NEED_BYTE_SWAP
	allocation_controller_raw->pos_1 = mavlink_msg_allocation_controller_raw_get_pos_1(msg);
	allocation_controller_raw->pos_2 = mavlink_msg_allocation_controller_raw_get_pos_2(msg);
	allocation_controller_raw->pos_3 = mavlink_msg_allocation_controller_raw_get_pos_3(msg);
	allocation_controller_raw->pos_4 = mavlink_msg_allocation_controller_raw_get_pos_4(msg);
	allocation_controller_raw->thrust_1 = mavlink_msg_allocation_controller_raw_get_thrust_1(msg);
	allocation_controller_raw->thrust_2 = mavlink_msg_allocation_controller_raw_get_thrust_2(msg);
	allocation_controller_raw->thrust_3 = mavlink_msg_allocation_controller_raw_get_thrust_3(msg);
	allocation_controller_raw->thrust_4 = mavlink_msg_allocation_controller_raw_get_thrust_4(msg);
#else
	memcpy(allocation_controller_raw, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ALLOCATION_CONTROLLER_RAW_LEN);
#endif
}
