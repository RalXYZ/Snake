#pragma once 

#define LENGTH 40

struct snake {
	int x;
	int y;
	snake* previous = nullptr;
	snake* next;
};

void visualSnake(snake*& tempBody);
void quaternaryToVector(int quaternaryVector, int* currentRow, int* currentColumn);
int keyToQuaternary(char input, int quaternaryVector, int length);
void mapInput();
void eatSound();
double accelerate(int length);
