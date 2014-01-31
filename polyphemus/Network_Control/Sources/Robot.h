/** @file Robot.h
 * Control the robot via the UART link. Concurrent requests to robot are internally protected with a mutex.
 * @author Adrien RICCIARDI
 * @version 1.0 : 17/12/2013
 * @warning None of this function is reentrant, simultaneous calls to the same function by several threads will lead to an unpredictible robot behaviour.
 */
#ifndef H_ROBOT_H
#define H_ROBOT_H

//-----------------------------------------------------------------------------
// Public constants
//-----------------------------------------------------------------------------
/** Fully-charged battery voltage in Volts. */
#define ROBOT_MAXIMUM_BATTERY_VOLTAGE 7.2f
/** Near to deep discharge battery voltage in Volts. */
#define ROBOT_MINIMUM_BATTERY_VOLTAGE 6.0f

//-----------------------------------------------------------------------------
// Public types
//-----------------------------------------------------------------------------
/** All possible motions for the robot. */
typedef enum
{
	ROBOT_MOTION_STOPPED,
	ROBOT_MOTION_FORWARD,
	ROBOT_MOTION_FORWARD_TURN_LEFT,
	ROBOT_MOTION_FORWARD_TURN_RIGHT,
	ROBOT_MOTION_BACKWARD,
	ROBOT_MOTION_BACKWARD_TURN_LEFT,
	ROBOT_MOTION_BACKWARD_TURN_RIGHT
} TRobotMotion;

/** All robot network commands.
 * @warning Values must fit on 8-bit data.
 */
typedef enum
{
	ROBOT_COMMAND_STOP,
	ROBOT_COMMAND_FORWARD,
	ROBOT_COMMAND_BACKWARD,
	ROBOT_COMMAND_LEFT,
	ROBOT_COMMAND_RIGHT,
	ROBOT_COMMAND_READ_BATTERY_VOLTAGE,
	ROBOT_COMMAND_LED_ON,
	ROBOT_COMMAND_LED_OFF
} TRobotCommand;

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------
/** Start the robot firmware.
 * @param String_UART_Device_File The /dev file name corresponding to the UART.
 * @return 1 if the robot is correctly initialized or 0 if an error occured.
 */
int RobotInit(char *String_UART_Device_File);

/** Light or turn off the green LED.
 * @param Is_Lighted Set to 1 to light the LED or set to 0 to turn off the LED.
 */
void RobotSetLedState(int Is_Lighted);

/** Get the current battery voltage.
 * @return The battery voltage in volts.
 */
float RobotReadBatteryVoltage(void);

/** Set the robot motions.
 * @param Motion The new predefined motion to set.
 */
void RobotSetMotion(TRobotMotion Motion);

#endif
