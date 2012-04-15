// MESSAGE SKYE_SCALED_PRESSURE PACKING

#define MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE 157

typedef struct __mavlink_skye_scaled_pressure_t
{
 uint32_t time_boot_ms; ///< Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 float press_abs1; ///< Absolute pressure (hectopascal)
 float press_diff11; ///< Differential pressure 1 (hectopascal)
 float press_diff12; ///< Differential pressure 1 (hectopascal)
 float press_diff13; ///< Differential pressure 1 (hectopascal)
 float press_abs2; ///< Absolute pressure (hectopascal)
 float press_diff21; ///< Differential pressure 1 (hectopascal)
 float press_diff22; ///< Differential pressure 1 (hectopascal)
 float press_diff23; ///< Differential pressure 1 (hectopascal)
 float press_abs3; ///< Absolute pressure (hectopascal)
 float press_diff31; ///< Differential pressure 1 (hectopascal)
 float press_diff32; ///< Differential pressure 1 (hectopascal)
 float press_diff33; ///< Differential pressure 1 (hectopascal)
 float press_abs4; ///< Absolute pressure (hectopascal)
 float press_diff41; ///< Differential pressure 1 (hectopascal)
 float press_diff42; ///< Differential pressure 1 (hectopascal)
 float press_diff43; ///< Differential pressure 1 (hectopascal)
 int16_t temperature; ///< Temperature measurement (0.01 degrees celsius)
} mavlink_skye_scaled_pressure_t;

#define MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE_LEN 70
#define MAVLINK_MSG_ID_157_LEN 70



#define MAVLINK_MESSAGE_INFO_SKYE_SCALED_PRESSURE { \
	"SKYE_SCALED_PRESSURE", \
	18, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_skye_scaled_pressure_t, time_boot_ms) }, \
         { "press_abs1", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_skye_scaled_pressure_t, press_abs1) }, \
         { "press_diff11", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_skye_scaled_pressure_t, press_diff11) }, \
         { "press_diff12", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_scaled_pressure_t, press_diff12) }, \
         { "press_diff13", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_scaled_pressure_t, press_diff13) }, \
         { "press_abs2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_skye_scaled_pressure_t, press_abs2) }, \
         { "press_diff21", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_skye_scaled_pressure_t, press_diff21) }, \
         { "press_diff22", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_skye_scaled_pressure_t, press_diff22) }, \
         { "press_diff23", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_skye_scaled_pressure_t, press_diff23) }, \
         { "press_abs3", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_skye_scaled_pressure_t, press_abs3) }, \
         { "press_diff31", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_skye_scaled_pressure_t, press_diff31) }, \
         { "press_diff32", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_skye_scaled_pressure_t, press_diff32) }, \
         { "press_diff33", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_skye_scaled_pressure_t, press_diff33) }, \
         { "press_abs4", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_skye_scaled_pressure_t, press_abs4) }, \
         { "press_diff41", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_skye_scaled_pressure_t, press_diff41) }, \
         { "press_diff42", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_skye_scaled_pressure_t, press_diff42) }, \
         { "press_diff43", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_skye_scaled_pressure_t, press_diff43) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 68, offsetof(mavlink_skye_scaled_pressure_t, temperature) }, \
         } \
}


/**
 * @brief Pack a skye_scaled_pressure message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param press_abs1 Absolute pressure (hectopascal)
 * @param press_diff11 Differential pressure 1 (hectopascal)
 * @param press_diff12 Differential pressure 1 (hectopascal)
 * @param press_diff13 Differential pressure 1 (hectopascal)
 * @param press_abs2 Absolute pressure (hectopascal)
 * @param press_diff21 Differential pressure 1 (hectopascal)
 * @param press_diff22 Differential pressure 1 (hectopascal)
 * @param press_diff23 Differential pressure 1 (hectopascal)
 * @param press_abs3 Absolute pressure (hectopascal)
 * @param press_diff31 Differential pressure 1 (hectopascal)
 * @param press_diff32 Differential pressure 1 (hectopascal)
 * @param press_diff33 Differential pressure 1 (hectopascal)
 * @param press_abs4 Absolute pressure (hectopascal)
 * @param press_diff41 Differential pressure 1 (hectopascal)
 * @param press_diff42 Differential pressure 1 (hectopascal)
 * @param press_diff43 Differential pressure 1 (hectopascal)
 * @param temperature Temperature measurement (0.01 degrees celsius)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_scaled_pressure_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, float press_abs1, float press_diff11, float press_diff12, float press_diff13, float press_abs2, float press_diff21, float press_diff22, float press_diff23, float press_abs3, float press_diff31, float press_diff32, float press_diff33, float press_abs4, float press_diff41, float press_diff42, float press_diff43, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[70];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_float(buf, 4, press_abs1);
	_mav_put_float(buf, 8, press_diff11);
	_mav_put_float(buf, 12, press_diff12);
	_mav_put_float(buf, 16, press_diff13);
	_mav_put_float(buf, 20, press_abs2);
	_mav_put_float(buf, 24, press_diff21);
	_mav_put_float(buf, 28, press_diff22);
	_mav_put_float(buf, 32, press_diff23);
	_mav_put_float(buf, 36, press_abs3);
	_mav_put_float(buf, 40, press_diff31);
	_mav_put_float(buf, 44, press_diff32);
	_mav_put_float(buf, 48, press_diff33);
	_mav_put_float(buf, 52, press_abs4);
	_mav_put_float(buf, 56, press_diff41);
	_mav_put_float(buf, 60, press_diff42);
	_mav_put_float(buf, 64, press_diff43);
	_mav_put_int16_t(buf, 68, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 70);
#else
	mavlink_skye_scaled_pressure_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.press_abs1 = press_abs1;
	packet.press_diff11 = press_diff11;
	packet.press_diff12 = press_diff12;
	packet.press_diff13 = press_diff13;
	packet.press_abs2 = press_abs2;
	packet.press_diff21 = press_diff21;
	packet.press_diff22 = press_diff22;
	packet.press_diff23 = press_diff23;
	packet.press_abs3 = press_abs3;
	packet.press_diff31 = press_diff31;
	packet.press_diff32 = press_diff32;
	packet.press_diff33 = press_diff33;
	packet.press_abs4 = press_abs4;
	packet.press_diff41 = press_diff41;
	packet.press_diff42 = press_diff42;
	packet.press_diff43 = press_diff43;
	packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 70);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE;
	return mavlink_finalize_message(msg, system_id, component_id, 70, 243);
}

/**
 * @brief Pack a skye_scaled_pressure message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param press_abs1 Absolute pressure (hectopascal)
 * @param press_diff11 Differential pressure 1 (hectopascal)
 * @param press_diff12 Differential pressure 1 (hectopascal)
 * @param press_diff13 Differential pressure 1 (hectopascal)
 * @param press_abs2 Absolute pressure (hectopascal)
 * @param press_diff21 Differential pressure 1 (hectopascal)
 * @param press_diff22 Differential pressure 1 (hectopascal)
 * @param press_diff23 Differential pressure 1 (hectopascal)
 * @param press_abs3 Absolute pressure (hectopascal)
 * @param press_diff31 Differential pressure 1 (hectopascal)
 * @param press_diff32 Differential pressure 1 (hectopascal)
 * @param press_diff33 Differential pressure 1 (hectopascal)
 * @param press_abs4 Absolute pressure (hectopascal)
 * @param press_diff41 Differential pressure 1 (hectopascal)
 * @param press_diff42 Differential pressure 1 (hectopascal)
 * @param press_diff43 Differential pressure 1 (hectopascal)
 * @param temperature Temperature measurement (0.01 degrees celsius)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_scaled_pressure_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,float press_abs1,float press_diff11,float press_diff12,float press_diff13,float press_abs2,float press_diff21,float press_diff22,float press_diff23,float press_abs3,float press_diff31,float press_diff32,float press_diff33,float press_abs4,float press_diff41,float press_diff42,float press_diff43,int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[70];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_float(buf, 4, press_abs1);
	_mav_put_float(buf, 8, press_diff11);
	_mav_put_float(buf, 12, press_diff12);
	_mav_put_float(buf, 16, press_diff13);
	_mav_put_float(buf, 20, press_abs2);
	_mav_put_float(buf, 24, press_diff21);
	_mav_put_float(buf, 28, press_diff22);
	_mav_put_float(buf, 32, press_diff23);
	_mav_put_float(buf, 36, press_abs3);
	_mav_put_float(buf, 40, press_diff31);
	_mav_put_float(buf, 44, press_diff32);
	_mav_put_float(buf, 48, press_diff33);
	_mav_put_float(buf, 52, press_abs4);
	_mav_put_float(buf, 56, press_diff41);
	_mav_put_float(buf, 60, press_diff42);
	_mav_put_float(buf, 64, press_diff43);
	_mav_put_int16_t(buf, 68, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 70);
#else
	mavlink_skye_scaled_pressure_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.press_abs1 = press_abs1;
	packet.press_diff11 = press_diff11;
	packet.press_diff12 = press_diff12;
	packet.press_diff13 = press_diff13;
	packet.press_abs2 = press_abs2;
	packet.press_diff21 = press_diff21;
	packet.press_diff22 = press_diff22;
	packet.press_diff23 = press_diff23;
	packet.press_abs3 = press_abs3;
	packet.press_diff31 = press_diff31;
	packet.press_diff32 = press_diff32;
	packet.press_diff33 = press_diff33;
	packet.press_abs4 = press_abs4;
	packet.press_diff41 = press_diff41;
	packet.press_diff42 = press_diff42;
	packet.press_diff43 = press_diff43;
	packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 70);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 70, 243);
}

/**
 * @brief Encode a skye_scaled_pressure struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_scaled_pressure C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_scaled_pressure_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_scaled_pressure_t* skye_scaled_pressure)
{
	return mavlink_msg_skye_scaled_pressure_pack(system_id, component_id, msg, skye_scaled_pressure->time_boot_ms, skye_scaled_pressure->press_abs1, skye_scaled_pressure->press_diff11, skye_scaled_pressure->press_diff12, skye_scaled_pressure->press_diff13, skye_scaled_pressure->press_abs2, skye_scaled_pressure->press_diff21, skye_scaled_pressure->press_diff22, skye_scaled_pressure->press_diff23, skye_scaled_pressure->press_abs3, skye_scaled_pressure->press_diff31, skye_scaled_pressure->press_diff32, skye_scaled_pressure->press_diff33, skye_scaled_pressure->press_abs4, skye_scaled_pressure->press_diff41, skye_scaled_pressure->press_diff42, skye_scaled_pressure->press_diff43, skye_scaled_pressure->temperature);
}

/**
 * @brief Send a skye_scaled_pressure message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param press_abs1 Absolute pressure (hectopascal)
 * @param press_diff11 Differential pressure 1 (hectopascal)
 * @param press_diff12 Differential pressure 1 (hectopascal)
 * @param press_diff13 Differential pressure 1 (hectopascal)
 * @param press_abs2 Absolute pressure (hectopascal)
 * @param press_diff21 Differential pressure 1 (hectopascal)
 * @param press_diff22 Differential pressure 1 (hectopascal)
 * @param press_diff23 Differential pressure 1 (hectopascal)
 * @param press_abs3 Absolute pressure (hectopascal)
 * @param press_diff31 Differential pressure 1 (hectopascal)
 * @param press_diff32 Differential pressure 1 (hectopascal)
 * @param press_diff33 Differential pressure 1 (hectopascal)
 * @param press_abs4 Absolute pressure (hectopascal)
 * @param press_diff41 Differential pressure 1 (hectopascal)
 * @param press_diff42 Differential pressure 1 (hectopascal)
 * @param press_diff43 Differential pressure 1 (hectopascal)
 * @param temperature Temperature measurement (0.01 degrees celsius)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_scaled_pressure_send(mavlink_channel_t chan, uint32_t time_boot_ms, float press_abs1, float press_diff11, float press_diff12, float press_diff13, float press_abs2, float press_diff21, float press_diff22, float press_diff23, float press_abs3, float press_diff31, float press_diff32, float press_diff33, float press_abs4, float press_diff41, float press_diff42, float press_diff43, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[70];
	_mav_put_uint32_t(buf, 0, time_boot_ms);
	_mav_put_float(buf, 4, press_abs1);
	_mav_put_float(buf, 8, press_diff11);
	_mav_put_float(buf, 12, press_diff12);
	_mav_put_float(buf, 16, press_diff13);
	_mav_put_float(buf, 20, press_abs2);
	_mav_put_float(buf, 24, press_diff21);
	_mav_put_float(buf, 28, press_diff22);
	_mav_put_float(buf, 32, press_diff23);
	_mav_put_float(buf, 36, press_abs3);
	_mav_put_float(buf, 40, press_diff31);
	_mav_put_float(buf, 44, press_diff32);
	_mav_put_float(buf, 48, press_diff33);
	_mav_put_float(buf, 52, press_abs4);
	_mav_put_float(buf, 56, press_diff41);
	_mav_put_float(buf, 60, press_diff42);
	_mav_put_float(buf, 64, press_diff43);
	_mav_put_int16_t(buf, 68, temperature);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE, buf, 70, 243);
#else
	mavlink_skye_scaled_pressure_t packet;
	packet.time_boot_ms = time_boot_ms;
	packet.press_abs1 = press_abs1;
	packet.press_diff11 = press_diff11;
	packet.press_diff12 = press_diff12;
	packet.press_diff13 = press_diff13;
	packet.press_abs2 = press_abs2;
	packet.press_diff21 = press_diff21;
	packet.press_diff22 = press_diff22;
	packet.press_diff23 = press_diff23;
	packet.press_abs3 = press_abs3;
	packet.press_diff31 = press_diff31;
	packet.press_diff32 = press_diff32;
	packet.press_diff33 = press_diff33;
	packet.press_abs4 = press_abs4;
	packet.press_diff41 = press_diff41;
	packet.press_diff42 = press_diff42;
	packet.press_diff43 = press_diff43;
	packet.temperature = temperature;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_SCALED_PRESSURE, (const char *)&packet, 70, 243);
#endif
}

#endif

// MESSAGE SKYE_SCALED_PRESSURE UNPACKING


/**
 * @brief Get field time_boot_ms from skye_scaled_pressure message
 *
 * @return Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 */
static inline uint32_t mavlink_msg_skye_scaled_pressure_get_time_boot_ms(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field press_abs1 from skye_scaled_pressure message
 *
 * @return Absolute pressure (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_abs1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field press_diff11 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff11(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field press_diff12 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff12(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field press_diff13 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff13(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field press_abs2 from skye_scaled_pressure message
 *
 * @return Absolute pressure (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_abs2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field press_diff21 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff21(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field press_diff22 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff22(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field press_diff23 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff23(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field press_abs3 from skye_scaled_pressure message
 *
 * @return Absolute pressure (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_abs3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field press_diff31 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff31(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field press_diff32 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff32(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field press_diff33 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff33(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field press_abs4 from skye_scaled_pressure message
 *
 * @return Absolute pressure (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_abs4(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field press_diff41 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff41(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field press_diff42 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff42(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field press_diff43 from skye_scaled_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline float mavlink_msg_skye_scaled_pressure_get_press_diff43(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field temperature from skye_scaled_pressure message
 *
 * @return Temperature measurement (0.01 degrees celsius)
 */
static inline int16_t mavlink_msg_skye_scaled_pressure_get_temperature(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  68);
}

/**
 * @brief Decode a skye_scaled_pressure message into a struct
 *
 * @param msg The message to decode
 * @param skye_scaled_pressure C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_scaled_pressure_decode(const mavlink_message_t* msg, mavlink_skye_scaled_pressure_t* skye_scaled_pressure)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_scaled_pressure->time_boot_ms = mavlink_msg_skye_scaled_pressure_get_time_boot_ms(msg);
	skye_scaled_pressure->press_abs1 = mavlink_msg_skye_scaled_pressure_get_press_abs1(msg);
	skye_scaled_pressure->press_diff11 = mavlink_msg_skye_scaled_pressure_get_press_diff11(msg);
	skye_scaled_pressure->press_diff12 = mavlink_msg_skye_scaled_pressure_get_press_diff12(msg);
	skye_scaled_pressure->press_diff13 = mavlink_msg_skye_scaled_pressure_get_press_diff13(msg);
	skye_scaled_pressure->press_abs2 = mavlink_msg_skye_scaled_pressure_get_press_abs2(msg);
	skye_scaled_pressure->press_diff21 = mavlink_msg_skye_scaled_pressure_get_press_diff21(msg);
	skye_scaled_pressure->press_diff22 = mavlink_msg_skye_scaled_pressure_get_press_diff22(msg);
	skye_scaled_pressure->press_diff23 = mavlink_msg_skye_scaled_pressure_get_press_diff23(msg);
	skye_scaled_pressure->press_abs3 = mavlink_msg_skye_scaled_pressure_get_press_abs3(msg);
	skye_scaled_pressure->press_diff31 = mavlink_msg_skye_scaled_pressure_get_press_diff31(msg);
	skye_scaled_pressure->press_diff32 = mavlink_msg_skye_scaled_pressure_get_press_diff32(msg);
	skye_scaled_pressure->press_diff33 = mavlink_msg_skye_scaled_pressure_get_press_diff33(msg);
	skye_scaled_pressure->press_abs4 = mavlink_msg_skye_scaled_pressure_get_press_abs4(msg);
	skye_scaled_pressure->press_diff41 = mavlink_msg_skye_scaled_pressure_get_press_diff41(msg);
	skye_scaled_pressure->press_diff42 = mavlink_msg_skye_scaled_pressure_get_press_diff42(msg);
	skye_scaled_pressure->press_diff43 = mavlink_msg_skye_scaled_pressure_get_press_diff43(msg);
	skye_scaled_pressure->temperature = mavlink_msg_skye_scaled_pressure_get_temperature(msg);
#else
	memcpy(skye_scaled_pressure, _MAV_PAYLOAD(msg), 70);
#endif
}
