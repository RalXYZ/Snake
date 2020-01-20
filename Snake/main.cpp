#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>
#include <string>
#include <thread>
#include <windows.h>
#include <conio.h>
#include "resource.h"
#include "utilities.h"
#include "welcome.h"
#include "graphic.h"

extern color theme[20];



bool windowCreated = false;
int themeNumber = 0;
int numberOfRow = 12, numberOfColumn = 12;
int fruitRow, fruitColumn;
double timePerFrame;
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
	bool fruitExists = false, fruitEaten = false;
	bool hitBody = false;

	snake* oldBody = (snake*)malloc(sizeof(snake));
	oldBody->x = numberOfRow / 2 + 1;
	oldBody->y = numberOfColumn / 2 + 1;
	oldBody->next = nullptr;
	snake* head = oldBody;
	snake* tail = oldBody;

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

	/*window initialization*/
	if (windowCreated == false) {
		initgraph(HORIZENTAL, VERTICAL);
		windowCreated = true;
	}

	welcome();

	setbkcolor(theme[themeNumber].background);
	setfillcolor(theme[themeNumber].accent);
	setlinestyle(PS_NULL);
	clearrectangle(0, 0, HORIZENTAL, VERTICAL);

	while (true) {
		/*detect user keyboard input, pause or go, and judge the next location of the snake's head based on it*/
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

		/*place food randomly until the food is not located on the snake's body*/
		while (fruitExists == false) {
			int tempRow = rand() % numberOfRow + 1;
			int tempColumn = rand() % numberOfColumn + 1;
			for (struct snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next) {
				if (tempBody->x == tempRow && tempBody->y == tempColumn)
					break;
				if (tempBody->next == nullptr) {
					fruitRow = tempRow;
					fruitColumn = tempColumn;
					setfillcolor(theme[themeNumber].foreground);
					fruitRectangle(fruitRow, fruitColumn);
					setfillcolor(theme[themeNumber].accent);
					fruitExists = true;
				}
			}
		}

		/*detect what exists at the next position where the snake's head locates*/
		if (currentRow == fruitRow && currentColumn == fruitColumn) {
			++length;
			fruitExists = false;
			fruitEaten = true;
			std::thread sound(eatSound);
			sound.detach();
		}
		else if (core[currentRow][currentColumn] == 666)
			break;
		else {
			for (snake* tempBody = head; tempBody != tail; tempBody = tempBody->next)
				if (tempBody->x == currentRow && tempBody->y == currentColumn)
					hitBody = true;
		}

		/*the movement of snake*/
		snake* newBody = (snake*)malloc(sizeof(snake));
		newBody->x = currentRow;
		newBody->y = currentColumn;
		newBody->previous = nullptr;
		newBody->next = oldBody;
		head = newBody;
		oldBody->previous = newBody;
		if (fruitEaten == false) {
			snake* temp = tail->previous;
			clearrectangle(tail->x * CUBE, tail->y * CUBE, tail->x * CUBE + CUBE, tail->y * CUBE + CUBE);
			free(tail);
			tail = temp;
			tail->next = nullptr;
		}
		else
			fruitEaten = false;
		oldBody = newBody;

		bool headExist = false; //ensure the head really "hits" the body visually while game over
		for (int i = 0; i < numberOfRow + 2; i++) {
			for (int j = 0; j < numberOfColumn + 2; j++) {
				if (core[i][j] == 666) {
					setfillcolor(theme[themeNumber].foreground);
					setfillstyle(BS_HATCHED, HS_DIAGCROSS);
					solidrectangle(j * CUBE, i * CUBE, j * CUBE + CUBE, i * CUBE + CUBE);  //return '#';
					setfillstyle(BS_SOLID);
					setfillcolor(theme[themeNumber].accent);
				}
			}
		}
		for (snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next) {
			visualSnake(tempBody);
		}
		statistics(length);
		if (hitBody == true)
			break;

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
	return 0;
}
