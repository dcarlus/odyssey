/** @file Motor.c
 * @see Motor.h for description.
 * @author Adrien RICCIARDI
 */
#include <system.h>
#include "Driver_EEPROM.h"
#include "Motor.h"

//---------------------------------------------------------------------------------------------------------------
// Private constants
//---------------------------------------------------------------------------------------------------------------
// PWM pins
#define MOTOR_LEFT_PIN 2
#define MOTOR_RIGHT_PIN 1

// Duty cycle values to make each motor rotate forward and backward
#define MOTOR_LEFT_DEFAULT_DUTY_CYCLE_FORWARD 200
#define MOTOR_LEFT_DEFAULT_DUTY_CYCLE_BACKWARD 500
#define MOTOR_RIGHT_DEFAULT_DUTY_CYCLE_FORWARD 800
#define MOTOR_RIGHT_DEFAULT_DUTY_CYCLE_BACKWARD 300

// EEPROM addresses of motor speed values
#define MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD 0
#define MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD 2
#define MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD 4
#define MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD 6

// PWM hardware limits
#define MOTOR_MINIMUM_DUTY_CYCLE_VALUE 0
#define MOTOR_MAXIMUM_DUTY_CYCLE_VALUE 1023

//---------------------------------------------------------------------------------------------------------------
// Private variables
//---------------------------------------------------------------------------------------------------------------
static unsigned short Motor_Left_Duty_Cycle_Forward, Motor_Left_Duty_Cycle_Backward, Motor_Right_Duty_Cycle_Forward, Motor_Right_Duty_Cycle_Backward;
static TMotorState Motor_Left_State, Motor_Right_State; // Keep current states to allow MotorChangeSpeed() to reset them

//---------------------------------------------------------------------------------------------------------------
// Public functions
//---------------------------------------------------------------------------------------------------------------
void MotorInit(void)
{	
	// Configure PWM pins as outputs
	trisc.MOTOR_LEFT_PIN = 0;
	trisc.MOTOR_RIGHT_PIN = 0;
	
	// Stop motors
	portc.MOTOR_LEFT_PIN = 0;
	portc.MOTOR_RIGHT_PIN = 0;
	
	// Check if the EEPROM contains the duty cycle values
	Motor_Left_Duty_Cycle_Forward = EEPROMReadWord(MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD);
	
	// Is the EEPROM memory empty ?
	if (Motor_Left_Duty_Cycle_Forward == 0xFFFF)
	{
		// Write default duty cycles to EEPROM
		EEPROMWriteWord(MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD, MOTOR_LEFT_DEFAULT_DUTY_CYCLE_FORWARD);
		EEPROMWriteWord(MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD, MOTOR_LEFT_DEFAULT_DUTY_CYCLE_BACKWARD);
		EEPROMWriteWord(MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD, MOTOR_RIGHT_DEFAULT_DUTY_CYCLE_FORWARD);
		EEPROMWriteWord(MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD, MOTOR_RIGHT_DEFAULT_DUTY_CYCLE_BACKWARD);
	
		// Use default values
		Motor_Left_Duty_Cycle_Forward = MOTOR_LEFT_DEFAULT_DUTY_CYCLE_FORWARD;
		Motor_Left_Duty_Cycle_Backward = MOTOR_LEFT_DEFAULT_DUTY_CYCLE_BACKWARD;
		Motor_Right_Duty_Cycle_Forward = MOTOR_RIGHT_DEFAULT_DUTY_CYCLE_FORWARD;
		Motor_Right_Duty_Cycle_Backward = MOTOR_RIGHT_DEFAULT_DUTY_CYCLE_BACKWARD;
	}
	else
	{
		// Load values from EEPROM
		Motor_Left_Duty_Cycle_Backward = EEPROMReadWord(MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD);
		Motor_Right_Duty_Cycle_Forward = EEPROMReadWord(MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD);
		Motor_Right_Duty_Cycle_Backward = EEPROMReadWord(MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD);
	}
	
	// Set the PWM period to 4.44 ms (it is the longuest we can achieve with a 3.6864 MHz clock)
	pr2 = 255;
	t2con = 0x06; // Enable timer 2 and set a 16x prescaler
}

void MotorSetState(TMotor Motor, TMotorState State)
{
	unsigned char *Pointer_CCPCON_Register, *Pointer_CCPRL_Register;
	unsigned short Duty_Cycle;
	
	// Get the configuration registers corresponding to the selected motor
	if (Motor == MOTOR_LEFT)
	{
		Pointer_CCPCON_Register = &ccp1con;
		Pointer_CCPRL_Register = &ccpr1l;
		Motor_Left_State = State;
	}
	else
	{
		Pointer_CCPCON_Register = &ccp2con;
		Pointer_CCPRL_Register = &ccpr2l;
		Motor_Right_State = State;
	}
	
	// Choose the right duty cycle according to selected state
	switch (State)
	{
		case MOTOR_STATE_STOPPED:
			*Pointer_CCPCON_Register = 0; // Stop PWM
			return;
			
		case MOTOR_STATE_FORWARD:
			if (Motor == MOTOR_LEFT) Duty_Cycle = Motor_Left_Duty_Cycle_Forward;
			else Duty_Cycle = Motor_Right_Duty_Cycle_Forward;
			break;
			
		case MOTOR_STATE_BACKWARD:
			if (Motor == MOTOR_LEFT) Duty_Cycle = Motor_Left_Duty_Cycle_Backward;
			else Duty_Cycle = Motor_Right_Duty_Cycle_Backward;
			break;
	}
	
	// Apply new duty cycle
	*Pointer_CCPCON_Register = (Duty_Cycle << 4) & 0x30;  // Stop this motor PWM and set duty cycle least significant bits in the same time
	*Pointer_CCPRL_Register = Duty_Cycle >> 2; // Set duty cycle most significant bits
	*Pointer_CCPCON_Register |= 0x0C; // Re-enable motor PWM
}

void MotorChangeSpeed(TMotor Motor, TMotorDirection Direction, unsigned char Is_Speed_Increased)
{
	// The left motor is mounted in the opposite direction than the right motor
	if (Motor == MOTOR_LEFT)
	{
		if (Direction == MOTOR_DIRECTION_FORWARD)
		{
			if (Is_Speed_Increased)
			{
				if (Motor_Left_Duty_Cycle_Forward > MOTOR_MINIMUM_DUTY_CYCLE_VALUE) Motor_Left_Duty_Cycle_Forward--;
			}
			else
			{
				if (Motor_Left_Duty_Cycle_Forward < MOTOR_MAXIMUM_DUTY_CYCLE_VALUE) Motor_Left_Duty_Cycle_Forward++;
			}
			EEPROMWriteWord(MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD, Motor_Left_Duty_Cycle_Forward);
		}
		else
		{
			if (Is_Speed_Increased)
			{
				if (Motor_Left_Duty_Cycle_Backward < MOTOR_MAXIMUM_DUTY_CYCLE_VALUE) Motor_Left_Duty_Cycle_Backward++; // Motor is mounted in the opposite direction
			}
			else
			{
				if (Motor_Left_Duty_Cycle_Backward > MOTOR_MINIMUM_DUTY_CYCLE_VALUE) Motor_Left_Duty_Cycle_Backward--;
			}
			EEPROMWriteWord(MOTOR_LEFT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD, Motor_Left_Duty_Cycle_Backward);
		}
		
		// Set new speed
		MotorSetState(MOTOR_LEFT, Motor_Left_State);
	}
	else
	{
		if (Direction == MOTOR_DIRECTION_FORWARD)
		{
			if (Is_Speed_Increased)
			{
				if (Motor_Right_Duty_Cycle_Forward < MOTOR_MAXIMUM_DUTY_CYCLE_VALUE) Motor_Right_Duty_Cycle_Forward++;
			}
			else
			{
				if (Motor_Right_Duty_Cycle_Forward > MOTOR_MINIMUM_DUTY_CYCLE_VALUE) Motor_Right_Duty_Cycle_Forward--;
			}
			EEPROMWriteWord(MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_FORWARD, Motor_Right_Duty_Cycle_Forward);
		}
		else
		{
			if (Is_Speed_Increased)
			{
				if (Motor_Right_Duty_Cycle_Backward > MOTOR_MINIMUM_DUTY_CYCLE_VALUE) Motor_Right_Duty_Cycle_Backward--;
			}
			else
			{
				if (Motor_Right_Duty_Cycle_Backward < MOTOR_MAXIMUM_DUTY_CYCLE_VALUE) Motor_Right_Duty_Cycle_Backward++;
			}
			EEPROMWriteWord(MOTOR_RIGHT_EEPROM_ADDRESS_DUTY_CYCLE_BACKWARD, Motor_Right_Duty_Cycle_Backward);
		}
		
		// Set new speed
		MotorSetState(MOTOR_RIGHT, Motor_Right_State);
	}
}
		