/** @file Driver_UART.h
 * Driver for the RS-232 Universal Asynchronous Receiver Transmitter.
 * @author Adrien RICCIARDI
 * @version 1.0 : 15/12/2013
 * @version 1.1 : 03/03/2014, handled reception overrun error.
 */ 
#ifndef H_DRIVER_UART_H
#define H_DRIVER_UART_H

#include <system.h> // Needed to use registers names

//---------------------------------------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------------------------------------
/** Baud rate of 115200 bit/s with a 3.6864 MHz clock. */
#define UART_BAUD_RATE_115200 1
/** Baud rate of 230400 bit/s with a 3.6864 MHz clock. */
#define UART_BAUD_RATE_230400 0

//---------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------
/** Initialize UART module at the specified baud rate.
 * @param Baud_Rate Use a UART_BAUD_RATE_X constant to indicate wanted baud rate.
 * @warning This function must be called only once at the beginning of the program.
 */
void UARTInit(unsigned char Baud_Rate);

/** Read a byte from the UART.
 * @return The read byte.
 * @note This function waits until a byte is available.
 */
unsigned char UARTReadByte(void);

/** Write a byte to the UART.
 * @param Byte The byte to write.
 */
void UARTWriteByte(unsigned char Byte);

/** Allow a received byte to trigger an interrupt. */
#ifdef DOXYGEN
	void UARTEnableInterrupt(void);
#else
	#define UARTEnableInterrupt() pie1.RCIE = 1
#endif

/** Disable all UART-related interrupts. */
#ifdef DOXYGEN
	void UARTDisableInterrupt(void);
#else
	#define UARTDisableInterrupt() pie1.RCIE = 0
#endif

/** Check if the UART interrupt happened.
 * @return 1 if the interrupt has triggered or 0 if not.
 */
#ifdef DOXYGEN
	unsigned char UARTHasInterruptOccured(void);
#else
	#define UARTHasInterruptOccured() pir1.RCIF
#endif

/** Clear interrupt flag to allow new interrupt. */
#ifdef DOXYGEN
	void UARTClearInterruptFlag(void);
#else
	#define UARTClearInterruptFlag() pir1.RCIF = 0
#endif

#endif