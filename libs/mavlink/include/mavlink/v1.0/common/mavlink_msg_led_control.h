// MESSAGE LED_CONTROL PACKING

#define MAVLINK_MSG_ID_LED_CONTROL 144

typedef struct __mavlink_led_control_t
{
 float frequency; ///< Frequency parameter, Hz
 uint8_t led_id; ///< Led ID
 uint8_t red; ///< Red color component for 24bit color
 uint8_t green; ///< Red color component for 24bit color
 uint8_t blue; ///< Red color component for 24bit color
 uint8_t mode; ///< Compare LED_CONTROL_MODE enumerator - 0: Constant light, 1: Blink on/off, 2: Pulsate, 3: Colorloop, 4: Disco
} mavlink_led_control_t;

#define MAVLINK_MSG_ID_LED_CONTROL_LEN 9
#define MAVLINK_MSG_ID_144_LEN 9

#define MAVLINK_MSG_ID_LED_CONTROL_CRC 76
#define MAVLINK_MSG_ID_144_CRC 76



#define MAVLINK_MESSAGE_INFO_LED_CONTROL { \
	"LED_CONTROL", \
	6, \
	{  { "frequency", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_led_control_t, frequency) }, \
         { "led_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_led_control_t, led_id) }, \
         { "red", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_led_control_t, red) }, \
         { "green", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_led_control_t, green) }, \
         { "blue", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_led_control_t, blue) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_led_control_t, mode) }, \
         } \
}


/**
 * @brief Pack a led_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param led_id Led ID
 * @param red Red color component for 24bit color
 * @param green Red color component for 24bit color
 * @param blue Red color component for 24bit color
 * @param mode Compare LED_CONTROL_MODE enumerator - 0: Constant light, 1: Blink on/off, 2: Pulsate, 3: Colorloop, 4: Disco
 * @param frequency Frequency parameter, Hz
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t led_id, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
	_mav_put_float(buf, 0, frequency);
	_mav_put_uint8_t(buf, 4, led_id);
	_mav_put_uint8_t(buf, 5, red);
	_mav_put_uint8_t(buf, 6, green);
	_mav_put_uint8_t(buf, 7, blue);
	_mav_put_uint8_t(buf, 8, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#else
	mavlink_led_control_t packet;
	packet.frequency = frequency;
	packet.led_id = led_id;
	packet.red = red;
	packet.green = green;
	packet.blue = blue;
	packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LED_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a led_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param led_id Led ID
 * @param red Red color component for 24bit color
 * @param green Red color component for 24bit color
 * @param blue Red color component for 24bit color
 * @param mode Compare LED_CONTROL_MODE enumerator - 0: Constant light, 1: Blink on/off, 2: Pulsate, 3: Colorloop, 4: Disco
 * @param frequency Frequency parameter, Hz
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t led_id,uint8_t red,uint8_t green,uint8_t blue,uint8_t mode,float frequency)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
	_mav_put_float(buf, 0, frequency);
	_mav_put_uint8_t(buf, 4, led_id);
	_mav_put_uint8_t(buf, 5, red);
	_mav_put_uint8_t(buf, 6, green);
	_mav_put_uint8_t(buf, 7, blue);
	_mav_put_uint8_t(buf, 8, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#else
	mavlink_led_control_t packet;
	packet.frequency = frequency;
	packet.led_id = led_id;
	packet.red = red;
	packet.green = green;
	packet.blue = blue;
	packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LED_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
}

/**
 * @brief Encode a led_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param led_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_led_control_t* led_control)
{
	return mavlink_msg_led_control_pack(system_id, component_id, msg, led_control->led_id, led_control->red, led_control->green, led_control->blue, led_control->mode, led_control->frequency);
}

/**
 * @brief Send a led_control message
 * @param chan MAVLink channel to send the message
 *
 * @param led_id Led ID
 * @param red Red color component for 24bit color
 * @param green Red color component for 24bit color
 * @param blue Red color component for 24bit color
 * @param mode Compare LED_CONTROL_MODE enumerator - 0: Constant light, 1: Blink on/off, 2: Pulsate, 3: Colorloop, 4: Disco
 * @param frequency Frequency parameter, Hz
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_led_control_send(mavlink_channel_t chan, uint8_t led_id, uint8_t red, uint8_t green, uint8_t blue, uint8_t mode, float frequency)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
	_mav_put_float(buf, 0, frequency);
	_mav_put_uint8_t(buf, 4, led_id);
	_mav_put_uint8_t(buf, 5, red);
	_mav_put_uint8_t(buf, 6, green);
	_mav_put_uint8_t(buf, 7, blue);
	_mav_put_uint8_t(buf, 8, mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
#else
	mavlink_led_control_t packet;
	packet.frequency = frequency;
	packet.led_id = led_id;
	packet.red = red;
	packet.green = green;
	packet.blue = blue;
	packet.mode = mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
#endif
}

#endif

// MESSAGE LED_CONTROL UNPACKING


/**
 * @brief Get field led_id from led_control message
 *
 * @return Led ID
 */
static inline uint8_t mavlink_msg_led_control_get_led_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field red from led_control message
 *
 * @return Red color component for 24bit color
 */
static inline uint8_t mavlink_msg_led_control_get_red(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field green from led_control message
 *
 * @return Red color component for 24bit color
 */
static inline uint8_t mavlink_msg_led_control_get_green(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field blue from led_control message
 *
 * @return Red color component for 24bit color
 */
static inline uint8_t mavlink_msg_led_control_get_blue(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field mode from led_control message
 *
 * @return Compare LED_CONTROL_MODE enumerator - 0: Constant light, 1: Blink on/off, 2: Pulsate, 3: Colorloop, 4: Disco
 */
static inline uint8_t mavlink_msg_led_control_get_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field frequency from led_control message
 *
 * @return Frequency parameter, Hz
 */
static inline float mavlink_msg_led_control_get_frequency(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a led_control message into a struct
 *
 * @param msg The message to decode
 * @param led_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_led_control_decode(const mavlink_message_t* msg, mavlink_led_control_t* led_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	led_control->frequency = mavlink_msg_led_control_get_frequency(msg);
	led_control->led_id = mavlink_msg_led_control_get_led_id(msg);
	led_control->red = mavlink_msg_led_control_get_red(msg);
	led_control->green = mavlink_msg_led_control_get_green(msg);
	led_control->blue = mavlink_msg_led_control_get_blue(msg);
	led_control->mode = mavlink_msg_led_control_get_mode(msg);
#else
	memcpy(led_control, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
}
