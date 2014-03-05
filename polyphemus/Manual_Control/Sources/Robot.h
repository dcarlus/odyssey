/** @file Robot.h
 * Control the robot via the UART link. Concurrent requests to robot are internally protected with a mutex.
 * @author Adrien RICCIARDI
 * @version 1.0 : 17/12/2013
 * @version 1.1 : 03/03/2014, added UART commands magic number and motors speed modification feature.
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
/** Identify the motor. */
typedef enum
{
	ROBOT_MOTOR_LEFT,
	ROBOT_MOTOR_RIGHT
} TRobotMotor;

/** All motor rotating directions. */
typedef enum
{
	ROBOT_MOTOR_DIRECTION_FORWARD,
	ROBOT_MOTOR_DIRECTION_BACKWARD
} TRobotMotorDirection;

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

/** Change the speed of a motor.
 * @param Motor The motor to change speed to.
 * @param Direction The motor direction to change speed to.
 * @param Is_Speed_Increased Set to 1 to increase the motor speed or set to zero to decrease the motor speed.
 */
void RobotChangeMotorSpeed(TRobotMotor Motor, TRobotMotorDirection Direction, int Is_Speed_Increased);

#endif
