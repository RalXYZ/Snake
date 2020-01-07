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

void quaternaryVectorInterpreter(int quaternaryVector, int* currentRow, int* currentColumn) {
	switch (quaternaryVector) {
	case 0:
		++(*currentColumn);
		break;
	case 2:
		--(*currentColumn);
		break;
	case 1:
		--(*currentRow);
		break;
	case 3:
		++(*currentRow);
		break;
	}
}

int keyToQuaternary(char input, int quaternaryVector, int length) {
	int temp = quaternaryVector;
	if (input == 'D' || input == 'd')
		temp = 0;
	else if (input == 'W' || input == 'w')
		temp = 1;
	else if (input == 'A' || input == 'a')
		temp = 2;
	else if (input == 'S' || input == 's')
		temp = 3;
	if (length > 1) //当蛇长大于1时，蛇头不可直接反向
		if ((quaternaryVector - temp) % 2 == 0)
			return quaternaryVector;
	return temp;
}
#endif
