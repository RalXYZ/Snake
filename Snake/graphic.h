#pragma once

#include <easyx.h>
#include "macros.h"
#include "utilities.h"

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

class WordFormat {
protected:
	static void smallFontsOutput(int height, int width);
};

class Word : public WordFormat {
public:
	static void paused();
	static void gameOver(int length);
	static void youWin();
	static void statistics(int length);
};

class Complex : public WordFormat {
public:
	static void welcome(Snake*& head);
	static void printMap();
	static void visualSnake(Snake* head);
	static void placeFruit(bool& fruitExists, Snake*& head);
};
