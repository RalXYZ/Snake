#pragma once

#include <math.h>
#include <stdio.h>
#include <easyx.h>
#include "graphic.h"
#include "utilities.h"
#include "resource.h"

void visualSnake(snake*& tempBody) {
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

int map[LENGTH + 2][LENGTH + 2];
void mapInput() {
	HRSRC hResource = FindResourceA(nullptr, MAKEINTRESOURCEA(IDR_MAP00), "TEXT");
	HGLOBAL hMemory = LoadResource(nullptr, hResource);
	char* mapElement = (char*)LockResource(hMemory);
	int str_size = SizeofResource(nullptr, hResource);
	if (!hResource) {
		printf("Unable to load map file!");
		exit(1);
	}
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			map[i][j] = *mapElement - '0';
			mapElement++;
		}
		mapElement++;
		mapElement++;
	}
}

extern int numberOfRow, numberOfColumn;
extern int fruitRow, fruitColumn;
extern int themeNumber;
void placeFruit(bool& fruitExists, snake*& head) {
	while (fruitExists == false) {
		int tempRow = rand() % numberOfRow + 1;
		int tempColumn = rand() % numberOfColumn + 1;
		if (map[tempColumn][tempRow] == 1)
			continue;
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
}

void eatSound() {
	//TODO find a proper sound fx
}

double accelerate(int length) {
	return (5.0 * exp(3.0 - 0.05 * length) + 200);
}
