/** @file Log.h
 * Write string data to syslog.
 * @author Adrien RICCIARDI
 * @version 1.0 : 18/01/2014
 */
#ifndef H_LOG_H
#define H_LOG_H

#include <syslog.h> // To provide LOG_XXX constants

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Enable or disable logs. */
#define LOG_ENABLE 1

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Connect to syslog.
 * @param String_Program_Name The program name which will appear in syslog.
 * @note There is no need to disconnect explicitely from syslog, so no LogQuit() function is provided.
 */
void LogInit(char *String_Program_Name);

/** Display a debug message to syslog.
 * @param Priority Syslog message priority (@see man syslog).
 * @param String_Format Format of the string to display.
 * @param ... Printf() like parameters.
 */
void Log(int Priority, char *String_Format, ...);

#endif

