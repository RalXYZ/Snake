#pragma once

#include <easyx.h>
#include <conio.h>
#include <math.h>
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

void upRightRectangle(int y, int x);
void upLeftRectangle(int y, int x);
void downRightRectangle(int y, int x);
void downLeftRectangle(int y, int x);
void downRectangle(int y, int x);
void upRectangle(int y, int x);
void rightRectangle(int y, int x);
void leftRectangle(int y, int x);
void verticalRectangle(int y, int x);
void horizontalRectangle(int y, int x);
void dotRectangle(int y, int x);
void fruitRectangle(int y, int x);

void smallFontsOutput(int height, int width);
void paused();
void gameOver(int length);
void youWin();
void statistics(int length);
void welcome(Snake*& head);
void printMap();
