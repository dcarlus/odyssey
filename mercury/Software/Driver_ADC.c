/** @file Driver_ADC.c
 * @see Driver_ADC.h for description.
 * @author Adrien RICCIARDI
 */
#include <system.h>
#include "Driver_ADC.h"

void ADCInit(void)
{
	// Configure ADC pin as input
	trisa.0 = 1;
	
	// Configure module
	adcon1 = 0x8E; // Result is right justified, select only RA0 as analog input
	adcon0 = 0x41; // Use a conversion clock of Fosc/8, select channel 0, enable module 
}

unsigned short ADCReadWord(void)
{
	// Start conversion
	adcon0.GO = 1;
	
	// Wait for conversion to finish
	while (adcon0.GO);
	return ((adresh << 8) & 0xFF00) | adresl;
}