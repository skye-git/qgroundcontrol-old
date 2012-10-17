// MESSAGE MANUAL_6DOF_CONTROL PACKING

#define MAVLINK_MSG_ID_MANUAL_6DOF_CONTROL 106

typedef struct __mavlink_manual_6dof_control_t
{
 int16_t x; ///< X-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to forward(1000)-backward(-1000) movement on a 3D mouse.
 int16_t y; ///< Y-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to left(1000)-right(-1000) movement on a 3D mouse
 int16_t z; ///< Z-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to up(1000)-down(-1000) movement on a 3D mouse
 int16_t roll; ///< X-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to roll right(1000)-left(-1000) twisting on a 3D mouse
 int16_t pitch; ///< Y-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to pitch down(1000)-up(-1000) twisting on a 3D mouse
 int16_t yaw; ///< Z-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to yaw left(1000)-right(-1000) twisting on a 3D mouse
 uint8_t target_system; ///< The system ID to be controlled
} mavlink_manual_6dof_control_t;

#define MAVLINK_MSG_ID_MANUAL_6DOF_CONTROL_LEN 13
#define MAVLINK_MSG_ID_106_LEN 13



#define MAVLINK_MESSAGE_INFO_MANUAL_6DOF_CONTROL { \
	"MANUAL_6DOF_CONTROL", \
	7, \
	{  { "x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_manual_6dof_control_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_manual_6dof_control_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_manual_6dof_control_t, z) }, \
         { "roll", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_manual_6dof_control_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_manual_6dof_control_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_INT16_T, 0, 10, offsetof(mavlink_manual_6dof_control_t, yaw) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_manual_6dof_control_t, target_system) }, \
         } \
}


/**
 * @brief Pack a manual_6dof_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system The system ID to be controlled
 * @param x X-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to forward(1000)-backward(-1000) movement on a 3D mouse.
 * @param y Y-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to left(1000)-right(-1000) movement on a 3D mouse
 * @param z Z-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to up(1000)-down(-1000) movement on a 3D mouse
 * @param roll X-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to roll right(1000)-left(-1000) twisting on a 3D mouse
 * @param pitch Y-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to pitch down(1000)-up(-1000) twisting on a 3D mouse
 * @param yaw Z-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to yaw left(1000)-right(-1000) twisting on a 3D mouse
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_manual_6dof_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, int16_t x, int16_t y, int16_t z, int16_t roll, int16_t pitch, int16_t yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_int16_t(buf, 0, x);
	_mav_put_int16_t(buf, 2, y);
	_mav_put_int16_t(buf, 4, z);
	_mav_put_int16_t(buf, 6, roll);
	_mav_put_int16_t(buf, 8, pitch);
	_mav_put_int16_t(buf, 10, yaw);
	_mav_put_uint8_t(buf, 12, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 13);
#else
	mavlink_manual_6dof_control_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 13);
#endif

	msg->msgid = MAVLINK_MSG_ID_MANUAL_6DOF_CONTROL;
	return mavlink_finalize_message(msg, system_id, component_id, 13, 22);
}

/**
 * @brief Pack a manual_6dof_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system The system ID to be controlled
 * @param x X-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to forward(1000)-backward(-1000) movement on a 3D mouse.
 * @param y Y-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to left(1000)-right(-1000) movement on a 3D mouse
 * @param z Z-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to up(1000)-down(-1000) movement on a 3D mouse
 * @param roll X-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to roll right(1000)-left(-1000) twisting on a 3D mouse
 * @param pitch Y-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to pitch down(1000)-up(-1000) twisting on a 3D mouse
 * @param yaw Z-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to yaw left(1000)-right(-1000) twisting on a 3D mouse
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_manual_6dof_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,int16_t x,int16_t y,int16_t z,int16_t roll,int16_t pitch,int16_t yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_int16_t(buf, 0, x);
	_mav_put_int16_t(buf, 2, y);
	_mav_put_int16_t(buf, 4, z);
	_mav_put_int16_t(buf, 6, roll);
	_mav_put_int16_t(buf, 8, pitch);
	_mav_put_int16_t(buf, 10, yaw);
	_mav_put_uint8_t(buf, 12, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 13);
#else
	mavlink_manual_6dof_control_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 13);
#endif

	msg->msgid = MAVLINK_MSG_ID_MANUAL_6DOF_CONTROL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 13, 22);
}

/**
 * @brief Encode a manual_6dof_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param manual_6dof_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_manual_6dof_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_manual_6dof_control_t* manual_6dof_control)
{
	return mavlink_msg_manual_6dof_control_pack(system_id, component_id, msg, manual_6dof_control->target_system, manual_6dof_control->x, manual_6dof_control->y, manual_6dof_control->z, manual_6dof_control->roll, manual_6dof_control->pitch, manual_6dof_control->yaw);
}

/**
 * @brief Send a manual_6dof_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system The system ID to be controlled
 * @param x X-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to forward(1000)-backward(-1000) movement on a 3D mouse.
 * @param y Y-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to left(1000)-right(-1000) movement on a 3D mouse
 * @param z Z-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to up(1000)-down(-1000) movement on a 3D mouse
 * @param roll X-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to roll right(1000)-left(-1000) twisting on a 3D mouse
 * @param pitch Y-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to pitch down(1000)-up(-1000) twisting on a 3D mouse
 * @param yaw Z-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to yaw left(1000)-right(-1000) twisting on a 3D mouse
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_manual_6dof_control_send(mavlink_channel_t chan, uint8_t target_system, int16_t x, int16_t y, int16_t z, int16_t roll, int16_t pitch, int16_t yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[13];
	_mav_put_int16_t(buf, 0, x);
	_mav_put_int16_t(buf, 2, y);
	_mav_put_int16_t(buf, 4, z);
	_mav_put_int16_t(buf, 6, roll);
	_mav_put_int16_t(buf, 8, pitch);
	_mav_put_int16_t(buf, 10, yaw);
	_mav_put_uint8_t(buf, 12, target_system);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MANUAL_6DOF_CONTROL, buf, 13, 22);
#else
	mavlink_manual_6dof_control_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MANUAL_6DOF_CONTROL, (const char *)&packet, 13, 22);
#endif
}

#endif

// MESSAGE MANUAL_6DOF_CONTROL UNPACKING


/**
 * @brief Get field target_system from manual_6dof_control message
 *
 * @return The system ID to be controlled
 */
static inline uint8_t mavlink_msg_manual_6dof_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field x from manual_6dof_control message
 *
 * @return X-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to forward(1000)-backward(-1000) movement on a 3D mouse.
 */
static inline int16_t mavlink_msg_manual_6dof_control_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field y from manual_6dof_control message
 *
 * @return Y-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to left(1000)-right(-1000) movement on a 3D mouse
 */
static inline int16_t mavlink_msg_manual_6dof_control_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field z from manual_6dof_control message
 *
 * @return Z-axis, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to up(1000)-down(-1000) movement on a 3D mouse
 */
static inline int16_t mavlink_msg_manual_6dof_control_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field roll from manual_6dof_control message
 *
 * @return X-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to roll right(1000)-left(-1000) twisting on a 3D mouse
 */
static inline int16_t mavlink_msg_manual_6dof_control_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Get field pitch from manual_6dof_control message
 *
 * @return Y-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to pitch down(1000)-up(-1000) twisting on a 3D mouse
 */
static inline int16_t mavlink_msg_manual_6dof_control_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  8);
}

/**
 * @brief Get field yaw from manual_6dof_control message
 *
 * @return Z-axis rotation, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to yaw left(1000)-right(-1000) twisting on a 3D mouse
 */
static inline int16_t mavlink_msg_manual_6dof_control_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  10);
}

/**
 * @brief Decode a manual_6dof_control message into a struct
 *
 * @param msg The message to decode
 * @param manual_6dof_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_manual_6dof_control_decode(const mavlink_message_t* msg, mavlink_manual_6dof_control_t* manual_6dof_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	manual_6dof_control->x = mavlink_msg_manual_6dof_control_get_x(msg);
	manual_6dof_control->y = mavlink_msg_manual_6dof_control_get_y(msg);
	manual_6dof_control->z = mavlink_msg_manual_6dof_control_get_z(msg);
	manual_6dof_control->roll = mavlink_msg_manual_6dof_control_get_roll(msg);
	manual_6dof_control->pitch = mavlink_msg_manual_6dof_control_get_pitch(msg);
	manual_6dof_control->yaw = mavlink_msg_manual_6dof_control_get_yaw(msg);
	manual_6dof_control->target_system = mavlink_msg_manual_6dof_control_get_target_system(msg);
#else
	memcpy(manual_6dof_control, _MAV_PAYLOAD(msg), 13);
#endif
}
