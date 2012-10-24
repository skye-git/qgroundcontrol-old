#ifndef QGC_skye_enums_H
#define QGC_skye_enums_H

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

/** @brief ID for each accu pack for detailed battery information */
#ifndef HAVE_ENUM_MAV_SKYE_BATTERY_PACK_ID
#define HAVE_ENUM_MAV_SKYE_BATTERY_PACK_ID
enum MAV_SKYE_BATTERY_PACK_ID
{
	MAV_SKYE_BATTERY_PACK_ID_NONE=0, /* no accu | */
	MAV_SKYE_BATTERY_PACK_ID_1=1, /* Accu pack 1 | */
	MAV_SKYE_BATTERY_PACK_ID_2=2, /* Accu pack 2 | */
	MAV_SKYE_BATTERY_PACK_ID_3=3, /* Accu pack 3 | */
	MAV_SKYE_BATTERY_PACK_ID_ENUM_END=4, /*  | */
};
#endif

#endif // QGC_skye_enums_H
