/** @file Driver_EEPROM.h
 * Allow to store and retrieve bytes in the internal EEPROM.
 * @author Adrien RICCIARDI
 * @version 1.0 : 01/03/2014
 */
#ifndef H_DRIVER_EEPROM_H
#define H_DRIVER_EEPROM_H

//---------------------------------------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------------------------------------
/** Size in bytes of the internal EEPROM. */
#define EEPROM_SIZE_BYTES 256

//---------------------------------------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------------------------------------
/** Read a 16-bit value from the internal EEPROM.
 * @param Address The address to read from.
 * @return The read 16-bit value.
 * @warning As the EEPROM is 256-byte wide, a word read at the address 255 is not allowed (the function will return 0).
 */
unsigned short EEPROMReadWord(unsigned char Address);

/** Write a 16-bit value to the internal EEPROM.
 * @param Address The EEPROM location to write to.
 * @param Word The value to write.
 * @warning As the EEPROM is 256-byte wide, a word write at the address 255 is not allowed (the function will do nothing).
 */
void EEPROMWriteWord(unsigned char Address, unsigned short Word);

#endif