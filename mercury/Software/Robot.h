/** @file Robot.h
 * Robot system configuration.
 * @author Adrien RICCIARDI
 * @version 1.0 : 17/12/2013
 */
#ifndef H_ROBOT_H
#define H_ROBOT_H

//---------------------------------------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------------------------------------
/** All robot commands must be preceded by this magic number to avoid UART glitches. */
#define ROBOT_COMMAND_MAGIC_NUMBER 0xA5

/** Bits 7 and 6 specify the command opcode. */
#define ROBOT_COMMANDS_CODE_MASK 0xC0

/** Set a motor state. Bit 5 selects the motor (0 = left, 1 = right). Bits 4-3 indicate motor state (00 = stopped, 01 = forward, 10 = backward). */
#define ROBOT_COMMAND_SET_MOTOR_STATE 0x00
/** Light or turn off green LED. Bit 5 indicates led state. */
#define ROBOT_COMMAND_SET_LED_STATE 0x40
/** Read the current battery voltage. Return the ADC 10-bit raw value. */
#define ROBOT_COMMAND_READ_BATTERY_VOLTAGE 0x80
/** Change a motor speed. Bit 5 selects the motor (0 = left, 1 = right). Bit 4 selects the rotating direction (0 = forward, 1 = backward). Bit 3 indicates the speed variation (0 = decrease, 1 = increase). */
#define ROBOT_COMMAND_CHANGE_MOTOR_SPEED 0xC0

//---------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------
/** Configure robot hardware. */
#ifdef DOXYGEN
	void RobotInit(void);
#else
	#define RobotInit() \
	{ \
		trisb = 0; /* Configure LED port as output */ \
		RobotLedOff(); \
	} 
#endif

/** Light the green LED. */
#ifdef DOXYGEN
	void RobotLedOn(void);
#else
	#define RobotLedOn() portb.7 = 1
#endif

/** Turn off the green LED. */
#ifdef DOXYGEN
	void RobotLedOff(void);
#else
	#define RobotLedOff() portb.7 = 0
#endif

#endif
