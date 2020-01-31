#pragma once

#include "utilities.h"

//extern int ravenSnake[];
extern int themeNumber;
extern color theme[];
void visualSnake(snake* head) {
	/*
	for (snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next) {
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
	*/
	int i = 0;
	size_t size = theme[themeNumber].accent.size();
	for (struct snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next, i++) {
		setfillcolor(theme[themeNumber].accent.at(i % size));
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
}

void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn) {
	switch (quaternaryVector) {
	case Right:
		++(*currentRow);
		break;
	case Left:
		--(*currentRow);
		break;
	case Up:
		--(*currentColumn);
		break;
	case Down:
		++(*currentColumn);
		break;
	}
}

int keyToQuaternary(int quaternaryVector, int length) {
	int temp = quaternaryVector;
	switch (_getch()) {
	case 77:
		temp = Right;
		break;
	case 72:
		temp = Up;
		break;
	case 75:
		temp = Left;
		break;
	case 80:
		temp = Down;
		break;
	}
	if (length > 1) //the snake should not reverse its orientation when its length is bigger than 1
		if ((quaternaryVector - temp) % 2 == 0)
			return quaternaryVector;
	return temp;
}

int map[LENGTH + 2][LENGTH + 2];
void mapInput(int mapMacro) {
	HRSRC hResource = FindResourceA(nullptr, MAKEINTRESOURCEA(mapMacro), "TEXT");
	HGLOBAL hMemory = LoadResource(nullptr, hResource);
	char* mapElement = (char*)LockResource(hMemory);
	int str_size = SizeofResource(nullptr, hResource);
	if (!hResource) {
		printf("Unable to load map file! %d", mapMacro);
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
	setfillcolor(theme[themeNumber].foreground);
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
				fruitRectangle(fruitRow, fruitColumn);
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
