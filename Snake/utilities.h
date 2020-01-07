#ifndef _UTILITIES_H
#define _UTILITIES_H

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	printf("\x1b[2J");
#endif
}

#endif
