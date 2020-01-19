#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>
#include <string>
#include <thread>
#include "resource.h"

#define HORIZENTAL 336
#define VERTICAL 408
#define CUBE 24

#include "system.h"
#include "utilities.h"
#include "graphic.h"
#include "welcome.h"

extern struct color theme[20];

struct snake {
	int x;
	int y;
	struct snake* previous = nullptr;
	struct snake* next;
};

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
	bool fruitExists = false;
	bool hitBody = false;

	struct snake* oldBody = (struct snake*)malloc(sizeof(struct snake));
	oldBody->x = numberOfRow / 2 + 1;
	oldBody->y = numberOfColumn / 2 + 1;
	oldBody->next = nullptr;
	struct snake* head = oldBody;
	struct snake* tail = oldBody;

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

		/*detect what exists at the next position where the snake's head locates*/
		if (currentRow == fruitRow && currentColumn == fruitColumn) {
			++length;
			fruitExists = false;
			std::thread sound(eatSound);
			sound.detach();
		}
		else if (core[currentRow][currentColumn] == 666)
			break;
		else {
			for (struct snake* tempBody = head; tempBody != tail; tempBody = tempBody->next)
				if (tempBody->x == currentRow && tempBody->y == currentColumn)
					hitBody = true;
		}

		/*the movement of snake*/
		struct snake* newBody = (struct snake*)malloc(sizeof(struct snake));
		newBody->x = currentRow;
		newBody->y = currentColumn;
		newBody->previous = nullptr;
		newBody->next = oldBody;
		head = newBody;
		oldBody->previous = newBody;
		if (fruitExists == true) {
			struct snake* temp = tail->previous;
			clearrectangle(tail->x * CUBE, tail->y * CUBE, tail->x * CUBE + CUBE, tail->y * CUBE + CUBE);
			free(tail);
			tail = temp;
			tail->next = nullptr;
		}
		oldBody = newBody;

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
		for (struct snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next) {
			if (tempBody->previous != nullptr && tempBody->next != nullptr) {
				if (tempBody->x == tempBody->previous->x && tempBody->x == tempBody->next->x)
					verticalRectangle(tempBody->x, tempBody->y);
				else if (tempBody->y == tempBody->previous->y && tempBody->y == tempBody->next->y)
					horizontalRectangle(tempBody->x, tempBody->y);
				else {
					if (tempBody->x == tempBody->next->x + 1 && tempBody->y == tempBody->previous->y + 1
						|| tempBody->x == tempBody->previous->x + 1 && tempBody->y == tempBody->next->y + 1)
						upLeftRectangle(tempBody->x, tempBody->y);
					else if (tempBody->x == tempBody->next->x - 1 && tempBody->y == tempBody->previous->y - 1
						|| tempBody->x == tempBody->previous->x - 1 && tempBody->y == tempBody->next->y - 1)
						downRightRectangle(tempBody->x, tempBody->y);
					else if (tempBody->x == tempBody->next->x + 1 && tempBody->y == tempBody->previous->y - 1
						|| tempBody->x == tempBody->previous->x + 1 && tempBody->y == tempBody->next->y - 1)
						downLeftRectangle(tempBody->x, tempBody->y);
					else if (tempBody->x == tempBody->next->x - 1 && tempBody->y == tempBody->previous->y + 1
						|| tempBody->x == tempBody->previous->x - 1 && tempBody->y == tempBody->next->y + 1)
						upRightRectangle(tempBody->x, tempBody->y);
				}
			}
			else if (tempBody->previous == nullptr && tempBody->next == nullptr)
				dotRectangle(tempBody->x, tempBody->y);
			else {
				if (tempBody->previous == nullptr) { //head
					if (tempBody->x == tempBody->next->x + 1)
						leftRectangle(tempBody->x, tempBody->y);
					else if (tempBody->x == tempBody->next->x - 1)
						rightRectangle(tempBody->x, tempBody->y);
					else if (tempBody->y == tempBody->next->y + 1)
						upRectangle(tempBody->x, tempBody->y);
					else if (tempBody->y == tempBody->next->y - 1)
						downRectangle(tempBody->x, tempBody->y);
				}
				if (tempBody->next == nullptr) { //tail
					if (tempBody->x == tempBody->previous->x + 1)
						leftRectangle(tempBody->x, tempBody->y);
					else if (tempBody->x == tempBody->previous->x - 1)
						rightRectangle(tempBody->x, tempBody->y);
					else if (tempBody->y == tempBody->previous->y + 1)
						upRectangle(tempBody->x, tempBody->y);
					else if (tempBody->y == tempBody->previous->y - 1)
						downRectangle(tempBody->x, tempBody->y);
				}
			}
		}
		//solidrectangle(tempBody->x * CUBE, tempBody->y * CUBE, tempBody->x * CUBE + CUBE, tempBody->y * CUBE + CUBE);
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
	clearScreen();
	return 0;
}
