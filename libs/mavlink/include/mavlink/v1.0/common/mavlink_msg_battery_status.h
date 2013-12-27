// MESSAGE BATTERY_STATUS PACKING

#define MAVLINK_MSG_ID_BATTERY_STATUS 146

typedef struct __mavlink_battery_status_t
{
 int32_t current; ///< Battery current, in milliamperes (1 = 1 milliampere), negative: outgoing current, positive: charging current
 int32_t energy; ///< Accumulated current since last reset, in milliamperehours (1 = 1 mAh), negative: outgoing energy, positive: charging energy
 uint16_t voltage; ///< Battery voltage, in millivolts (1 = 1 millivolt)
 uint8_t accu_id; ///< Accupack ID
 int8_t status; ///< bit 0: attached flag, bit 1: undervoltage flag, bit 2: disabled flag, bit 3: charging flag, bit 4: balancing flag, bit 5: battery full, bit 7: error
} mavlink_battery_status_t;

#define MAVLINK_MSG_ID_BATTERY_STATUS_LEN 12
#define MAVLINK_MSG_ID_146_LEN 12

#define MAVLINK_MSG_ID_BATTERY_STATUS_CRC 170
#define MAVLINK_MSG_ID_146_CRC 170



#define MAVLINK_MESSAGE_INFO_BATTERY_STATUS { \
	"BATTERY_STATUS", \
	5, \
	{  { "current", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_battery_status_t, current) }, \
         { "energy", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_battery_status_t, energy) }, \
         { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_battery_status_t, voltage) }, \
         { "accu_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_battery_status_t, accu_id) }, \
         { "status", NULL, MAVLINK_TYPE_INT8_T, 0, 11, offsetof(mavlink_battery_status_t, status) }, \
         } \
}


/**
 * @brief Pack a battery_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param accu_id Accupack ID
 * @param status bit 0: attached flag, bit 1: undervoltage flag, bit 2: disabled flag, bit 3: charging flag, bit 4: balancing flag, bit 5: battery full, bit 7: error
 * @param voltage Battery voltage, in millivolts (1 = 1 millivolt)
 * @param current Battery current, in milliamperes (1 = 1 milliampere), negative: outgoing current, positive: charging current
 * @param energy Accumulated current since last reset, in milliamperehours (1 = 1 mAh), negative: outgoing energy, positive: charging energy
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t accu_id, int8_t status, uint16_t voltage, int32_t current, int32_t energy)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_STATUS_LEN];
	_mav_put_int32_t(buf, 0, current);
	_mav_put_int32_t(buf, 4, energy);
	_mav_put_uint16_t(buf, 8, voltage);
	_mav_put_uint8_t(buf, 10, accu_id);
	_mav_put_int8_t(buf, 11, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#else
	mavlink_battery_status_t packet;
	packet.current = current;
	packet.energy = energy;
	packet.voltage = voltage;
	packet.accu_id = accu_id;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_STATUS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif
}

/**
 * @brief Pack a battery_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accu_id Accupack ID
 * @param status bit 0: attached flag, bit 1: undervoltage flag, bit 2: disabled flag, bit 3: charging flag, bit 4: balancing flag, bit 5: battery full, bit 7: error
 * @param voltage Battery voltage, in millivolts (1 = 1 millivolt)
 * @param current Battery current, in milliamperes (1 = 1 milliampere), negative: outgoing current, positive: charging current
 * @param energy Accumulated current since last reset, in milliamperehours (1 = 1 mAh), negative: outgoing energy, positive: charging energy
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t accu_id,int8_t status,uint16_t voltage,int32_t current,int32_t energy)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_STATUS_LEN];
	_mav_put_int32_t(buf, 0, current);
	_mav_put_int32_t(buf, 4, energy);
	_mav_put_uint16_t(buf, 8, voltage);
	_mav_put_uint8_t(buf, 10, accu_id);
	_mav_put_int8_t(buf, 11, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#else
	mavlink_battery_status_t packet;
	packet.current = current;
	packet.energy = energy;
	packet.voltage = voltage;
	packet.accu_id = accu_id;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_STATUS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif
}

/**
 * @brief Encode a battery_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param battery_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_battery_status_t* battery_status)
{
	return mavlink_msg_battery_status_pack(system_id, component_id, msg, battery_status->accu_id, battery_status->status, battery_status->voltage, battery_status->current, battery_status->energy);
}

/**
 * @brief Encode a battery_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param battery_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_battery_status_t* battery_status)
{
	return mavlink_msg_battery_status_pack_chan(system_id, component_id, chan, msg, battery_status->accu_id, battery_status->status, battery_status->voltage, battery_status->current, battery_status->energy);
}

/**
 * @brief Send a battery_status message
 * @param chan MAVLink channel to send the message
 *
 * @param accu_id Accupack ID
 * @param status bit 0: attached flag, bit 1: undervoltage flag, bit 2: disabled flag, bit 3: charging flag, bit 4: balancing flag, bit 5: battery full, bit 7: error
 * @param voltage Battery voltage, in millivolts (1 = 1 millivolt)
 * @param current Battery current, in milliamperes (1 = 1 milliampere), negative: outgoing current, positive: charging current
 * @param energy Accumulated current since last reset, in milliamperehours (1 = 1 mAh), negative: outgoing energy, positive: charging energy
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_battery_status_send(mavlink_channel_t chan, uint8_t accu_id, int8_t status, uint16_t voltage, int32_t current, int32_t energy)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_STATUS_LEN];
	_mav_put_int32_t(buf, 0, current);
	_mav_put_int32_t(buf, 4, energy);
	_mav_put_uint16_t(buf, 8, voltage);
	_mav_put_uint8_t(buf, 10, accu_id);
	_mav_put_int8_t(buf, 11, status);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_STATUS, buf, MAVLINK_MSG_ID_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_STATUS, buf, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif
#else
	mavlink_battery_status_t packet;
	packet.current = current;
	packet.energy = energy;
	packet.voltage = voltage;
	packet.accu_id = accu_id;
	packet.status = status;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_STATUS, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_STATUS, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif
#endif
}

#endif

// MESSAGE BATTERY_STATUS UNPACKING


/**
 * @brief Get field accu_id from battery_status message
 *
 * @return Accupack ID
 */
static inline uint8_t mavlink_msg_battery_status_get_accu_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field status from battery_status message
 *
 * @return bit 0: attached flag, bit 1: undervoltage flag, bit 2: disabled flag, bit 3: charging flag, bit 4: balancing flag, bit 5: battery full, bit 7: error
 */
static inline int8_t mavlink_msg_battery_status_get_status(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  11);
}

/**
 * @brief Get field voltage from battery_status message
 *
 * @return Battery voltage, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_status_get_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field current from battery_status message
 *
 * @return Battery current, in milliamperes (1 = 1 milliampere), negative: outgoing current, positive: charging current
 */
static inline int32_t mavlink_msg_battery_status_get_current(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field energy from battery_status message
 *
 * @return Accumulated current since last reset, in milliamperehours (1 = 1 mAh), negative: outgoing energy, positive: charging energy
 */
static inline int32_t mavlink_msg_battery_status_get_energy(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Decode a battery_status message into a struct
 *
 * @param msg The message to decode
 * @param battery_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_battery_status_decode(const mavlink_message_t* msg, mavlink_battery_status_t* battery_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	battery_status->current = mavlink_msg_battery_status_get_current(msg);
	battery_status->energy = mavlink_msg_battery_status_get_energy(msg);
	battery_status->voltage = mavlink_msg_battery_status_get_voltage(msg);
	battery_status->accu_id = mavlink_msg_battery_status_get_accu_id(msg);
	battery_status->status = mavlink_msg_battery_status_get_status(msg);
#else
	memcpy(battery_status, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BATTERY_STATUS_LEN);
#endif
}
