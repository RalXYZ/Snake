#pragma once

#include "macros.h"
#include "utilities.h"

extern int mapNumber;
extern int length;
extern int themeNumber;
extern int numberOfRow, numberOfColumn;
extern int mapCurrent[LENGTH + 2][LENGTH + 2];

class DrawRectangle {
public:
	static inline void upRight(int y, int x);
	static inline void upLeft(int y, int x);
	static inline void downRight(int y, int x);
	static inline void downLeft(int y, int x);
	static inline void down(int y, int x);
	static inline void up(int y, int x);
	static inline void right(int y, int x);
	static inline void left(int y, int x);
	static inline void vertical(int y, int x);
	static inline void horizontal(int y, int x);
	static inline void dot(int y, int x);
	static inline void fruit(int y, int x);
};

class WordFormat {
protected:
	static void smallFontsOutput(int height, int width);
};

class DisplayWord : public WordFormat {
public:
	static void paused();
	static void gameOver(int length);
	static void youWin();
	static void statistics(int length);
};

class DisplayComplex : public WordFormat, public DrawRectangle {
public:
	static void welcome(Snake*& head);
	static void printMap();
	static void visualSnake(Snake* head);
	static void placeFruit(bool& fruitExists, Snake*& head);
	static void headStuck(Snake*& head, Directions headDirection);
};
