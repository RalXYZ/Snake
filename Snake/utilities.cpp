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

void mapInput() {
	HRSRC hResource = FindResourceA(nullptr, MAKEINTRESOURCEA(IDR_MAP01), "TEXT");
	HGLOBAL hMemory = LoadResource(nullptr, hResource);
	char* map = (char*)LockResource(hMemory);
	int str_size = SizeofResource(nullptr, hResource);
	if (!hResource) {
		printf("Unable to load map file!");
		exit(1);
	}
	for (int i = 0; i < str_size; i++) {
		printf("%c", *map);
		map++;
	}
}

void eatSound() {
	//TODO find a proper sound fx
}

double accelerate(int length) {
	return (5.0 * exp(3.0 - 0.05 * length) + 200);
}
