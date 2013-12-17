/** @file Motor.h
 * Use PWM modules to control the servomotors.
 * Each servomotor is driven by the duty cycle of a PWM signal. The PWM period must be greater than 3ms and less than 20ms.
 * A servomoter rotates in one direction if the high value of the PWM signal lasts 1ms, and it rotates in the opposite direction when the high value of the PWM signal lasts 2ms.
 * A high value signal duration of 1.5ms lets the servomotor idle. We prefer setting the PWM signal low to stop a motor in order to prevent jolts.
 * @author Adrien RICCIARDI
 * @version 1.0 : 17/12/2013
 */
#ifndef H_MOTOR_H
#define H_MOTOR_H

/** Identify the motor. */
typedef enum {Left, Right} TMotor;

/** Identify the state of a motor. */
typedef enum {Stopped, Forward, Backward} TMotorState;

/** Initialize the PWM modules used to control the motors.
 * @warning This function must be called only once at the beginning of the program.
 */
void MotorInit(void);

/** Set the state of a motor (running forward, running backward or stopped).
 * @param Motor The motor to command.
 * @param State The new state of the motor.
 */
void MotorSetState(TMotor Motor, TMotorState State);

#endif