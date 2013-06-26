// MESSAGE ACTUATION_CURRENT PACKING

#define MAVLINK_MSG_ID_ACTUATION_CURRENT 145

typedef struct __mavlink_actuation_current_t
{
 int16_t current_1; ///< Actuation unit 1 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 int16_t current_2; ///< Actuation unit 2 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 int16_t current_3; ///< Actuation unit 3 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 int16_t current_4; ///< Actuation unit 4 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 uint8_t id; ///< ID for personal specification
} mavlink_actuation_current_t;

#define MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN 9
#define MAVLINK_MSG_ID_145_LEN 9

#define MAVLINK_MSG_ID_ACTUATION_CURRENT_CRC 106
#define MAVLINK_MSG_ID_145_CRC 106



#define MAVLINK_MESSAGE_INFO_ACTUATION_CURRENT { \
	"ACTUATION_CURRENT", \
	5, \
	{  { "current_1", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_actuation_current_t, current_1) }, \
         { "current_2", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_actuation_current_t, current_2) }, \
         { "current_3", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_actuation_current_t, current_3) }, \
         { "current_4", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_actuation_current_t, current_4) }, \
         { "id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_actuation_current_t, id) }, \
         } \
}


/**
 * @brief Pack a actuation_current message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id ID for personal specification
 * @param current_1 Actuation unit 1 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_2 Actuation unit 2 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_3 Actuation unit 3 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_4 Actuation unit 4 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_current_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t id, int16_t current_1, int16_t current_2, int16_t current_3, int16_t current_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN];
	_mav_put_int16_t(buf, 0, current_1);
	_mav_put_int16_t(buf, 2, current_2);
	_mav_put_int16_t(buf, 4, current_3);
	_mav_put_int16_t(buf, 6, current_4);
	_mav_put_uint8_t(buf, 8, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#else
	mavlink_actuation_current_t packet;
	packet.current_1 = current_1;
	packet.current_2 = current_2;
	packet.current_3 = current_3;
	packet.current_4 = current_4;
	packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_CURRENT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN, MAVLINK_MSG_ID_ACTUATION_CURRENT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif
}

/**
 * @brief Pack a actuation_current message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param id ID for personal specification
 * @param current_1 Actuation unit 1 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_2 Actuation unit 2 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_3 Actuation unit 3 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_4 Actuation unit 4 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_current_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t id,int16_t current_1,int16_t current_2,int16_t current_3,int16_t current_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN];
	_mav_put_int16_t(buf, 0, current_1);
	_mav_put_int16_t(buf, 2, current_2);
	_mav_put_int16_t(buf, 4, current_3);
	_mav_put_int16_t(buf, 6, current_4);
	_mav_put_uint8_t(buf, 8, id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#else
	mavlink_actuation_current_t packet;
	packet.current_1 = current_1;
	packet.current_2 = current_2;
	packet.current_3 = current_3;
	packet.current_4 = current_4;
	packet.id = id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_CURRENT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN, MAVLINK_MSG_ID_ACTUATION_CURRENT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif
}

/**
 * @brief Encode a actuation_current struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param actuation_current C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_current_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_actuation_current_t* actuation_current)
{
	return mavlink_msg_actuation_current_pack(system_id, component_id, msg, actuation_current->id, actuation_current->current_1, actuation_current->current_2, actuation_current->current_3, actuation_current->current_4);
}

/**
 * @brief Send a actuation_current message
 * @param chan MAVLink channel to send the message
 *
 * @param id ID for personal specification
 * @param current_1 Actuation unit 1 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_2 Actuation unit 2 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_3 Actuation unit 3 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param current_4 Actuation unit 4 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_actuation_current_send(mavlink_channel_t chan, uint8_t id, int16_t current_1, int16_t current_2, int16_t current_3, int16_t current_4)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN];
	_mav_put_int16_t(buf, 0, current_1);
	_mav_put_int16_t(buf, 2, current_2);
	_mav_put_int16_t(buf, 4, current_3);
	_mav_put_int16_t(buf, 6, current_4);
	_mav_put_uint8_t(buf, 8, id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CURRENT, buf, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN, MAVLINK_MSG_ID_ACTUATION_CURRENT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CURRENT, buf, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif
#else
	mavlink_actuation_current_t packet;
	packet.current_1 = current_1;
	packet.current_2 = current_2;
	packet.current_3 = current_3;
	packet.current_4 = current_4;
	packet.id = id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CURRENT, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN, MAVLINK_MSG_ID_ACTUATION_CURRENT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_CURRENT, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif
#endif
}

#endif

// MESSAGE ACTUATION_CURRENT UNPACKING


/**
 * @brief Get field id from actuation_current message
 *
 * @return ID for personal specification
 */
static inline uint8_t mavlink_msg_actuation_current_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field current_1 from actuation_current message
 *
 * @return Actuation unit 1 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 */
static inline int16_t mavlink_msg_actuation_current_get_current_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field current_2 from actuation_current message
 *
 * @return Actuation unit 2 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 */
static inline int16_t mavlink_msg_actuation_current_get_current_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field current_3 from actuation_current message
 *
 * @return Actuation unit 3 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 */
static inline int16_t mavlink_msg_actuation_current_get_current_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field current_4 from actuation_current message
 *
 * @return Actuation unit 4 current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 */
static inline int16_t mavlink_msg_actuation_current_get_current_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Decode a actuation_current message into a struct
 *
 * @param msg The message to decode
 * @param actuation_current C-struct to decode the message contents into
 */
static inline void mavlink_msg_actuation_current_decode(const mavlink_message_t* msg, mavlink_actuation_current_t* actuation_current)
{
#if MAVLINK_NEED_BYTE_SWAP
	actuation_current->current_1 = mavlink_msg_actuation_current_get_current_1(msg);
	actuation_current->current_2 = mavlink_msg_actuation_current_get_current_2(msg);
	actuation_current->current_3 = mavlink_msg_actuation_current_get_current_3(msg);
	actuation_current->current_4 = mavlink_msg_actuation_current_get_current_4(msg);
	actuation_current->id = mavlink_msg_actuation_current_get_id(msg);
#else
	memcpy(actuation_current, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACTUATION_CURRENT_LEN);
#endif
}
