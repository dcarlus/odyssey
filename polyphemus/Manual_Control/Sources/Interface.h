/** @file Interface.h
 * Display robot informations on a terminal screen.
 * @author Adrien RICCIARDI
 * @version 1.0 : 20/12/2013
 */
#ifndef H_INTERFACE_H
#define H_INTERFACE_H

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------
/** Initialize the terminal interface.
 * @return 1 if the initialization was successful or 0 otherwise.
 */
int InterfaceInit(void);

/** This function must be called prior to exit program to release all allocated resources. */
void InterfaceTerminate(void);

/** Display the battery voltage.
 * @param Percentage Battery charge value in range [0, 100].
 * @param Voltage Battery current voltage.
 */
void InterfaceDisplayBatteryVoltage(int Percentage, float Voltage);

/** Display the current direction.
 * @param String_Direction A null-terminated string indicating the direction.
 */
void InterfaceDisplayDirection(char *String_Direction);

/** Display the last speed modification.
 * @param String_Speed A null-terminated string indicating the speed modification.
 */
void InterfaceDisplaySpeed(char *String_Speed);

/** Show keyboard commands and hints on the bottom of the screen. */
void InterfaceDisplayHints(void);

#endif
