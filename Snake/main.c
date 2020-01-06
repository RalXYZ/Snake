#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "system.h"
#include "utilities.h"

#define LENGTH 40

double timePerFrame;
int numberOfRow = 12, numberOfColumn = 12;
int pulse = 0; //控制果实oO

double accelerate(int length);
int keyToQuaternary(char input, int quaternaryVector, int length); //将用户键盘输入的值翻译为方向值
void quaternaryVectorInterpreter(int quaternaryVector, int* currentRow, int* currentColumn); //将方向值与行列位置变化对应
char coreToScreen(int number, int length, int quaternaryVector); //将core数组中存储的核心数据可视化

int main() {
	/*创建随机数种子*/
	srand((unsigned)time(NULL));

	/*数据预处理*/
	int core[LENGTH + 2][LENGTH + 2] = { 0 };
	char screen[2 * (LENGTH + 2) + 1][2 * (LENGTH + 2) + 1] = { 0 };
	int currentRow = numberOfRow / 2 + 1, currentColumn = numberOfColumn / 2 + 1;
	int quaternaryVector = rand() % 4;
	int length = 1;
	bool judgeSeed = false;

	/*棋盘预处理*/
	for (int i = 0; i < numberOfRow + 2; i++) {
		if (i == 0 || i == numberOfRow + 1) //在首行和末行全置入'#'
			for (int j = 0; j < numberOfColumn + 2; j++)
				core[i][j] = 666;
		else //在其它行的开始与末尾置入'#'
			for (int j = 0; j < numberOfColumn + 2; j++)
				if (j == 0 || j == numberOfColumn + 1)
					core[i][j] = 666;
	}

	while (true) {
		/*检测用户键盘输入，并由输入给出蛇头下一步移动的位置*/
		if (_kbhit())
			quaternaryVector = keyToQuaternary(_getch(), quaternaryVector, length);
		quaternaryVectorInterpreter(quaternaryVector, &currentRow, &currentColumn);

		/*“探针”探测下一个移动位置的情况*/
		if (core[currentRow][currentColumn] == 777) {
			++length;
			judgeSeed = false;
		}
		else if (core[currentRow][currentColumn] != 0)
			break;

		/*蛇移动模块*/
		for (int i = 1; i <= numberOfRow; i++) {
			for (int j = 1; j <= numberOfColumn; j++)
				if (core[i][j] != 0 && core[i][j] != 777) {
					++core[i][j];
					if (core[i][j] > length)
						core[i][j] = 0;
				}
		}
		core[currentRow][currentColumn] = 1;

		/*随机放置贪吃蛇食物，循环直到食物不位于蛇身上为止*/
		while (judgeSeed == false) {
			int tempRow = rand() % numberOfRow + 1;
			int tempColumn = rand() % numberOfColumn + 1;
			if (core[tempRow][tempColumn] == 0) {
				core[tempRow][tempColumn] = 777;
				judgeSeed = true;
			}
		}

		/*将要输出的数据统一放至screen[][]*/
		for (int i = 0; i < numberOfRow + 2; i++) {
			for (int j = 0; j < numberOfColumn + 2; j++) {
				screen[i][2 * j] = coreToScreen(core[i][j], length, quaternaryVector);
				screen[i][2 * j + 1] = ' '; //注意，为了输出美观，考虑到字符所占像素，故在每一个元素后加一个空格
			}
			screen[i][2 * (numberOfColumn + 1) + 1] = '\n';
		}

		/*辅助数据*/
		// multiple unsequenced modifications to 'pulse'
		pulse++;
		pulse %= 2;

		/*统一输出*/
		clearScreen();
		for (int i = 0; i < numberOfRow + 2; i++)
			printf("%s", screen[i]);
		printf("Your current length is: %d\n", length);
		timePerFrame = accelerate(length);
		Sleep(timePerFrame);
	}

	/*在结束游戏后显示输赢*/
	if (length != numberOfRow * numberOfColumn) {
		screen[numberOfRow / 2][numberOfColumn - 1] = 'G';
		screen[numberOfRow / 2][numberOfColumn] = 'A';
		screen[numberOfRow / 2][numberOfColumn + 1] = 'M';
		screen[numberOfRow / 2][numberOfColumn + 2] = 'E';
		screen[numberOfRow / 2 + 1][numberOfColumn - 1] = 'O';
		screen[numberOfRow / 2 + 1][numberOfColumn] = 'V';
		screen[numberOfRow / 2 + 1][numberOfColumn + 1] = 'E';
		screen[numberOfRow / 2 + 1][numberOfColumn + 2] = 'R';
	}
	else {
		screen[numberOfRow / 2][numberOfColumn - 1] = 'Y';
		screen[numberOfRow / 2][numberOfColumn] = 'O';
		screen[numberOfRow / 2][numberOfColumn + 1] = 'U';
		screen[numberOfRow / 2 + 1][numberOfColumn - 1] = 'W';
		screen[numberOfRow / 2 + 1][numberOfColumn] = 'I';
		screen[numberOfRow / 2 + 1][numberOfColumn + 1] = 'N';
	}
	clearScreen();
	for (int i = 0; i < numberOfRow + 2; i++)
		printf("%s", screen[i]);
	printf("Your final length is: %d\n", length);
	Sleep(10000);
	return 0;
}

double accelerate(int length) {
	return (5.0 * exp(3.0 - 0.05 * length) + 100);
}

void quaternaryVectorInterpreter(int quaternaryVector, int* currentRow, int* currentColumn) {
	switch (quaternaryVector) {
	case 0:
		++ * currentColumn;
		break;
	case 2:
		-- * currentColumn;
		break;
	case 1:
		-- * currentRow;
		break;
	case 3:
		++ * currentRow;
		break;
	}
}

char coreToScreen(int number, int length, int quaternaryVector) {
	if (number == 0)
		return ' ';
	else if (number <= length)
		if (number != 1)
			return '*';
		else
			switch (quaternaryVector) { //不同方向的蛇头
			case 0:
				return '>';
			case 1:
				return 'A';
			case 2:
				return '<';
			case 3:
				return 'V';
			}
	else if (number == 666)
		return '#';
	else if (number == 777) {
		if (pulse == 0)
			return 'o';
		else
			return 'O';
	}
	return '?'; // warning: control may reach end of non-void function
}

int keyToQuaternary(char input, int quaternaryVector, int length) {
	int temp = quaternaryVector;
	if (input == 'D' || input == 'd')
		temp = 0;
	else if (input == 'W' || input == 'w')
		temp = 1;
	else if (input == 'A' || input == 'a')
		temp = 2;
	else if (input == 'S' || input == 's')
		temp = 3;
	if (length > 1) //当蛇长大于1时，蛇头不可直接反向
		if ((quaternaryVector - temp) % 2 == 0)
			return quaternaryVector;
	return temp;
}
