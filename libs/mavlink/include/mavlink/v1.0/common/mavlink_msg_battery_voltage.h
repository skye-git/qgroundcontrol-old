// MESSAGE BATTERY_VOLTAGE PACKING

#define MAVLINK_MSG_ID_BATTERY_VOLTAGE 146

typedef struct __mavlink_battery_voltage_t
{
 uint16_t voltage_1; ///< Battery voltage of accu 1, in millivolts (1 = 1 millivolt)
 uint16_t voltage_2; ///< Battery voltage of accu 2, in millivolts (1 = 1 millivolt), -1: no cell
 uint16_t voltage_3; ///< Battery voltage of accu 3, in millivolts (1 = 1 millivolt), -1: no cell
 uint16_t voltage_4; ///< Battery voltage of accu 4, in millivolts (1 = 1 millivolt), -1: no cell
 uint8_t id; ///< ID for personal specification
 int8_t battery_remaining; ///< Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot does not estimate the remaining battery
} mavlink_battery_voltage_t;

#define MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN 10
#define MAVLINK_MSG_ID_146_LEN 10

#define MAVLINK_MSG_ID_BATTERY_VOLTAGE_CRC 80
#define MAVLINK_MSG_ID_146_CRC 80



#define MAVLINK_MESSAGE_INFO_BATTERY_VOLTAGE { \
	"BATTERY_VOLTAGE", \
	6, \
	{  { "voltage_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_battery_voltage_t, voltage_1) }, \
         { "voltage_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_battery_voltage_t, voltage_2) }, \
         { "voltage_3", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_battery_voltage_t, voltage_3) }, \
         { "voltage_4", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_battery_voltage_t, voltage_4) }, \
         { "id", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_battery_voltage_t, id) }, \
         { "battery_remaining", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_battery_voltage_t, battery_remaining) }, \
         } \
}


/**
 * @brief Pack a battery_voltage message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id ID for personal specification
 * @param voltage_1 Battery voltage of accu 1, in millivolts (1 = 1 millivolt)
 * @param voltage_2 Battery voltage of accu 2, in millivolts (1 = 1 millivolt), -1: no cell
 * @param voltage_3 Battery voltage of accu 3, in millivolts (1 = 1 millivolt), -1: no cell
 * @param voltage_4 Battery voltage of accu 4, in millivolts (1 = 1 millivolt), -1: no cell
 * @param battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot does not estimate the remaining battery
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_voltage_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t id, uint16_t voltage_1, uint16_t voltage_2, uint16_t voltage_3, uint16_t voltage_4, int8_t battery_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN];
	_mav_put_uint16_t(buf, 0, voltage_1);
	_mav_put_uint16_t(buf, 2, voltage_2);
	_mav_put_uint16_t(buf, 4, voltage_3);
	_mav_put_uint16_t(buf, 6, voltage_4);
	_mav_put_uint8_t(buf, 8, id);
	_mav_put_int8_t(buf, 9, battery_remaining);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#else
	mavlink_battery_voltage_t packet;
	packet.voltage_1 = voltage_1;
	packet.voltage_2 = voltage_2;
	packet.voltage_3 = voltage_3;
	packet.voltage_4 = voltage_4;
	packet.id = id;
	packet.battery_remaining = battery_remaining;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_VOLTAGE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN, MAVLINK_MSG_ID_BATTERY_VOLTAGE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif
}

/**
 * @brief Pack a battery_voltage message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param id ID for personal specification
 * @param voltage_1 Battery voltage of accu 1, in millivolts (1 = 1 millivolt)
 * @param voltage_2 Battery voltage of accu 2, in millivolts (1 = 1 millivolt), -1: no cell
 * @param voltage_3 Battery voltage of accu 3, in millivolts (1 = 1 millivolt), -1: no cell
 * @param voltage_4 Battery voltage of accu 4, in millivolts (1 = 1 millivolt), -1: no cell
 * @param battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot does not estimate the remaining battery
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_voltage_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t id,uint16_t voltage_1,uint16_t voltage_2,uint16_t voltage_3,uint16_t voltage_4,int8_t battery_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN];
	_mav_put_uint16_t(buf, 0, voltage_1);
	_mav_put_uint16_t(buf, 2, voltage_2);
	_mav_put_uint16_t(buf, 4, voltage_3);
	_mav_put_uint16_t(buf, 6, voltage_4);
	_mav_put_uint8_t(buf, 8, id);
	_mav_put_int8_t(buf, 9, battery_remaining);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#else
	mavlink_battery_voltage_t packet;
	packet.voltage_1 = voltage_1;
	packet.voltage_2 = voltage_2;
	packet.voltage_3 = voltage_3;
	packet.voltage_4 = voltage_4;
	packet.id = id;
	packet.battery_remaining = battery_remaining;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_VOLTAGE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN, MAVLINK_MSG_ID_BATTERY_VOLTAGE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif
}

/**
 * @brief Encode a battery_voltage struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param battery_voltage C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_voltage_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_battery_voltage_t* battery_voltage)
{
	return mavlink_msg_battery_voltage_pack(system_id, component_id, msg, battery_voltage->id, battery_voltage->voltage_1, battery_voltage->voltage_2, battery_voltage->voltage_3, battery_voltage->voltage_4, battery_voltage->battery_remaining);
}

/**
 * @brief Send a battery_voltage message
 * @param chan MAVLink channel to send the message
 *
 * @param id ID for personal specification
 * @param voltage_1 Battery voltage of accu 1, in millivolts (1 = 1 millivolt)
 * @param voltage_2 Battery voltage of accu 2, in millivolts (1 = 1 millivolt), -1: no cell
 * @param voltage_3 Battery voltage of accu 3, in millivolts (1 = 1 millivolt), -1: no cell
 * @param voltage_4 Battery voltage of accu 4, in millivolts (1 = 1 millivolt), -1: no cell
 * @param battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot does not estimate the remaining battery
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_battery_voltage_send(mavlink_channel_t chan, uint8_t id, uint16_t voltage_1, uint16_t voltage_2, uint16_t voltage_3, uint16_t voltage_4, int8_t battery_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN];
	_mav_put_uint16_t(buf, 0, voltage_1);
	_mav_put_uint16_t(buf, 2, voltage_2);
	_mav_put_uint16_t(buf, 4, voltage_3);
	_mav_put_uint16_t(buf, 6, voltage_4);
	_mav_put_uint8_t(buf, 8, id);
	_mav_put_int8_t(buf, 9, battery_remaining);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_VOLTAGE, buf, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN, MAVLINK_MSG_ID_BATTERY_VOLTAGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_VOLTAGE, buf, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif
#else
	mavlink_battery_voltage_t packet;
	packet.voltage_1 = voltage_1;
	packet.voltage_2 = voltage_2;
	packet.voltage_3 = voltage_3;
	packet.voltage_4 = voltage_4;
	packet.id = id;
	packet.battery_remaining = battery_remaining;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_VOLTAGE, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN, MAVLINK_MSG_ID_BATTERY_VOLTAGE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_VOLTAGE, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif
#endif
}

#endif

// MESSAGE BATTERY_VOLTAGE UNPACKING


/**
 * @brief Get field id from battery_voltage message
 *
 * @return ID for personal specification
 */
static inline uint8_t mavlink_msg_battery_voltage_get_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field voltage_1 from battery_voltage message
 *
 * @return Battery voltage of accu 1, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_voltage_get_voltage_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field voltage_2 from battery_voltage message
 *
 * @return Battery voltage of accu 2, in millivolts (1 = 1 millivolt), -1: no cell
 */
static inline uint16_t mavlink_msg_battery_voltage_get_voltage_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field voltage_3 from battery_voltage message
 *
 * @return Battery voltage of accu 3, in millivolts (1 = 1 millivolt), -1: no cell
 */
static inline uint16_t mavlink_msg_battery_voltage_get_voltage_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field voltage_4 from battery_voltage message
 *
 * @return Battery voltage of accu 4, in millivolts (1 = 1 millivolt), -1: no cell
 */
static inline uint16_t mavlink_msg_battery_voltage_get_voltage_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field battery_remaining from battery_voltage message
 *
 * @return Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot does not estimate the remaining battery
 */
static inline int8_t mavlink_msg_battery_voltage_get_battery_remaining(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  9);
}

/**
 * @brief Decode a battery_voltage message into a struct
 *
 * @param msg The message to decode
 * @param battery_voltage C-struct to decode the message contents into
 */
static inline void mavlink_msg_battery_voltage_decode(const mavlink_message_t* msg, mavlink_battery_voltage_t* battery_voltage)
{
#if MAVLINK_NEED_BYTE_SWAP
	battery_voltage->voltage_1 = mavlink_msg_battery_voltage_get_voltage_1(msg);
	battery_voltage->voltage_2 = mavlink_msg_battery_voltage_get_voltage_2(msg);
	battery_voltage->voltage_3 = mavlink_msg_battery_voltage_get_voltage_3(msg);
	battery_voltage->voltage_4 = mavlink_msg_battery_voltage_get_voltage_4(msg);
	battery_voltage->id = mavlink_msg_battery_voltage_get_id(msg);
	battery_voltage->battery_remaining = mavlink_msg_battery_voltage_get_battery_remaining(msg);
#else
	memcpy(battery_voltage, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BATTERY_VOLTAGE_LEN);
#endif
}
