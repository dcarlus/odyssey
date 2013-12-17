/** @file Driver_ADC.h
 * Driver for the 10-bit Analog to Digital Converter.
 * @author Adrien RICCIARDI
 * @version 1.0 : 16/12/2013
 */
#ifndef H_DRIVER_ADC_H
#define H_DRIVER_ADC_H

/** Initialize ADC module to sample the battery voltage present on pin RA0.
 * @warning This function must be called only once at the beginning of the program.
 */
void ADCInit(void);

/** Sample a 10-bit value representing the voltage at the RA0 pin. */
unsigned short ADCReadWord(void);

#endif