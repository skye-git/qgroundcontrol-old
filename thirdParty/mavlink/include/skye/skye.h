/** @file
 *	@brief MAVLink comm protocol generated from skye.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef SKYE_H
#define SKYE_H

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {9, 31, 12, 0, 14, 28, 3, 32, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 20, 2, 25, 23, 30, 101, 22, 26, 16, 14, 28, 32, 28, 28, 22, 22, 21, 6, 6, 37, 4, 4, 2, 2, 4, 2, 2, 3, 13, 12, 19, 17, 15, 15, 27, 25, 18, 18, 20, 20, 9, 54, 26, 0, 36, 0, 6, 4, 0, 21, 18, 0, 0, 0, 20, 0, 33, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 56, 42, 33, 0, 0, 0, 0, 0, 0, 0, 22, 32, 32, 20, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 13, 25, 25, 17, 70, 16, 12, 16, 105, 2, 53, 3, 33, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 30, 18, 18, 51, 9, 0}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {50, 124, 137, 0, 237, 217, 104, 119, 0, 0, 0, 89, 0, 0, 0, 0, 0, 0, 0, 0, 214, 159, 220, 168, 24, 23, 170, 144, 67, 115, 39, 246, 185, 104, 237, 244, 222, 212, 9, 254, 230, 28, 28, 132, 221, 232, 11, 153, 41, 39, 214, 223, 141, 33, 15, 3, 100, 24, 239, 238, 30, 200, 183, 0, 130, 0, 148, 21, 0, 52, 124, 0, 0, 0, 20, 0, 152, 143, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 231, 183, 63, 54, 0, 0, 0, 0, 0, 0, 0, 31, 102, 158, 208, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 77, 204, 175, 171, 198, 243, 166, 241, 28, 172, 197, 154, 124, 151, 219, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 204, 49, 170, 44, 83, 46, 0}
#endif

#ifndef MAVLINK_MESSAGE_INFO
#define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_SYS_STATUS, MAVLINK_MESSAGE_INFO_SYSTEM_TIME, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_PING, MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL, MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL_ACK, MAVLINK_MESSAGE_INFO_AUTH_KEY, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_SET_MODE, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_PARAM_REQUEST_READ, MAVLINK_MESSAGE_INFO_PARAM_REQUEST_LIST, MAVLINK_MESSAGE_INFO_PARAM_VALUE, MAVLINK_MESSAGE_INFO_PARAM_SET, MAVLINK_MESSAGE_INFO_GPS_RAW_INT, MAVLINK_MESSAGE_INFO_GPS_STATUS, MAVLINK_MESSAGE_INFO_SCALED_IMU, MAVLINK_MESSAGE_INFO_RAW_IMU, MAVLINK_MESSAGE_INFO_RAW_PRESSURE, MAVLINK_MESSAGE_INFO_SCALED_PRESSURE, MAVLINK_MESSAGE_INFO_ATTITUDE, MAVLINK_MESSAGE_INFO_ATTITUDE_QUATERNION, MAVLINK_MESSAGE_INFO_LOCAL_POSITION_NED, MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_INT, MAVLINK_MESSAGE_INFO_RC_CHANNELS_SCALED, MAVLINK_MESSAGE_INFO_RC_CHANNELS_RAW, MAVLINK_MESSAGE_INFO_SERVO_OUTPUT_RAW, MAVLINK_MESSAGE_INFO_MISSION_REQUEST_PARTIAL_LIST, MAVLINK_MESSAGE_INFO_MISSION_WRITE_PARTIAL_LIST, MAVLINK_MESSAGE_INFO_MISSION_ITEM, MAVLINK_MESSAGE_INFO_MISSION_REQUEST, MAVLINK_MESSAGE_INFO_MISSION_SET_CURRENT, MAVLINK_MESSAGE_INFO_MISSION_CURRENT, MAVLINK_MESSAGE_INFO_MISSION_REQUEST_LIST, MAVLINK_MESSAGE_INFO_MISSION_COUNT, MAVLINK_MESSAGE_INFO_MISSION_CLEAR_ALL, MAVLINK_MESSAGE_INFO_MISSION_ITEM_REACHED, MAVLINK_MESSAGE_INFO_MISSION_ACK, MAVLINK_MESSAGE_INFO_SET_GPS_GLOBAL_ORIGIN, MAVLINK_MESSAGE_INFO_GPS_GLOBAL_ORIGIN, MAVLINK_MESSAGE_INFO_SET_LOCAL_POSITION_SETPOINT, MAVLINK_MESSAGE_INFO_LOCAL_POSITION_SETPOINT, MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_SETPOINT_INT, MAVLINK_MESSAGE_INFO_SET_GLOBAL_POSITION_SETPOINT_INT, MAVLINK_MESSAGE_INFO_SAFETY_SET_ALLOWED_AREA, MAVLINK_MESSAGE_INFO_SAFETY_ALLOWED_AREA, MAVLINK_MESSAGE_INFO_SET_ROLL_PITCH_YAW_THRUST, MAVLINK_MESSAGE_INFO_SET_ROLL_PITCH_YAW_SPEED_THRUST, MAVLINK_MESSAGE_INFO_ROLL_PITCH_YAW_THRUST_SETPOINT, MAVLINK_MESSAGE_INFO_ROLL_PITCH_YAW_SPEED_THRUST_SETPOINT, MAVLINK_MESSAGE_INFO_SET_QUAD_MOTORS_SETPOINT, MAVLINK_MESSAGE_INFO_SET_QUAD_SWARM_ROLL_PITCH_YAW_THRUST, MAVLINK_MESSAGE_INFO_NAV_CONTROLLER_OUTPUT, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_STATE_CORRECTION, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_REQUEST_DATA_STREAM, MAVLINK_MESSAGE_INFO_DATA_STREAM, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_MANUAL_CONTROL, MAVLINK_MESSAGE_INFO_RC_CHANNELS_OVERRIDE, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_VFR_HUD, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_COMMAND_LONG, MAVLINK_MESSAGE_INFO_COMMAND_ACK, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET, MAVLINK_MESSAGE_INFO_HIL_STATE, MAVLINK_MESSAGE_INFO_HIL_CONTROLS, MAVLINK_MESSAGE_INFO_HIL_RC_INPUTS_RAW, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_OPTICAL_FLOW, MAVLINK_MESSAGE_INFO_GLOBAL_VISION_POSITION_ESTIMATE, MAVLINK_MESSAGE_INFO_VISION_POSITION_ESTIMATE, MAVLINK_MESSAGE_INFO_VISION_SPEED_ESTIMATE, MAVLINK_MESSAGE_INFO_VICON_POSITION_ESTIMATE, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_SKYE_BATTERY_STATUS, MAVLINK_MESSAGE_INFO_SKYE_TEST_MOTORS, MAVLINK_MESSAGE_INFO_SKYE_DIRECT_CONTROL, MAVLINK_MESSAGE_INFO_SKYE_ASSISTED_CONTROL, MAVLINK_MESSAGE_INFO_SKYE_ASSISTED_RC_CONTROL, MAVLINK_MESSAGE_INFO_SKYE_SCALED_PRESSURE, MAVLINK_MESSAGE_INFO_SKYE_MOTOR_SIGNAL, MAVLINK_MESSAGE_INFO_SKYE_MOTOR_MEASSURED_POSITION, MAVLINK_MESSAGE_INFO_SKYE_CONTROLLER_OUTPUT, MAVLINK_MESSAGE_INFO_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS, MAVLINK_MESSAGE_INFO_SKYE_CAM_RECONFIGURE_PROSILICA_SETTINGS, MAVLINK_MESSAGE_INFO_SKYE_CAM_HANDLE_SAVE_IMAGE, MAVLINK_MESSAGE_INFO_SKYE_CAM_TAKE_SHOT, MAVLINK_MESSAGE_INFO_SKYE_CAM_IMAGE_TRIGGERED, MAVLINK_MESSAGE_INFO_SKYE_HOME_MAXON, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_DATA_TRANSMISSION_HANDSHAKE, MAVLINK_MESSAGE_INFO_ENCAPSULATED_DATA, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_MEMORY_VECT, MAVLINK_MESSAGE_INFO_DEBUG_VECT, MAVLINK_MESSAGE_INFO_NAMED_VALUE_FLOAT, MAVLINK_MESSAGE_INFO_NAMED_VALUE_INT, MAVLINK_MESSAGE_INFO_STATUSTEXT, MAVLINK_MESSAGE_INFO_DEBUG, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_SKYE

#include "../common/common.h"

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// ENUM DEFINITIONS


/** @brief These defines are predefined OR-combined mode flags used for project skye. There is no need to use values from this enum, but it simplifies the use of the mode flags. Note that manual input is enabled in all modes as a safety override. */
#ifndef HAVE_ENUM_MAV_SKYE_MODE
#define HAVE_ENUM_MAV_SKYE_MODE
enum MAV_SKYE_MODE
{
	MAV_MODE_DIRECT_CONTROL_DISARMED=65, /* System is under Direct Control, no stabilization. | */
	MAV_MODE_TESTPHASE_DISARMED=67, /* System is ready to test the motors. | */
	MAV_MODE_ASSISTED_CONTROL_DISARMED=81, /* System is under Assisted Control, stabalized. | */
	MAV_MODE_HALF_AUTOMATIC_DISARMED=89, /* System is under Half Automatic Control, translation by waypoints, rotation by manual input. Stabalized. | */
	MAV_MODE_FULL_AUTOMATIC_DISARMED=93, /* System is under Full Automatic Control, steering by waypoints only. Stabalized. | */
	MAV_MODE_DIRECT_CONTROL_ARMED=193, /* System is under Direct Control, no stabilization. | */
	MAV_MODE_TESTPHASE_ARMED=195, /* System is ready to test the motors. | */
	MAV_MODE_ASSISTED_CONTROL_ARMED=209, /* System is under Assisted Control, stabalized. | */
	MAV_MODE_HALF_AUTOMATIC_ARMED=217, /* System is under Half Automatic Control, translation by waypoints, rotation by manual input. Stabalized. | */
	MAV_MODE_FULL_AUTOMATIC_ARMED=221, /* System is under Full Automatic Control, steering by waypoints only. Stabalized. | */
	MAV_SKYE_MODE_ENUM_END=222, /*  | */
};
#endif

/** @brief Camera Reconfigure parameter "color_coding" */
#ifndef HAVE_ENUM_MAV_CAM_RECONFIG_PIXEL_CLOCK
#define HAVE_ENUM_MAV_CAM_RECONFIG_PIXEL_CLOCK
enum MAV_CAM_RECONFIG_PIXEL_CLOCK
{
	MAV_CAM_RECONFIG_PIXEL_CLOCK_6M=6, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_8M=8, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_10M=10, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_13M5=13, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_20M=20, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_24M=24, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_27M6=27, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_32M=32, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_37M=37, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_40M=40, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_50M=50, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_57M6=57, /*  | */
	MAV_CAM_RECONFIG_PIXEL_CLOCK_ENUM_END=58, /*  | */
};
#endif

/** @brief Camera Reconfigure parameter "color_coding" */
#ifndef HAVE_ENUM_MAV_CAM_RECONFIG_COLOR_CODING
#define HAVE_ENUM_MAV_CAM_RECONFIG_COLOR_CODING
enum MAV_CAM_RECONFIG_COLOR_CODING
{
	MAV_CAM_RECONFIG_COLOR_CODING_AUTO=0, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_MONO8=1, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_MONO16=2, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_RAW8=3, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_BGR8=4, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_BGRA8=5, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_BGR16=6, /*  | */
	MAV_CAM_RECONFIG_COLOR_CODING_ENUM_END=7, /*  | */
};
#endif

/** @brief Camera Reconfigure parameter "bayer_method" */
#ifndef HAVE_ENUM_MAV_CAM_RECONFIG_BAYER_METHOD
#define HAVE_ENUM_MAV_CAM_RECONFIG_BAYER_METHOD
enum MAV_CAM_RECONFIG_BAYER_METHOD
{
	MAV_CAM_RECONFIG_BAYER_METHOD_IMAGE_PROC=0, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_DOWNSAMPLE=1, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_SIMPLE=2, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_BILINEAR=3, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_HQ=4, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_VNG=5, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_AHD=6, /*  | */
	MAV_CAM_RECONFIG_BAYER_METHOD_ENUM_END=7, /*  | */
};
#endif

/** @brief Camera Reconfigure parameter "auto_control_speed" */
#ifndef HAVE_ENUM_MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
#define HAVE_ENUM_MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
{
	MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ACS_MEDIUM=0, /* Medium | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ACS_SLOW=1, /* Slow | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ACS_FAST=2, /* Fast | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED_ENUM_END=3, /*  | */
};
#endif

/** @brief Camera Reconfigure parameter "hdr_mode" */
#ifndef HAVE_ENUM_MAV_CAM_RECONFIG_HDR_MODE
#define HAVE_ENUM_MAV_CAM_RECONFIG_HDR_MODE
enum MAV_CAM_RECONFIG_HDR_MODE
{
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_OFF=0, /* Off | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED0=1, /* Fixed0 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED1=2, /* Fixed1 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED2=3, /* Fixed2 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED3=4, /* Fixed3 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED4=5, /* Fixed4 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED5=6, /* Fixed5 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_FIXED6=7, /* Fixed6 | */
	MAV_CAM_RECONFIG_AUTO_CONTROL_HDR_MODE_HDR_USER=8, /* User | */
	MAV_CAM_RECONFIG_HDR_MODE_ENUM_END=9, /*  | */
};
#endif

/** @brief Camera ID */
#ifndef HAVE_ENUM_MAV_CAM_ID
#define HAVE_ENUM_MAV_CAM_ID
enum MAV_CAM_ID
{
	MAV_CAM_ID_ALL=0, /* Off | */
	MAV_CAM_ID_PROSILICA=1, /* High resolution AVT prosilica camera | */
	MAV_CAM_ID_BLUEFOX_LEFT=2, /* Low resolution matrix-vision bluefox camera, position left | */
	MAV_CAM_ID_BLUEFOX_RIGHT=3, /* Low resolution matrix-vision bluefox camera, position right | */
	MAV_CAM_ID_ENUM_END=4, /*  | */
};
#endif

/** @brief Image Format */
#ifndef HAVE_ENUM_MAV_CAM_IMAGE_FORMAT
#define HAVE_ENUM_MAV_CAM_IMAGE_FORMAT
enum MAV_CAM_IMAGE_FORMAT
{
	MAV_CAM_IMAGE_FORMAT_RAW=0, /* RAW format | */
	MAV_CAM_IMAGE_FORMAT_JPEG=1, /* JPEG format | */
	MAV_CAM_IMAGE_FORMAT_PNG=2, /* PNG format | */
	MAV_CAM_IMAGE_FORMAT_ENUM_END=3, /*  | */
};
#endif

/** @brief Content Types for data transmission handshake */
#ifndef HAVE_ENUM_DATA_TYPES
#define HAVE_ENUM_DATA_TYPES
enum DATA_TYPES
{
	DATA_TYPE_JPEG_IMAGE=1, /*  | */
	DATA_TYPE_RAW_IMAGE=2, /*  | */
	DATA_TYPE_KINECT=3, /*  | */
	DATA_TYPES_ENUM_END=4, /*  | */
};
#endif

/** @brief ID for each accu pack for detailed battery information */
#ifndef HAVE_ENUM_MAV_SKYE_BATTERY_PACK_ID
#define HAVE_ENUM_MAV_SKYE_BATTERY_PACK_ID
enum MAV_SKYE_BATTERY_PACK_ID
{
	MAV_SKYE_BATTERY_PACK_ID_NONE=0, /* no accu | */
	MAV_SKYE_BATTERY_PACK_ID_1=1, /* Accu pack 1 | */
	MAV_SKYE_BATTERY_PACK_ID_2=2, /* Accu pack 1 | */
	MAV_SKYE_BATTERY_PACK_ID_3=3, /* Accu pack 1 | */
	MAV_SKYE_BATTERY_PACK_ID_ENUM_END=4, /*  | */
};
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_skye_battery_status.h"
#include "./mavlink_msg_skye_test_motors.h"
#include "./mavlink_msg_skye_direct_control.h"
#include "./mavlink_msg_skye_assisted_control.h"
#include "./mavlink_msg_skye_assisted_rc_control.h"
#include "./mavlink_msg_skye_scaled_pressure.h"
#include "./mavlink_msg_skye_motor_signal.h"
#include "./mavlink_msg_skye_motor_meassured_position.h"
#include "./mavlink_msg_skye_controller_output.h"
#include "./mavlink_msg_skye_cam_reconfigure_bluefox_settings.h"
#include "./mavlink_msg_skye_cam_reconfigure_prosilica_settings.h"
#include "./mavlink_msg_skye_cam_handle_save_image.h"
#include "./mavlink_msg_skye_cam_take_shot.h"
#include "./mavlink_msg_skye_cam_image_triggered.h"
#include "./mavlink_msg_skye_home_maxon.h"
#include "./mavlink_msg_data_transmission_handshake.h"
#include "./mavlink_msg_encapsulated_data.h"

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SKYE_H
