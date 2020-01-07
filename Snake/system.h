#pragma once 

/* for the sh*t, WIN32 */
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <tgmath.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Windows 與 Linux 的函式庫名稱稍微不同。
#define Sleep(msec) usleep(msec * 1000); // 不支援 s
#define _getch() getc(stdin)

// thanks to https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int _kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}
#endif
