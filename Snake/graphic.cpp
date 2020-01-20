#pragma once

#include <easyx.h>
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

void paused() {
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
	outtextxy(72, 148, _T("GAME  OVER"));
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
	outtextxy(100, 148, _T("YOU  WIN"));
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
