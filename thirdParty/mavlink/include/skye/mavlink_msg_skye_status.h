// MESSAGE SKYE_STATUS PACKING

#define MAVLINK_MSG_ID_SKYE_STATUS 151

typedef struct __mavlink_skye_status_t
{
 uint32_t onboard_control_sensors_present; ///< Bitmask showing which controllers an sensors are present. =0:not present, =1:present, Sensors: last bit 1: 3D gyro, 2: 3D acc, 4: 3D mag, 8: absolute pressure, 16: differential pressures, 32: GPS, 64: motor homing, 128: motor decoding (EPOS), Controllers: 256: attitude stabilization, 512: z/altitude control, 1024: x/y position control, 2048: motor outputs control
 uint32_t onboard_control_sensors_enabled; ///< Bitmask showing which controllers an sensors are enabled. =0:not enabled, =1:enabled, same bit contribution as field before.
		
 uint32_t onboard_control_sensors_operating; ///< Bitmask showing controllers and sensors are operating or have an error. =0:ERROR, =1:operating, same bit contribution as field before.
 float hull_pressure; ///< Remaining hull pressure (hectopascal), -1: no pressure data
 float hull_temperature; ///< Hull temperature (Kelvin), -1: no temperature data
 uint16_t mainloop_load; ///< Maximum usage of the mainloop time, (0%: 0, 100%: 1000) should be always below 1000
 uint16_t drop_rate_comm; ///< Communication drops in percent, (0%: 0, 100%: 10'000), (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 uint16_t errors_comm; ///< Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
} mavlink_skye_status_t;

#define MAVLINK_MSG_ID_SKYE_STATUS_LEN 26
#define MAVLINK_MSG_ID_151_LEN 26



#define MAVLINK_MESSAGE_INFO_SKYE_STATUS { \
	"SKYE_STATUS", \
	8, \
	{  { "onboard_control_sensors_present", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_skye_status_t, onboard_control_sensors_present) }, \
         { "onboard_control_sensors_enabled", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_skye_status_t, onboard_control_sensors_enabled) }, \
         { "onboard_control_sensors_operating", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_skye_status_t, onboard_control_sensors_operating) }, \
         { "hull_pressure", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_status_t, hull_pressure) }, \
         { "hull_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_status_t, hull_temperature) }, \
         { "mainloop_load", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_skye_status_t, mainloop_load) }, \
         { "drop_rate_comm", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_skye_status_t, drop_rate_comm) }, \
         { "errors_comm", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_skye_status_t, errors_comm) }, \
         } \
}


/**
 * @brief Pack a skye_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param onboard_control_sensors_present Bitmask showing which controllers an sensors are present. =0:not present, =1:present, Sensors: last bit 1: 3D gyro, 2: 3D acc, 4: 3D mag, 8: absolute pressure, 16: differential pressures, 32: GPS, 64: motor homing, 128: motor decoding (EPOS), Controllers: 256: attitude stabilization, 512: z/altitude control, 1024: x/y position control, 2048: motor outputs control
 * @param onboard_control_sensors_enabled Bitmask showing which controllers an sensors are enabled. =0:not enabled, =1:enabled, same bit contribution as field before.
		
 * @param onboard_control_sensors_operating Bitmask showing controllers and sensors are operating or have an error. =0:ERROR, =1:operating, same bit contribution as field before.
 * @param mainloop_load Maximum usage of the mainloop time, (0%: 0, 100%: 1000) should be always below 1000
 * @param hull_pressure Remaining hull pressure (hectopascal), -1: no pressure data
 * @param hull_temperature Hull temperature (Kelvin), -1: no temperature data
 * @param drop_rate_comm Communication drops in percent, (0%: 0, 100%: 10'000), (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 * @param errors_comm Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t onboard_control_sensors_present, uint32_t onboard_control_sensors_enabled, uint32_t onboard_control_sensors_operating, uint16_t mainloop_load, float hull_pressure, float hull_temperature, uint16_t drop_rate_comm, uint16_t errors_comm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[26];
	_mav_put_uint32_t(buf, 0, onboard_control_sensors_present);
	_mav_put_uint32_t(buf, 4, onboard_control_sensors_enabled);
	_mav_put_uint32_t(buf, 8, onboard_control_sensors_operating);
	_mav_put_float(buf, 12, hull_pressure);
	_mav_put_float(buf, 16, hull_temperature);
	_mav_put_uint16_t(buf, 20, mainloop_load);
	_mav_put_uint16_t(buf, 22, drop_rate_comm);
	_mav_put_uint16_t(buf, 24, errors_comm);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 26);
#else
	mavlink_skye_status_t packet;
	packet.onboard_control_sensors_present = onboard_control_sensors_present;
	packet.onboard_control_sensors_enabled = onboard_control_sensors_enabled;
	packet.onboard_control_sensors_operating = onboard_control_sensors_operating;
	packet.hull_pressure = hull_pressure;
	packet.hull_temperature = hull_temperature;
	packet.mainloop_load = mainloop_load;
	packet.drop_rate_comm = drop_rate_comm;
	packet.errors_comm = errors_comm;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 26);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_STATUS;
	return mavlink_finalize_message(msg, system_id, component_id, 26, 135);
}

/**
 * @brief Pack a skye_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param onboard_control_sensors_present Bitmask showing which controllers an sensors are present. =0:not present, =1:present, Sensors: last bit 1: 3D gyro, 2: 3D acc, 4: 3D mag, 8: absolute pressure, 16: differential pressures, 32: GPS, 64: motor homing, 128: motor decoding (EPOS), Controllers: 256: attitude stabilization, 512: z/altitude control, 1024: x/y position control, 2048: motor outputs control
 * @param onboard_control_sensors_enabled Bitmask showing which controllers an sensors are enabled. =0:not enabled, =1:enabled, same bit contribution as field before.
		
 * @param onboard_control_sensors_operating Bitmask showing controllers and sensors are operating or have an error. =0:ERROR, =1:operating, same bit contribution as field before.
 * @param mainloop_load Maximum usage of the mainloop time, (0%: 0, 100%: 1000) should be always below 1000
 * @param hull_pressure Remaining hull pressure (hectopascal), -1: no pressure data
 * @param hull_temperature Hull temperature (Kelvin), -1: no temperature data
 * @param drop_rate_comm Communication drops in percent, (0%: 0, 100%: 10'000), (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 * @param errors_comm Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t onboard_control_sensors_present,uint32_t onboard_control_sensors_enabled,uint32_t onboard_control_sensors_operating,uint16_t mainloop_load,float hull_pressure,float hull_temperature,uint16_t drop_rate_comm,uint16_t errors_comm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[26];
	_mav_put_uint32_t(buf, 0, onboard_control_sensors_present);
	_mav_put_uint32_t(buf, 4, onboard_control_sensors_enabled);
	_mav_put_uint32_t(buf, 8, onboard_control_sensors_operating);
	_mav_put_float(buf, 12, hull_pressure);
	_mav_put_float(buf, 16, hull_temperature);
	_mav_put_uint16_t(buf, 20, mainloop_load);
	_mav_put_uint16_t(buf, 22, drop_rate_comm);
	_mav_put_uint16_t(buf, 24, errors_comm);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 26);
#else
	mavlink_skye_status_t packet;
	packet.onboard_control_sensors_present = onboard_control_sensors_present;
	packet.onboard_control_sensors_enabled = onboard_control_sensors_enabled;
	packet.onboard_control_sensors_operating = onboard_control_sensors_operating;
	packet.hull_pressure = hull_pressure;
	packet.hull_temperature = hull_temperature;
	packet.mainloop_load = mainloop_load;
	packet.drop_rate_comm = drop_rate_comm;
	packet.errors_comm = errors_comm;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 26);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_STATUS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 26, 135);
}

/**
 * @brief Encode a skye_status struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_status_t* skye_status)
{
	return mavlink_msg_skye_status_pack(system_id, component_id, msg, skye_status->onboard_control_sensors_present, skye_status->onboard_control_sensors_enabled, skye_status->onboard_control_sensors_operating, skye_status->mainloop_load, skye_status->hull_pressure, skye_status->hull_temperature, skye_status->drop_rate_comm, skye_status->errors_comm);
}

/**
 * @brief Send a skye_status message
 * @param chan MAVLink channel to send the message
 *
 * @param onboard_control_sensors_present Bitmask showing which controllers an sensors are present. =0:not present, =1:present, Sensors: last bit 1: 3D gyro, 2: 3D acc, 4: 3D mag, 8: absolute pressure, 16: differential pressures, 32: GPS, 64: motor homing, 128: motor decoding (EPOS), Controllers: 256: attitude stabilization, 512: z/altitude control, 1024: x/y position control, 2048: motor outputs control
 * @param onboard_control_sensors_enabled Bitmask showing which controllers an sensors are enabled. =0:not enabled, =1:enabled, same bit contribution as field before.
		
 * @param onboard_control_sensors_operating Bitmask showing controllers and sensors are operating or have an error. =0:ERROR, =1:operating, same bit contribution as field before.
 * @param mainloop_load Maximum usage of the mainloop time, (0%: 0, 100%: 1000) should be always below 1000
 * @param hull_pressure Remaining hull pressure (hectopascal), -1: no pressure data
 * @param hull_temperature Hull temperature (Kelvin), -1: no temperature data
 * @param drop_rate_comm Communication drops in percent, (0%: 0, 100%: 10'000), (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 * @param errors_comm Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_status_send(mavlink_channel_t chan, uint32_t onboard_control_sensors_present, uint32_t onboard_control_sensors_enabled, uint32_t onboard_control_sensors_operating, uint16_t mainloop_load, float hull_pressure, float hull_temperature, uint16_t drop_rate_comm, uint16_t errors_comm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[26];
	_mav_put_uint32_t(buf, 0, onboard_control_sensors_present);
	_mav_put_uint32_t(buf, 4, onboard_control_sensors_enabled);
	_mav_put_uint32_t(buf, 8, onboard_control_sensors_operating);
	_mav_put_float(buf, 12, hull_pressure);
	_mav_put_float(buf, 16, hull_temperature);
	_mav_put_uint16_t(buf, 20, mainloop_load);
	_mav_put_uint16_t(buf, 22, drop_rate_comm);
	_mav_put_uint16_t(buf, 24, errors_comm);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_STATUS, buf, 26, 135);
#else
	mavlink_skye_status_t packet;
	packet.onboard_control_sensors_present = onboard_control_sensors_present;
	packet.onboard_control_sensors_enabled = onboard_control_sensors_enabled;
	packet.onboard_control_sensors_operating = onboard_control_sensors_operating;
	packet.hull_pressure = hull_pressure;
	packet.hull_temperature = hull_temperature;
	packet.mainloop_load = mainloop_load;
	packet.drop_rate_comm = drop_rate_comm;
	packet.errors_comm = errors_comm;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_STATUS, (const char *)&packet, 26, 135);
#endif
}

#endif

// MESSAGE SKYE_STATUS UNPACKING


/**
 * @brief Get field onboard_control_sensors_present from skye_status message
 *
 * @return Bitmask showing which controllers an sensors are present. =0:not present, =1:present, Sensors: last bit 1: 3D gyro, 2: 3D acc, 4: 3D mag, 8: absolute pressure, 16: differential pressures, 32: GPS, 64: motor homing, 128: motor decoding (EPOS), Controllers: 256: attitude stabilization, 512: z/altitude control, 1024: x/y position control, 2048: motor outputs control
 */
static inline uint32_t mavlink_msg_skye_status_get_onboard_control_sensors_present(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field onboard_control_sensors_enabled from skye_status message
 *
 * @return Bitmask showing which controllers an sensors are enabled. =0:not enabled, =1:enabled, same bit contribution as field before.
		
 */
static inline uint32_t mavlink_msg_skye_status_get_onboard_control_sensors_enabled(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field onboard_control_sensors_operating from skye_status message
 *
 * @return Bitmask showing controllers and sensors are operating or have an error. =0:ERROR, =1:operating, same bit contribution as field before.
 */
static inline uint32_t mavlink_msg_skye_status_get_onboard_control_sensors_operating(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field mainloop_load from skye_status message
 *
 * @return Maximum usage of the mainloop time, (0%: 0, 100%: 1000) should be always below 1000
 */
static inline uint16_t mavlink_msg_skye_status_get_mainloop_load(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field hull_pressure from skye_status message
 *
 * @return Remaining hull pressure (hectopascal), -1: no pressure data
 */
static inline float mavlink_msg_skye_status_get_hull_pressure(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field hull_temperature from skye_status message
 *
 * @return Hull temperature (Kelvin), -1: no temperature data
 */
static inline float mavlink_msg_skye_status_get_hull_temperature(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field drop_rate_comm from skye_status message
 *
 * @return Communication drops in percent, (0%: 0, 100%: 10'000), (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 */
static inline uint16_t mavlink_msg_skye_status_get_drop_rate_comm(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Get field errors_comm from skye_status message
 *
 * @return Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
 */
static inline uint16_t mavlink_msg_skye_status_get_errors_comm(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Decode a skye_status message into a struct
 *
 * @param msg The message to decode
 * @param skye_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_status_decode(const mavlink_message_t* msg, mavlink_skye_status_t* skye_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_status->onboard_control_sensors_present = mavlink_msg_skye_status_get_onboard_control_sensors_present(msg);
	skye_status->onboard_control_sensors_enabled = mavlink_msg_skye_status_get_onboard_control_sensors_enabled(msg);
	skye_status->onboard_control_sensors_operating = mavlink_msg_skye_status_get_onboard_control_sensors_operating(msg);
	skye_status->hull_pressure = mavlink_msg_skye_status_get_hull_pressure(msg);
	skye_status->hull_temperature = mavlink_msg_skye_status_get_hull_temperature(msg);
	skye_status->mainloop_load = mavlink_msg_skye_status_get_mainloop_load(msg);
	skye_status->drop_rate_comm = mavlink_msg_skye_status_get_drop_rate_comm(msg);
	skye_status->errors_comm = mavlink_msg_skye_status_get_errors_comm(msg);
#else
	memcpy(skye_status, _MAV_PAYLOAD(msg), 26);
#endif
}
