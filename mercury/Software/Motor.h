/** @file Motor.h
 * Use PWM modules to control the servomotors.
 * Each servomotor is driven by the duty cycle of a PWM signal. The PWM period must be greater than 3ms and less than 20ms.
 * A servomoter rotates in one direction if the high value of the PWM signal lasts 1ms, and it rotates in the opposite direction when the high value of the PWM signal lasts 2ms.
 * A high value signal duration of 1.5ms lets the servomotor idle. We prefer setting the PWM signal low to stop a motor in order to prevent jolts.
 * @author Adrien RICCIARDI
 * @version 1.0 : 17/12/2013
 * @version 1.1 : 01/03/2014, added variable motor speeds.
 */
#ifndef H_MOTOR_H
#define H_MOTOR_H

//---------------------------------------------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------------------------------------------
/** Identify the motor. */
typedef enum 
{
	MOTOR_LEFT,
	MOTOR_RIGHT
} TMotor;

/** Identify the state of a motor. */
typedef enum
{
	MOTOR_STATE_STOPPED,
	MOTOR_STATE_FORWARD,
	MOTOR_STATE_BACKWARD
} TMotorState;

/** Identify the direction of a motor. */
typedef enum 
{
	MOTOR_DIRECTION_FORWARD,
	MOTOR_DIRECTION_BACKWARD
} TMotorDirection;

//---------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------
/** Initialize the PWM modules used to control the motors.
 * @warning This function must be called only once at the beginning of the program.
 */
void MotorInit(void);

/** Set the state of a motor (running forward, running backward or stopped).
 * @param Motor The motor to command.
 * @param State The new state of the motor.
 */
void MotorSetState(TMotor Motor, TMotorState State);

/** Change the rotating speed of a motor.
 * @param Motor The motor to change speed.
 * @param Direction The motor direction to change speed.
 * @param Is_Speed_Increased Set to 1 to increase speed or to 0 to decrease speed.
 */
void MotorChangeSpeed(TMotor Motor, TMotorDirection Direction, unsigned char Is_Speed_Increased);

#endif