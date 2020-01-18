#pragma once

extern struct color theme[20];
extern int themeNumber;
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
	outtextxy(96, 148, _T("SNAKE"));
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
