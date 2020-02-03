#pragma once 

#include <cmath>
#include <cstdio>
#include <conio.h>
#include <easyx.h>
#include "macros.h"
#include "resource.h"

struct snake {
	int x;
	int y;
	snake* previous = nullptr;
	snake* next;
};

#include "graphic.h"

extern vector<color> theme;
extern int numberOfRow, numberOfColumn;
extern int fruitRow, fruitColumn;
extern int themeNumber;
extern int themeNumber;
extern int mapCurrent[LENGTH + 2][LENGTH + 2];

void visualSnake(snake* tempBody);
void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn);
Directions keyToQuaternary(Directions quaternaryVector, int length);
void mapInput(int mapMacro);
void placeFruit(bool& fruitExists, snake*& head);
void eatSound();
DWORD accelerate(int length);
