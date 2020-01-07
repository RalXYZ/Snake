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
	if (length > 1) //当蛇长大于1时，蛇头不可直接反向
		if ((quaternaryVector - temp) % 2 == 0)
			return quaternaryVector;
	return temp;
}
