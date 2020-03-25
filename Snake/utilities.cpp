#pragma once

#include "utilities.h"

void visualSnake(Snake* head) {
	int i = 0;
	size_t size = Theme[themeNumber].accent.size();
	for (struct Snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next, i++) {
		setfillcolor(Theme[themeNumber].accent.at(i % size));
		if (tempBody->previous != nullptr && tempBody->next != nullptr) {
			if (tempBody->x == tempBody->previous->x && tempBody->x == tempBody->next->x)
				drawRectangle::vertical(tempBody->x, tempBody->y);
			else if (tempBody->y == tempBody->previous->y && tempBody->y == tempBody->next->y)
				drawRectangle::horizontal(tempBody->x, tempBody->y);
			else {
				if (tempBody->x == tempBody->next->x + 1 && tempBody->y == tempBody->previous->y + 1
					|| tempBody->x == tempBody->previous->x + 1 && tempBody->y == tempBody->next->y + 1)
					drawRectangle::upLeft(tempBody->x, tempBody->y);
				else if (tempBody->x == tempBody->next->x - 1 && tempBody->y == tempBody->previous->y - 1
					|| tempBody->x == tempBody->previous->x - 1 && tempBody->y == tempBody->next->y - 1)
					drawRectangle::downRight(tempBody->x, tempBody->y);
				else if (tempBody->x == tempBody->next->x + 1 && tempBody->y == tempBody->previous->y - 1
					|| tempBody->x == tempBody->previous->x + 1 && tempBody->y == tempBody->next->y - 1)
					drawRectangle::downLeft(tempBody->x, tempBody->y);
				else if (tempBody->x == tempBody->next->x - 1 && tempBody->y == tempBody->previous->y + 1
					|| tempBody->x == tempBody->previous->x - 1 && tempBody->y == tempBody->next->y + 1)
					drawRectangle::upRight(tempBody->x, tempBody->y);
			}
		}
		else if (tempBody->previous == nullptr && tempBody->next == nullptr)
			drawRectangle::dot(tempBody->x, tempBody->y);
		else {
			if (tempBody->previous == nullptr) { //head
				if (tempBody->x == tempBody->next->x + 1)
					drawRectangle::left(tempBody->x, tempBody->y);
				else if (tempBody->x == tempBody->next->x - 1)
					drawRectangle::right(tempBody->x, tempBody->y);
				else if (tempBody->y == tempBody->next->y + 1)
					drawRectangle::up(tempBody->x, tempBody->y);
				else if (tempBody->y == tempBody->next->y - 1)
					drawRectangle::down(tempBody->x, tempBody->y);
			}
			if (tempBody->next == nullptr) { //tail
				if (tempBody->x == tempBody->previous->x + 1)
					drawRectangle::left(tempBody->x, tempBody->y);
				else if (tempBody->x == tempBody->previous->x - 1)
					drawRectangle::right(tempBody->x, tempBody->y);
				else if (tempBody->y == tempBody->previous->y + 1)
					drawRectangle::up(tempBody->x, tempBody->y);
				else if (tempBody->y == tempBody->previous->y - 1)
					drawRectangle::down(tempBody->x, tempBody->y);
			}
		}
	}
}

void quaternaryToVector(Directions quaternaryVector, int& currentRow, int& currentColumn) {
	switch (quaternaryVector) {
	case Directions::Right:
		++currentRow;
		break;
	case Directions::Left:
		--currentRow;
		break;
	case Directions::Up:
		--currentColumn;
		break;
	case Directions::Down:
		++currentColumn;
		break;
	}
}

Directions keyToQuaternary(Directions quaternaryVector, int length) {
	Directions temp = quaternaryVector;
	switch ((Keyboard)_getch()) {
	case Keyboard::Right:
		temp = Directions::Right;
		break;
	case Keyboard::Up:
		temp = Directions::Up;
		break;
	case Keyboard::Left:
		temp = Directions::Left;
		break;
	case Keyboard::Down:
		temp = Directions::Down;
		break;
	}
	if (length > 1) //the Snake should not reverse its orientation when its length is bigger than 1
		if (((int)quaternaryVector - (int)temp) % 2 == 0)
			return quaternaryVector;
	return temp;
}

void mapInput(int mapMacro) {
	HRSRC hResource = FindResourceA(nullptr, MAKEINTRESOURCEA(mapMacro), "TEXT");
	HGLOBAL hMemory = LoadResource(nullptr, hResource);
	char* mapElement = (char*)LockResource(hMemory);
	int str_size = SizeofResource(nullptr, hResource);
	if (!hResource) {
		std::cout << "Unable to load map file! " << mapMacro;
		exit(1);
	}
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			mapCurrent[i][j] = *mapElement - '0';
			mapElement++;
		}
		mapElement++;
		mapElement++;
	}
}

void placeFruit(bool& fruitExists, Snake*& head) {
	setfillcolor(Theme[themeNumber].foreground);
	while (fruitExists == false) {
		int tempRow = rand() % numberOfRow + 1;
		int tempColumn = rand() % numberOfColumn + 1;
		if (mapCurrent[tempColumn][tempRow] == 1)
			continue;
		for (struct Snake* tempBody = head; tempBody != nullptr; tempBody = tempBody->next) {
			if (tempBody->x == tempRow && tempBody->y == tempColumn)
				break;
			if (tempBody->next == nullptr) {
				fruitRow = tempRow;
				fruitColumn = tempColumn;
				drawRectangle::fruit(fruitRow, fruitColumn);
				fruitExists = true;
			}
		}
	}
}

void eatSound() {
	//TODO find a proper sound fx
}
