// MESSAGE MANUAL_8DOF_CONTROL PACKING

#define MAVLINK_MSG_ID_MANUAL_8DOF_CONTROL 107

typedef struct __mavlink_manual_8dof_control_t
{
 int16_t motor_1; ///< Motor 1 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_2; ///< Motor 2 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_3; ///< Motor 3 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_4; ///< Motor 4 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_5; ///< Motor 5 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_6; ///< Motor 6 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_7; ///< Motor 7 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 int16_t motor_8; ///< Motor 8 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 uint8_t target_system; ///< The system ID to be controlled
} mavlink_manual_8dof_control_t;

#define MAVLINK_MSG_ID_MANUAL_8DOF_CONTROL_LEN 17
#define MAVLINK_MSG_ID_107_LEN 17



#define MAVLINK_MESSAGE_INFO_MANUAL_8DOF_CONTROL { \
	"MANUAL_8DOF_CONTROL", \
	9, \
	{  { "motor_1", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_manual_8dof_control_t, motor_1) }, \
         { "motor_2", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_manual_8dof_control_t, motor_2) }, \
         { "motor_3", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_manual_8dof_control_t, motor_3) }, \
         { "motor_4", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_manual_8dof_control_t, motor_4) }, \
         { "motor_5", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_manual_8dof_control_t, motor_5) }, \
         { "motor_6", NULL, MAVLINK_TYPE_INT16_T, 0, 10, offsetof(mavlink_manual_8dof_control_t, motor_6) }, \
         { "motor_7", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_manual_8dof_control_t, motor_7) }, \
         { "motor_8", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_manual_8dof_control_t, motor_8) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_manual_8dof_control_t, target_system) }, \
         } \
}


/**
 * @brief Pack a manual_8dof_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system The system ID to be controlled
 * @param motor_1 Motor 1 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_2 Motor 2 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_3 Motor 3 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_4 Motor 4 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_5 Motor 5 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_6 Motor 6 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_7 Motor 7 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_8 Motor 8 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_manual_8dof_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, int16_t motor_1, int16_t motor_2, int16_t motor_3, int16_t motor_4, int16_t motor_5, int16_t motor_6, int16_t motor_7, int16_t motor_8)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[17];
	_mav_put_int16_t(buf, 0, motor_1);
	_mav_put_int16_t(buf, 2, motor_2);
	_mav_put_int16_t(buf, 4, motor_3);
	_mav_put_int16_t(buf, 6, motor_4);
	_mav_put_int16_t(buf, 8, motor_5);
	_mav_put_int16_t(buf, 10, motor_6);
	_mav_put_int16_t(buf, 12, motor_7);
	_mav_put_int16_t(buf, 14, motor_8);
	_mav_put_uint8_t(buf, 16, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 17);
#else
	mavlink_manual_8dof_control_t packet;
	packet.motor_1 = motor_1;
	packet.motor_2 = motor_2;
	packet.motor_3 = motor_3;
	packet.motor_4 = motor_4;
	packet.motor_5 = motor_5;
	packet.motor_6 = motor_6;
	packet.motor_7 = motor_7;
	packet.motor_8 = motor_8;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 17);
#endif

	msg->msgid = MAVLINK_MSG_ID_MANUAL_8DOF_CONTROL;
	return mavlink_finalize_message(msg, system_id, component_id, 17, 84);
}

/**
 * @brief Pack a manual_8dof_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system The system ID to be controlled
 * @param motor_1 Motor 1 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_2 Motor 2 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_3 Motor 3 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_4 Motor 4 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_5 Motor 5 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_6 Motor 6 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_7 Motor 7 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_8 Motor 8 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_manual_8dof_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,int16_t motor_1,int16_t motor_2,int16_t motor_3,int16_t motor_4,int16_t motor_5,int16_t motor_6,int16_t motor_7,int16_t motor_8)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[17];
	_mav_put_int16_t(buf, 0, motor_1);
	_mav_put_int16_t(buf, 2, motor_2);
	_mav_put_int16_t(buf, 4, motor_3);
	_mav_put_int16_t(buf, 6, motor_4);
	_mav_put_int16_t(buf, 8, motor_5);
	_mav_put_int16_t(buf, 10, motor_6);
	_mav_put_int16_t(buf, 12, motor_7);
	_mav_put_int16_t(buf, 14, motor_8);
	_mav_put_uint8_t(buf, 16, target_system);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 17);
#else
	mavlink_manual_8dof_control_t packet;
	packet.motor_1 = motor_1;
	packet.motor_2 = motor_2;
	packet.motor_3 = motor_3;
	packet.motor_4 = motor_4;
	packet.motor_5 = motor_5;
	packet.motor_6 = motor_6;
	packet.motor_7 = motor_7;
	packet.motor_8 = motor_8;
	packet.target_system = target_system;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 17);
#endif

	msg->msgid = MAVLINK_MSG_ID_MANUAL_8DOF_CONTROL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 17, 84);
}

/**
 * @brief Encode a manual_8dof_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param manual_8dof_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_manual_8dof_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_manual_8dof_control_t* manual_8dof_control)
{
	return mavlink_msg_manual_8dof_control_pack(system_id, component_id, msg, manual_8dof_control->target_system, manual_8dof_control->motor_1, manual_8dof_control->motor_2, manual_8dof_control->motor_3, manual_8dof_control->motor_4, manual_8dof_control->motor_5, manual_8dof_control->motor_6, manual_8dof_control->motor_7, manual_8dof_control->motor_8);
}

/**
 * @brief Send a manual_8dof_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system The system ID to be controlled
 * @param motor_1 Motor 1 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_2 Motor 2 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_3 Motor 3 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_4 Motor 4 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_5 Motor 5 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_6 Motor 6 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_7 Motor 7 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 * @param motor_8 Motor 8 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_manual_8dof_control_send(mavlink_channel_t chan, uint8_t target_system, int16_t motor_1, int16_t motor_2, int16_t motor_3, int16_t motor_4, int16_t motor_5, int16_t motor_6, int16_t motor_7, int16_t motor_8)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[17];
	_mav_put_int16_t(buf, 0, motor_1);
	_mav_put_int16_t(buf, 2, motor_2);
	_mav_put_int16_t(buf, 4, motor_3);
	_mav_put_int16_t(buf, 6, motor_4);
	_mav_put_int16_t(buf, 8, motor_5);
	_mav_put_int16_t(buf, 10, motor_6);
	_mav_put_int16_t(buf, 12, motor_7);
	_mav_put_int16_t(buf, 14, motor_8);
	_mav_put_uint8_t(buf, 16, target_system);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MANUAL_8DOF_CONTROL, buf, 17, 84);
#else
	mavlink_manual_8dof_control_t packet;
	packet.motor_1 = motor_1;
	packet.motor_2 = motor_2;
	packet.motor_3 = motor_3;
	packet.motor_4 = motor_4;
	packet.motor_5 = motor_5;
	packet.motor_6 = motor_6;
	packet.motor_7 = motor_7;
	packet.motor_8 = motor_8;
	packet.target_system = target_system;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MANUAL_8DOF_CONTROL, (const char *)&packet, 17, 84);
#endif
}

#endif

// MESSAGE MANUAL_8DOF_CONTROL UNPACKING


/**
 * @brief Get field target_system from manual_8dof_control message
 *
 * @return The system ID to be controlled
 */
static inline uint8_t mavlink_msg_manual_8dof_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field motor_1 from manual_8dof_control message
 *
 * @return Motor 1 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field motor_2 from manual_8dof_control message
 *
 * @return Motor 2 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field motor_3 from manual_8dof_control message
 *
 * @return Motor 3 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field motor_4 from manual_8dof_control message
 *
 * @return Motor 4 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Get field motor_5 from manual_8dof_control message
 *
 * @return Motor 5 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_5(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  8);
}

/**
 * @brief Get field motor_6 from manual_8dof_control message
 *
 * @return Motor 6 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_6(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  10);
}

/**
 * @brief Get field motor_7 from manual_8dof_control message
 *
 * @return Motor 7 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_7(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  12);
}

/**
 * @brief Get field motor_8 from manual_8dof_control message
 *
 * @return Motor 8 input, normalized to the range [-1000,1000]. A value of INT16_MAX indicates that this input is invalid.
 */
static inline int16_t mavlink_msg_manual_8dof_control_get_motor_8(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  14);
}

/**
 * @brief Decode a manual_8dof_control message into a struct
 *
 * @param msg The message to decode
 * @param manual_8dof_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_manual_8dof_control_decode(const mavlink_message_t* msg, mavlink_manual_8dof_control_t* manual_8dof_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	manual_8dof_control->motor_1 = mavlink_msg_manual_8dof_control_get_motor_1(msg);
	manual_8dof_control->motor_2 = mavlink_msg_manual_8dof_control_get_motor_2(msg);
	manual_8dof_control->motor_3 = mavlink_msg_manual_8dof_control_get_motor_3(msg);
	manual_8dof_control->motor_4 = mavlink_msg_manual_8dof_control_get_motor_4(msg);
	manual_8dof_control->motor_5 = mavlink_msg_manual_8dof_control_get_motor_5(msg);
	manual_8dof_control->motor_6 = mavlink_msg_manual_8dof_control_get_motor_6(msg);
	manual_8dof_control->motor_7 = mavlink_msg_manual_8dof_control_get_motor_7(msg);
	manual_8dof_control->motor_8 = mavlink_msg_manual_8dof_control_get_motor_8(msg);
	manual_8dof_control->target_system = mavlink_msg_manual_8dof_control_get_target_system(msg);
#else
	memcpy(manual_8dof_control, _MAV_PAYLOAD(msg), 17);
#endif
}
