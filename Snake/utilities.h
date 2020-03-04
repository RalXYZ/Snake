#pragma once 

#include <cmath>
#include <iostream>
#include <conio.h>
#include <easyx.h>
#include "macros.h"
#include "resource.h"

class Snake {
public:
	int x = 0;
	int y = 0;
	Snake* previous = nullptr;
	Snake* next = nullptr;
};

#include "graphic.h"

extern int numberOfRow, numberOfColumn;
extern int fruitRow, fruitColumn;
extern int themeNumber;
extern int themeNumber;
extern int mapCurrent[LENGTH + 2][LENGTH + 2];

void visualSnake(Snake* tempBody);
void quaternaryToVector(Directions quaternaryVector, int& currentRow, int& currentColumn);
Directions keyToQuaternary(Directions quaternaryVector, int length);
void mapInput(int mapMacro);
void placeFruit(bool& fruitExists, Snake*& head);
void eatSound();
inline DWORD accelerate(int length) { return DWORD(5.0 * exp(3.0 - 0.05 * length) + 200); }
