#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h> // For system()
#include "Robot.h"
#include "Interface.h"

// Read the battery voltage each second
void *ThreadReadBatteryVoltage(void *Pointer_Parameters)
{
	float Battery_Voltage;
	int Is_Led_Lighted = 1, Percentage;

	while (1)
	{
		// Get voltage
		Battery_Voltage = RobotReadBatteryVoltage();

		// Compute percentage
		Percentage = ((Battery_Voltage - ROBOT_MINIMUM_BATTERY_VOLTAGE) / (ROBOT_MAXIMUM_BATTERY_VOLTAGE - ROBOT_MINIMUM_BATTERY_VOLTAGE)) * 100.f;
		// Adjust values to stay in [0, 100] range
		if (Percentage < 0) Percentage = 0;
		else if (Percentage > 100) Percentage = 100;

		// Display values
		InterfaceDisplayBatteryVoltage(Percentage, Battery_Voltage);

		// Blink LED
		RobotSetLedState(Is_Led_Lighted);
		Is_Led_Lighted = !Is_Led_Lighted;

		usleep(1000000);
	}
}

int main(void)
{
	pthread_t Thread_ID;

	// Connect to the robot
	if (!RobotInit("/dev/ttyAMA0"))
	{
		puts("Error : can't connect to the robot.");
		return -1;
	}

	// Create threads
	if (pthread_create(&Thread_ID, NULL, ThreadReadBatteryVoltage, NULL) != 0)
	{
		puts("Error : can't create battery voltage thread.");
		return -1;
	}

	// Initialize interface
	if (!InterfaceInit())
	{
		puts("Error : can't initialize interface. Make sure ncurses library is installed.");
		return -1;
	}
	InterfaceDisplayHints();

	while (1)
	{
		switch (getchar())
		{
			case 'z':
				InterfaceDisplayDirection("FORWARD");
				RobotSetMotion(ROBOT_MOTION_FORWARD);
				break;

			case 's':
				InterfaceDisplayDirection("BACKWARD");
				RobotSetMotion(ROBOT_MOTION_BACKWARD);
				break;

			case 'q':
				InterfaceDisplayDirection("LEFT");
				RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_LEFT);
				break;

			case 'd':
				InterfaceDisplayDirection("RIGHT");
				RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_RIGHT);
				break;

			// Stop robot
			case ' ':
				InterfaceDisplayDirection("STOPPED");
				RobotSetMotion(ROBOT_MOTION_STOPPED);
				break;

			// Increase left motor forward speed
			case 'u':
				InterfaceDisplaySpeed("Left forward faster");
				RobotChangeMotorSpeed(ROBOT_MOTOR_LEFT, ROBOT_MOTOR_DIRECTION_FORWARD, 1);
				break;

			// Decrease left motor forward speed
			case 'j':
				InterfaceDisplaySpeed("Left forward slower");
				RobotChangeMotorSpeed(ROBOT_MOTOR_LEFT, ROBOT_MOTOR_DIRECTION_FORWARD, 0);
				break;

			// Increase right motor forward speed
			case 'i':
				InterfaceDisplaySpeed("Right forward faster");
				RobotChangeMotorSpeed(ROBOT_MOTOR_RIGHT, ROBOT_MOTOR_DIRECTION_FORWARD, 1);
				break;

			// Decrease right motor forward speed
			case 'k':
				InterfaceDisplaySpeed("Right forward slower");
				RobotChangeMotorSpeed(ROBOT_MOTOR_RIGHT, ROBOT_MOTOR_DIRECTION_FORWARD, 0);
				break;

			// Increase left motor backward speed
			case 'o':
				InterfaceDisplaySpeed("Left backward faster");
				RobotChangeMotorSpeed(ROBOT_MOTOR_LEFT, ROBOT_MOTOR_DIRECTION_BACKWARD, 1);
				break;

			// Decrease left motor backward speed
			case 'l':
				InterfaceDisplaySpeed("Left backward slower");
				RobotChangeMotorSpeed(ROBOT_MOTOR_LEFT, ROBOT_MOTOR_DIRECTION_BACKWARD, 0);
				break;

			// Increase right motor backward speed
			case 'p':
				InterfaceDisplaySpeed("Right backward faster");
				RobotChangeMotorSpeed(ROBOT_MOTOR_RIGHT, ROBOT_MOTOR_DIRECTION_BACKWARD, 1);
				break;

			// Decrease right motor backward speed
			case 'm':
				InterfaceDisplaySpeed("Right backward slower");
				RobotChangeMotorSpeed(ROBOT_MOTOR_RIGHT, ROBOT_MOTOR_DIRECTION_BACKWARD, 0);
				break;

			// Exit
			case 'x':
				RobotSetMotion(ROBOT_MOTION_STOPPED);
				RobotSetLedState(0);
				InterfaceTerminate();
				return 0;
		}
	}
}
