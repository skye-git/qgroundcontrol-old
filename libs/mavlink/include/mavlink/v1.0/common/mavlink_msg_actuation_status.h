// MESSAGE ACTUATION_STATUS PACKING

#define MAVLINK_MSG_ID_ACTUATION_STATUS 145

typedef struct __mavlink_actuation_status_t
{
 uint8_t au_id; ///< a ID
 int8_t status; ///< -1: unknown, 0: detached:, 1: init, 2: homing, 3: ready, 4: disabled, 5: error
} mavlink_actuation_status_t;

#define MAVLINK_MSG_ID_ACTUATION_STATUS_LEN 2
#define MAVLINK_MSG_ID_145_LEN 2

#define MAVLINK_MSG_ID_ACTUATION_STATUS_CRC 228
#define MAVLINK_MSG_ID_145_CRC 228



#define MAVLINK_MESSAGE_INFO_ACTUATION_STATUS { \
	"ACTUATION_STATUS", \
	2, \
	{  { "au_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_actuation_status_t, au_id) }, \
         { "status", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_actuation_status_t, status) }, \
         } \
}


/**
 * @brief Pack a actuation_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param au_id a ID
 * @param status -1: unknown, 0: detached:, 1: init, 2: homing, 3: ready, 4: disabled, 5: error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t au_id, int8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, au_id);
	_mav_put_int8_t(buf, 1, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#else
	mavlink_actuation_status_t packet;
	packet.au_id = au_id;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN, MAVLINK_MSG_ID_ACTUATION_STATUS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif
}

/**
 * @brief Pack a actuation_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param au_id a ID
 * @param status -1: unknown, 0: detached:, 1: init, 2: homing, 3: ready, 4: disabled, 5: error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_actuation_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t au_id,int8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, au_id);
	_mav_put_int8_t(buf, 1, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#else
	mavlink_actuation_status_t packet;
	packet.au_id = au_id;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACTUATION_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN, MAVLINK_MSG_ID_ACTUATION_STATUS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif
}

/**
 * @brief Encode a actuation_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param actuation_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_actuation_status_t* actuation_status)
{
	return mavlink_msg_actuation_status_pack(system_id, component_id, msg, actuation_status->au_id, actuation_status->status);
}

/**
 * @brief Encode a actuation_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param actuation_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_actuation_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_actuation_status_t* actuation_status)
{
	return mavlink_msg_actuation_status_pack_chan(system_id, component_id, chan, msg, actuation_status->au_id, actuation_status->status);
}

/**
 * @brief Send a actuation_status message
 * @param chan MAVLink channel to send the message
 *
 * @param au_id a ID
 * @param status -1: unknown, 0: detached:, 1: init, 2: homing, 3: ready, 4: disabled, 5: error
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_actuation_status_send(mavlink_channel_t chan, uint8_t au_id, int8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACTUATION_STATUS_LEN];
	_mav_put_uint8_t(buf, 0, au_id);
	_mav_put_int8_t(buf, 1, status);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_STATUS, buf, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN, MAVLINK_MSG_ID_ACTUATION_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_STATUS, buf, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif
#else
	mavlink_actuation_status_t packet;
	packet.au_id = au_id;
	packet.status = status;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_STATUS, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN, MAVLINK_MSG_ID_ACTUATION_STATUS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACTUATION_STATUS, (const char *)&packet, MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif
#endif
}

#endif

// MESSAGE ACTUATION_STATUS UNPACKING


/**
 * @brief Get field au_id from actuation_status message
 *
 * @return a ID
 */
static inline uint8_t mavlink_msg_actuation_status_get_au_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field status from actuation_status message
 *
 * @return -1: unknown, 0: detached:, 1: init, 2: homing, 3: ready, 4: disabled, 5: error
 */
static inline int8_t mavlink_msg_actuation_status_get_status(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  1);
}

/**
 * @brief Decode a actuation_status message into a struct
 *
 * @param msg The message to decode
 * @param actuation_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_actuation_status_decode(const mavlink_message_t* msg, mavlink_actuation_status_t* actuation_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	actuation_status->au_id = mavlink_msg_actuation_status_get_au_id(msg);
	actuation_status->status = mavlink_msg_actuation_status_get_status(msg);
#else
	memcpy(actuation_status, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACTUATION_STATUS_LEN);
#endif
}
