#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <windows.h>

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	printf("\x1b[2J");
#endif
}

#endif
