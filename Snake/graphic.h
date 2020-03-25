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

namespace drawRectangle {
	void upRight(int y, int x);
	void upLeft(int y, int x);
	void downRight(int y, int x);
	void downLeft(int y, int x);
	void down(int y, int x);
	void up(int y, int x);
	void right(int y, int x);
	void left(int y, int x);
	void vertical(int y, int x);
	void horizontal(int y, int x);
	void dot(int y, int x);
	void fruit(int y, int x);
};

void smallFontsOutput(int height, int width);
void paused();
void gameOver(int length);
void youWin();
void statistics(int length);
void welcome(Snake*& head);
void printMap();
