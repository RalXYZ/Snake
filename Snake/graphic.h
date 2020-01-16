#pragma once

void upRightRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 18);
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void upLeftRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 18);
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void downRightRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 24);
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void downLeftRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 24);
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void downRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 24);
}

void upRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 18);
}

void rightRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void leftRectangle(int y, int x) {
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void verticalRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 24);
}

void horizontalRectangle(int y, int x) {
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void dotRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void fruitRectangle(int y, int x) {
	fillrectangle(y * 20 + 9, x * 20 + 9, y * 20 + 15, x * 20 + 15);
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
	settextcolor(PIK);
	outtextxy(30, 280, _T("GAME  PAUSED"));
	settextcolor(GOD);

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(PIK);
	outtextxy(20, 328, _T("PRESS ANY KEY TO CONTINUE"));
	settextcolor(GOD);
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
	settextcolor(PIK);
	outtextxy(48, 280, _T("GAME  OVER"));
	settextcolor(GOD);

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	f.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(f.lfFaceName, _T("Small Fonts"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(PIK);
	outtextxy(38, 328, _T("PRESS SPACE TO REPLAY"));
	settextcolor(GOD);
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
	settextcolor(PIK);
	outtextxy(68, 280, _T("YOU  WIN"));
	settextcolor(GOD);
}
