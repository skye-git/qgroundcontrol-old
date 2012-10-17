/** @file
 *	@brief MAVLink comm protocol testsuite generated from newskye.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef NEWSKYE_TESTSUITE_H
#define NEWSKYE_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_newskye(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_newskye(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_manual_6dof_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_manual_6dof_control_t packet_in = {
		17235,
	17339,
	17443,
	17547,
	17651,
	17755,
	41,
	};
	mavlink_manual_6dof_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.x = packet_in.x;
        	packet1.y = packet_in.y;
        	packet1.z = packet_in.z;
        	packet1.roll = packet_in.roll;
        	packet1.pitch = packet_in.pitch;
        	packet1.yaw = packet_in.yaw;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_6dof_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_manual_6dof_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_6dof_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.x , packet1.y , packet1.z , packet1.roll , packet1.pitch , packet1.yaw );
	mavlink_msg_manual_6dof_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_6dof_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.x , packet1.y , packet1.z , packet1.roll , packet1.pitch , packet1.yaw );
	mavlink_msg_manual_6dof_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_manual_6dof_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_6dof_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.x , packet1.y , packet1.z , packet1.roll , packet1.pitch , packet1.yaw );
	mavlink_msg_manual_6dof_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_manual_8dof_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_manual_8dof_control_t packet_in = {
		17235,
	17339,
	17443,
	17547,
	17651,
	17755,
	17859,
	17963,
	53,
	};
	mavlink_manual_8dof_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.motor_1 = packet_in.motor_1;
        	packet1.motor_2 = packet_in.motor_2;
        	packet1.motor_3 = packet_in.motor_3;
        	packet1.motor_4 = packet_in.motor_4;
        	packet1.motor_5 = packet_in.motor_5;
        	packet1.motor_6 = packet_in.motor_6;
        	packet1.motor_7 = packet_in.motor_7;
        	packet1.motor_8 = packet_in.motor_8;
        	packet1.target_system = packet_in.target_system;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_8dof_control_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_manual_8dof_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_8dof_control_pack(system_id, component_id, &msg , packet1.target_system , packet1.motor_1 , packet1.motor_2 , packet1.motor_3 , packet1.motor_4 , packet1.motor_5 , packet1.motor_6 , packet1.motor_7 , packet1.motor_8 );
	mavlink_msg_manual_8dof_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_8dof_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.motor_1 , packet1.motor_2 , packet1.motor_3 , packet1.motor_4 , packet1.motor_5 , packet1.motor_6 , packet1.motor_7 , packet1.motor_8 );
	mavlink_msg_manual_8dof_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_manual_8dof_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_manual_8dof_control_send(MAVLINK_COMM_1 , packet1.target_system , packet1.motor_1 , packet1.motor_2 , packet1.motor_3 , packet1.motor_4 , packet1.motor_5 , packet1.motor_6 , packet1.motor_7 , packet1.motor_8 );
	mavlink_msg_manual_8dof_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

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

static void mavlink_test_newskye(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_manual_6dof_control(system_id, component_id, last_msg);
	mavlink_test_manual_8dof_control(system_id, component_id, last_msg);
	mavlink_test_skye_battery_status(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // NEWSKYE_TESTSUITE_H
