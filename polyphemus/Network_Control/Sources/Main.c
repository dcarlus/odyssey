/** @file Main.c
 * Main loop.
 * @author Adrien RICCIARDI
 * @version 1.0 : 07/01/2014
 * @version 1.1 : 09/01/2014, added debugging function.
 * @version 1.2 : 11/01/2014, debug is now written to syslog and server is a daemon.
 * @version 1.3 : 14/01/2014, added security.
 */
#include <stdio.h>
#include <unistd.h> // For read(), write()...
#include <pthread.h>
#include <stdlib.h> // For atoi()
#include <signal.h>
#include "Robot.h"
#include "Network.h"
#include "Security_Server.h"
#include "Log.h"
#include "Crypto/Utils.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private constants
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** The acknowledge code. */
#define COMMAND_ACKNOWLEDGE 32

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static int Socket_Server, Socket_Client;
static unsigned char Battery_Voltage_Percentage = 0;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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

/** Read the battery voltage each second. */
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

/** Called when the SIGTERM signal is received, stop the server.
 * @param Signal_Number The signal which triggered the handler.
 */
static void SignalHandler(int Signal_Number)
{
	SecurityServerQuit();
	close(Socket_Client);
	close(Socket_Server);
	Log(LOG_INFO, "Server successfully exited.");
	exit(0);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	pthread_t Thread_ID;
	char *String_Server_IP, *String_File_Path_Keys, *String_File_Path_Counter;
	unsigned short Server_Port;
	TRobotCommand Command;
	struct sigaction Signal_Action;

	// Connect to syslog
	LogInit("Polyphemus");
	Log(LOG_INFO, "--- Polyphemus server starting ---");

	// Check parameters
	if (argc != 5)
	{
		Log(LOG_ERR, "Bad calling arguments. Usage : %s serverIpAddress serverListeningPort keysFilePath counterFilePath", argv[0]);
		return -1;
	}

	// Retrieve parameters values
	String_Server_IP = argv[1];
	Server_Port = atoi(argv[2]);
	String_File_Path_Keys = argv[3];
	String_File_Path_Counter = argv[4];

	// Connect to the robot
	if (!RobotInit("/dev/ttyAMA0"))
	{
		Log(LOG_ERR, "Error : can't connect to the robot.");
		return -1;
	}
	// Stop robot in case of UART glitch
	RobotSetMotion(ROBOT_MOTION_STOPPED);
	RobotSetLedState(0);

	// Initialize security subsystem
	switch (SecurityServerInit(String_File_Path_Keys, String_File_Path_Counter))
	{
		case 0:
			Log(LOG_INFO, "Security subsystem successfully initialized.");
			break;
		case 1:
			Log(LOG_ERR, "Error : can't find security keys file.");
			return -1;
		case 2:
			Log(LOG_ERR, "Error : can't find security anti replay counter file.");
			return -1;
	}

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

	// Set a new signal handler for SIGTERM, which is sent to stop the daemon
	Signal_Action.sa_handler = SignalHandler;
	if (sigaction(SIGTERM, &Signal_Action, NULL) == -1)
	{
		Log(LOG_ERR, "Error : can't register signal handler.");
		return -1;
	}

	// Daemonize server
	if (daemon(0, 1) != 0)
	{
		Log(LOG_ERR, "Error : can't daemonize server.");
		return -1;
	}

	Log(LOG_INFO, "Server ready.");

	while (1)
	{
		Log(LOG_INFO, "Server waiting for client...");

		// Wait for the unique client
		Socket_Client = NetworkServerListen(Socket_Server);
		if (Socket_Client < 0)
		{
			Log(LOG_ERR, "Error : the client could not connect.");
			close(Socket_Server);
			return -1;
		}
		Log(LOG_INFO, "Client trying to connect...");

		// Authenticate client
		if (!SecurityServerAuthenticateClient(Socket_Client))
		{
			Log(LOG_WARNING, "Warning : could not authenticate client (maybe robot is under attack ?).");
			close(Socket_Client);
			continue;
		}
		Log(LOG_INFO, "Client connected.");

		while (1)
		{
			// Wait for a command
			if (!SecurityServerReceiveRobotCommand(Socket_Client, &Command))
			{
				Log(LOG_INFO, "Could not receive client's command, disconnecting.");
				RobotSetMotion(ROBOT_MOTION_STOPPED);
				RobotSetLedState(0);
				close(Socket_Client);
				break;
			}

			// Execute command
			switch (Command)
			{
				case ROBOT_COMMAND_STOP:
					Log(LOG_DEBUG, "Stop.");
					RobotSetMotion(ROBOT_MOTION_STOPPED);
					//SendAcknowledge();
					break;

				case ROBOT_COMMAND_FORWARD:
					Log(LOG_DEBUG, "Forward.");
					RobotSetMotion(ROBOT_MOTION_FORWARD);
					//SendAcknowledge();
					break;

				case ROBOT_COMMAND_BACKWARD:
					Log(LOG_DEBUG, "Backward.");
					RobotSetMotion(ROBOT_MOTION_BACKWARD);
					//SendAcknowledge();
					break;

				case ROBOT_COMMAND_LEFT:
					Log(LOG_DEBUG, "Left.");
					RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_LEFT);
					//SendAcknowledge();
					break;

				case ROBOT_COMMAND_RIGHT:
					Log(LOG_DEBUG, "Right.");
					RobotSetMotion(ROBOT_MOTION_FORWARD_TURN_RIGHT);
					//SendAcknowledge();
					break;

				case ROBOT_COMMAND_READ_BATTERY_VOLTAGE:
					Log(LOG_DEBUG, "Read battery voltage percentage : %d%%.", Battery_Voltage_Percentage);
					SecurityServerSendRobotData(Socket_Client, Battery_Voltage_Percentage);
					break;

				case ROBOT_COMMAND_LED_ON:
					Log(LOG_DEBUG, "Light led.");
					RobotSetLedState(1);
					//SendAcknowledge();
					break;

				case ROBOT_COMMAND_LED_OFF:
					Log(LOG_DEBUG, "Turn off led.");
					RobotSetLedState(0);
					//SendAcknowledge();
					break;

				default:
					Log(LOG_DEBUG, "Unknown command received.");
					break;
			}
		}
	}
}
