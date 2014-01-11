/** @file Main.c
 * Main loop.
 * @author Adrien RICCIARDI
 * @version 1.0 : 07/01/2014
 * @version 1.1 : 09/01/2014, added debugging function.
 * @version 1.2 : 11/01/2014, debug is now written to syslog and server is a daemon.
 */
#include <stdio.h>
#include <unistd.h> // For read(), write()...
#include <pthread.h>
#include <stdlib.h> // For atoi()
#include <stdarg.h> // For va_list and friends
#include <syslog.h>
#include "Robot.h"
#include "Network.h"

/** Comment this to disable all debug messages. */
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

/** Display a debug message to syslog.
 * @param Priority Syslog message priority (@see man syslog).
 * @param String_Format Format of the string to display.
 * @param ... Printf() like parameters.
 */
static void Log(int Priority, char *String_Format, ...)
{
	#ifdef DEBUG
		va_list List_Arguments;

		va_start(List_Arguments, String_Format);
		vsyslog(Priority, String_Format, List_Arguments);
		va_end(List_Arguments);
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
		Log(LOG_WARNING, "WARNING : could not send acknowledge to client, stopping robot.\n");
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

	// Connect to syslog
	openlog("Polyphemus", LOG_CONS, LOG_DAEMON);

	// Check parameters
	if (argc != 3)
	{
		Log(LOG_ERR, "Bad calling arguments.\nUsage : %s serverIpAddress serverListeningPort\n", argv[0]);
		return -1;
	}

	// Retrieve parameters values
	String_Server_IP = argv[1];
	Server_Port = atoi(argv[2]);

	// Connect to the robot
	if (!RobotInit("/dev/ttyAMA0"))
	{
		Log(LOG_ERR, "Error : can't connect to the robot.");
		return -1;
	}
	// Stop robot in case of UART glitch
	RobotSetMotion(ROBOT_MOTION_STOPPED);
	RobotSetLedState(0);

	// Create threads
	if (pthread_create(&Thread_ID, NULL, ThreadReadBatteryVoltage, NULL) != 0)
	{
		Log(LOG_ERR, "Error : can't create battery voltage thread.");
		return -1;
	}

	// Create server
	Socket_Server = NetworkServerCreate(String_Server_IP, Server_Port);
	if (Socket_Server == -1)
	{
		Log(LOG_ERR, "Error : can't bind server socket.");
		return -1;
	}
	else if (Socket_Server == -2)
	{
		Log(LOG_ERR, "Error : can't bind server.");
		return -1;
	}

	// Daemonize server
	if (daemon(0, 1) != 0)
	{
		Log(LOG_ERR, "Error : can't daemonize server.");
		return -1;
	}

	while (1)
	{
		Log(LOG_INFO, "Server ready.");

		// Wait for the unique client
		Socket_Client = NetworkServerListen(Socket_Server);
		if (Socket_Client < 0)
		{
			Log(LOG_ERR, "Error : the client could not connect.\n");
			close(Socket_Server);
			return -1;
		}
		Log(LOG_INFO, "Client connected.\n");

		while (1)
		{
			// Read a command
			if (read(Socket_Client, &Byte, 1) != 1)
			{
				Log(LOG_INFO, "!!!! Could not receive client's command, disconnecting !!!!\n");
				RobotSetMotion(ROBOT_MOTION_STOPPED);
				RobotSetLedState(0);
				close(Socket_Client);
				break;
			}
			Command = (TCommand) Byte;

			// Execute command
			switch (Command)
			{
				case COMMAND_STOP:
					Log(LOG_DEBUG, "Stop");
					RobotSetMotion(ROBOT_MOTION_STOPPED);
					SendAcknowledge();
					break;

				case COMMAND_FORWARD:
					Log(LOG_DEBUG, "Forward");
					RobotSetMotion(ROBOT_MOTION_FORWARD);
					SendAcknowledge();
					break;

				case COMMAND_BACKWARD:
					Log(LOG_DEBUG, "Backward");
					RobotSetMotion(ROBOT_MOTION_BACKWARD);
					SendAcknowledge();
					break;

				case COMMAND_LEFT:
					Log(LOG_DEBUG, "Left");
					RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_LEFT);
					SendAcknowledge();
					break;

				case COMMAND_RIGHT:
					Log(LOG_DEBUG, "Right");
					RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_RIGHT);
					SendAcknowledge();
					break;

				case COMMAND_READ_BATTERY_VOLTAGE:
					Log(LOG_DEBUG, "Read battery voltage percentage : %d%%", Battery_Voltage_Percentage);
					write(Socket_Client, &Battery_Voltage_Percentage, sizeof(Battery_Voltage_Percentage));
					break;

				case COMMAND_LED_ON:
					Log(LOG_DEBUG, "Light led");
					RobotSetLedState(1);
					SendAcknowledge();
					break;

				case COMMAND_LED_OFF:
					Log(LOG_DEBUG, "Turn off led");
					RobotSetLedState(0);
					SendAcknowledge();
					break;
			}
		}
	}
}
