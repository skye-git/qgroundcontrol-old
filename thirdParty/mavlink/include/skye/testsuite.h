/** @file
 *	@brief MAVLink comm protocol testsuite generated from skye.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef SKYE_TESTSUITE_H
#define SKYE_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_skye(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_skye(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_test_motors(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_test_motors_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	129.0,
	157.0,
	185.0,
	213.0,
	101,
	};
	mavlink_test_motors_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.thrust_1 = packet_in.thrust_1;
        	packet1.thrust_2 = packet_in.thrust_2;
        	packet1.thrust_3 = packet_in.thrust_3;
        	packet1.thrust_4 = packet_in.thrust_4;
        	packet1.direct_1 = packet_in.direct_1;
        	packet1.direct_2 = packet_in.direct_2;
        	packet1.direct_3 = packet_in.direct_3;
        	packet1.direct_4 = packet_in.direct_4;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_test_motors_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_test_motors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_test_motors_pack(system_id, component_id, &msg , packet1.target_system , packet1.thrust_1 , packet1.thrust_2 , packet1.thrust_3 , packet1.thrust_4 , packet1.direct_1 , packet1.direct_2 , packet1.direct_3 , packet1.direct_4 );
	mavlink_msg_test_motors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_test_motors_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.thrust_1 , packet1.thrust_2 , packet1.thrust_3 , packet1.thrust_4 , packet1.direct_1 , packet1.direct_2 , packet1.direct_3 , packet1.direct_4 );
	mavlink_msg_test_motors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_test_motors_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_test_motors_send(MAVLINK_COMM_1 , packet1.target_system , packet1.thrust_1 , packet1.thrust_2 , packet1.thrust_3 , packet1.thrust_4 , packet1.direct_1 , packet1.direct_2 , packet1.direct_3 , packet1.direct_4 );
	mavlink_msg_test_motors_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_direct_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_direct_control_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	129.0,
	157.0,
	77,
	};
	mavlink_direct_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.thrust_x = packet_in.thrust_x;
        	packet1.thrust_y = packet_in.thrust_y;
        	packet1.thrust_z = packet_in.thrust_z;
        	packet1.moment_x = packet_in.moment_x;
        	packet1.moment_y = packet_in.moment_y;
        	packet1.moment_z = packet_in.moment_z;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_direct_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_direct_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_direct_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.thrust_x , packet1.thrust_y , packet1.thrust_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_direct_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_direct_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.thrust_x , packet1.thrust_y , packet1.thrust_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_direct_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_direct_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_direct_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.thrust_x , packet1.thrust_y , packet1.thrust_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_direct_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_assisted_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_assisted_control_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	129.0,
	157.0,
	77,
	};
	mavlink_assisted_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.translation_x = packet_in.translation_x;
        	packet1.translation_y = packet_in.translation_y;
        	packet1.translation_z = packet_in.translation_z;
        	packet1.rotation_x = packet_in.rotation_x;
        	packet1.rotation_y = packet_in.rotation_y;
        	packet1.rotation_z = packet_in.rotation_z;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_assisted_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.translation_x , packet1.translation_y , packet1.translation_z , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_assisted_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.translation_x , packet1.translation_y , packet1.translation_z , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_assisted_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_assisted_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.translation_x , packet1.translation_y , packet1.translation_z , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_assisted_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_assisted_rc_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_assisted_rc_control_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	53,
	};
	mavlink_assisted_rc_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.translation_x = packet_in.translation_x;
        	packet1.rotation_x = packet_in.rotation_x;
        	packet1.rotation_y = packet_in.rotation_y;
        	packet1.rotation_z = packet_in.rotation_z;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_rc_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_assisted_rc_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_rc_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.translation_x , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_assisted_rc_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_rc_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.translation_x , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_assisted_rc_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_assisted_rc_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_assisted_rc_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.translation_x , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_assisted_rc_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_cam_reconfigure_bluefox(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_cam_reconfigure_bluefox_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	129.0,
	18275,
	18379,
	18483,
	18587,
	89,
	156,
	"EFGHIJKLMNOPQRSTUVWXYZABCDEFGHI",
	"KLMNOPQRSTUVWXYZABCDEFGHIJKLMNO",
	"QRSTUVWXYZABCDEFGHIJKLMNOPQRSTU",
	255,
	66,
	133,
	200,
	11,
	78,
	145,
	212,
	23,
	90,
	157,
	224,
	35,
	102,
	};
	mavlink_cam_reconfigure_bluefox_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.pixel_clock = packet_in.pixel_clock;
        	packet1.frame_rate = packet_in.frame_rate;
        	packet1.shutter_auto_min = packet_in.shutter_auto_min;
        	packet1.shutter_auto_max = packet_in.shutter_auto_max;
        	packet1.shutter = packet_in.shutter;
        	packet1.roi_width = packet_in.roi_width;
        	packet1.roi_height = packet_in.roi_height;
        	packet1.x_offset = packet_in.x_offset;
        	packet1.y_offset = packet_in.y_offset;
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.binning_x = packet_in.binning_x;
        	packet1.binning_y = packet_in.binning_y;
        	packet1.color_coding = packet_in.color_coding;
        	packet1.bayer_method = packet_in.bayer_method;
        	packet1.exposure = packet_in.exposure;
        	packet1.shutter_auto = packet_in.shutter_auto;
        	packet1.gain_auto = packet_in.gain_auto;
        	packet1.gain_auto_min = packet_in.gain_auto_min;
        	packet1.gain_auto_max = packet_in.gain_auto_max;
        	packet1.gain = packet_in.gain;
        	packet1.auto_control_speed = packet_in.auto_control_speed;
        	packet1.auto_query_values = packet_in.auto_query_values;
        	packet1.hdr_mode = packet_in.hdr_mode;
        	packet1.use_ros_time = packet_in.use_ros_time;
        
        	mav_array_memcpy(packet1.guid, packet_in.guid, sizeof(char)*32);
        	mav_array_memcpy(packet1.frame_id, packet_in.frame_id, sizeof(char)*32);
        	mav_array_memcpy(packet1.camera_info_url, packet_in.camera_info_url, sizeof(char)*32);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_cam_reconfigure_bluefox_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_cam_reconfigure_bluefox_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_cam_reconfigure_bluefox_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.guid , packet1.frame_id , packet1.pixel_clock , packet1.frame_rate , packet1.camera_info_url , packet1.binning_x , packet1.binning_y , packet1.roi_width , packet1.roi_height , packet1.x_offset , packet1.y_offset , packet1.color_coding , packet1.bayer_method , packet1.exposure , packet1.shutter_auto , packet1.shutter_auto_min , packet1.shutter_auto_max , packet1.shutter , packet1.gain_auto , packet1.gain_auto_min , packet1.gain_auto_max , packet1.gain , packet1.auto_control_speed , packet1.auto_query_values , packet1.hdr_mode , packet1.use_ros_time );
	mavlink_msg_cam_reconfigure_bluefox_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_cam_reconfigure_bluefox_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.guid , packet1.frame_id , packet1.pixel_clock , packet1.frame_rate , packet1.camera_info_url , packet1.binning_x , packet1.binning_y , packet1.roi_width , packet1.roi_height , packet1.x_offset , packet1.y_offset , packet1.color_coding , packet1.bayer_method , packet1.exposure , packet1.shutter_auto , packet1.shutter_auto_min , packet1.shutter_auto_max , packet1.shutter , packet1.gain_auto , packet1.gain_auto_min , packet1.gain_auto_max , packet1.gain , packet1.auto_control_speed , packet1.auto_query_values , packet1.hdr_mode , packet1.use_ros_time );
	mavlink_msg_cam_reconfigure_bluefox_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_cam_reconfigure_bluefox_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_cam_reconfigure_bluefox_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.guid , packet1.frame_id , packet1.pixel_clock , packet1.frame_rate , packet1.camera_info_url , packet1.binning_x , packet1.binning_y , packet1.roi_width , packet1.roi_height , packet1.x_offset , packet1.y_offset , packet1.color_coding , packet1.bayer_method , packet1.exposure , packet1.shutter_auto , packet1.shutter_auto_min , packet1.shutter_auto_max , packet1.shutter , packet1.gain_auto , packet1.gain_auto_min , packet1.gain_auto_max , packet1.gain , packet1.auto_control_speed , packet1.auto_query_values , packet1.hdr_mode , packet1.use_ros_time );
	mavlink_msg_cam_reconfigure_bluefox_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_test_motors(system_id, component_id, last_msg);
	mavlink_test_direct_control(system_id, component_id, last_msg);
	mavlink_test_assisted_control(system_id, component_id, last_msg);
	mavlink_test_assisted_rc_control(system_id, component_id, last_msg);
	mavlink_test_cam_reconfigure_bluefox(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SKYE_TESTSUITE_H
