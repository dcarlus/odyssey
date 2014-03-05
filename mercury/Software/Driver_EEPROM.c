/** @file Driver_EEPROM.c
 * @see Driver_EEPROM.h for description.
 * @author Adrien RICCIARDI
 */
#include <system.h>
#include "Driver_EEPROM.h"

//---------------------------------------------------------------------------------------------------------------
// Private functions
//---------------------------------------------------------------------------------------------------------------
/** Read a byte from the internal EEPROM.
 * @param Address The EEPROM location to read from.
 * @return The read byte value.
 */
static unsigned char EEPROMReadByte(unsigned char Address)
{
	eeadr = Address;
	
	// Do read operation
	eecon1.EEPGD = 0; // Select EEPROM memory
	eecon1.RD = 1; // Start reading
	
	// Wait for the read operation to finish
	while (eecon1.RD);
	
	return eedata;
}

/** Write a byte to the internal EEPROM.
 * @param Address The EEPROM location to write to.
 * @param Byte The value to write.
 */
static void EEPROMWriteByte(unsigned char Address, unsigned char Byte)
{
	// Set location and data to write
	eeadr = Address;
	eedata = Byte;
	
	// Disable interrupts
	intcon.GIE = 0;
	
	// Configure write operation
	eecon1.EEPGD = 0; // Select EEPROM memory
	eecon1.WREN = 1; // Enable writing to the EEPROM
	
	// Do special write sequence
	eecon2 = 0x55;
	eecon2 = 0xAA;
	eecon1.WR = 1; // Start write operation
	
	// Wait for the write operation to finish
	while (eecon1.WR);
	
	// Disable writing to the EEPROM
	eecon1.WREN = 0;
	
	// Reenable interrupts
	intcon.GIE = 1;
}

//---------------------------------------------------------------------------------------------------------------
// Public functions
//---------------------------------------------------------------------------------------------------------------
unsigned short EEPROMReadWord(unsigned char Address)
{
	unsigned short Return_Value = 0;
	unsigned char High_Byte, Low_Byte;
	
	if (Address < EEPROM_SIZE_BYTES - 1)
	{
		// Retrieve little-endian data
		Low_Byte = EEPROMReadByte(Address); // Low order byte
		High_Byte = EEPROMReadByte(Address + 1); // High order byte
		Return_Value = (High_Byte << 8) | Low_Byte;
	}
		
	return Return_Value;
}

void EEPROMWriteWord(unsigned char Address, unsigned short Word)
{
	if (Address < EEPROM_SIZE_BYTES - 1)
	{
		// Store data in little-endian form
		EEPROMWriteByte(Address, Word);
		EEPROMWriteByte(Address + 1, Word >> 8);
	}
}