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
void visualSnake(snake* tempBody);
void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn);
int keyToQuaternary(int quaternaryVector, int length);
void mapInput(int mapMacro);
void placeFruit(bool& fruitExists, snake*& head);
void eatSound();
double accelerate(int length);
