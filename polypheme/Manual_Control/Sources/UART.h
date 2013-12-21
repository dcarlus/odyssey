/** @file UART.h
 * Easy-to-use RS-232 communication layer.
 * @author Adrien RICCIARDI
 * @version 1.0 : 24/02/2013
 */
#ifndef H_UART_H
#define H_UART_H

#include <termios.h> // Needed by speed_t

/** Initialize PC UART at the specified baud rate, 8 data bit, no parity, 1 stop bit.
 * @param String_Device_File_Name Name of the UART device, like "/dev/ttyS0" or "/dev/ttyUSB0" if using USB serial port converter.
 * @param Baud_Rate Speed in bit/s. Use a termios Bxxx constant to specify speed.
 * @return 1 if the UART was correctly initialized or 0 if not. See errno to find the error.
 */
int UARTOpen(char *String_Device_File_Name, speed_t Baud_Rate);

/** Read a byte from the UART.
 * @return The read byte.
 * @warning This is a blocking function.
 */
unsigned char UARTReadByte(void);

/** Write a byte to the UART.
 * @param Byte The byte to send.
 */
void UARTWriteByte(unsigned char Byte);

/** Check if a byte was received by the UART.
 * @param Available_Byte Store the received byte if there was one available.
 * @return 0 if no byte was received (and Available_Byte has unknown value) or 1 if a byte is available (in this case the byte is stored into Available_Byte).
 */
int UARTIsByteAvailable(unsigned char *Available_Byte);

/** Restore previous parameters and close UART. */
void UARTClose(void);

#endif
