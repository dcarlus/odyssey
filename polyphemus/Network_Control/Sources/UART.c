/** RS-232 simple interface.
 * @see UART.h for description.
 * @author Adrien RICCIARDI
 */
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "UART.h"

// File representing the UART
static int File_Descriptor_UART;

// Old UART parameters
static struct termios Parameters_Old;

int UARTOpen(char *String_Device_File_Name, speed_t Baud_Rate)
{
	struct termios Parameters_New;

	// Open device file
	File_Descriptor_UART = open(String_Device_File_Name, O_RDWR | O_NONBLOCK);
	if (File_Descriptor_UART == -1) return 0;

	// Backup old UART parameters
	if (tcgetattr(File_Descriptor_UART, &Parameters_Old) == -1) return 0;

	// Configure new parameters
	Parameters_New.c_iflag = IGNBRK | IGNPAR; // Ignore break, no parity
	Parameters_New.c_oflag = 0;
	Parameters_New.c_cflag = CS8 | CREAD | CLOCAL; // 8 data bits, receiver enabled, ignore modem control lines
	Parameters_New.c_lflag = 0; // Use raw mode

	// Set speeds
	if (cfsetispeed(&Parameters_New, Baud_Rate) == -1) return 0;
	if (cfsetospeed(&Parameters_New, Baud_Rate) == -1) return 0;

	// Set parameters
	if (tcsetattr(File_Descriptor_UART, TCSANOW, &Parameters_New) == -1) return 0;
	return 1;
}

unsigned char UARTReadByte(void)
{
	unsigned char Byte;

	while (read(File_Descriptor_UART, &Byte, 1) <= 0);
	return Byte;
}

void UARTWriteByte(unsigned char Byte)
{
	write(File_Descriptor_UART, &Byte, 1);
}

int UARTIsByteAvailable(unsigned char *Available_Byte)
{
	if (read(File_Descriptor_UART, Available_Byte, 1) == 1) return 1;
	return 0;
}

void UARTClose(void)
{
	// Restore previous parameters
	tcsetattr(File_Descriptor_UART, TCSANOW, &Parameters_Old);
	close(File_Descriptor_UART);
}
