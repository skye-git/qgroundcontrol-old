// MESSAGE SKYE_BATTERY_STATUS PACKING

#define MAVLINK_MSG_ID_SKYE_BATTERY_STATUS 152

typedef struct __mavlink_skye_battery_status_t
{
 uint16_t voltage_cell_1; ///< Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_2; ///< Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_3; ///< Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_4; ///< Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 int16_t current_battery; ///< Battery current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 uint8_t target_system; ///< System ID
 uint8_t accu_id; ///< Accupack ID
 int8_t battery_remaining; ///< Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
} mavlink_skye_battery_status_t;

#define MAVLINK_MSG_ID_SKYE_BATTERY_STATUS_LEN 13
#define MAVLINK_MSG_ID_152_LEN 13



#define MAVLINK_MESSAGE_INFO_SKYE_BATTERY_STATUS { \
	"SKYE_BATTERY_STATUS", \
	8, \
	{  { "voltage_cell_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_skye_battery_status_t, voltage_cell_1) }, \
         { "voltage_cell_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_skye_battery_status_t, voltage_cell_2) }, \
         { "voltage_cell_3", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_skye_battery_status_t, voltage_cell_3) }, \
         { "voltage_cell_4", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_skye_battery_status_t, voltage_cell_4) }, \
         { "current_battery", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_skye_battery_status_t, current_battery) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_skye_battery_status_t, target_system) }, \
         { "accu_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_skye_battery_status_t, accu_id) }, \
         { "battery_remaining", NULL, MAVLINK_TYPE_INT8_T, 0, 12, offsetof(mavlink_skye_battery_status_t, battery_remaining) }, \
         } \
}


/**
 * @brief Pack a skye_battery_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param accu_id Accupack ID
 * @param voltage_cell_1 Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_2 Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_3 Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_4 Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 * @param current_battery Battery current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_battery_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t accu_id, uint16_t voltage_cell_1, uint16_t voltage_cell_2, uint16_t voltage_cell_3, uint16_t voltage_cell_4, int16_t current_battery, int8_t battery_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_int16_t(buf, 8, current_battery);
	_mav_put_uint8_t(buf, 10, target_system);
	_mav_put_uint8_t(buf, 11, accu_id);
	_mav_put_int8_t(buf, 12, battery_remaining);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 13);
#else
	mavlink_skye_battery_status_t packet;
	packet.voltage_cell_1 = voltage_cell_1;
	packet.voltage_cell_2 = voltage_cell_2;
	packet.voltage_cell_3 = voltage_cell_3;
	packet.voltage_cell_4 = voltage_cell_4;
	packet.current_battery = current_battery;
	packet.target_system = target_system;
	packet.accu_id = accu_id;
	packet.battery_remaining = battery_remaining;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 13);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_BATTERY_STATUS;
	return mavlink_finalize_message(msg, system_id, component_id, 13, 211);
}

/**
 * @brief Pack a skye_battery_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param accu_id Accupack ID
 * @param voltage_cell_1 Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_2 Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_3 Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_4 Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 * @param current_battery Battery current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_battery_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t accu_id,uint16_t voltage_cell_1,uint16_t voltage_cell_2,uint16_t voltage_cell_3,uint16_t voltage_cell_4,int16_t current_battery,int8_t battery_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_int16_t(buf, 8, current_battery);
	_mav_put_uint8_t(buf, 10, target_system);
	_mav_put_uint8_t(buf, 11, accu_id);
	_mav_put_int8_t(buf, 12, battery_remaining);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 13);
#else
	mavlink_skye_battery_status_t packet;
	packet.voltage_cell_1 = voltage_cell_1;
	packet.voltage_cell_2 = voltage_cell_2;
	packet.voltage_cell_3 = voltage_cell_3;
	packet.voltage_cell_4 = voltage_cell_4;
	packet.current_battery = current_battery;
	packet.target_system = target_system;
	packet.accu_id = accu_id;
	packet.battery_remaining = battery_remaining;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 13);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_BATTERY_STATUS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 13, 211);
}

/**
 * @brief Encode a skye_battery_status struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_battery_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_battery_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_battery_status_t* skye_battery_status)
{
	return mavlink_msg_skye_battery_status_pack(system_id, component_id, msg, skye_battery_status->target_system, skye_battery_status->accu_id, skye_battery_status->voltage_cell_1, skye_battery_status->voltage_cell_2, skye_battery_status->voltage_cell_3, skye_battery_status->voltage_cell_4, skye_battery_status->current_battery, skye_battery_status->battery_remaining);
}

/**
 * @brief Send a skye_battery_status message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param accu_id Accupack ID
 * @param voltage_cell_1 Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_2 Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_3 Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_4 Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 * @param current_battery Battery current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 * @param battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_battery_status_send(mavlink_channel_t chan, uint8_t target_system, uint8_t accu_id, uint16_t voltage_cell_1, uint16_t voltage_cell_2, uint16_t voltage_cell_3, uint16_t voltage_cell_4, int16_t current_battery, int8_t battery_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_int16_t(buf, 8, current_battery);
	_mav_put_uint8_t(buf, 10, target_system);
	_mav_put_uint8_t(buf, 11, accu_id);
	_mav_put_int8_t(buf, 12, battery_remaining);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_BATTERY_STATUS, buf, 13, 211);
#else
	mavlink_skye_battery_status_t packet;
	packet.voltage_cell_1 = voltage_cell_1;
	packet.voltage_cell_2 = voltage_cell_2;
	packet.voltage_cell_3 = voltage_cell_3;
	packet.voltage_cell_4 = voltage_cell_4;
	packet.current_battery = current_battery;
	packet.target_system = target_system;
	packet.accu_id = accu_id;
	packet.battery_remaining = battery_remaining;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_BATTERY_STATUS, (const char *)&packet, 13, 211);
#endif
}

#endif

// MESSAGE SKYE_BATTERY_STATUS UNPACKING


/**
 * @brief Get field target_system from skye_battery_status message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_battery_status_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field accu_id from skye_battery_status message
 *
 * @return Accupack ID
 */
static inline uint8_t mavlink_msg_skye_battery_status_get_accu_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field voltage_cell_1 from skye_battery_status message
 *
 * @return Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_skye_battery_status_get_voltage_cell_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field voltage_cell_2 from skye_battery_status message
 *
 * @return Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_skye_battery_status_get_voltage_cell_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field voltage_cell_3 from skye_battery_status message
 *
 * @return Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_skye_battery_status_get_voltage_cell_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field voltage_cell_4 from skye_battery_status message
 *
 * @return Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_skye_battery_status_get_voltage_cell_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field current_battery from skye_battery_status message
 *
 * @return Battery current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
 */
static inline int16_t mavlink_msg_skye_battery_status_get_current_battery(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  8);
}

/**
 * @brief Get field battery_remaining from skye_battery_status message
 *
 * @return Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
 */
static inline int8_t mavlink_msg_skye_battery_status_get_battery_remaining(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  12);
}

/**
 * @brief Decode a skye_battery_status message into a struct
 *
 * @param msg The message to decode
 * @param skye_battery_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_battery_status_decode(const mavlink_message_t* msg, mavlink_skye_battery_status_t* skye_battery_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_battery_status->voltage_cell_1 = mavlink_msg_skye_battery_status_get_voltage_cell_1(msg);
	skye_battery_status->voltage_cell_2 = mavlink_msg_skye_battery_status_get_voltage_cell_2(msg);
	skye_battery_status->voltage_cell_3 = mavlink_msg_skye_battery_status_get_voltage_cell_3(msg);
	skye_battery_status->voltage_cell_4 = mavlink_msg_skye_battery_status_get_voltage_cell_4(msg);
	skye_battery_status->current_battery = mavlink_msg_skye_battery_status_get_current_battery(msg);
	skye_battery_status->target_system = mavlink_msg_skye_battery_status_get_target_system(msg);
	skye_battery_status->accu_id = mavlink_msg_skye_battery_status_get_accu_id(msg);
	skye_battery_status->battery_remaining = mavlink_msg_skye_battery_status_get_battery_remaining(msg);
#else
	memcpy(skye_battery_status, _MAV_PAYLOAD(msg), 13);
#endif
}
