#pragma once 

#include "macros.h"

struct snake {
	int x;
	int y;
	snake* previous = nullptr;
	snake* next;
};

void visualSnake(snake*& tempBody);
void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn);
int keyToQuaternary(char input, int quaternaryVector, int length);
void mapInput(int mapMacro);
void placeFruit(bool& fruitExists, snake*& head);
void eatSound();
double accelerate(int length);
