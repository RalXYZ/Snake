/**
 * It should not be included if system.h
 * hasn't been included.
 */

#pragma once 

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	printf("\x1b[2J");
#endif
}
