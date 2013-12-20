/** @file Motor.c
 * @see Motor.h for description.
 * @author Adrien RICCIARDI
 */
#include <system.h>
#include "Motor.h"

// Duty cycle values to make each motor rotate forward and backward
#define MOTOR_LEFT_DUTY_CYCLE_FORWARD 200
#define MOTOR_LEFT_DUTY_CYCLE_BACKWARD 500
#define MOTOR_RIGHT_DUTY_CYCLE_FORWARD 800
#define MOTOR_RIGHT_DUTY_CYCLE_BACKWARD 300

void MotorInit(void)
{
	// Configure PWM pins RC1 and RC2 as outputs
	trisc.1 = 0;
	trisc.2 = 0;
	
	// Stop motors
	portc.1 = 0;
	portc.2 = 0;
	
	// Set the PWM period to 4.44 ms (it is the longuest we can achieve with a 3.6864 MHz clock)
	pr2 = 255;
	t2con = 0x06; // Enable timer 2 and set a 16x prescaler
}

void MotorSetState(TMotor Motor, TMotorState State)
{
	unsigned char *Pointer_CCPCON_Register, *Pointer_CCPRL_Register;
	unsigned short Duty_Cycle;
	
	// Get the configuration registers corresponding to the selected motor
	if (Motor == Left)
	{
		Pointer_CCPCON_Register = &ccp1con;
		Pointer_CCPRL_Register = &ccpr1l;
	}
	else
	{
		Pointer_CCPCON_Register = &ccp2con;
		Pointer_CCPRL_Register = &ccpr2l;
	}
	
	// Choose the right duty cycle according to selected state
	switch (State)
	{
		case Stopped:
			*Pointer_CCPCON_Register = 0; // Stop PWM
			return;
			
		case Forward:
			if (Motor == Left) Duty_Cycle = MOTOR_LEFT_DUTY_CYCLE_FORWARD;
			else Duty_Cycle = MOTOR_RIGHT_DUTY_CYCLE_FORWARD;
			break;
			
		case Backward:
			if (Motor == Left) Duty_Cycle = MOTOR_LEFT_DUTY_CYCLE_BACKWARD;
			else Duty_Cycle = MOTOR_RIGHT_DUTY_CYCLE_BACKWARD;
			break;
	}
	
	// Apply new duty cycle
	*Pointer_CCPCON_Register = (Duty_Cycle << 4) & 0x30;  // Stop this motor PWM and set duty cycle least significant bits in the same time
	*Pointer_CCPRL_Register = Duty_Cycle >> 2; // Set duty cycle most significant bits
	*Pointer_CCPCON_Register |= 0x0C; // Re-enable motor PWM
}