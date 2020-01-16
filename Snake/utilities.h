/**
 * It should not be included if system.h
 * hasn't been included.
 */

#pragma once 
#define LENGTH 40

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	printf("\x1b[2J");
#endif
}

void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn) {
	switch (quaternaryVector) {
	case 0:
		++(*currentRow);
		break;
	case 2:
		--(*currentRow);
		break;
	case 1:
		--(*currentColumn);
		break;
	case 3:
		++(*currentColumn);
		break;
	}
}

int keyToQuaternary(char input, int quaternaryVector, int length) {
	int temp = quaternaryVector;
	switch (input) {
	case 'D': case 'd': // >
		temp = 0;
		break;
	case 'W': case 'w': // ^
		temp = 1;
		break;
	case 'A': case 'a': // <
		temp = 2;
		break;
	case 'S': case 's': // v
		temp = 3;
		break;
	}
	if (length > 1) //the snake should not reverse its orientation when its length is bigger than 1
		if ((quaternaryVector - temp) % 2 == 0)
			return quaternaryVector;
	return temp;
}
