/** @file Driver_UART.c
 * @see Driver_UART.h for description.
 * @author Adrien RICCIARDI
 */
#include <system.h>
#include "Driver_UART.h"

void UARTInit(unsigned char Baud_Rate)
{
	// Set UART pins as inputs
	trisc.7 = 1;
	trisc.6 = 1;
	
	// Configure module
	spbrg = Baud_Rate; // Set baud rate
	txsta = 0x26; // 8-bit transmission, transmission enabled, high speed
	rcsta = 0x90; // Reception and serial port module enabled
}

unsigned char UARTReadByte(void)
{
	// Check if an overrun error happened
	if (rcsta.OERR)
	{
		// Clear error
		rcsta.OERR = 0;
		
		// Reset receiver logic to reenable reception
		rcsta.CREN = 0;
		rcsta.CREN = 1;
	}

	// Wait for data to be received
	while (!pir1.RCIF);
	// Get data
	return rcreg;
}

void UARTWriteByte(unsigned char Byte)
{
	// Wait until the Tx line becomes available
	while (!pir1.TXIF);
	// Send data
	txreg = Byte;
}