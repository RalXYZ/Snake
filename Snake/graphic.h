#pragma once

#include <easyx.h>
#include <conio.h>
#include <cmath>
#include "macros.h"
#include "theme.h"
#include "macros.h"
#include "utilities.h"
#include "maps.h"

extern int mapNumber;
extern int length;
extern int themeNumber;
extern int numberOfRow, numberOfColumn;
extern int mapCurrent[LENGTH + 2][LENGTH + 2];

class Rectangle {
public:
	static void upRightRectangle(int y, int x);
	static void upLeftRectangle(int y, int x);
	static void downRightRectangle(int y, int x);
	static void downLeftRectangle(int y, int x);
	static void downRectangle(int y, int x);
	static void upRectangle(int y, int x);
	static void rightRectangle(int y, int x);
	static void leftRectangle(int y, int x);
	static void verticalRectangle(int y, int x);
	static void horizontalRectangle(int y, int x);
	static void dotRectangle(int y, int x);
	static void fruitRectangle(int y, int x);
};


void smallFontsOutput(int height, int width);
void paused();
void gameOver(int length);
void youWin();
void statistics(int length);
void welcome(Snake*& head);
void printMap();
