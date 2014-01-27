#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Network_Control/Sources/Log.h"
#include "../Network_Control/Sources/Network.h"
#include "../Network_Control/Sources/Security_Client.h"

int NetworkClientConnect(char *String_IP_Address, unsigned short Port)
{
	int Socket;
	struct sockaddr_in Address;

	// Create the socket
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == -1) return -1;

	// Fill server address
	Address.sin_family = AF_INET;
	Address.sin_port = htons(Port);
	Address.sin_addr.s_addr = inet_addr(String_IP_Address);

	// Connect to server
	if (connect(Socket, (const struct sockaddr *) &Address, sizeof(Address)) == -1)
	{
		close(Socket);
		return -2;
	}

	return Socket;
}

int main(int argc, char *argv[])
{
	char *String_Server_IP, *String_File_Path_Keys, *String_File_Path_Counter;
	unsigned short Server_Port;
	int Socket_Server, Return_Value = -1, Battery_Voltage_Percentage;
	static int Is_Led_Lighted = 0;

	// Connect to syslog
	LogInit("JupiterTEST");
	Log(LOG_INFO, "--- Jupiter test starting ---");

	// Check parameters
	if (argc != 5)
	{
		printf("Bad calling arguments. Usage : %s serverIpAddress serverListeningPort keysFilePath counterFilePath\n", argv[0]);
		return -1;
	}

	// Retrieve parameters values
	String_Server_IP = argv[1];
	Server_Port = atoi(argv[2]);
	String_File_Path_Keys = argv[3];
	String_File_Path_Counter = argv[4];

	// Initialize security subsystem
	switch (SecurityClientInit(String_File_Path_Keys, String_File_Path_Counter))
	{
		case 0:
			printf("Security subsystem successfully initialized.\n");
			break;
		case 1:
			printf("Error : can't find security keys file.\n");
			return -1;
		case 2:
			printf("Error : can't find security anti replay counter file.\n");
			return -1;
	}

	Socket_Server = NetworkClientConnect(String_Server_IP, Server_Port);
	if (Socket_Server < 0)
	{
		printf("Error : can't connect to server.\n");
		goto Exit;
	}

	printf("Connecting to robot...\n");
	if (!SecurityClientAuthenticateServer(Socket_Server))
	{
		printf("Error : could not authenticate robot.\n");
		goto Exit;
	}
	printf("Connected.\n");

	system("stty raw -echo");

	while (1)
	{
		switch (getchar())
		{
			case ' ':
				printf("STOP\r\n");
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_STOP);
				break;

			case 'Z':
			case 'z':
				printf("FORWARD\r\n");
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_FORWARD);
				break;

			case 'S':
			case 's':
				printf("BACKWARD\r\n");
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_BACKWARD);
				break;

			case 'Q':
			case 'q':
				printf("LEFT\r\n");
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_LEFT);
				break;

			case 'D':
			case 'd':
				printf("RIGHT\r\n");
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_RIGHT);
				break;

			case 'L':
			case 'l':
				printf("TOGGLE LED\r\n");
				if (Is_Led_Lighted) SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_LED_OFF);
				else SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_LED_ON);
				Is_Led_Lighted = !Is_Led_Lighted;
				break;

			case 'B':
			case 'b':
				printf("BATTERY VOLTAGE : ");
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_READ_BATTERY_VOLTAGE);
				SecurityClientReceiveRobotData(Socket_Server, &Battery_Voltage_Percentage);
				printf("%d %%\r\n", Battery_Voltage_Percentage);
				break;

			case 'X':
			case 'x':
				SecurityClientSendRobotCommand(Socket_Server, ROBOT_COMMAND_STOP);
				Return_Value = 0;
				goto Exit;
		}
	}

Exit:
	system("stty -raw echo");
	SecurityClientQuit();
	return Return_Value;
}
