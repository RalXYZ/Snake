#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <easyx.h>
#include <string>
#include <thread>
#include "resource.h"

#define HORIZENTAL 336
#define VERTICAL 408
#define CUBE 24
#define PUR 0x3a2528
#define PIK 0x4f17c3
#define GOD 0x8d83b5

#include "system.h"
#include "utilities.h"
#include "graphic.h"

double timePerFrame;
int numberOfRow = 12, numberOfColumn = 12;
double accelerate(int length);
int keyToQuaternary(char input, int quaternaryVector, int length); //interpret the user input to "orientation value"
void quaternarsyToVector(int quaternaryVector, int* currentRow, int* currentColumn); //manipulate the position of the snake's head directly
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

	initgraph(HORIZENTAL, VERTICAL);
	setbkcolor(PUR);
	setfillcolor(GOD);
	setlinestyle(PS_NULL);
	clearrectangle(0, 0, HORIZENTAL, VERTICAL);
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
		char key = '\0';
		if (key = _kbhit()) {
			key = _getch();
			if (key == ' ') {
				clearrectangle(0, 336, HORIZENTAL, VERTICAL);
				paused();
				_getch();
				clearrectangle(0, 336, HORIZENTAL, VERTICAL);
			}
			else
				quaternaryVector = keyToQuaternary(key, quaternaryVector, length);
		}

		quaternaryToVector(quaternaryVector, &currentRow, &currentColumn);

		/*detect what exists at the next position the snake's head locates*/
		if (core[currentRow][currentColumn] == 777) {
			++length;
			judgeSeed = false;
			std::thread sound(eatSound);
			sound.detach();
		}
		else if (core[currentRow][currentColumn] != 0 && core[currentRow][currentColumn] != length)
			break;
		else
			for (int i = 1; i <= numberOfRow; i++)
				for (int j = 1; j <= numberOfColumn; j++)
					if (core[i][j] != 0 && (core[i][j] == length || core[i][j] == length - 1))
						clearrectangle(i * 24, j * 24, i * 24 + 24, j * 24 + 24);

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

		clearrectangle(0, 336, HORIZENTAL, VERTICAL);
		wchar_t s[5];
		wsprintf(s, L"%d", length);
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 48;
		f.lfWidth = 18;
		_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(PIK);
		outtextxy(168 - ((int)log10(length) + 1) * 9, 336, s);
		settextcolor(GOD);

		gettextstyle(&f);
		f.lfHeight = 20;
		f.lfWidth = 8;
		f.lfPitchAndFamily = FIXED_PITCH;
		_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(PIK);
		outtextxy(72, 384, _T("PRESS SPACE TO PAUSE"));
		settextcolor(GOD);

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
						else if (core[i][j] == 2 || core[i][j] == length - 1) {
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
				else if (core[i][j] == 666) {
					setfillcolor(PIK);
					setfillstyle(BS_HATCHED, HS_DIAGCROSS);
					fillrectangle(j * CUBE, i * CUBE, j * CUBE + CUBE, i * CUBE + CUBE);  //return '#';
					setfillstyle(BS_SOLID);
					setfillcolor(GOD);
				}

				else if (core[i][j] == 777) {
					setfillcolor(PIK);
					fruitRectangle(i, j); //return 'o';
					setfillcolor(GOD);
				}
			}
		}
		timePerFrame = accelerate(length);
		Sleep(timePerFrame);
	}

	/*judge win or loss after ending*/ //TODO need to fix
	if (length != numberOfRow * numberOfColumn) {
		char key = '\0';
		gameOver();
		while (key = _getch())
			if (key == ' ')
				main();
	}
	else
		youWin();
	clearScreen();
	return 0;
}

double accelerate(int length) {
	return (5.0 * exp(3.0 - 0.05 * length) + 150);
}
