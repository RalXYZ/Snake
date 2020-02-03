#pragma once

#include <easyx.h>
#include <conio.h>
#include <math.h>
#include "graphic.h"

void upRightRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 18);
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
}

void upLeftRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 18);
	solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
}

void downRightRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 24);
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
}

void downLeftRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 24);
	solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
}

void downRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 24);
}

void upRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 18);
}

void rightRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
}

void leftRectangle(int y, int x) {
	solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
}

void verticalRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 24);
}

void horizontalRectangle(int y, int x) {
	solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
}

void dotRectangle(int y, int x) {
	solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
}

void fruitRectangle(int y, int x) {
	solidrectangle(y * CUBE + 9, x * CUBE + 9, y * CUBE + 15, x * CUBE + 15);
}

void smallFontsOutput(int height, int width) {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = height;
	f.lfWidth = width;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
}

void paused() {
	clearrectangle(0, 336, HORIZENTAL, VERTICAL);
	smallFontsOutput(48, 16);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(54, 336, _T("GAME  PAUSED"));

	smallFontsOutput(20, 8);
	outtextxy(46, 384, _T("PRESS ANY KEY TO CONTINUE"));
}

void gameOver(int length) {
	clearrectangle(0, 384, HORIZENTAL, VERTICAL);
	wchar_t s[5];
	wsprintf(s, L"%d", length);
	smallFontsOutput(48, 18);
	settextcolor(theme[themeNumber].accent.front());
	outtextxy(164 - ((int)log10(length) + 1) * 9, 336, s);

	smallFontsOutput(20, 8);
	outtextxy(14, 384, _T("GAME OVER"));
	settextcolor(theme[themeNumber].foreground);
	outtextxy(120, 384, _T("PRESS SPACE TO REPLAY"));
}

void youWin() {
	smallFontsOutput(48, 16);
	settextcolor(theme[themeNumber].foreground);
	setbkmode(TRANSPARENT);
	outtextxy(100, 144, _T("YOU  WIN"));
	setbkmode(OPAQUE);
}

void statistics(int length) {
	clearrectangle(0, 336, HORIZENTAL, VERTICAL);
	wchar_t s[5];
	wsprintf(s, L"%d", length);
	smallFontsOutput(48, 18);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(164 - ((int)log10(length) + 1) * 9, 336, s);

	smallFontsOutput(20, 8);
	outtextxy(72, 384, _T("PRESS SPACE TO PAUSE"));
}

void welcome(snake*& head) {
	setbkcolor(theme[themeNumber].background);
	clearrectangle(0, 0, HORIZENTAL, VERTICAL);

	printMap();
	setfillcolor(theme[themeNumber].accent.front());
	dotRectangle(head->x, head->y);

	smallFontsOutput(20, 8);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(2, 342, _T("PRESS ANY                     TO CHANGE THEME"));
	outtextxy(38, 363, _T("PRESS      OR      TO CHANGE MAP"));
	outtextxy(72, 384, _T("PRESS SPACE TO PLAY"));
	settextcolor(theme[themeNumber].accent.front());
	outtextxy(98, 363, _T("<"));
	outtextxy(146, 363, _T(">"));
	outtextxy(98, 342, _T("NUMBER"));

	while (true) {
		char temp = _getch();
		if (temp == ' ')
			break;
		/*
		else if (temp >= '0' && temp <= '9') {
			themeNumber = temp - '0';
			welcome(head);
			break;
		}
		*/
		else if (temp == -32) {
			int direction = _getch();
			if (direction == 72) { // ^
				if (themeNumber == 0)
					themeNumber = (int)theme.size() - 1;
				else
					--themeNumber;
				welcome(head);
				break;
			}
			else if (direction == 80) { // v
				(++themeNumber) %= (int)theme.size();
				welcome(head);
				break;
			}
			else if (direction == 75) { // <
				if (mapNumber == 0)
					mapNumber = 6;
				else
					--mapNumber;
				mapInput(mapResource[mapNumber].mapMacro);
				welcome(head);
				break;
			}
			else if (direction == 77) { // >
				(++mapNumber) %= 7;
				mapInput(mapResource[mapNumber].mapMacro);
				welcome(head);
				break;
			}
		}
	}
}

void printMap() {
	setfillcolor(theme[themeNumber].foreground);
	for (int i = 0; i < numberOfRow + 2; i++) {
		for (int j = 0; j < numberOfColumn + 2; j++) {
			if (mapCurrent[i][j] == 1) {
				solidrectangle(j * CUBE, i * CUBE, j * CUBE + CUBE, i * CUBE + CUBE);
			}
		}
	}
	setfillcolor(theme[themeNumber].background);
	for (int i = 0; i < numberOfRow + 2; i++)
		for (int j = 0; j < numberOfColumn + 2; j++)
			if (mapCurrent[i][j] == 0)
				solidrectangle(j * CUBE, i * CUBE, j * CUBE + CUBE, i * CUBE + CUBE);
}
