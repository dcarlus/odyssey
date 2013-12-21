/** @file Interface.c
 * @see Interface.h for description.
 * @author Adrien RICCIARDI
 */
#include <curses.h>
#include <string.h>
#include "Interface.h"

//-----------------------------------------------------------------------------
// Private constants
//-----------------------------------------------------------------------------
// Ncurses color pairs
#define COLOR_PAIR_YELLOW 1
#define COLOR_PAIR_RED 2

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------
int InterfaceInit(void)
{
	// Initialize curses
	if (initscr() == NULL) return 0;

	// Save current terminal screen
	savetty();

	// Enable use of colors
	start_color();
	// Create all colors used by the program
	init_pair(COLOR_PAIR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_PAIR_RED, COLOR_RED, COLOR_BLACK);

	// Disable terminal line buffering to get each character when user types it
	if (cbreak() == ERR)
	{
		InterfaceTerminate();
		return 0;
	}

	// Disable characters echo
	if (noecho() == ERR)
	{
		InterfaceTerminate();
		return 0;
	}

	// Hide cursor
	curs_set(0);

	return 1;
}

void InterfaceTerminate(void)
{
	// Restore previous terminal screen
	resetty();

	// Stop ncurses
	endwin();
}

void InterfaceDisplayBatteryVoltage(int Percentage, float Voltage)
{
	char String_Output[32];
	int Is_Battery_Low;

	if (Percentage < 30) Is_Battery_Low = 1;
	else Is_Battery_Low = 0;

	// Format values (the extra spaces at the end of the line are used to erase a longer line previously displayed)
	sprintf(String_Output, "Battery : %d%% (%.2f V)     ", Percentage, Voltage);

	// Display values
	if (Is_Battery_Low) attron(COLOR_PAIR(COLOR_PAIR_RED));
	mvaddstr(0, 0, String_Output);
	if (Is_Battery_Low) attroff(COLOR_PAIR(COLOR_PAIR_RED));
	refresh();
}

void InterfaceDisplayDirection(char *String_Direction)
{
	mvaddstr(2, 0, "Direction : ");
	attron(COLOR_PAIR(COLOR_PAIR_YELLOW));
	addstr(String_Direction);
	attroff(COLOR_PAIR(COLOR_PAIR_YELLOW));
	refresh();
}

void InterfaceDisplayHints(void)
{
	char *String_Hints = "Use Z, Q, S, D keys to move the robot.\nHit Space to stop the robot.\nHit X to quit program.";

	mvaddstr(LINES - 3, 0, String_Hints);
}
