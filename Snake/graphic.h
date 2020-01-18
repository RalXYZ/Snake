#pragma once

extern int themeNumber;

struct color {
	int background;
	int foreground;
	int accent;
};

color nightClub = { 0x3a2528, 0x4f17c3, 0x8d83b5 };
color cangSong = { 0x273220, 0x6d7b63, 0xadc29c };
color hoopoe = { 0x4d95ff, 0x1e2f48, 0xd8e6ff };
color redBean = { 0xb4b2b9, 0x1f121b, 0x0e0b7a };
color bluebird = { 0xd9d1c9, 0xba8047, 0x5552ba };
color rose = { 0x312e31, 0xb9b6ff, 0x7f5fff };
color halloween = { 0x2b161c, 0x1281c3, 0x0a4eb9 };
color panda = { 0x222222, 0xeaeaea, 0x828282 };
color snowOwl = { 0xfafafa, 0x47cdfa, 0x20273d };
color nightRain = { 0x201c19, 0x705f52, 0xd9baa2 };
color plumage = { 0xffefdd, 0x00bdd4, 0xc0ac6e };

color theme[20] = { nightClub, cangSong, hoopoe, redBean, bluebird, rose, halloween, panda, snowOwl, nightRain, plumage };

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
