#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <easyx.h>
#include "system.h"
#include "utilities.h"
#include "graphic.h"

double timePerFrame;
int numberOfRow = 12, numberOfColumn = 12;
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

	initgraph(280, 280);
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

		clearrectangle(0, 0, 400, 400);
		/*save all the outputs in screen[][]*/
		for (int i = 0; i < numberOfRow + 2; i++) {
			for (int j = 0; j < numberOfColumn + 2; j++) {
				if (core[i][j] == 0)
					;
				else if (core[i][j] <= length) {
					if (length == 1)
						dotRectangle(i, j);
					else {
						if (core[i][j] == 1) {
							if (core[i + 1][j] == 2)
								rightRectangle(i, j);
							else if (core[i - 1][j] == 2)
								leftRectangle(i, j);
							else if (core[i][j + 1] == 2)
								downRectangle(i, j);
							else if (core[i][j - 1] == 2)
								upRectangle(i, j);
						}
						else if (core[i][j] == length) {
							if (core[i + 1][j] == length - 1)
								rightRectangle(i, j);
							else if (core[i - 1][j] == length - 1)
								leftRectangle(i, j);
							else if (core[i][j + 1] == length - 1)
								downRectangle(i, j);
							else if (core[i][j - 1] == length - 1)
								upRectangle(i, j);
						}
						else {
							if ((core[i + 1][j] == core[i][j] + 1 || core[i + 1][j] == core[i][j] - 1)
								&& (core[i - 1][j] == core[i][j] + 1 || core[i - 1][j] == core[i][j] - 1))
								horizontalRectangle(i, j);
							else if ((core[i][j + 1] == core[i][j] + 1 || core[i][j + 1] == core[i][j] - 1)
								&& (core[i][j - 1] == core[i][j] + 1 || core[i][j - 1] == core[i][j] - 1))
								verticalRectangle(i, j);
							else {
								if ((core[i][j + 1] == core[i][j] + 1 || core[i][j + 1] == core[i][j] - 1)
									&& (core[i - 1][j] == core[i][j] + 1 || core[i - 1][j] == core[i][j] - 1))
									downLeftRectangle(i, j);
								else if ((core[i][j + 1] == core[i][j] + 1 || core[i][j + 1] == core[i][j] - 1)
									&& (core[i + 1][j] == core[i][j] + 1 || core[i + 1][j] == core[i][j] - 1))
									downRightRectangle(i, j);
								else if ((core[i][j - 1] == core[i][j] + 1 || core[i][j - 1] == core[i][j] - 1)
									&& (core[i - 1][j] == core[i][j] + 1 || core[i - 1][j] == core[i][j] - 1))
									upLeftRectangle(i, j);
								else if ((core[i][j - 1] == core[i][j] + 1 || core[i][j - 1] == core[i][j] - 1)
									&& (core[i + 1][j] == core[i][j] + 1 || core[i + 1][j] == core[i][j] - 1))
									upRightRectangle(i, j);
							}
						}
					}
				}
				else if (core[i][j] == 666)
					fillrectangle(j * 20, i * 20, j * 20 + 20, i * 20 + 20);  //return '#';
				else if (core[i][j] == 777) {
					fruitRectangle(i, j); //return 'o';
				}
			}
		}
		timePerFrame = accelerate(length);
		Sleep(timePerFrame);
	}

	/*judge win or loss after ending*/ //TODO need to fix
	if (length != numberOfRow * numberOfColumn)
		gameOver();
	else
		youWin();
	clearScreen();
	Sleep(11000);
	return 0;
}

double accelerate(int length) {
	return (5.0 * exp(3.0 - 0.05 * length) + 100);
}
