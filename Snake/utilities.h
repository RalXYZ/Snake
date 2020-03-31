#pragma once 

#include <easyx.h>
#include <cmath>
#include "macros.h"

class Snake {
public:
	int x = 0;
	int y = 0;
	Snake* previous = nullptr;
	Snake* next = nullptr;
};

extern int numberOfRow, numberOfColumn;
extern int fruitRow, fruitColumn;
extern int themeNumber;
extern int themeNumber;
extern int mapCurrent[LENGTH + 2][LENGTH + 2];

void quaternaryToVector(Directions quaternaryVector, int& currentRow, int& currentColumn);
Directions keyToQuaternary(Directions quaternaryVector, int length);
void mapInput(int mapMacro);
void eatSound();
inline DWORD accelerate(int length) { return DWORD(5.0 * exp(3.0 - 0.05 * length) + 200); }
