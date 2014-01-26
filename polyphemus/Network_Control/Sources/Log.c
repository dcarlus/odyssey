/** @file Log.c
 * @see Log.h for description.
 * @author Adrien RICCIARDI
 */
#include <syslog.h>
#include <stdarg.h>
#include "Log.h"

void LogInit(char *String_Program_Name)
{
	openlog(String_Program_Name, LOG_CONS, LOG_DAEMON);
}

void Log(int Priority, char *String_Format, ...)
{
	#if LOG_ENABLE == 1
		va_list List_Arguments;

		va_start(List_Arguments, String_Format);
		vsyslog(Priority, String_Format, List_Arguments);
		va_end(List_Arguments);
	#endif
}


