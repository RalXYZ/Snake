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

extern char screen[2 * (LENGTH + 2) + 1][2 * (LENGTH + 2) + 1];
extern numberOfRow, numberOfColumn;
void gameOver() {
	screen[numberOfRow / 2][numberOfColumn - 1] = 'G';
	screen[numberOfRow / 2][numberOfColumn] = 'A';
	screen[numberOfRow / 2][numberOfColumn + 1] = 'M';
	screen[numberOfRow / 2][numberOfColumn + 2] = 'E';
	screen[numberOfRow / 2 + 1][numberOfColumn - 1] = 'O';
	screen[numberOfRow / 2 + 1][numberOfColumn] = 'V';
	screen[numberOfRow / 2 + 1][numberOfColumn + 1] = 'E';
	screen[numberOfRow / 2 + 1][numberOfColumn + 2] = 'R';
}
void youWin() {
	screen[numberOfRow / 2][numberOfColumn - 1] = 'Y';
	screen[numberOfRow / 2][numberOfColumn] = 'O';
	screen[numberOfRow / 2][numberOfColumn + 1] = 'U';
	screen[numberOfRow / 2 + 1][numberOfColumn - 1] = 'W';
	screen[numberOfRow / 2 + 1][numberOfColumn] = 'I';
	screen[numberOfRow / 2 + 1][numberOfColumn + 1] = 'N';
}
