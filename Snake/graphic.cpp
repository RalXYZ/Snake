#pragma once

#include <easyx.h>
#include <conio.h>
#include <math.h>
#include "graphic.h"

extern int themeNumber;

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

extern int length;
void paused() {
	clearrectangle(0, 336, HORIZENTAL, VERTICAL);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 48;
	f.lfWidth = 16;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(54, 336, _T("GAME  PAUSED"));
	settextcolor(theme[themeNumber].accent);

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(46, 384, _T("PRESS ANY KEY TO CONTINUE"));
	settextcolor(theme[themeNumber].accent);
}

void gameOver() {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 48;
	f.lfWidth = 16;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	setbkmode(TRANSPARENT);
	outtextxy(76, 144, _T("GAME  OVER"));
	settextcolor(theme[themeNumber].accent);
	setbkmode(OPAQUE);

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(64, 384, _T("PRESS SPACE TO REPLAY"));
	settextcolor(theme[themeNumber].accent);
}

void youWin() {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 48;
	f.lfWidth = 16;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	setbkmode(TRANSPARENT);
	outtextxy(100, 144, _T("YOU  WIN"));
	settextcolor(theme[themeNumber].accent);
	setbkmode(OPAQUE);
}

void statistics(int length) {
	clearrectangle(0, 336, HORIZENTAL, VERTICAL);
	wchar_t s[5];
	wsprintf(s, L"%d", length);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 48;
	f.lfWidth = 18;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(164 - ((int)log10(length) + 1) * 9, 336, s);
	settextcolor(theme[themeNumber].accent);

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(72, 384, _T("PRESS SPACE TO PAUSE"));
	settextcolor(theme[themeNumber].accent);
}

void welcome() {
	setbkcolor(theme[themeNumber].background);
	clearrectangle(0, 0, HORIZENTAL, VERTICAL);

	setfillcolor(theme[themeNumber].foreground);
	setfillstyle(BS_HATCHED, HS_DIAGCROSS);
	solidrectangle(0, 0, HORIZENTAL, HORIZENTAL);
	setfillstyle(BS_SOLID);
	clearrectangle(CUBE, CUBE, HORIZENTAL - CUBE, HORIZENTAL - CUBE);

	LOGFONT f;

	gettextstyle(&f);
	f.lfHeight = 48;
	f.lfWidth = 18;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(96, 144, _T("SNAKE"));
	settextcolor(theme[themeNumber].accent);

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(theme[themeNumber].foreground);
	outtextxy(2, 349, _T("PRESS ANY                     TO CHANGE THEME"));
	outtextxy(72, 375, _T("PRESS SPACE TO PLAY"));
	settextcolor(theme[themeNumber].accent);
	outtextxy(98, 349, _T("NUMBER"));

	while (true) {
		char temp = _getch();
		if (temp == ' ')
			break;
		else if (temp >= '0' && temp <= '9') {
			themeNumber = temp - '0';
			welcome();
			break;
		}
	}
}
