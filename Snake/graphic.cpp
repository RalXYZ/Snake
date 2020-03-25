#pragma once

#include "graphic.h"

namespace drawRectangle {
	void upRight(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 18);
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
	}

	void upLeft(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 18);
		solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
	}

	void downRight(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 24);
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
	}

	void downLeft(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 24);
		solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
	}

	void down(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 24);
	}

	void up(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 18);
	}

	void right(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
	}

	void left(const int y, const int x) {
		solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
	}

	void vertical(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 0, y * CUBE + 18, x * CUBE + 24);
	}

	void horizontal(const int y, const int x) {
		solidrectangle(y * CUBE + 0, x * CUBE + 6, y * CUBE + 24, x * CUBE + 18);
	}

	void dot(const int y, const int x) {
		solidrectangle(y * CUBE + 6, x * CUBE + 6, y * CUBE + 18, x * CUBE + 18);
	}

	void fruit(const int y, const int x) {
		solidrectangle(y * CUBE + 9, x * CUBE + 9, y * CUBE + 15, x * CUBE + 15);
	}

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
	settextcolor(Theme[themeNumber].foreground);
	outtextxy(54, 336, _T("GAME  PAUSED"));

	smallFontsOutput(20, 8);
	outtextxy(46, 384, _T("PRESS ANY KEY TO CONTINUE"));
}

void gameOver(int length) {
	clearrectangle(0, 384, HORIZENTAL, VERTICAL);
	wchar_t s[5];
	wsprintf(s, L"%d", length);
	smallFontsOutput(48, 18);
	settextcolor(Theme[themeNumber].accent.front());
	outtextxy(164 - ((int)log10(length) + 1) * 9, 336, s);

	smallFontsOutput(20, 8);
	outtextxy(14, 384, _T("GAME OVER"));
	settextcolor(Theme[themeNumber].foreground);
	outtextxy(120, 384, _T("PRESS SPACE TO REPLAY"));
}

void youWin() {
	smallFontsOutput(48, 16);
	settextcolor(Theme[themeNumber].foreground);
	setbkmode(TRANSPARENT);
	outtextxy(100, 144, _T("YOU  WIN"));
	setbkmode(OPAQUE);
}

void statistics(int length) {
	clearrectangle(0, 336, HORIZENTAL, VERTICAL);
	wchar_t s[5];
	wsprintf(s, L"%d", length);
	smallFontsOutput(48, 18);
	settextcolor(Theme[themeNumber].foreground);
	outtextxy(164 - ((int)log10(length) + 1) * 9, 336, s);

	smallFontsOutput(20, 8);
	outtextxy(72, 384, _T("PRESS SPACE TO PAUSE"));
}

void welcome(Snake*& head) {
	setbkcolor(Theme[themeNumber].background);
	clearrectangle(0, 0, HORIZENTAL, VERTICAL);

	printMap();
	setfillcolor(Theme[themeNumber].accent.front());
	drawRectangle::dot(head->x, head->y);

	smallFontsOutput(20, 8);
	settextcolor(Theme[themeNumber].foreground);
	outtextxy(28, 342, _T("PRESS      OR      TO CHANGE THEME"));
	outtextxy(38, 363, _T("PRESS      OR      TO CHANGE MAP"));
	outtextxy(72, 384, _T("PRESS SPACE TO PLAY"));
	settextcolor(Theme[themeNumber].accent.front());
	smallFontsOutput(20, 10);
	outtextxy(98, 363, _T("←"));
	outtextxy(146, 363, _T("→"));
	outtextxy(90, 342, _T("↑"));
	outtextxy(138, 342, _T("↓"));

	while (true) {
		char temp = _getch();
		if (temp == ' ')
			break;
		else if (temp == -32) {
			Keyboard direction = (Keyboard)_getch();
			if (direction == Keyboard::Up) {
				if (themeNumber == 0)
					themeNumber = ThemeSize - 1;
				else
					--themeNumber;
				welcome(head);
				break;
			}
			else if (direction == Keyboard::Down) {
				(++themeNumber) %= ThemeSize;
				welcome(head);
				break;
			}
			else if (direction == Keyboard::Left) {
				if (mapNumber == 0)
					mapNumber = MapResourceSize - 1;
				else
					--mapNumber;
				mapInput(MapResource[mapNumber].mapMacro);
				welcome(head);
				break;
			}
			else if (direction == Keyboard::Right) {
				(++mapNumber) %= MapResourceSize;
				mapInput(MapResource[mapNumber].mapMacro);
				welcome(head);
				break;
			}
		}
	}
}

void printMap() {
	setfillcolor(Theme[themeNumber].foreground);
	for (int i = 0; i < numberOfRow + 2; i++)
		for (int j = 0; j < numberOfColumn + 2; j++)
			if (mapCurrent[i][j] == 1)
				solidrectangle(j * CUBE, i * CUBE, j * CUBE + CUBE, i * CUBE + CUBE);

	setfillcolor(Theme[themeNumber].background);
	for (int i = 0; i < numberOfRow + 2; i++)
		for (int j = 0; j < numberOfColumn + 2; j++)
			if (mapCurrent[i][j] == 0)
				solidrectangle(j * CUBE, i * CUBE, j * CUBE + CUBE, i * CUBE + CUBE);
}
