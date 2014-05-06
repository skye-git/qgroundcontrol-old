// MESSAGE SKYE_FEEDBACK_COMBINED PACKING

#define MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED 131

typedef struct __mavlink_skye_feedback_combined_t
{
 uint64_t timestamp; ///< Onboard time
 float omega_raw[3]; ///< Raw angular velocity. IMU frame. rad/sec
 float accel_raw[3]; ///< Raw acceleration. IMU frame. m/s2
 float alpha_ekf[3]; ///< Filtered angular acceleration. IMU frame. rad/sec
 float omega_ekf[3]; ///< Filtered angular velocity. IMU frame. rad/sec
 float quat_ekf[4]; ///< Filtered Orientation. IMU frame. rad/sec
 float thrust[6]; ///< Thrust estimate of actuation units in Newton
 float angle[6]; ///< Orientation readout of actuation units in Degree
} mavlink_skye_feedback_combined_t;

#define MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN 120
#define MAVLINK_MSG_ID_131_LEN 120

#define MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC 78
#define MAVLINK_MSG_ID_131_CRC 78

#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_OMEGA_RAW_LEN 3
#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_ACCEL_RAW_LEN 3
#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_ALPHA_EKF_LEN 3
#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_OMEGA_EKF_LEN 3
#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_QUAT_EKF_LEN 4
#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_THRUST_LEN 6
#define MAVLINK_MSG_SKYE_FEEDBACK_COMBINED_FIELD_ANGLE_LEN 6

#define MAVLINK_MESSAGE_INFO_SKYE_FEEDBACK_COMBINED { \
	"SKYE_FEEDBACK_COMBINED", \
	8, \
	{  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_skye_feedback_combined_t, timestamp) }, \
         { "omega_raw", NULL, MAVLINK_TYPE_FLOAT, 3, 8, offsetof(mavlink_skye_feedback_combined_t, omega_raw) }, \
         { "accel_raw", NULL, MAVLINK_TYPE_FLOAT, 3, 20, offsetof(mavlink_skye_feedback_combined_t, accel_raw) }, \
         { "alpha_ekf", NULL, MAVLINK_TYPE_FLOAT, 3, 32, offsetof(mavlink_skye_feedback_combined_t, alpha_ekf) }, \
         { "omega_ekf", NULL, MAVLINK_TYPE_FLOAT, 3, 44, offsetof(mavlink_skye_feedback_combined_t, omega_ekf) }, \
         { "quat_ekf", NULL, MAVLINK_TYPE_FLOAT, 4, 56, offsetof(mavlink_skye_feedback_combined_t, quat_ekf) }, \
         { "thrust", NULL, MAVLINK_TYPE_FLOAT, 6, 72, offsetof(mavlink_skye_feedback_combined_t, thrust) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 6, 96, offsetof(mavlink_skye_feedback_combined_t, angle) }, \
         } \
}


/**
 * @brief Pack a skye_feedback_combined message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp Onboard time
 * @param omega_raw Raw angular velocity. IMU frame. rad/sec
 * @param accel_raw Raw acceleration. IMU frame. m/s2
 * @param alpha_ekf Filtered angular acceleration. IMU frame. rad/sec
 * @param omega_ekf Filtered angular velocity. IMU frame. rad/sec
 * @param quat_ekf Filtered Orientation. IMU frame. rad/sec
 * @param thrust Thrust estimate of actuation units in Newton
 * @param angle Orientation readout of actuation units in Degree
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t timestamp, const float *omega_raw, const float *accel_raw, const float *alpha_ekf, const float *omega_ekf, const float *quat_ekf, const float *thrust, const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, omega_raw, 3);
	_mav_put_float_array(buf, 20, accel_raw, 3);
	_mav_put_float_array(buf, 32, alpha_ekf, 3);
	_mav_put_float_array(buf, 44, omega_ekf, 3);
	_mav_put_float_array(buf, 56, quat_ekf, 4);
	_mav_put_float_array(buf, 72, thrust, 6);
	_mav_put_float_array(buf, 96, angle, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#else
	mavlink_skye_feedback_combined_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.omega_raw, omega_raw, sizeof(float)*3);
	mav_array_memcpy(packet.accel_raw, accel_raw, sizeof(float)*3);
	mav_array_memcpy(packet.alpha_ekf, alpha_ekf, sizeof(float)*3);
	mav_array_memcpy(packet.omega_ekf, omega_ekf, sizeof(float)*3);
	mav_array_memcpy(packet.quat_ekf, quat_ekf, sizeof(float)*4);
	mav_array_memcpy(packet.thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet.angle, angle, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
}

/**
 * @brief Pack a skye_feedback_combined message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp Onboard time
 * @param omega_raw Raw angular velocity. IMU frame. rad/sec
 * @param accel_raw Raw acceleration. IMU frame. m/s2
 * @param alpha_ekf Filtered angular acceleration. IMU frame. rad/sec
 * @param omega_ekf Filtered angular velocity. IMU frame. rad/sec
 * @param quat_ekf Filtered Orientation. IMU frame. rad/sec
 * @param thrust Thrust estimate of actuation units in Newton
 * @param angle Orientation readout of actuation units in Degree
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t timestamp,const float *omega_raw,const float *accel_raw,const float *alpha_ekf,const float *omega_ekf,const float *quat_ekf,const float *thrust,const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, omega_raw, 3);
	_mav_put_float_array(buf, 20, accel_raw, 3);
	_mav_put_float_array(buf, 32, alpha_ekf, 3);
	_mav_put_float_array(buf, 44, omega_ekf, 3);
	_mav_put_float_array(buf, 56, quat_ekf, 4);
	_mav_put_float_array(buf, 72, thrust, 6);
	_mav_put_float_array(buf, 96, angle, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#else
	mavlink_skye_feedback_combined_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.omega_raw, omega_raw, sizeof(float)*3);
	mav_array_memcpy(packet.accel_raw, accel_raw, sizeof(float)*3);
	mav_array_memcpy(packet.alpha_ekf, alpha_ekf, sizeof(float)*3);
	mav_array_memcpy(packet.omega_ekf, omega_ekf, sizeof(float)*3);
	mav_array_memcpy(packet.quat_ekf, quat_ekf, sizeof(float)*4);
	mav_array_memcpy(packet.thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet.angle, angle, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
}

/**
 * @brief Encode a skye_feedback_combined struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_feedback_combined C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_feedback_combined_t* skye_feedback_combined)
{
	return mavlink_msg_skye_feedback_combined_pack(system_id, component_id, msg, skye_feedback_combined->timestamp, skye_feedback_combined->omega_raw, skye_feedback_combined->accel_raw, skye_feedback_combined->alpha_ekf, skye_feedback_combined->omega_ekf, skye_feedback_combined->quat_ekf, skye_feedback_combined->thrust, skye_feedback_combined->angle);
}

/**
 * @brief Encode a skye_feedback_combined struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param skye_feedback_combined C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_skye_feedback_combined_t* skye_feedback_combined)
{
	return mavlink_msg_skye_feedback_combined_pack_chan(system_id, component_id, chan, msg, skye_feedback_combined->timestamp, skye_feedback_combined->omega_raw, skye_feedback_combined->accel_raw, skye_feedback_combined->alpha_ekf, skye_feedback_combined->omega_ekf, skye_feedback_combined->quat_ekf, skye_feedback_combined->thrust, skye_feedback_combined->angle);
}

/**
 * @brief Send a skye_feedback_combined message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp Onboard time
 * @param omega_raw Raw angular velocity. IMU frame. rad/sec
 * @param accel_raw Raw acceleration. IMU frame. m/s2
 * @param alpha_ekf Filtered angular acceleration. IMU frame. rad/sec
 * @param omega_ekf Filtered angular velocity. IMU frame. rad/sec
 * @param quat_ekf Filtered Orientation. IMU frame. rad/sec
 * @param thrust Thrust estimate of actuation units in Newton
 * @param angle Orientation readout of actuation units in Degree
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_feedback_combined_send(mavlink_channel_t chan, uint64_t timestamp, const float *omega_raw, const float *accel_raw, const float *alpha_ekf, const float *omega_ekf, const float *quat_ekf, const float *thrust, const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN];
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, omega_raw, 3);
	_mav_put_float_array(buf, 20, accel_raw, 3);
	_mav_put_float_array(buf, 32, alpha_ekf, 3);
	_mav_put_float_array(buf, 44, omega_ekf, 3);
	_mav_put_float_array(buf, 56, quat_ekf, 4);
	_mav_put_float_array(buf, 72, thrust, 6);
	_mav_put_float_array(buf, 96, angle, 6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, buf, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, buf, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
#else
	mavlink_skye_feedback_combined_t packet;
	packet.timestamp = timestamp;
	mav_array_memcpy(packet.omega_raw, omega_raw, sizeof(float)*3);
	mav_array_memcpy(packet.accel_raw, accel_raw, sizeof(float)*3);
	mav_array_memcpy(packet.alpha_ekf, alpha_ekf, sizeof(float)*3);
	mav_array_memcpy(packet.omega_ekf, omega_ekf, sizeof(float)*3);
	mav_array_memcpy(packet.quat_ekf, quat_ekf, sizeof(float)*4);
	mav_array_memcpy(packet.thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet.angle, angle, sizeof(float)*6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, (const char *)&packet, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, (const char *)&packet, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_skye_feedback_combined_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, const float *omega_raw, const float *accel_raw, const float *alpha_ekf, const float *omega_ekf, const float *quat_ekf, const float *thrust, const float *angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, timestamp);
	_mav_put_float_array(buf, 8, omega_raw, 3);
	_mav_put_float_array(buf, 20, accel_raw, 3);
	_mav_put_float_array(buf, 32, alpha_ekf, 3);
	_mav_put_float_array(buf, 44, omega_ekf, 3);
	_mav_put_float_array(buf, 56, quat_ekf, 4);
	_mav_put_float_array(buf, 72, thrust, 6);
	_mav_put_float_array(buf, 96, angle, 6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, buf, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, buf, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
#else
	mavlink_skye_feedback_combined_t *packet = (mavlink_skye_feedback_combined_t *)msgbuf;
	packet->timestamp = timestamp;
	mav_array_memcpy(packet->omega_raw, omega_raw, sizeof(float)*3);
	mav_array_memcpy(packet->accel_raw, accel_raw, sizeof(float)*3);
	mav_array_memcpy(packet->alpha_ekf, alpha_ekf, sizeof(float)*3);
	mav_array_memcpy(packet->omega_ekf, omega_ekf, sizeof(float)*3);
	mav_array_memcpy(packet->quat_ekf, quat_ekf, sizeof(float)*4);
	mav_array_memcpy(packet->thrust, thrust, sizeof(float)*6);
	mav_array_memcpy(packet->angle, angle, sizeof(float)*6);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, (const char *)packet, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED, (const char *)packet, MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SKYE_FEEDBACK_COMBINED UNPACKING


/**
 * @brief Get field timestamp from skye_feedback_combined message
 *
 * @return Onboard time
 */
static inline uint64_t mavlink_msg_skye_feedback_combined_get_timestamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field omega_raw from skye_feedback_combined message
 *
 * @return Raw angular velocity. IMU frame. rad/sec
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_omega_raw(const mavlink_message_t* msg, float *omega_raw)
{
	return _MAV_RETURN_float_array(msg, omega_raw, 3,  8);
}

/**
 * @brief Get field accel_raw from skye_feedback_combined message
 *
 * @return Raw acceleration. IMU frame. m/s2
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_accel_raw(const mavlink_message_t* msg, float *accel_raw)
{
	return _MAV_RETURN_float_array(msg, accel_raw, 3,  20);
}

/**
 * @brief Get field alpha_ekf from skye_feedback_combined message
 *
 * @return Filtered angular acceleration. IMU frame. rad/sec
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_alpha_ekf(const mavlink_message_t* msg, float *alpha_ekf)
{
	return _MAV_RETURN_float_array(msg, alpha_ekf, 3,  32);
}

/**
 * @brief Get field omega_ekf from skye_feedback_combined message
 *
 * @return Filtered angular velocity. IMU frame. rad/sec
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_omega_ekf(const mavlink_message_t* msg, float *omega_ekf)
{
	return _MAV_RETURN_float_array(msg, omega_ekf, 3,  44);
}

/**
 * @brief Get field quat_ekf from skye_feedback_combined message
 *
 * @return Filtered Orientation. IMU frame. rad/sec
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_quat_ekf(const mavlink_message_t* msg, float *quat_ekf)
{
	return _MAV_RETURN_float_array(msg, quat_ekf, 4,  56);
}

/**
 * @brief Get field thrust from skye_feedback_combined message
 *
 * @return Thrust estimate of actuation units in Newton
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_thrust(const mavlink_message_t* msg, float *thrust)
{
	return _MAV_RETURN_float_array(msg, thrust, 6,  72);
}

/**
 * @brief Get field angle from skye_feedback_combined message
 *
 * @return Orientation readout of actuation units in Degree
 */
static inline uint16_t mavlink_msg_skye_feedback_combined_get_angle(const mavlink_message_t* msg, float *angle)
{
	return _MAV_RETURN_float_array(msg, angle, 6,  96);
}

/**
 * @brief Decode a skye_feedback_combined message into a struct
 *
 * @param msg The message to decode
 * @param skye_feedback_combined C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_feedback_combined_decode(const mavlink_message_t* msg, mavlink_skye_feedback_combined_t* skye_feedback_combined)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_feedback_combined->timestamp = mavlink_msg_skye_feedback_combined_get_timestamp(msg);
	mavlink_msg_skye_feedback_combined_get_omega_raw(msg, skye_feedback_combined->omega_raw);
	mavlink_msg_skye_feedback_combined_get_accel_raw(msg, skye_feedback_combined->accel_raw);
	mavlink_msg_skye_feedback_combined_get_alpha_ekf(msg, skye_feedback_combined->alpha_ekf);
	mavlink_msg_skye_feedback_combined_get_omega_ekf(msg, skye_feedback_combined->omega_ekf);
	mavlink_msg_skye_feedback_combined_get_quat_ekf(msg, skye_feedback_combined->quat_ekf);
	mavlink_msg_skye_feedback_combined_get_thrust(msg, skye_feedback_combined->thrust);
	mavlink_msg_skye_feedback_combined_get_angle(msg, skye_feedback_combined->angle);
#else
	memcpy(skye_feedback_combined, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SKYE_FEEDBACK_COMBINED_LEN);
#endif
}
