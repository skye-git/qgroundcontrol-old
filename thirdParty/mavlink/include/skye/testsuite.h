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


static void mavlink_test_skye_battery_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_battery_status_t packet_in = {
		17235,
	17339,
	17443,
	17547,
	17651,
	163,
	230,
	};
	mavlink_skye_battery_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_cell_1 = packet_in.voltage_cell_1;
        	packet1.voltage_cell_2 = packet_in.voltage_cell_2;
        	packet1.voltage_cell_3 = packet_in.voltage_cell_3;
        	packet1.voltage_cell_4 = packet_in.voltage_cell_4;
        	packet1.current_battery = packet_in.current_battery;
        	packet1.accu_id = packet_in.accu_id;
        	packet1.battery_remaining = packet_in.battery_remaining;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_battery_status_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_battery_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_battery_status_pack(system_id, component_id, &msg , packet1.accu_id , packet1.voltage_cell_1 , packet1.voltage_cell_2 , packet1.voltage_cell_3 , packet1.voltage_cell_4 , packet1.current_battery , packet1.battery_remaining );
	mavlink_msg_skye_battery_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_battery_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.accu_id , packet1.voltage_cell_1 , packet1.voltage_cell_2 , packet1.voltage_cell_3 , packet1.voltage_cell_4 , packet1.current_battery , packet1.battery_remaining );
	mavlink_msg_skye_battery_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_battery_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_battery_status_send(MAVLINK_COMM_1 , packet1.accu_id , packet1.voltage_cell_1 , packet1.voltage_cell_2 , packet1.voltage_cell_3 , packet1.voltage_cell_4 , packet1.current_battery , packet1.battery_remaining );
	mavlink_msg_skye_battery_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_test_motors(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_test_motors_t packet_in = {
		963497464,
	963497672,
	963497880,
	963498088,
	53,
	120,
	187,
	254,
	65,
	};
	mavlink_skye_test_motors_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.direct_1 = packet_in.direct_1;
        	packet1.direct_2 = packet_in.direct_2;
        	packet1.direct_3 = packet_in.direct_3;
        	packet1.direct_4 = packet_in.direct_4;
        	packet1.target_system = packet_in.target_system;
        	packet1.thrust_1 = packet_in.thrust_1;
        	packet1.thrust_2 = packet_in.thrust_2;
        	packet1.thrust_3 = packet_in.thrust_3;
        	packet1.thrust_4 = packet_in.thrust_4;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_test_motors_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_test_motors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_test_motors_pack(system_id, component_id, &msg , packet1.target_system , packet1.thrust_1 , packet1.thrust_2 , packet1.thrust_3 , packet1.thrust_4 , packet1.direct_1 , packet1.direct_2 , packet1.direct_3 , packet1.direct_4 );
	mavlink_msg_skye_test_motors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_test_motors_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.thrust_1 , packet1.thrust_2 , packet1.thrust_3 , packet1.thrust_4 , packet1.direct_1 , packet1.direct_2 , packet1.direct_3 , packet1.direct_4 );
	mavlink_msg_skye_test_motors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_test_motors_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_test_motors_send(MAVLINK_COMM_1 , packet1.target_system , packet1.thrust_1 , packet1.thrust_2 , packet1.thrust_3 , packet1.thrust_4 , packet1.direct_1 , packet1.direct_2 , packet1.direct_3 , packet1.direct_4 );
	mavlink_msg_skye_test_motors_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_direct_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_direct_control_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	129.0,
	157.0,
	77,
	};
	mavlink_skye_direct_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.thrust_x = packet_in.thrust_x;
        	packet1.thrust_y = packet_in.thrust_y;
        	packet1.thrust_z = packet_in.thrust_z;
        	packet1.moment_x = packet_in.moment_x;
        	packet1.moment_y = packet_in.moment_y;
        	packet1.moment_z = packet_in.moment_z;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_direct_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_direct_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_direct_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.thrust_x , packet1.thrust_y , packet1.thrust_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_skye_direct_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_direct_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.thrust_x , packet1.thrust_y , packet1.thrust_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_skye_direct_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_direct_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_direct_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.thrust_x , packet1.thrust_y , packet1.thrust_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_skye_direct_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_assisted_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_assisted_control_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	129.0,
	157.0,
	77,
	};
	mavlink_skye_assisted_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.translation_lat = packet_in.translation_lat;
        	packet1.translation_long = packet_in.translation_long;
        	packet1.translation_alt = packet_in.translation_alt;
        	packet1.rotation_x = packet_in.rotation_x;
        	packet1.rotation_y = packet_in.rotation_y;
        	packet1.rotation_z = packet_in.rotation_z;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_assisted_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.translation_lat , packet1.translation_long , packet1.translation_alt , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_skye_assisted_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.translation_lat , packet1.translation_long , packet1.translation_alt , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_skye_assisted_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_assisted_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.translation_lat , packet1.translation_long , packet1.translation_alt , packet1.rotation_x , packet1.rotation_y , packet1.rotation_z );
	mavlink_msg_skye_assisted_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_assisted_rc_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_assisted_rc_control_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	53,
	};
	mavlink_skye_assisted_rc_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.translation_lat = packet_in.translation_lat;
        	packet1.translation_long = packet_in.translation_long;
        	packet1.translation_alt = packet_in.translation_alt;
        	packet1.rotation_z = packet_in.rotation_z;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_rc_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_assisted_rc_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_rc_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.translation_lat , packet1.translation_long , packet1.translation_alt , packet1.rotation_z );
	mavlink_msg_skye_assisted_rc_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_rc_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.translation_lat , packet1.translation_long , packet1.translation_alt , packet1.rotation_z );
	mavlink_msg_skye_assisted_rc_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_assisted_rc_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_assisted_rc_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.translation_lat , packet1.translation_long , packet1.translation_alt , packet1.rotation_z );
	mavlink_msg_skye_assisted_rc_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_scaled_pressure(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_scaled_pressure_t packet_in = {
		963497464,
	45.0,
	73.0,
	101.0,
	129.0,
	157.0,
	185.0,
	213.0,
	241.0,
	269.0,
	297.0,
	325.0,
	353.0,
	381.0,
	409.0,
	437.0,
	465.0,
	20771,
	};
	mavlink_skye_scaled_pressure_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_boot_ms = packet_in.time_boot_ms;
        	packet1.press_abs1 = packet_in.press_abs1;
        	packet1.press_diff11 = packet_in.press_diff11;
        	packet1.press_diff12 = packet_in.press_diff12;
        	packet1.press_diff13 = packet_in.press_diff13;
        	packet1.press_abs2 = packet_in.press_abs2;
        	packet1.press_diff21 = packet_in.press_diff21;
        	packet1.press_diff22 = packet_in.press_diff22;
        	packet1.press_diff23 = packet_in.press_diff23;
        	packet1.press_abs3 = packet_in.press_abs3;
        	packet1.press_diff31 = packet_in.press_diff31;
        	packet1.press_diff32 = packet_in.press_diff32;
        	packet1.press_diff33 = packet_in.press_diff33;
        	packet1.press_abs4 = packet_in.press_abs4;
        	packet1.press_diff41 = packet_in.press_diff41;
        	packet1.press_diff42 = packet_in.press_diff42;
        	packet1.press_diff43 = packet_in.press_diff43;
        	packet1.temperature = packet_in.temperature;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_scaled_pressure_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_scaled_pressure_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_scaled_pressure_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.press_abs1 , packet1.press_diff11 , packet1.press_diff12 , packet1.press_diff13 , packet1.press_abs2 , packet1.press_diff21 , packet1.press_diff22 , packet1.press_diff23 , packet1.press_abs3 , packet1.press_diff31 , packet1.press_diff32 , packet1.press_diff33 , packet1.press_abs4 , packet1.press_diff41 , packet1.press_diff42 , packet1.press_diff43 , packet1.temperature );
	mavlink_msg_skye_scaled_pressure_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_scaled_pressure_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.press_abs1 , packet1.press_diff11 , packet1.press_diff12 , packet1.press_diff13 , packet1.press_abs2 , packet1.press_diff21 , packet1.press_diff22 , packet1.press_diff23 , packet1.press_abs3 , packet1.press_diff31 , packet1.press_diff32 , packet1.press_diff33 , packet1.press_abs4 , packet1.press_diff41 , packet1.press_diff42 , packet1.press_diff43 , packet1.temperature );
	mavlink_msg_skye_scaled_pressure_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_scaled_pressure_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_scaled_pressure_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.press_abs1 , packet1.press_diff11 , packet1.press_diff12 , packet1.press_diff13 , packet1.press_abs2 , packet1.press_diff21 , packet1.press_diff22 , packet1.press_diff23 , packet1.press_abs3 , packet1.press_diff31 , packet1.press_diff32 , packet1.press_diff33 , packet1.press_abs4 , packet1.press_diff41 , packet1.press_diff42 , packet1.press_diff43 , packet1.temperature );
	mavlink_msg_skye_scaled_pressure_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_motor_signal(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_motor_signal_t packet_in = {
		963497464,
	17443,
	17547,
	17651,
	17755,
	17859,
	17963,
	18067,
	18171,
	};
	mavlink_skye_motor_signal_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_usec = packet_in.time_usec;
        	packet1.thrust1_raw = packet_in.thrust1_raw;
        	packet1.thrust2_raw = packet_in.thrust2_raw;
        	packet1.thrust3_raw = packet_in.thrust3_raw;
        	packet1.thrust4_raw = packet_in.thrust4_raw;
        	packet1.position1_raw = packet_in.position1_raw;
        	packet1.position2_raw = packet_in.position2_raw;
        	packet1.position3_raw = packet_in.position3_raw;
        	packet1.position4_raw = packet_in.position4_raw;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_signal_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_motor_signal_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_signal_pack(system_id, component_id, &msg , packet1.time_usec , packet1.thrust1_raw , packet1.thrust2_raw , packet1.thrust3_raw , packet1.thrust4_raw , packet1.position1_raw , packet1.position2_raw , packet1.position3_raw , packet1.position4_raw );
	mavlink_msg_skye_motor_signal_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_signal_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.thrust1_raw , packet1.thrust2_raw , packet1.thrust3_raw , packet1.thrust4_raw , packet1.position1_raw , packet1.position2_raw , packet1.position3_raw , packet1.position4_raw );
	mavlink_msg_skye_motor_signal_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_motor_signal_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_signal_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.thrust1_raw , packet1.thrust2_raw , packet1.thrust3_raw , packet1.thrust4_raw , packet1.position1_raw , packet1.position2_raw , packet1.position3_raw , packet1.position4_raw );
	mavlink_msg_skye_motor_signal_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_motor_meassured_position(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_motor_meassured_position_t packet_in = {
		963497464,
	17443,
	17547,
	17651,
	17755,
	};
	mavlink_skye_motor_meassured_position_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_usec = packet_in.time_usec;
        	packet1.pos1_raw = packet_in.pos1_raw;
        	packet1.pos2_raw = packet_in.pos2_raw;
        	packet1.pos3_raw = packet_in.pos3_raw;
        	packet1.pos4_raw = packet_in.pos4_raw;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_meassured_position_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_motor_meassured_position_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_meassured_position_pack(system_id, component_id, &msg , packet1.time_usec , packet1.pos1_raw , packet1.pos2_raw , packet1.pos3_raw , packet1.pos4_raw );
	mavlink_msg_skye_motor_meassured_position_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_meassured_position_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.pos1_raw , packet1.pos2_raw , packet1.pos3_raw , packet1.pos4_raw );
	mavlink_msg_skye_motor_meassured_position_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_motor_meassured_position_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_motor_meassured_position_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.pos1_raw , packet1.pos2_raw , packet1.pos3_raw , packet1.pos4_raw );
	mavlink_msg_skye_motor_meassured_position_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_controller_output(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_controller_output_t packet_in = {
		963497464,
	17443,
	17547,
	17651,
	17755,
	17859,
	17963,
	};
	mavlink_skye_controller_output_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.time_usec = packet_in.time_usec;
        	packet1.force_x = packet_in.force_x;
        	packet1.force_y = packet_in.force_y;
        	packet1.force_z = packet_in.force_z;
        	packet1.moment_x = packet_in.moment_x;
        	packet1.moment_y = packet_in.moment_y;
        	packet1.moment_z = packet_in.moment_z;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_controller_output_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_controller_output_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_controller_output_pack(system_id, component_id, &msg , packet1.time_usec , packet1.force_x , packet1.force_y , packet1.force_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_skye_controller_output_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_controller_output_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.force_x , packet1.force_y , packet1.force_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_skye_controller_output_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_controller_output_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_controller_output_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.force_x , packet1.force_y , packet1.force_z , packet1.moment_x , packet1.moment_y , packet1.moment_z );
	mavlink_msg_skye_controller_output_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_cam_reconfigure_bluefox_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_cam_reconfigure_bluefox_settings_t packet_in = {
		17.0,
	45.0,
	73.0,
	101.0,
	18067,
	18171,
	18275,
	18379,
	77,
	144,
	"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDE",
	51,
	"HIJKLMNOPQRSTUVWXYZABCDEFGHIJKL",
	214,
	25,
	92,
	159,
	226,
	37,
	104,
	171,
	238,
	49,
	116,
	183,
	250,
	61,
	};
	mavlink_skye_cam_reconfigure_bluefox_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.frame_rate = packet_in.frame_rate;
        	packet1.shutter_auto_min = packet_in.shutter_auto_min;
        	packet1.shutter_auto_max = packet_in.shutter_auto_max;
        	packet1.shutter = packet_in.shutter;
        	packet1.roi_width = packet_in.roi_width;
        	packet1.roi_height = packet_in.roi_height;
        	packet1.x_offset = packet_in.x_offset;
        	packet1.y_offset = packet_in.y_offset;
        	packet1.target_system = packet_in.target_system;
        	packet1.cam_id = packet_in.cam_id;
        	packet1.pixel_clock = packet_in.pixel_clock;
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
        
        	mav_array_memcpy(packet1.frame_id, packet_in.frame_id, sizeof(char)*32);
        	mav_array_memcpy(packet1.camera_info_url, packet_in.camera_info_url, sizeof(char)*32);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_pack(system_id, component_id, &msg , packet1.target_system , packet1.cam_id , packet1.frame_id , packet1.pixel_clock , packet1.frame_rate , packet1.camera_info_url , packet1.binning_x , packet1.binning_y , packet1.roi_width , packet1.roi_height , packet1.x_offset , packet1.y_offset , packet1.color_coding , packet1.bayer_method , packet1.exposure , packet1.shutter_auto , packet1.shutter_auto_min , packet1.shutter_auto_max , packet1.shutter , packet1.gain_auto , packet1.gain_auto_min , packet1.gain_auto_max , packet1.gain , packet1.auto_control_speed , packet1.auto_query_values , packet1.hdr_mode , packet1.use_ros_time );
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.cam_id , packet1.frame_id , packet1.pixel_clock , packet1.frame_rate , packet1.camera_info_url , packet1.binning_x , packet1.binning_y , packet1.roi_width , packet1.roi_height , packet1.x_offset , packet1.y_offset , packet1.color_coding , packet1.bayer_method , packet1.exposure , packet1.shutter_auto , packet1.shutter_auto_min , packet1.shutter_auto_max , packet1.shutter , packet1.gain_auto , packet1.gain_auto_min , packet1.gain_auto_max , packet1.gain , packet1.auto_control_speed , packet1.auto_query_values , packet1.hdr_mode , packet1.use_ros_time );
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_send(MAVLINK_COMM_1 , packet1.target_system , packet1.cam_id , packet1.frame_id , packet1.pixel_clock , packet1.frame_rate , packet1.camera_info_url , packet1.binning_x , packet1.binning_y , packet1.roi_width , packet1.roi_height , packet1.x_offset , packet1.y_offset , packet1.color_coding , packet1.bayer_method , packet1.exposure , packet1.shutter_auto , packet1.shutter_auto_min , packet1.shutter_auto_max , packet1.shutter , packet1.gain_auto , packet1.gain_auto_min , packet1.gain_auto_max , packet1.gain , packet1.auto_control_speed , packet1.auto_query_values , packet1.hdr_mode , packet1.use_ros_time );
	mavlink_msg_skye_cam_reconfigure_bluefox_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_cam_reconfigure_prosilica_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_cam_reconfigure_prosilica_settings_t packet_in = {
		5,
	72,
	};
	mavlink_skye_cam_reconfigure_prosilica_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.cam_id = packet_in.cam_id;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_pack(system_id, component_id, &msg , packet1.target_system , packet1.cam_id );
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.cam_id );
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_send(MAVLINK_COMM_1 , packet1.target_system , packet1.cam_id );
	mavlink_msg_skye_cam_reconfigure_prosilica_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_cam_handle_save_image(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_cam_handle_save_image_t packet_in = {
		5,
	72,
	139,
	206,
	17,
	84,
	151,
	"HIJKLMN",
	"PQRSTUVWXYZABCDEFGHIJKLMNOPQRST",
	82,
	149,
	216,
	27,
	94,
	161,
	};
	mavlink_skye_cam_handle_save_image_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.cam_id = packet_in.cam_id;
        	packet1.save_image = packet_in.save_image;
        	packet1.save_percent = packet_in.save_percent;
        	packet1.format = packet_in.format;
        	packet1.png_level = packet_in.png_level;
        	packet1.jpeg_quality = packet_in.jpeg_quality;
        	packet1.send_image = packet_in.send_image;
        	packet1.send_percent = packet_in.send_percent;
        	packet1.format2 = packet_in.format2;
        	packet1.png_level2 = packet_in.png_level2;
        	packet1.jpeg_quality2 = packet_in.jpeg_quality2;
        	packet1.keep_old_modus = packet_in.keep_old_modus;
        
        	mav_array_memcpy(packet1.frame_name, packet_in.frame_name, sizeof(char)*8);
        	mav_array_memcpy(packet1.path, packet_in.path, sizeof(char)*32);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_handle_save_image_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_cam_handle_save_image_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_handle_save_image_pack(system_id, component_id, &msg , packet1.target_system , packet1.cam_id , packet1.save_image , packet1.save_percent , packet1.format , packet1.png_level , packet1.jpeg_quality , packet1.frame_name , packet1.path , packet1.send_image , packet1.send_percent , packet1.format2 , packet1.png_level2 , packet1.jpeg_quality2 , packet1.keep_old_modus );
	mavlink_msg_skye_cam_handle_save_image_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_handle_save_image_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.cam_id , packet1.save_image , packet1.save_percent , packet1.format , packet1.png_level , packet1.jpeg_quality , packet1.frame_name , packet1.path , packet1.send_image , packet1.send_percent , packet1.format2 , packet1.png_level2 , packet1.jpeg_quality2 , packet1.keep_old_modus );
	mavlink_msg_skye_cam_handle_save_image_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_cam_handle_save_image_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_handle_save_image_send(MAVLINK_COMM_1 , packet1.target_system , packet1.cam_id , packet1.save_image , packet1.save_percent , packet1.format , packet1.png_level , packet1.jpeg_quality , packet1.frame_name , packet1.path , packet1.send_image , packet1.send_percent , packet1.format2 , packet1.png_level2 , packet1.jpeg_quality2 , packet1.keep_old_modus );
	mavlink_msg_skye_cam_handle_save_image_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_cam_take_shot(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_cam_take_shot_t packet_in = {
		5,
	72,
	139,
	};
	mavlink_skye_cam_take_shot_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.cam_id = packet_in.cam_id;
        	packet1.take_shot = packet_in.take_shot;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_take_shot_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_cam_take_shot_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_take_shot_pack(system_id, component_id, &msg , packet1.target_system , packet1.cam_id , packet1.take_shot );
	mavlink_msg_skye_cam_take_shot_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_take_shot_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.cam_id , packet1.take_shot );
	mavlink_msg_skye_cam_take_shot_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_cam_take_shot_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_take_shot_send(MAVLINK_COMM_1 , packet1.target_system , packet1.cam_id , packet1.take_shot );
	mavlink_msg_skye_cam_take_shot_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_cam_image_triggered(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_cam_image_triggered_t packet_in = {
		93372036854775807ULL,
	73.0,
	101.0,
	129.0,
	963498504,
	963498712,
	963498920,
	101,
	};
	mavlink_skye_cam_image_triggered_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.timestamp = packet_in.timestamp;
        	packet1.roll = packet_in.roll;
        	packet1.pitch = packet_in.pitch;
        	packet1.yaw = packet_in.yaw;
        	packet1.lat = packet_in.lat;
        	packet1.lon = packet_in.lon;
        	packet1.alt = packet_in.alt;
        	packet1.cam_id = packet_in.cam_id;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_image_triggered_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_cam_image_triggered_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_image_triggered_pack(system_id, component_id, &msg , packet1.timestamp , packet1.cam_id , packet1.roll , packet1.pitch , packet1.yaw , packet1.lat , packet1.lon , packet1.alt );
	mavlink_msg_skye_cam_image_triggered_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_image_triggered_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.cam_id , packet1.roll , packet1.pitch , packet1.yaw , packet1.lat , packet1.lon , packet1.alt );
	mavlink_msg_skye_cam_image_triggered_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_cam_image_triggered_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_cam_image_triggered_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.cam_id , packet1.roll , packet1.pitch , packet1.yaw , packet1.lat , packet1.lon , packet1.alt );
	mavlink_msg_skye_cam_image_triggered_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye_home_maxon(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_skye_home_maxon_t packet_in = {
		5,
	72,
	};
	mavlink_skye_home_maxon_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.homing = packet_in.homing;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_home_maxon_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_skye_home_maxon_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_home_maxon_pack(system_id, component_id, &msg , packet1.target_system , packet1.homing );
	mavlink_msg_skye_home_maxon_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_home_maxon_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.homing );
	mavlink_msg_skye_home_maxon_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_skye_home_maxon_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_skye_home_maxon_send(MAVLINK_COMM_1 , packet1.target_system , packet1.homing );
	mavlink_msg_skye_home_maxon_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_data_transmission_handshake(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_data_transmission_handshake_t packet_in = {
		963497464,
	17443,
	17547,
	29,
	96,
	163,
	230,
	};
	mavlink_data_transmission_handshake_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.size = packet_in.size;
        	packet1.width = packet_in.width;
        	packet1.height = packet_in.height;
        	packet1.type = packet_in.type;
        	packet1.packets = packet_in.packets;
        	packet1.payload = packet_in.payload;
        	packet1.jpg_quality = packet_in.jpg_quality;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_data_transmission_handshake_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_data_transmission_handshake_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_data_transmission_handshake_pack(system_id, component_id, &msg , packet1.type , packet1.size , packet1.width , packet1.height , packet1.packets , packet1.payload , packet1.jpg_quality );
	mavlink_msg_data_transmission_handshake_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_data_transmission_handshake_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.type , packet1.size , packet1.width , packet1.height , packet1.packets , packet1.payload , packet1.jpg_quality );
	mavlink_msg_data_transmission_handshake_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_data_transmission_handshake_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_data_transmission_handshake_send(MAVLINK_COMM_1 , packet1.type , packet1.size , packet1.width , packet1.height , packet1.packets , packet1.payload , packet1.jpg_quality );
	mavlink_msg_data_transmission_handshake_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_encapsulated_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_encapsulated_data_t packet_in = {
		17235,
	{ 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135 },
	};
	mavlink_encapsulated_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.seqnr = packet_in.seqnr;
        
        	mav_array_memcpy(packet1.data, packet_in.data, sizeof(uint8_t)*253);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encapsulated_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_encapsulated_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encapsulated_data_pack(system_id, component_id, &msg , packet1.seqnr , packet1.data );
	mavlink_msg_encapsulated_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encapsulated_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.seqnr , packet1.data );
	mavlink_msg_encapsulated_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_encapsulated_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_encapsulated_data_send(MAVLINK_COMM_1 , packet1.seqnr , packet1.data );
	mavlink_msg_encapsulated_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_skye(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_skye_battery_status(system_id, component_id, last_msg);
	mavlink_test_skye_test_motors(system_id, component_id, last_msg);
	mavlink_test_skye_direct_control(system_id, component_id, last_msg);
	mavlink_test_skye_assisted_control(system_id, component_id, last_msg);
	mavlink_test_skye_assisted_rc_control(system_id, component_id, last_msg);
	mavlink_test_skye_scaled_pressure(system_id, component_id, last_msg);
	mavlink_test_skye_motor_signal(system_id, component_id, last_msg);
	mavlink_test_skye_motor_meassured_position(system_id, component_id, last_msg);
	mavlink_test_skye_controller_output(system_id, component_id, last_msg);
	mavlink_test_skye_cam_reconfigure_bluefox_settings(system_id, component_id, last_msg);
	mavlink_test_skye_cam_reconfigure_prosilica_settings(system_id, component_id, last_msg);
	mavlink_test_skye_cam_handle_save_image(system_id, component_id, last_msg);
	mavlink_test_skye_cam_take_shot(system_id, component_id, last_msg);
	mavlink_test_skye_cam_image_triggered(system_id, component_id, last_msg);
	mavlink_test_skye_home_maxon(system_id, component_id, last_msg);
	mavlink_test_data_transmission_handshake(system_id, component_id, last_msg);
	mavlink_test_encapsulated_data(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SKYE_TESTSUITE_H
