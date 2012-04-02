// MESSAGE SKYE_CONTROLLER_OUTPUT PACKING

#define MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT 160

typedef struct __mavlink_skye_controller_output_t
{
 uint32_t time_usec; ///< Timestamp (since UNIX epoch or microseconds since system boot)
 float force_x; ///< Signal given from controller to actuation chain, 1 Newton
 float force_y; ///< Signal given from controller to actuation chain, 1 Newton
 float force_z; ///< Signal given from controller to actuation chain, 1 Newton
 float moment_x; ///< Signal given from controller to actuation chain, 1 Newtonmeter
 float moment_y; ///< Signal given from controller to actuation chain, 1 Newtonmeter
 float moment_z; ///< Signal given from controller to actuation chain, 1 Newtonmeter
} mavlink_skye_controller_output_t;

#define MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT_LEN 28
#define MAVLINK_MSG_ID_160_LEN 28



#define MAVLINK_MESSAGE_INFO_SKYE_CONTROLLER_OUTPUT { \
	"SKYE_CONTROLLER_OUTPUT", \
	7, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_skye_controller_output_t, time_usec) }, \
         { "force_x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_skye_controller_output_t, force_x) }, \
         { "force_y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_skye_controller_output_t, force_y) }, \
         { "force_z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_controller_output_t, force_z) }, \
         { "moment_x", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_controller_output_t, moment_x) }, \
         { "moment_y", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_skye_controller_output_t, moment_y) }, \
         { "moment_z", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_skye_controller_output_t, moment_z) }, \
         } \
}


/**
 * @brief Pack a skye_controller_output message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param force_x Signal given from controller to actuation chain, 1 Newton
 * @param force_y Signal given from controller to actuation chain, 1 Newton
 * @param force_z Signal given from controller to actuation chain, 1 Newton
 * @param moment_x Signal given from controller to actuation chain, 1 Newtonmeter
 * @param moment_y Signal given from controller to actuation chain, 1 Newtonmeter
 * @param moment_z Signal given from controller to actuation chain, 1 Newtonmeter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_controller_output_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_usec, float force_x, float force_y, float force_z, float moment_x, float moment_y, float moment_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[28];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, force_x);
	_mav_put_float(buf, 8, force_y);
	_mav_put_float(buf, 12, force_z);
	_mav_put_float(buf, 16, moment_x);
	_mav_put_float(buf, 20, moment_y);
	_mav_put_float(buf, 24, moment_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 28);
#else
	mavlink_skye_controller_output_t packet;
	packet.time_usec = time_usec;
	packet.force_x = force_x;
	packet.force_y = force_y;
	packet.force_z = force_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 28);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT;
	return mavlink_finalize_message(msg, system_id, component_id, 28, 103);
}

/**
 * @brief Pack a skye_controller_output message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param force_x Signal given from controller to actuation chain, 1 Newton
 * @param force_y Signal given from controller to actuation chain, 1 Newton
 * @param force_z Signal given from controller to actuation chain, 1 Newton
 * @param moment_x Signal given from controller to actuation chain, 1 Newtonmeter
 * @param moment_y Signal given from controller to actuation chain, 1 Newtonmeter
 * @param moment_z Signal given from controller to actuation chain, 1 Newtonmeter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_controller_output_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_usec,float force_x,float force_y,float force_z,float moment_x,float moment_y,float moment_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[28];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, force_x);
	_mav_put_float(buf, 8, force_y);
	_mav_put_float(buf, 12, force_z);
	_mav_put_float(buf, 16, moment_x);
	_mav_put_float(buf, 20, moment_y);
	_mav_put_float(buf, 24, moment_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 28);
#else
	mavlink_skye_controller_output_t packet;
	packet.time_usec = time_usec;
	packet.force_x = force_x;
	packet.force_y = force_y;
	packet.force_z = force_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 28);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 28, 103);
}

/**
 * @brief Encode a skye_controller_output struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_controller_output C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_controller_output_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_controller_output_t* skye_controller_output)
{
	return mavlink_msg_skye_controller_output_pack(system_id, component_id, msg, skye_controller_output->time_usec, skye_controller_output->force_x, skye_controller_output->force_y, skye_controller_output->force_z, skye_controller_output->moment_x, skye_controller_output->moment_y, skye_controller_output->moment_z);
}

/**
 * @brief Send a skye_controller_output message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (since UNIX epoch or microseconds since system boot)
 * @param force_x Signal given from controller to actuation chain, 1 Newton
 * @param force_y Signal given from controller to actuation chain, 1 Newton
 * @param force_z Signal given from controller to actuation chain, 1 Newton
 * @param moment_x Signal given from controller to actuation chain, 1 Newtonmeter
 * @param moment_y Signal given from controller to actuation chain, 1 Newtonmeter
 * @param moment_z Signal given from controller to actuation chain, 1 Newtonmeter
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_controller_output_send(mavlink_channel_t chan, uint32_t time_usec, float force_x, float force_y, float force_z, float moment_x, float moment_y, float moment_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[28];
	_mav_put_uint32_t(buf, 0, time_usec);
	_mav_put_float(buf, 4, force_x);
	_mav_put_float(buf, 8, force_y);
	_mav_put_float(buf, 12, force_z);
	_mav_put_float(buf, 16, moment_x);
	_mav_put_float(buf, 20, moment_y);
	_mav_put_float(buf, 24, moment_z);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT, buf, 28, 103);
#else
	mavlink_skye_controller_output_t packet;
	packet.time_usec = time_usec;
	packet.force_x = force_x;
	packet.force_y = force_y;
	packet.force_z = force_z;
	packet.moment_x = moment_x;
	packet.moment_y = moment_y;
	packet.moment_z = moment_z;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CONTROLLER_OUTPUT, (const char *)&packet, 28, 103);
#endif
}

#endif

// MESSAGE SKYE_CONTROLLER_OUTPUT UNPACKING


/**
 * @brief Get field time_usec from skye_controller_output message
 *
 * @return Timestamp (since UNIX epoch or microseconds since system boot)
 */
static inline uint32_t mavlink_msg_skye_controller_output_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field force_x from skye_controller_output message
 *
 * @return Signal given from controller to actuation chain, 1 Newton
 */
static inline float mavlink_msg_skye_controller_output_get_force_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field force_y from skye_controller_output message
 *
 * @return Signal given from controller to actuation chain, 1 Newton
 */
static inline float mavlink_msg_skye_controller_output_get_force_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field force_z from skye_controller_output message
 *
 * @return Signal given from controller to actuation chain, 1 Newton
 */
static inline float mavlink_msg_skye_controller_output_get_force_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field moment_x from skye_controller_output message
 *
 * @return Signal given from controller to actuation chain, 1 Newtonmeter
 */
static inline float mavlink_msg_skye_controller_output_get_moment_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field moment_y from skye_controller_output message
 *
 * @return Signal given from controller to actuation chain, 1 Newtonmeter
 */
static inline float mavlink_msg_skye_controller_output_get_moment_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field moment_z from skye_controller_output message
 *
 * @return Signal given from controller to actuation chain, 1 Newtonmeter
 */
static inline float mavlink_msg_skye_controller_output_get_moment_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Decode a skye_controller_output message into a struct
 *
 * @param msg The message to decode
 * @param skye_controller_output C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_controller_output_decode(const mavlink_message_t* msg, mavlink_skye_controller_output_t* skye_controller_output)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_controller_output->time_usec = mavlink_msg_skye_controller_output_get_time_usec(msg);
	skye_controller_output->force_x = mavlink_msg_skye_controller_output_get_force_x(msg);
	skye_controller_output->force_y = mavlink_msg_skye_controller_output_get_force_y(msg);
	skye_controller_output->force_z = mavlink_msg_skye_controller_output_get_force_z(msg);
	skye_controller_output->moment_x = mavlink_msg_skye_controller_output_get_moment_x(msg);
	skye_controller_output->moment_y = mavlink_msg_skye_controller_output_get_moment_y(msg);
	skye_controller_output->moment_z = mavlink_msg_skye_controller_output_get_moment_z(msg);
#else
	memcpy(skye_controller_output, _MAV_PAYLOAD(msg), 28);
#endif
}
