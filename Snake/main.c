#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "system.h"
#include "utilities.h"

double timePerFrame;
int numberOfRow = 12, numberOfColumn = 12;
int pulse = 0; //control the food 'o' 'O'
char screen[2 * (LENGTH + 2) + 1][2 * (LENGTH + 2) + 1] = { 0 };
double accelerate(int length);
int keyToQuaternary(char input, int quaternaryVector, int length); //interpret the user input to "orientation value"
void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn); //manipulate the position of the snake's head directly
char coreToScreen(int number, int length, int quaternaryVector);

int main() {
	/*create the seed for randoming*/
	srand((unsigned)time(NULL));

	/*data initialization*/
	int core[LENGTH + 2][LENGTH + 2] = { 0 };

	int currentRow = numberOfRow / 2 + 1, currentColumn = numberOfColumn / 2 + 1;
	int quaternaryVector = rand() % 4;
	int length = 1;
	bool judgeSeed = false;

	/*checkerboard initialization*/
	for (int i = 0; i < numberOfRow + 2; i++) {
		if (i == 0 || i == numberOfRow + 1) //place '#' at the first and the last row
			for (int j = 0; j < numberOfColumn + 2; j++)
				core[i][j] = 666;
		else //place '#' at the start and the end of each resting row
			for (int j = 0; j < numberOfColumn + 2; j++)
				if (j == 0 || j == numberOfColumn + 1)
					core[i][j] = 666;
	}

	while (true) {
		/*detect user keyboard input, and judge the next location of the snake's head based on it*/
		if (_kbhit())
			quaternaryVector = keyToQuaternary(_getch(), quaternaryVector, length);
		quaternaryToVector(quaternaryVector, &currentRow, &currentColumn);

		/*detect what exists at the next position the snake's head locates*/
		if (core[currentRow][currentColumn] == 777) {
			++length;
			judgeSeed = false;
		}
		else if (core[currentRow][currentColumn] != 0)
			break;

		/*the movement of snake*/
		for (int i = 1; i <= numberOfRow; i++) {
			for (int j = 1; j <= numberOfColumn; j++)
				if (core[i][j] != 0 && core[i][j] != 777) {
					++core[i][j];
					if (core[i][j] > length)
						core[i][j] = 0;
				}
		}
		core[currentRow][currentColumn] = 1;

		/*place food randomly until the food is not located on the snake's body*/
		while (judgeSeed == false) {
			int tempRow = rand() % numberOfRow + 1;
			int tempColumn = rand() % numberOfColumn + 1;
			if (core[tempRow][tempColumn] == 0) {
				core[tempRow][tempColumn] = 777;
				judgeSeed = true;
			}
		}

		/*save all the outputs in screen[][]*/
		for (int i = 0; i < numberOfRow + 2; i++) {
			for (int j = 0; j < numberOfColumn + 2; j++) {
				screen[i][2 * j] = coreToScreen(core[i][j], length, quaternaryVector);
				screen[i][2 * j + 1] = ' '; //attention, that for the visual beauty, I considered the pixles each character occupies, so I add one space ' ' after each character
			}
			screen[i][2 * (numberOfColumn + 1) + 1] = '\n';
		}

		/*assistant data*/
		// multiple unsequenced modifications to 'pulse'
		pulse++;
		pulse %= 2;

		/*outputing*/
		clearScreen();
		for (int i = 0; i < numberOfRow + 2; i++)
			printf("%s", screen[i]);
		printf("Your current length is: %d\n", length);
		timePerFrame = accelerate(length);
		Sleep(timePerFrame);
	}

	/*judge win or loss after ending*/
	if (length != numberOfRow * numberOfColumn)
		gameOver();
	else
		youWin();
	clearScreen();
	for (int i = 0; i < numberOfRow + 2; i++)
		printf("%s", screen[i]);
	printf("Your final length is: %d\n", length);
	Sleep(11000);
	return 0;
}

double accelerate(int length) {
	return (5.0 * exp(3.0 - 0.05 * length) + 100);
}

char coreToScreen(int number, int length, int quaternaryVector) {
	if (number == 0)
		return ' ';
	else if (number <= length)
		if (number != 1)
			return '*';
		else
			switch (quaternaryVector) { //head pointed to different directions
			case 0:
				return '>';
			case 1:
				return 'A';
			case 2:
				return '<';
			case 3:
				return 'V';
			}
	else if (number == 666)
		return '#';
	else if (number == 777) {
		if (pulse == 0)
			return 'o';
		else
			return 'O';
	}
	return '?'; // warning: control may reach end of non-void function
}
