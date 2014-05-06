// MESSAGE BATTERY_CELLS_STATUS PACKING

#define MAVLINK_MSG_ID_BATTERY_CELLS_STATUS 147

typedef struct __mavlink_battery_cells_status_t
{
 uint16_t voltage_cell_1; ///< Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_2; ///< Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_3; ///< Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_4; ///< Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_5; ///< Battery voltage of cell 5, in millivolts (1 = 1 millivolt)
 uint16_t voltage_cell_6; ///< Battery voltage of cell 6, in millivolts (1 = 1 millivolt)
 uint8_t accu_id; ///< Accupack ID
} mavlink_battery_cells_status_t;

#define MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN 13
#define MAVLINK_MSG_ID_147_LEN 13

#define MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC 92
#define MAVLINK_MSG_ID_147_CRC 92



#define MAVLINK_MESSAGE_INFO_BATTERY_CELLS_STATUS { \
	"BATTERY_CELLS_STATUS", \
	7, \
	{  { "voltage_cell_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_battery_cells_status_t, voltage_cell_1) }, \
         { "voltage_cell_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_battery_cells_status_t, voltage_cell_2) }, \
         { "voltage_cell_3", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_battery_cells_status_t, voltage_cell_3) }, \
         { "voltage_cell_4", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_battery_cells_status_t, voltage_cell_4) }, \
         { "voltage_cell_5", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_battery_cells_status_t, voltage_cell_5) }, \
         { "voltage_cell_6", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_battery_cells_status_t, voltage_cell_6) }, \
         { "accu_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_battery_cells_status_t, accu_id) }, \
         } \
}


/**
 * @brief Pack a battery_cells_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param accu_id Accupack ID
 * @param voltage_cell_1 Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_2 Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_3 Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_4 Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_5 Battery voltage of cell 5, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_6 Battery voltage of cell 6, in millivolts (1 = 1 millivolt)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_cells_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t accu_id, uint16_t voltage_cell_1, uint16_t voltage_cell_2, uint16_t voltage_cell_3, uint16_t voltage_cell_4, uint16_t voltage_cell_5, uint16_t voltage_cell_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN];
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_uint16_t(buf, 8, voltage_cell_5);
	_mav_put_uint16_t(buf, 10, voltage_cell_6);
	_mav_put_uint8_t(buf, 12, accu_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#else
	mavlink_battery_cells_status_t packet;
	packet.voltage_cell_1 = voltage_cell_1;
	packet.voltage_cell_2 = voltage_cell_2;
	packet.voltage_cell_3 = voltage_cell_3;
	packet.voltage_cell_4 = voltage_cell_4;
	packet.voltage_cell_5 = voltage_cell_5;
	packet.voltage_cell_6 = voltage_cell_6;
	packet.accu_id = accu_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_CELLS_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
}

/**
 * @brief Pack a battery_cells_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accu_id Accupack ID
 * @param voltage_cell_1 Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_2 Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_3 Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_4 Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_5 Battery voltage of cell 5, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_6 Battery voltage of cell 6, in millivolts (1 = 1 millivolt)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery_cells_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t accu_id,uint16_t voltage_cell_1,uint16_t voltage_cell_2,uint16_t voltage_cell_3,uint16_t voltage_cell_4,uint16_t voltage_cell_5,uint16_t voltage_cell_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN];
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_uint16_t(buf, 8, voltage_cell_5);
	_mav_put_uint16_t(buf, 10, voltage_cell_6);
	_mav_put_uint8_t(buf, 12, accu_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#else
	mavlink_battery_cells_status_t packet;
	packet.voltage_cell_1 = voltage_cell_1;
	packet.voltage_cell_2 = voltage_cell_2;
	packet.voltage_cell_3 = voltage_cell_3;
	packet.voltage_cell_4 = voltage_cell_4;
	packet.voltage_cell_5 = voltage_cell_5;
	packet.voltage_cell_6 = voltage_cell_6;
	packet.accu_id = accu_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BATTERY_CELLS_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
}

/**
 * @brief Encode a battery_cells_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param battery_cells_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_cells_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_battery_cells_status_t* battery_cells_status)
{
	return mavlink_msg_battery_cells_status_pack(system_id, component_id, msg, battery_cells_status->accu_id, battery_cells_status->voltage_cell_1, battery_cells_status->voltage_cell_2, battery_cells_status->voltage_cell_3, battery_cells_status->voltage_cell_4, battery_cells_status->voltage_cell_5, battery_cells_status->voltage_cell_6);
}

/**
 * @brief Encode a battery_cells_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param battery_cells_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery_cells_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_battery_cells_status_t* battery_cells_status)
{
	return mavlink_msg_battery_cells_status_pack_chan(system_id, component_id, chan, msg, battery_cells_status->accu_id, battery_cells_status->voltage_cell_1, battery_cells_status->voltage_cell_2, battery_cells_status->voltage_cell_3, battery_cells_status->voltage_cell_4, battery_cells_status->voltage_cell_5, battery_cells_status->voltage_cell_6);
}

/**
 * @brief Send a battery_cells_status message
 * @param chan MAVLink channel to send the message
 *
 * @param accu_id Accupack ID
 * @param voltage_cell_1 Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_2 Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_3 Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_4 Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_5 Battery voltage of cell 5, in millivolts (1 = 1 millivolt)
 * @param voltage_cell_6 Battery voltage of cell 6, in millivolts (1 = 1 millivolt)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_battery_cells_status_send(mavlink_channel_t chan, uint8_t accu_id, uint16_t voltage_cell_1, uint16_t voltage_cell_2, uint16_t voltage_cell_3, uint16_t voltage_cell_4, uint16_t voltage_cell_5, uint16_t voltage_cell_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN];
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_uint16_t(buf, 8, voltage_cell_5);
	_mav_put_uint16_t(buf, 10, voltage_cell_6);
	_mav_put_uint8_t(buf, 12, accu_id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, buf, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, buf, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
#else
	mavlink_battery_cells_status_t packet;
	packet.voltage_cell_1 = voltage_cell_1;
	packet.voltage_cell_2 = voltage_cell_2;
	packet.voltage_cell_3 = voltage_cell_3;
	packet.voltage_cell_4 = voltage_cell_4;
	packet.voltage_cell_5 = voltage_cell_5;
	packet.voltage_cell_6 = voltage_cell_6;
	packet.accu_id = accu_id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, (const char *)&packet, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_battery_cells_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t accu_id, uint16_t voltage_cell_1, uint16_t voltage_cell_2, uint16_t voltage_cell_3, uint16_t voltage_cell_4, uint16_t voltage_cell_5, uint16_t voltage_cell_6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, voltage_cell_1);
	_mav_put_uint16_t(buf, 2, voltage_cell_2);
	_mav_put_uint16_t(buf, 4, voltage_cell_3);
	_mav_put_uint16_t(buf, 6, voltage_cell_4);
	_mav_put_uint16_t(buf, 8, voltage_cell_5);
	_mav_put_uint16_t(buf, 10, voltage_cell_6);
	_mav_put_uint8_t(buf, 12, accu_id);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, buf, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, buf, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
#else
	mavlink_battery_cells_status_t *packet = (mavlink_battery_cells_status_t *)msgbuf;
	packet->voltage_cell_1 = voltage_cell_1;
	packet->voltage_cell_2 = voltage_cell_2;
	packet->voltage_cell_3 = voltage_cell_3;
	packet->voltage_cell_4 = voltage_cell_4;
	packet->voltage_cell_5 = voltage_cell_5;
	packet->voltage_cell_6 = voltage_cell_6;
	packet->accu_id = accu_id;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, (const char *)packet, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS, (const char *)packet, MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE BATTERY_CELLS_STATUS UNPACKING


/**
 * @brief Get field accu_id from battery_cells_status message
 *
 * @return Accupack ID
 */
static inline uint8_t mavlink_msg_battery_cells_status_get_accu_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field voltage_cell_1 from battery_cells_status message
 *
 * @return Battery voltage of cell 1, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_cells_status_get_voltage_cell_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field voltage_cell_2 from battery_cells_status message
 *
 * @return Battery voltage of cell 2, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_cells_status_get_voltage_cell_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field voltage_cell_3 from battery_cells_status message
 *
 * @return Battery voltage of cell 3, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_cells_status_get_voltage_cell_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field voltage_cell_4 from battery_cells_status message
 *
 * @return Battery voltage of cell 4, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_cells_status_get_voltage_cell_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field voltage_cell_5 from battery_cells_status message
 *
 * @return Battery voltage of cell 5, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_cells_status_get_voltage_cell_5(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field voltage_cell_6 from battery_cells_status message
 *
 * @return Battery voltage of cell 6, in millivolts (1 = 1 millivolt)
 */
static inline uint16_t mavlink_msg_battery_cells_status_get_voltage_cell_6(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Decode a battery_cells_status message into a struct
 *
 * @param msg The message to decode
 * @param battery_cells_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_battery_cells_status_decode(const mavlink_message_t* msg, mavlink_battery_cells_status_t* battery_cells_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	battery_cells_status->voltage_cell_1 = mavlink_msg_battery_cells_status_get_voltage_cell_1(msg);
	battery_cells_status->voltage_cell_2 = mavlink_msg_battery_cells_status_get_voltage_cell_2(msg);
	battery_cells_status->voltage_cell_3 = mavlink_msg_battery_cells_status_get_voltage_cell_3(msg);
	battery_cells_status->voltage_cell_4 = mavlink_msg_battery_cells_status_get_voltage_cell_4(msg);
	battery_cells_status->voltage_cell_5 = mavlink_msg_battery_cells_status_get_voltage_cell_5(msg);
	battery_cells_status->voltage_cell_6 = mavlink_msg_battery_cells_status_get_voltage_cell_6(msg);
	battery_cells_status->accu_id = mavlink_msg_battery_cells_status_get_accu_id(msg);
#else
	memcpy(battery_cells_status, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BATTERY_CELLS_STATUS_LEN);
#endif
}
