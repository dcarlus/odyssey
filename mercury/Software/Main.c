/** Main.c
 * Main loop.
 * @author Adrien RICCIARDI
 * @version 1.0 : 15/12/2013
 */
#include <system.h>
#include "Driver_UART.h"
#include "Driver_ADC.h"
#include "Robot.h"
#include "Motor.h"

//---------------------------------------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------------------------------------
// Configure PIC16F876 fuses
#pragma DATA _CONFIG, _PWRTE_ON & _BODEN_ON & _WDT_OFF & _LVP_OFF & _CPD_OFF & _DEBUG_OFF & _XT_OSC & _CP_OFF
// Configure clock frequency (Hz)
#pragma CLOCK_FREQ 3686400

//---------------------------------------------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------------------------------------------
unsigned short Battery_Voltage;

//---------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------
void interrupt(void)
{
	unsigned char Command;
	TMotor Motor;
	TMotorState State;
	
	// Handle UART receive interrupt
	if (UARTHasInterruptOccured())
	{
		Command = UARTReadByte();
		
		// Check command opcode
		switch (Command & ROBOT_COMMANDS_CODE_MASK)
		{
			// Set motor state
			case ROBOT_COMMAND_SET_MOTOR_STATE:
				// Extract motor ID
				if (Command & 0x20) Motor = Right;
				else Motor = Left;
				
				// Extract requested state
				Command = (Command >> 3) & 0x03;
				if (Command == 1) State = Forward;
				else if (Command == 2) State = Backward;
				else State = Stopped; // So an unknown state will stop the motor
				
				// Apply new state
				MotorSetState(Motor, State);
				break;
				
			// Light or turn off the green LED
			case ROBOT_COMMAND_SET_LED_STATE:
				// Bit 5 tells the led state
				if (Command & 40) RobotLedOn();
				else RobotLedOff();
				break;
				
			// Return the last sampled battery voltage value
			case ROBOT_COMMAND_READ_BATTERY_VOLTAGE:
				// Send value in big endian mode
				UARTWriteByte(Battery_Voltage >> 8);
				UARTWriteByte(Battery_Voltage);
				break;
		
			// Unknown command, do nothing
			default:
				break;
		}
	
		// Re-enable UART interrupt
		UARTClearInterruptFlag();
	}
}

void main(void)
{
	// Initialize robot
	RobotInit();
	MotorInit();
	ADCInit();
	UARTInit(UART_BAUD_RATE_115200);
	
	// Stop motors
	MotorSetState(Left, Stopped);
	MotorSetState(Right, Stopped);
		
	// Turn off LED to let master light it when it has finished booting
	RobotLedOff();
	
	// Do some fake reads to calibrate ADC
	ADCReadWord();
	ADCReadWord();
	
	// Wait for the master to send the start code (avoid interpreting false commands sent when master is booting)
	while (UARTReadByte() != ROBOT_START_CODE);
	
	// Enable interrupts
	intcon = 0xC0;
	
	// Main loop
	while (1)
	{
		// Read battery voltage each second
		UARTDisableInterrupt(); // Atomic operation
		Battery_Voltage = ADCReadWord();
		UARTEnableInterrupt();
		delay_s(1);
	}
}