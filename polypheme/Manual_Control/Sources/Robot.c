/** @file Robot.c
 * @see Robot.h for description.
 * @author Adrien RICCIARDI
 */
#include <pthread.h> // For mutex
#include <unistd.h> // For usleep()
#include "UART.h"
#include "Robot.h"

//-----------------------------------------------------------------------------
// Private constants
//-----------------------------------------------------------------------------
/* How many microseconds to wait for the motors to stop. */
#define ROBOT_MOTORS_STOPPING_TIME 500000

//-----------------------------------------------------------------------------
// Private types
//-----------------------------------------------------------------------------
// Identify the motor
typedef enum
{
	MOTOR_LEFT,
	MOTOR_RIGHT
} TMotor;

// Available states for a motor
typedef enum
{
	MOTOR_STATE_STOPPED,
	MOTOR_STATE_FORWARD,
	MOTOR_STATE_BACKWARD
} TMotorState;

//-----------------------------------------------------------------------------
// Private variables
//-----------------------------------------------------------------------------
// Protect concurrent accesses to robot link
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;

//-----------------------------------------------------------------------------
// Private functions
//-----------------------------------------------------------------------------
/* Set a motor state.
 * @param Motor The concerned motor.
 * @param State The new state for this motor.
 * @warning It is not possible to instantly change a motor direction, you have to wait some time to avoid high currents rebooting the system.
 * @warning This function is not protected by the mutex.
 */
static void RobotSetMotorState(TMotor Motor, TMotorState State)
{
	unsigned char Command = 0; // Opcode is 0

	// Set motor ID
	if (Motor == MOTOR_RIGHT) Command |= 0x20;

	// Set state
	if (State == MOTOR_STATE_FORWARD) Command |= 0x08;
	else if (State == MOTOR_STATE_BACKWARD) Command |= 0x10;

	// Send command
	UARTWriteByte(Command);
}

/* Stop the motors and wait the required time for the motor to evacuate their internal current. */
static void RobotStopMotors(void)
{
	// Stop motors
	pthread_mutex_lock(&Mutex);
	RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_STOPPED);
	RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_STOPPED);
	pthread_mutex_unlock(&Mutex);

	// Wait for the minimum time needed by the motors to stop and evacuate their internel high current
	usleep(ROBOT_MOTORS_STOPPING_TIME);
}

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------
int RobotInit(char *String_UART_Device_File)
{
	if (!UARTOpen(String_UART_Device_File, B115200)) return 0;

	// Start robot firmware
	UARTWriteByte(0xCA);
	return 1;
}

void RobotSetLedState(int Is_Lighted)
{
	pthread_mutex_lock(&Mutex);

	if (Is_Lighted) UARTWriteByte(0x60);
	else UARTWriteByte(0x40);

	pthread_mutex_unlock(&Mutex);
}

float RobotReadBatteryVoltage(void)
{
	unsigned short Raw_Value;

	pthread_mutex_lock(&Mutex);

	// Send command
	UARTWriteByte(0x80);

	// Receive raw ADC 10-bit value in big endian
	Raw_Value = (UARTReadByte() << 8) | UARTReadByte();

	pthread_mutex_unlock(&Mutex);

	// Convert to volts (the sampled value 1023 corresponds to 5 V and the battery voltage is divided by 3)
	return (Raw_Value / 204.6f) * 3.f;
}

void RobotSetMotion(TRobotMotion Motion)
{
	static TRobotMotion Previous_Motion = ROBOT_MOTION_STOPPED; // Keep the previous motion to avoid sending again the command to the robot if the new motion is the same

	// It is not possible to instantly change a motor direction, we must wait some time to avoid high currents rebooting the system
	switch (Motion)
	{
		case ROBOT_MOTION_FORWARD:
			if (Previous_Motion == ROBOT_MOTION_FORWARD) break;

			// Need to stop if the robot was going somewhat backward
			if ((Previous_Motion == ROBOT_MOTION_BACKWARD) || (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_LEFT) || (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_RIGHT)) RobotStopMotors();

			// Go forward
			pthread_mutex_lock(&Mutex);
			RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_FORWARD);
			RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_FORWARD);
			pthread_mutex_unlock(&Mutex);

			Previous_Motion = ROBOT_MOTION_FORWARD;
			break;

		case ROBOT_MOTION_FORWARD_TURN_LEFT:
			if (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_LEFT) break;

			// Need to stop if the robot was going somewhat backward
			if ((Previous_Motion == ROBOT_MOTION_BACKWARD) || (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_LEFT) || (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_RIGHT)) RobotStopMotors();

			// Go forward and turn left
			pthread_mutex_lock(&Mutex);
			RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_STOPPED);
			RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_FORWARD);
			pthread_mutex_unlock(&Mutex);

			Previous_Motion = ROBOT_MOTION_FORWARD_TURN_LEFT;
			break;

		case ROBOT_MOTION_FORWARD_TURN_RIGHT:
			if (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_RIGHT) break;

			// Need to stop if the robot was going somewhat backward
			if ((Previous_Motion == ROBOT_MOTION_BACKWARD) || (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_LEFT) || (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_RIGHT)) RobotStopMotors();

			// Go forward and turn right
			pthread_mutex_lock(&Mutex);
			RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_FORWARD);
			RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_STOPPED);
			pthread_mutex_unlock(&Mutex);

			Previous_Motion = ROBOT_MOTION_FORWARD_TURN_RIGHT;
			break;

		case ROBOT_MOTION_BACKWARD:
			if (Previous_Motion == ROBOT_MOTION_BACKWARD) break;

			// Need to stop if the robot was going somewhat forward
			if ((Previous_Motion == ROBOT_MOTION_FORWARD) || (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_LEFT) || (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_RIGHT)) RobotStopMotors();

			// Go backward
			pthread_mutex_lock(&Mutex);
			RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_BACKWARD);
			RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_BACKWARD);
			pthread_mutex_unlock(&Mutex);

			Previous_Motion = ROBOT_MOTION_BACKWARD;
			break;

		case ROBOT_MOTION_BACKWARD_TURN_LEFT:
			if (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_LEFT) break;

			// Need to stop if the robot was going somewhat forward
			if ((Previous_Motion == ROBOT_MOTION_FORWARD) || (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_LEFT) || (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_RIGHT)) RobotStopMotors();

			// Go backward and turn left
			pthread_mutex_lock(&Mutex);
			RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_STOPPED);
			RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_BACKWARD);
			pthread_mutex_unlock(&Mutex);

			Previous_Motion = ROBOT_MOTION_BACKWARD_TURN_LEFT;
			break;

		case ROBOT_MOTION_BACKWARD_TURN_RIGHT:
			if (Previous_Motion == ROBOT_MOTION_BACKWARD_TURN_RIGHT) break;

			// Need to stop if the robot was going somewhat forward
			if ((Previous_Motion == ROBOT_MOTION_FORWARD) || (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_LEFT) || (Previous_Motion == ROBOT_MOTION_FORWARD_TURN_RIGHT)) RobotStopMotors();

			// Go backward and turn right
			pthread_mutex_lock(&Mutex);
			RobotSetMotorState(MOTOR_LEFT, MOTOR_STATE_BACKWARD);
			RobotSetMotorState(MOTOR_RIGHT, MOTOR_STATE_STOPPED);
			pthread_mutex_unlock(&Mutex);

			Previous_Motion = ROBOT_MOTION_BACKWARD_TURN_RIGHT;
			break;

		case ROBOT_MOTION_STOPPED:
		default:
			RobotStopMotors();
			Previous_Motion = ROBOT_MOTION_STOPPED;
			break;
	}
}
