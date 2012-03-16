// MESSAGE SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS PACKING

#define MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS 161

typedef struct __mavlink_skye_cam_reconfigure_bluefox_settings_t
{
 float pixel_clock; ///< Pixel clock of image sensor [MHz]. See enum MAV_CAM_RECONFIG_PIXEL_CLOCK
 float frame_rate; ///< Camera speed (frames per second). Range: 1.0 to 240.0
 float shutter_auto_min; ///< Min shutter time [s] in auto mode. Range: 0.0 to 0.1
 float shutter_auto_max; ///< Max shutter time [s] in auto mode Range: 0.0 to 0.1
 float shutter; ///< Shutter time [s]. Range: 0.0 to 0.1
 uint16_t roi_width; ///< Width of Region of Interest in unbinned pixels, full width if zero. Range: 0 to 5000
 uint16_t roi_height; ///< Height of Region of Interest in unbinned pixels, full height if zero. Range: 0 to 5000
 uint16_t x_offset; ///< Horizontal offset for left side of ROI in unbinned pixels. Range: 0 to 5000
 uint16_t y_offset; ///< Vertical offset for top of ROI in unbinned pixels. Range: 0 to 5000
 uint8_t target_system; ///< System ID
 uint8_t cam_id; ///< ID of camera, see ENUM MAV_CAM_ID
 char frame_id[32]; ///< ROS tf frame of reference, resolved with tf_prefix unless absolute.
 char camera_info_url[32]; ///< Camera calibration URL for this video_mode (uncalibrated if null). 
 uint8_t binning_x; ///< Number of pixels combined for horizontal binning, use device hints if zero. Range: 0 to 4
 uint8_t binning_y; ///< Number of pixels combined for vertical binning, use device hints if zero. Range: 0 to 4
 uint8_t color_coding; ///< Color coding. See enum MAV_CAM_RECONFIG_COLOR_CODING
 uint8_t bayer_method; ///< Bayer decoding method (default: ROS image_proc). See enum MAV_CAM_RECONFIG_BAYER_METHOD
 uint8_t exposure; ///< Auto exposure value . Range: 0 to 255
 uint8_t shutter_auto; ///< boolean. Shutter control state. 
 uint8_t gain_auto; ///< boolean. Gain control state. 
 uint8_t gain_auto_min; ///< Min relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 uint8_t gain_auto_max; ///< Max relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 uint8_t gain; ///< Relative circuit gain [dB]  Range: 0.0 to 12.0
 uint8_t auto_control_speed; ///< Control speed for automatic features. See enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
 uint8_t auto_query_values; ///< boolean. Queries settings that are auto controlled. 
 uint8_t hdr_mode; ///< HDR mode. See enum MAV_CAM_RECONFIG_HDR_MODE
 uint8_t use_ros_time; ///< boolean. Timestamp Image and CameraInfo using ros::Time::now() 
} mavlink_skye_cam_reconfigure_bluefox_settings_t;

#define MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS_LEN 108
#define MAVLINK_MSG_ID_161_LEN 108

#define MAVLINK_MSG_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS_FIELD_FRAME_ID_LEN 32
#define MAVLINK_MSG_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS_FIELD_CAMERA_INFO_URL_LEN 32

#define MAVLINK_MESSAGE_INFO_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS { \
	"SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS", \
	27, \
	{  { "pixel_clock", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, pixel_clock) }, \
         { "frame_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, frame_rate) }, \
         { "shutter_auto_min", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, shutter_auto_min) }, \
         { "shutter_auto_max", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, shutter_auto_max) }, \
         { "shutter", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, shutter) }, \
         { "roi_width", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, roi_width) }, \
         { "roi_height", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, roi_height) }, \
         { "x_offset", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, x_offset) }, \
         { "y_offset", NULL, MAVLINK_TYPE_UINT16_T, 0, 26, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, y_offset) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, target_system) }, \
         { "cam_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, cam_id) }, \
         { "frame_id", NULL, MAVLINK_TYPE_CHAR, 32, 30, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, frame_id) }, \
         { "camera_info_url", NULL, MAVLINK_TYPE_CHAR, 32, 62, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, camera_info_url) }, \
         { "binning_x", NULL, MAVLINK_TYPE_UINT8_T, 0, 94, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, binning_x) }, \
         { "binning_y", NULL, MAVLINK_TYPE_UINT8_T, 0, 95, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, binning_y) }, \
         { "color_coding", NULL, MAVLINK_TYPE_UINT8_T, 0, 96, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, color_coding) }, \
         { "bayer_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 97, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, bayer_method) }, \
         { "exposure", NULL, MAVLINK_TYPE_UINT8_T, 0, 98, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, exposure) }, \
         { "shutter_auto", NULL, MAVLINK_TYPE_UINT8_T, 0, 99, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, shutter_auto) }, \
         { "gain_auto", NULL, MAVLINK_TYPE_UINT8_T, 0, 100, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, gain_auto) }, \
         { "gain_auto_min", NULL, MAVLINK_TYPE_UINT8_T, 0, 101, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, gain_auto_min) }, \
         { "gain_auto_max", NULL, MAVLINK_TYPE_UINT8_T, 0, 102, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, gain_auto_max) }, \
         { "gain", NULL, MAVLINK_TYPE_UINT8_T, 0, 103, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, gain) }, \
         { "auto_control_speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 104, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, auto_control_speed) }, \
         { "auto_query_values", NULL, MAVLINK_TYPE_UINT8_T, 0, 105, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, auto_query_values) }, \
         { "hdr_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 106, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, hdr_mode) }, \
         { "use_ros_time", NULL, MAVLINK_TYPE_UINT8_T, 0, 107, offsetof(mavlink_skye_cam_reconfigure_bluefox_settings_t, use_ros_time) }, \
         } \
}


/**
 * @brief Pack a skye_cam_reconfigure_bluefox_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param frame_id ROS tf frame of reference, resolved with tf_prefix unless absolute.
 * @param pixel_clock Pixel clock of image sensor [MHz]. See enum MAV_CAM_RECONFIG_PIXEL_CLOCK
 * @param frame_rate Camera speed (frames per second). Range: 1.0 to 240.0
 * @param camera_info_url Camera calibration URL for this video_mode (uncalibrated if null). 
 * @param binning_x Number of pixels combined for horizontal binning, use device hints if zero. Range: 0 to 4
 * @param binning_y Number of pixels combined for vertical binning, use device hints if zero. Range: 0 to 4
 * @param roi_width Width of Region of Interest in unbinned pixels, full width if zero. Range: 0 to 5000
 * @param roi_height Height of Region of Interest in unbinned pixels, full height if zero. Range: 0 to 5000
 * @param x_offset Horizontal offset for left side of ROI in unbinned pixels. Range: 0 to 5000
 * @param y_offset Vertical offset for top of ROI in unbinned pixels. Range: 0 to 5000
 * @param color_coding Color coding. See enum MAV_CAM_RECONFIG_COLOR_CODING
 * @param bayer_method Bayer decoding method (default: ROS image_proc). See enum MAV_CAM_RECONFIG_BAYER_METHOD
 * @param exposure Auto exposure value . Range: 0 to 255
 * @param shutter_auto boolean. Shutter control state. 
 * @param shutter_auto_min Min shutter time [s] in auto mode. Range: 0.0 to 0.1
 * @param shutter_auto_max Max shutter time [s] in auto mode Range: 0.0 to 0.1
 * @param shutter Shutter time [s]. Range: 0.0 to 0.1
 * @param gain_auto boolean. Gain control state. 
 * @param gain_auto_min Min relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 * @param gain_auto_max Max relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 * @param gain Relative circuit gain [dB]  Range: 0.0 to 12.0
 * @param auto_control_speed Control speed for automatic features. See enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
 * @param auto_query_values boolean. Queries settings that are auto controlled. 
 * @param hdr_mode HDR mode. See enum MAV_CAM_RECONFIG_HDR_MODE
 * @param use_ros_time boolean. Timestamp Image and CameraInfo using ros::Time::now() 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t cam_id, const char *frame_id, float pixel_clock, float frame_rate, const char *camera_info_url, uint8_t binning_x, uint8_t binning_y, uint16_t roi_width, uint16_t roi_height, uint16_t x_offset, uint16_t y_offset, uint8_t color_coding, uint8_t bayer_method, uint8_t exposure, uint8_t shutter_auto, float shutter_auto_min, float shutter_auto_max, float shutter, uint8_t gain_auto, uint8_t gain_auto_min, uint8_t gain_auto_max, uint8_t gain, uint8_t auto_control_speed, uint8_t auto_query_values, uint8_t hdr_mode, uint8_t use_ros_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[108];
	_mav_put_float(buf, 0, pixel_clock);
	_mav_put_float(buf, 4, frame_rate);
	_mav_put_float(buf, 8, shutter_auto_min);
	_mav_put_float(buf, 12, shutter_auto_max);
	_mav_put_float(buf, 16, shutter);
	_mav_put_uint16_t(buf, 20, roi_width);
	_mav_put_uint16_t(buf, 22, roi_height);
	_mav_put_uint16_t(buf, 24, x_offset);
	_mav_put_uint16_t(buf, 26, y_offset);
	_mav_put_uint8_t(buf, 28, target_system);
	_mav_put_uint8_t(buf, 29, cam_id);
	_mav_put_uint8_t(buf, 94, binning_x);
	_mav_put_uint8_t(buf, 95, binning_y);
	_mav_put_uint8_t(buf, 96, color_coding);
	_mav_put_uint8_t(buf, 97, bayer_method);
	_mav_put_uint8_t(buf, 98, exposure);
	_mav_put_uint8_t(buf, 99, shutter_auto);
	_mav_put_uint8_t(buf, 100, gain_auto);
	_mav_put_uint8_t(buf, 101, gain_auto_min);
	_mav_put_uint8_t(buf, 102, gain_auto_max);
	_mav_put_uint8_t(buf, 103, gain);
	_mav_put_uint8_t(buf, 104, auto_control_speed);
	_mav_put_uint8_t(buf, 105, auto_query_values);
	_mav_put_uint8_t(buf, 106, hdr_mode);
	_mav_put_uint8_t(buf, 107, use_ros_time);
	_mav_put_char_array(buf, 30, frame_id, 32);
	_mav_put_char_array(buf, 62, camera_info_url, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 108);
#else
	mavlink_skye_cam_reconfigure_bluefox_settings_t packet;
	packet.pixel_clock = pixel_clock;
	packet.frame_rate = frame_rate;
	packet.shutter_auto_min = shutter_auto_min;
	packet.shutter_auto_max = shutter_auto_max;
	packet.shutter = shutter;
	packet.roi_width = roi_width;
	packet.roi_height = roi_height;
	packet.x_offset = x_offset;
	packet.y_offset = y_offset;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.binning_x = binning_x;
	packet.binning_y = binning_y;
	packet.color_coding = color_coding;
	packet.bayer_method = bayer_method;
	packet.exposure = exposure;
	packet.shutter_auto = shutter_auto;
	packet.gain_auto = gain_auto;
	packet.gain_auto_min = gain_auto_min;
	packet.gain_auto_max = gain_auto_max;
	packet.gain = gain;
	packet.auto_control_speed = auto_control_speed;
	packet.auto_query_values = auto_query_values;
	packet.hdr_mode = hdr_mode;
	packet.use_ros_time = use_ros_time;
	mav_array_memcpy(packet.frame_id, frame_id, sizeof(char)*32);
	mav_array_memcpy(packet.camera_info_url, camera_info_url, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 108);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS;
	return mavlink_finalize_message(msg, system_id, component_id, 108, 147);
}

/**
 * @brief Pack a skye_cam_reconfigure_bluefox_settings message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param frame_id ROS tf frame of reference, resolved with tf_prefix unless absolute.
 * @param pixel_clock Pixel clock of image sensor [MHz]. See enum MAV_CAM_RECONFIG_PIXEL_CLOCK
 * @param frame_rate Camera speed (frames per second). Range: 1.0 to 240.0
 * @param camera_info_url Camera calibration URL for this video_mode (uncalibrated if null). 
 * @param binning_x Number of pixels combined for horizontal binning, use device hints if zero. Range: 0 to 4
 * @param binning_y Number of pixels combined for vertical binning, use device hints if zero. Range: 0 to 4
 * @param roi_width Width of Region of Interest in unbinned pixels, full width if zero. Range: 0 to 5000
 * @param roi_height Height of Region of Interest in unbinned pixels, full height if zero. Range: 0 to 5000
 * @param x_offset Horizontal offset for left side of ROI in unbinned pixels. Range: 0 to 5000
 * @param y_offset Vertical offset for top of ROI in unbinned pixels. Range: 0 to 5000
 * @param color_coding Color coding. See enum MAV_CAM_RECONFIG_COLOR_CODING
 * @param bayer_method Bayer decoding method (default: ROS image_proc). See enum MAV_CAM_RECONFIG_BAYER_METHOD
 * @param exposure Auto exposure value . Range: 0 to 255
 * @param shutter_auto boolean. Shutter control state. 
 * @param shutter_auto_min Min shutter time [s] in auto mode. Range: 0.0 to 0.1
 * @param shutter_auto_max Max shutter time [s] in auto mode Range: 0.0 to 0.1
 * @param shutter Shutter time [s]. Range: 0.0 to 0.1
 * @param gain_auto boolean. Gain control state. 
 * @param gain_auto_min Min relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 * @param gain_auto_max Max relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 * @param gain Relative circuit gain [dB]  Range: 0.0 to 12.0
 * @param auto_control_speed Control speed for automatic features. See enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
 * @param auto_query_values boolean. Queries settings that are auto controlled. 
 * @param hdr_mode HDR mode. See enum MAV_CAM_RECONFIG_HDR_MODE
 * @param use_ros_time boolean. Timestamp Image and CameraInfo using ros::Time::now() 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t cam_id,const char *frame_id,float pixel_clock,float frame_rate,const char *camera_info_url,uint8_t binning_x,uint8_t binning_y,uint16_t roi_width,uint16_t roi_height,uint16_t x_offset,uint16_t y_offset,uint8_t color_coding,uint8_t bayer_method,uint8_t exposure,uint8_t shutter_auto,float shutter_auto_min,float shutter_auto_max,float shutter,uint8_t gain_auto,uint8_t gain_auto_min,uint8_t gain_auto_max,uint8_t gain,uint8_t auto_control_speed,uint8_t auto_query_values,uint8_t hdr_mode,uint8_t use_ros_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[108];
	_mav_put_float(buf, 0, pixel_clock);
	_mav_put_float(buf, 4, frame_rate);
	_mav_put_float(buf, 8, shutter_auto_min);
	_mav_put_float(buf, 12, shutter_auto_max);
	_mav_put_float(buf, 16, shutter);
	_mav_put_uint16_t(buf, 20, roi_width);
	_mav_put_uint16_t(buf, 22, roi_height);
	_mav_put_uint16_t(buf, 24, x_offset);
	_mav_put_uint16_t(buf, 26, y_offset);
	_mav_put_uint8_t(buf, 28, target_system);
	_mav_put_uint8_t(buf, 29, cam_id);
	_mav_put_uint8_t(buf, 94, binning_x);
	_mav_put_uint8_t(buf, 95, binning_y);
	_mav_put_uint8_t(buf, 96, color_coding);
	_mav_put_uint8_t(buf, 97, bayer_method);
	_mav_put_uint8_t(buf, 98, exposure);
	_mav_put_uint8_t(buf, 99, shutter_auto);
	_mav_put_uint8_t(buf, 100, gain_auto);
	_mav_put_uint8_t(buf, 101, gain_auto_min);
	_mav_put_uint8_t(buf, 102, gain_auto_max);
	_mav_put_uint8_t(buf, 103, gain);
	_mav_put_uint8_t(buf, 104, auto_control_speed);
	_mav_put_uint8_t(buf, 105, auto_query_values);
	_mav_put_uint8_t(buf, 106, hdr_mode);
	_mav_put_uint8_t(buf, 107, use_ros_time);
	_mav_put_char_array(buf, 30, frame_id, 32);
	_mav_put_char_array(buf, 62, camera_info_url, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 108);
#else
	mavlink_skye_cam_reconfigure_bluefox_settings_t packet;
	packet.pixel_clock = pixel_clock;
	packet.frame_rate = frame_rate;
	packet.shutter_auto_min = shutter_auto_min;
	packet.shutter_auto_max = shutter_auto_max;
	packet.shutter = shutter;
	packet.roi_width = roi_width;
	packet.roi_height = roi_height;
	packet.x_offset = x_offset;
	packet.y_offset = y_offset;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.binning_x = binning_x;
	packet.binning_y = binning_y;
	packet.color_coding = color_coding;
	packet.bayer_method = bayer_method;
	packet.exposure = exposure;
	packet.shutter_auto = shutter_auto;
	packet.gain_auto = gain_auto;
	packet.gain_auto_min = gain_auto_min;
	packet.gain_auto_max = gain_auto_max;
	packet.gain = gain;
	packet.auto_control_speed = auto_control_speed;
	packet.auto_query_values = auto_query_values;
	packet.hdr_mode = hdr_mode;
	packet.use_ros_time = use_ros_time;
	mav_array_memcpy(packet.frame_id, frame_id, sizeof(char)*32);
	mav_array_memcpy(packet.camera_info_url, camera_info_url, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 108);
#endif

	msg->msgid = MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 108, 147);
}

/**
 * @brief Encode a skye_cam_reconfigure_bluefox_settings struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param skye_cam_reconfigure_bluefox_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_skye_cam_reconfigure_bluefox_settings_t* skye_cam_reconfigure_bluefox_settings)
{
	return mavlink_msg_skye_cam_reconfigure_bluefox_settings_pack(system_id, component_id, msg, skye_cam_reconfigure_bluefox_settings->target_system, skye_cam_reconfigure_bluefox_settings->cam_id, skye_cam_reconfigure_bluefox_settings->frame_id, skye_cam_reconfigure_bluefox_settings->pixel_clock, skye_cam_reconfigure_bluefox_settings->frame_rate, skye_cam_reconfigure_bluefox_settings->camera_info_url, skye_cam_reconfigure_bluefox_settings->binning_x, skye_cam_reconfigure_bluefox_settings->binning_y, skye_cam_reconfigure_bluefox_settings->roi_width, skye_cam_reconfigure_bluefox_settings->roi_height, skye_cam_reconfigure_bluefox_settings->x_offset, skye_cam_reconfigure_bluefox_settings->y_offset, skye_cam_reconfigure_bluefox_settings->color_coding, skye_cam_reconfigure_bluefox_settings->bayer_method, skye_cam_reconfigure_bluefox_settings->exposure, skye_cam_reconfigure_bluefox_settings->shutter_auto, skye_cam_reconfigure_bluefox_settings->shutter_auto_min, skye_cam_reconfigure_bluefox_settings->shutter_auto_max, skye_cam_reconfigure_bluefox_settings->shutter, skye_cam_reconfigure_bluefox_settings->gain_auto, skye_cam_reconfigure_bluefox_settings->gain_auto_min, skye_cam_reconfigure_bluefox_settings->gain_auto_max, skye_cam_reconfigure_bluefox_settings->gain, skye_cam_reconfigure_bluefox_settings->auto_control_speed, skye_cam_reconfigure_bluefox_settings->auto_query_values, skye_cam_reconfigure_bluefox_settings->hdr_mode, skye_cam_reconfigure_bluefox_settings->use_ros_time);
}

/**
 * @brief Send a skye_cam_reconfigure_bluefox_settings message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param cam_id ID of camera, see ENUM MAV_CAM_ID
 * @param frame_id ROS tf frame of reference, resolved with tf_prefix unless absolute.
 * @param pixel_clock Pixel clock of image sensor [MHz]. See enum MAV_CAM_RECONFIG_PIXEL_CLOCK
 * @param frame_rate Camera speed (frames per second). Range: 1.0 to 240.0
 * @param camera_info_url Camera calibration URL for this video_mode (uncalibrated if null). 
 * @param binning_x Number of pixels combined for horizontal binning, use device hints if zero. Range: 0 to 4
 * @param binning_y Number of pixels combined for vertical binning, use device hints if zero. Range: 0 to 4
 * @param roi_width Width of Region of Interest in unbinned pixels, full width if zero. Range: 0 to 5000
 * @param roi_height Height of Region of Interest in unbinned pixels, full height if zero. Range: 0 to 5000
 * @param x_offset Horizontal offset for left side of ROI in unbinned pixels. Range: 0 to 5000
 * @param y_offset Vertical offset for top of ROI in unbinned pixels. Range: 0 to 5000
 * @param color_coding Color coding. See enum MAV_CAM_RECONFIG_COLOR_CODING
 * @param bayer_method Bayer decoding method (default: ROS image_proc). See enum MAV_CAM_RECONFIG_BAYER_METHOD
 * @param exposure Auto exposure value . Range: 0 to 255
 * @param shutter_auto boolean. Shutter control state. 
 * @param shutter_auto_min Min shutter time [s] in auto mode. Range: 0.0 to 0.1
 * @param shutter_auto_max Max shutter time [s] in auto mode Range: 0.0 to 0.1
 * @param shutter Shutter time [s]. Range: 0.0 to 0.1
 * @param gain_auto boolean. Gain control state. 
 * @param gain_auto_min Min relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 * @param gain_auto_max Max relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 * @param gain Relative circuit gain [dB]  Range: 0.0 to 12.0
 * @param auto_control_speed Control speed for automatic features. See enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
 * @param auto_query_values boolean. Queries settings that are auto controlled. 
 * @param hdr_mode HDR mode. See enum MAV_CAM_RECONFIG_HDR_MODE
 * @param use_ros_time boolean. Timestamp Image and CameraInfo using ros::Time::now() 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_skye_cam_reconfigure_bluefox_settings_send(mavlink_channel_t chan, uint8_t target_system, uint8_t cam_id, const char *frame_id, float pixel_clock, float frame_rate, const char *camera_info_url, uint8_t binning_x, uint8_t binning_y, uint16_t roi_width, uint16_t roi_height, uint16_t x_offset, uint16_t y_offset, uint8_t color_coding, uint8_t bayer_method, uint8_t exposure, uint8_t shutter_auto, float shutter_auto_min, float shutter_auto_max, float shutter, uint8_t gain_auto, uint8_t gain_auto_min, uint8_t gain_auto_max, uint8_t gain, uint8_t auto_control_speed, uint8_t auto_query_values, uint8_t hdr_mode, uint8_t use_ros_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[108];
	_mav_put_float(buf, 0, pixel_clock);
	_mav_put_float(buf, 4, frame_rate);
	_mav_put_float(buf, 8, shutter_auto_min);
	_mav_put_float(buf, 12, shutter_auto_max);
	_mav_put_float(buf, 16, shutter);
	_mav_put_uint16_t(buf, 20, roi_width);
	_mav_put_uint16_t(buf, 22, roi_height);
	_mav_put_uint16_t(buf, 24, x_offset);
	_mav_put_uint16_t(buf, 26, y_offset);
	_mav_put_uint8_t(buf, 28, target_system);
	_mav_put_uint8_t(buf, 29, cam_id);
	_mav_put_uint8_t(buf, 94, binning_x);
	_mav_put_uint8_t(buf, 95, binning_y);
	_mav_put_uint8_t(buf, 96, color_coding);
	_mav_put_uint8_t(buf, 97, bayer_method);
	_mav_put_uint8_t(buf, 98, exposure);
	_mav_put_uint8_t(buf, 99, shutter_auto);
	_mav_put_uint8_t(buf, 100, gain_auto);
	_mav_put_uint8_t(buf, 101, gain_auto_min);
	_mav_put_uint8_t(buf, 102, gain_auto_max);
	_mav_put_uint8_t(buf, 103, gain);
	_mav_put_uint8_t(buf, 104, auto_control_speed);
	_mav_put_uint8_t(buf, 105, auto_query_values);
	_mav_put_uint8_t(buf, 106, hdr_mode);
	_mav_put_uint8_t(buf, 107, use_ros_time);
	_mav_put_char_array(buf, 30, frame_id, 32);
	_mav_put_char_array(buf, 62, camera_info_url, 32);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS, buf, 108, 147);
#else
	mavlink_skye_cam_reconfigure_bluefox_settings_t packet;
	packet.pixel_clock = pixel_clock;
	packet.frame_rate = frame_rate;
	packet.shutter_auto_min = shutter_auto_min;
	packet.shutter_auto_max = shutter_auto_max;
	packet.shutter = shutter;
	packet.roi_width = roi_width;
	packet.roi_height = roi_height;
	packet.x_offset = x_offset;
	packet.y_offset = y_offset;
	packet.target_system = target_system;
	packet.cam_id = cam_id;
	packet.binning_x = binning_x;
	packet.binning_y = binning_y;
	packet.color_coding = color_coding;
	packet.bayer_method = bayer_method;
	packet.exposure = exposure;
	packet.shutter_auto = shutter_auto;
	packet.gain_auto = gain_auto;
	packet.gain_auto_min = gain_auto_min;
	packet.gain_auto_max = gain_auto_max;
	packet.gain = gain;
	packet.auto_control_speed = auto_control_speed;
	packet.auto_query_values = auto_query_values;
	packet.hdr_mode = hdr_mode;
	packet.use_ros_time = use_ros_time;
	mav_array_memcpy(packet.frame_id, frame_id, sizeof(char)*32);
	mav_array_memcpy(packet.camera_info_url, camera_info_url, sizeof(char)*32);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS, (const char *)&packet, 108, 147);
#endif
}

#endif

// MESSAGE SKYE_CAM_RECONFIGURE_BLUEFOX_SETTINGS UNPACKING


/**
 * @brief Get field target_system from skye_cam_reconfigure_bluefox_settings message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field cam_id from skye_cam_reconfigure_bluefox_settings message
 *
 * @return ID of camera, see ENUM MAV_CAM_ID
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_cam_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  29);
}

/**
 * @brief Get field frame_id from skye_cam_reconfigure_bluefox_settings message
 *
 * @return ROS tf frame of reference, resolved with tf_prefix unless absolute.
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_frame_id(const mavlink_message_t* msg, char *frame_id)
{
	return _MAV_RETURN_char_array(msg, frame_id, 32,  30);
}

/**
 * @brief Get field pixel_clock from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Pixel clock of image sensor [MHz]. See enum MAV_CAM_RECONFIG_PIXEL_CLOCK
 */
static inline float mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_pixel_clock(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field frame_rate from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Camera speed (frames per second). Range: 1.0 to 240.0
 */
static inline float mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_frame_rate(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field camera_info_url from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Camera calibration URL for this video_mode (uncalibrated if null). 
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_camera_info_url(const mavlink_message_t* msg, char *camera_info_url)
{
	return _MAV_RETURN_char_array(msg, camera_info_url, 32,  62);
}

/**
 * @brief Get field binning_x from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Number of pixels combined for horizontal binning, use device hints if zero. Range: 0 to 4
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_binning_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  94);
}

/**
 * @brief Get field binning_y from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Number of pixels combined for vertical binning, use device hints if zero. Range: 0 to 4
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_binning_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  95);
}

/**
 * @brief Get field roi_width from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Width of Region of Interest in unbinned pixels, full width if zero. Range: 0 to 5000
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_roi_width(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field roi_height from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Height of Region of Interest in unbinned pixels, full height if zero. Range: 0 to 5000
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_roi_height(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Get field x_offset from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Horizontal offset for left side of ROI in unbinned pixels. Range: 0 to 5000
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_x_offset(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field y_offset from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Vertical offset for top of ROI in unbinned pixels. Range: 0 to 5000
 */
static inline uint16_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_y_offset(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  26);
}

/**
 * @brief Get field color_coding from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Color coding. See enum MAV_CAM_RECONFIG_COLOR_CODING
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_color_coding(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  96);
}

/**
 * @brief Get field bayer_method from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Bayer decoding method (default: ROS image_proc). See enum MAV_CAM_RECONFIG_BAYER_METHOD
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_bayer_method(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  97);
}

/**
 * @brief Get field exposure from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Auto exposure value . Range: 0 to 255
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_exposure(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  98);
}

/**
 * @brief Get field shutter_auto from skye_cam_reconfigure_bluefox_settings message
 *
 * @return boolean. Shutter control state. 
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter_auto(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  99);
}

/**
 * @brief Get field shutter_auto_min from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Min shutter time [s] in auto mode. Range: 0.0 to 0.1
 */
static inline float mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter_auto_min(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field shutter_auto_max from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Max shutter time [s] in auto mode Range: 0.0 to 0.1
 */
static inline float mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter_auto_max(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field shutter from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Shutter time [s]. Range: 0.0 to 0.1
 */
static inline float mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field gain_auto from skye_cam_reconfigure_bluefox_settings message
 *
 * @return boolean. Gain control state. 
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain_auto(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  100);
}

/**
 * @brief Get field gain_auto_min from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Min relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain_auto_min(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  101);
}

/**
 * @brief Get field gain_auto_max from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Max relative circuit gain [dB] in auto mode. Range: 0.0 to 12.0
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain_auto_max(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  102);
}

/**
 * @brief Get field gain from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Relative circuit gain [dB]  Range: 0.0 to 12.0
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  103);
}

/**
 * @brief Get field auto_control_speed from skye_cam_reconfigure_bluefox_settings message
 *
 * @return Control speed for automatic features. See enum MAV_CAM_RECONFIG_AUTO_CONTROL_SPEED
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_auto_control_speed(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  104);
}

/**
 * @brief Get field auto_query_values from skye_cam_reconfigure_bluefox_settings message
 *
 * @return boolean. Queries settings that are auto controlled. 
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_auto_query_values(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  105);
}

/**
 * @brief Get field hdr_mode from skye_cam_reconfigure_bluefox_settings message
 *
 * @return HDR mode. See enum MAV_CAM_RECONFIG_HDR_MODE
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_hdr_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  106);
}

/**
 * @brief Get field use_ros_time from skye_cam_reconfigure_bluefox_settings message
 *
 * @return boolean. Timestamp Image and CameraInfo using ros::Time::now() 
 */
static inline uint8_t mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_use_ros_time(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  107);
}

/**
 * @brief Decode a skye_cam_reconfigure_bluefox_settings message into a struct
 *
 * @param msg The message to decode
 * @param skye_cam_reconfigure_bluefox_settings C-struct to decode the message contents into
 */
static inline void mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(const mavlink_message_t* msg, mavlink_skye_cam_reconfigure_bluefox_settings_t* skye_cam_reconfigure_bluefox_settings)
{
#if MAVLINK_NEED_BYTE_SWAP
	skye_cam_reconfigure_bluefox_settings->pixel_clock = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_pixel_clock(msg);
	skye_cam_reconfigure_bluefox_settings->frame_rate = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_frame_rate(msg);
	skye_cam_reconfigure_bluefox_settings->shutter_auto_min = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter_auto_min(msg);
	skye_cam_reconfigure_bluefox_settings->shutter_auto_max = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter_auto_max(msg);
	skye_cam_reconfigure_bluefox_settings->shutter = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter(msg);
	skye_cam_reconfigure_bluefox_settings->roi_width = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_roi_width(msg);
	skye_cam_reconfigure_bluefox_settings->roi_height = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_roi_height(msg);
	skye_cam_reconfigure_bluefox_settings->x_offset = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_x_offset(msg);
	skye_cam_reconfigure_bluefox_settings->y_offset = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_y_offset(msg);
	skye_cam_reconfigure_bluefox_settings->target_system = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_target_system(msg);
	skye_cam_reconfigure_bluefox_settings->cam_id = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_cam_id(msg);
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_frame_id(msg, skye_cam_reconfigure_bluefox_settings->frame_id);
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_camera_info_url(msg, skye_cam_reconfigure_bluefox_settings->camera_info_url);
	skye_cam_reconfigure_bluefox_settings->binning_x = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_binning_x(msg);
	skye_cam_reconfigure_bluefox_settings->binning_y = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_binning_y(msg);
	skye_cam_reconfigure_bluefox_settings->color_coding = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_color_coding(msg);
	skye_cam_reconfigure_bluefox_settings->bayer_method = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_bayer_method(msg);
	skye_cam_reconfigure_bluefox_settings->exposure = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_exposure(msg);
	skye_cam_reconfigure_bluefox_settings->shutter_auto = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_shutter_auto(msg);
	skye_cam_reconfigure_bluefox_settings->gain_auto = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain_auto(msg);
	skye_cam_reconfigure_bluefox_settings->gain_auto_min = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain_auto_min(msg);
	skye_cam_reconfigure_bluefox_settings->gain_auto_max = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain_auto_max(msg);
	skye_cam_reconfigure_bluefox_settings->gain = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_gain(msg);
	skye_cam_reconfigure_bluefox_settings->auto_control_speed = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_auto_control_speed(msg);
	skye_cam_reconfigure_bluefox_settings->auto_query_values = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_auto_query_values(msg);
	skye_cam_reconfigure_bluefox_settings->hdr_mode = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_hdr_mode(msg);
	skye_cam_reconfigure_bluefox_settings->use_ros_time = mavlink_msg_skye_cam_reconfigure_bluefox_settings_get_use_ros_time(msg);
#else
	memcpy(skye_cam_reconfigure_bluefox_settings, _MAV_PAYLOAD(msg), 108);
#endif
}
