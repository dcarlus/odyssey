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
/** Arbitrary code sent to start the robot. */
#define ROBOT_START_CODE 0xCA

/** Bits 7 and 6 specify the command opcode. */
#define ROBOT_COMMANDS_CODE_MASK 0xC0

/** Set a motor state. Bit 5 selects the motor (0 = left, 1 = right). Bits 4-3 indicate motor state (00 = Stopped, 01 = Forward, 10 = Backward). */
#define ROBOT_COMMAND_SET_MOTOR_STATE 0x00
/** Light or turn off green LED. Bit 5 indicates led state. */
#define ROBOT_COMMAND_SET_LED_STATE 0x40
/** Read the current battery voltage. Return the ADC 10-bit raw value. */
#define ROBOT_COMMAND_READ_BATTERY_VOLTAGE 0x80

//---------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------
/** Configure robot hardware. */
#ifdef DOXYGEN
	void RobotInit(void);
#else
	#define RobotInit() trisb = 0 // Configure LED port as output
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
