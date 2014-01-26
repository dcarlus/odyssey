/** @file Network.c
 * @see Network.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h> // For NULL
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // For htons()
#include <netinet/in.h>
#include <unistd.h> // For close()

int NetworkServerCreate(char *String_IP_Address, unsigned short Port)
{
	int Socket, Is_Enabled = 1;
	struct sockaddr_in Address;

	// Create the socket
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == -1) return -1;

	// Allow address to be reused instantly
	setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &Is_Enabled, sizeof(Is_Enabled));

	// Bind the specified port
	Address.sin_family = AF_INET;
	Address.sin_port = htons(Port);
	Address.sin_addr.s_addr = inet_addr(String_IP_Address);
	if (bind(Socket, (const struct sockaddr *) &Address, sizeof(Address)) == -1)
	{
		close(Socket);
		return -2;
	}

	return Socket;
}

int NetworkServerListen(int Socket_Server)
{
	int Socket_Client;

	// Listen for one client
	if (listen(Socket_Server, 1) == -1) return -1;

	// Accept him
	Socket_Client = accept(Socket_Server, NULL, NULL);
	if (Socket_Client == -1) return -2;

	return Socket_Client;
}

int NetworkServerWrite(int Socket_Client, const void *Message, const int Message_Length)
{
    int Length_Sent = write(Socket_Client, Message, Message_Length);
    if (Length_Sent == -1) return -2;

    return Length_Sent;
}


int NetworkServerRead(int Socket_Client, void *Message, const int Message_Length)
{
    int Length_Read = read(Socket_Client, Message, Message_Length);
    if (Length_Read == -1) return -2;

    return Length_Read;
}
