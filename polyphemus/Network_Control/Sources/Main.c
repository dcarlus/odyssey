/** @file Main.c
 * Main loop.
 * @author Adrien RICCIARDI
 * @version 1.0 : 07/01/2014
 * @version 1.1 : 09/01/2014, added debugging function.
 */
#include <stdio.h>
#include <unistd.h> // For read(), write()...
#include <pthread.h>
#include <stdlib.h> // For atoi()
#include <stdarg.h> // For va_list and friends
#include <time.h>
#include "Robot.h"
#include "Network.h"

/** Comment this out to disable debug messages. */
#define DEBUG

/** The acknowledge code. */
#define COMMAND_ACKNOWLEDGE 32

/** All robot network commands.
 * @warning Values must fit on 8-bit data.
 */
typedef enum
{
	COMMAND_STOP,
	COMMAND_FORWARD,
	COMMAND_BACKWARD,
	COMMAND_LEFT,
	COMMAND_RIGHT,
	COMMAND_READ_BATTERY_VOLTAGE,
	COMMAND_LED_ON,
	COMMAND_LED_OFF
} TCommand;

static int Socket_Client;
static unsigned char Battery_Voltage_Percentage = 0;

/** Display a debug message.
 * @param String_Format Format of the string to display.
 * @param ... Printf() like parameters.
 */
static void PrintDebug(char *String_Format, ...)
{
#ifdef DEBUG
	va_list List_Arguments;
	time_t Time;
	struct tm *Pointer_Splitted_Time;

	// Get current time
	Time = time(NULL);
	// Split time in hours, minutes...
	Pointer_Splitted_Time = localtime(&Time);
	// Display time
	printf("[%02d:%02d:%02d] ", Pointer_Splitted_Time->tm_hour, Pointer_Splitted_Time->tm_min, Pointer_Splitted_Time->tm_sec);

	// Show debug string
	va_start(List_Arguments, String_Format);
	vprintf(String_Format, List_Arguments);
	va_end(List_Arguments);
	putchar('\n');
#endif
}

/** Send an acknowledge code to the client socket.
 * @note Stop the robot if the acknowledge sending failed.
 */
static void SendAcknowledge(void)
{
	unsigned char Byte = COMMAND_ACKNOWLEDGE;
	size_t Size;

	Size = sizeof(Byte);
	if (write(Socket_Client, &Byte, Size) != Size)
	{
		printf("WARNING : could not send acknowledge to client, stopping robot.\n");
		RobotSetMotion(ROBOT_MOTION_STOPPED);
	}
}

// Read the battery voltage each second
static void *ThreadReadBatteryVoltage(void *Pointer_Parameters)
{
	float Battery_Voltage;
	int Percentage;

	while (1)
	{
		// Compute percentage
		Battery_Voltage = RobotReadBatteryVoltage();
		Percentage = ((Battery_Voltage - ROBOT_MINIMUM_BATTERY_VOLTAGE) / (ROBOT_MAXIMUM_BATTERY_VOLTAGE - ROBOT_MINIMUM_BATTERY_VOLTAGE)) * 100.f;

		// Adjust values to stay in [0, 100] range
		if (Percentage < 0) Percentage = 0;
		else if (Percentage > 100) Percentage = 100;
		Battery_Voltage_Percentage = Percentage;

		usleep(1000000);
	}

	// Only to make gcc happy
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t Thread_ID;
	char *String_Server_IP;
	unsigned short Server_Port;
	int Socket_Server;
	unsigned char Byte;
	TCommand Command;

	// Check parameters
	if (argc != 3)
	{
		printf("Bad arguments.\nUsage : %s serverIpAddress serverListeningPort\n", argv[0]);
		return -1;
	}

	// Retrieve parameters values
	String_Server_IP = argv[1];
	Server_Port = atoi(argv[2]);

	// Connect to the robot
	if (!RobotInit("/dev/ttyAMA0"))
	{
		puts("Error : can't connect to the robot.");
		return -1;
	}
	// Stop robot in case of UART glitch
	RobotSetMotion(ROBOT_MOTION_STOPPED);

	// Create threads
	if (pthread_create(&Thread_ID, NULL, ThreadReadBatteryVoltage, NULL) != 0)
	{
		puts("Error : can't create battery voltage thread.");
		return -1;
	}

	// Create server
	Socket_Server = NetworkServerCreate(String_Server_IP, Server_Port);
	if (Socket_Server == -1)
	{
		printf("Error : can't bind server socket.\n");
		return -1;
	}
	else if (Socket_Server == -2)
	{
		printf("Error : can't bind server.\n");
		return -1;
	}
	else PrintDebug("Server ready.");

	// Wait for the unique client
	Socket_Client = NetworkServerListen(Socket_Server);
	if (Socket_Client < 0)
	{
		printf("Error : the client could not connect.\n");
		close(Socket_Server);
		return -1;
	}
	PrintDebug("Client connected.\n");

	while (1)
	{
		// Read a command
		if (read(Socket_Client, &Byte, 1) != 1)
		{
			printf("Could not receive client's command, disconnecting.\n");
			RobotSetMotion(ROBOT_MOTION_STOPPED);
			RobotSetLedState(0);
			close(Socket_Client);
			close(Socket_Server);
			return 0;
		}
		Command = (TCommand) Byte;

		// Execute command
		switch (Command)
		{
			case COMMAND_STOP:
				PrintDebug("Stop");
				RobotSetMotion(ROBOT_MOTION_STOPPED);
				SendAcknowledge();
				break;

			case COMMAND_FORWARD:
				PrintDebug("Forward");
				RobotSetMotion(ROBOT_MOTION_FORWARD);
				SendAcknowledge();
				break;

			case COMMAND_BACKWARD:
				PrintDebug("Backward");
				RobotSetMotion(ROBOT_MOTION_BACKWARD);
				SendAcknowledge();
				break;

			case COMMAND_LEFT:
				PrintDebug("Left");
				RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_LEFT);
				SendAcknowledge();
				break;

			case COMMAND_RIGHT:
				PrintDebug("Right");
				RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_RIGHT);
				SendAcknowledge();
				break;

			case COMMAND_READ_BATTERY_VOLTAGE:
				PrintDebug("Read battery voltage percentage : %d%%", Battery_Voltage_Percentage);
				write(Socket_Client, &Battery_Voltage_Percentage, sizeof(Battery_Voltage_Percentage));
				break;

			case COMMAND_LED_ON:
				PrintDebug("Light led");
				RobotSetLedState(1);
				SendAcknowledge();
				break;

			case COMMAND_LED_OFF:
				PrintDebug("Turn off led");
				RobotSetLedState(0);
				SendAcknowledge();
				break;
		}
	}
}
