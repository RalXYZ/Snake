#include <iostream>
#include <conio.h>
#include <easyx.h>
#include <cmath>
#include "macros.h"
#include "resource.h"
#include "utilities.h"

void quaternaryToVector(Directions quaternaryVector, int& currentRow, int& currentColumn) {
	switch (quaternaryVector) {
	case Directions::Right:
		++currentRow;
		break;
	case Directions::Left:
		--currentRow;
		break;
	case Directions::Up:
		--currentColumn;
		break;
	case Directions::Down:
		++currentColumn;
		break;
	}
}

Directions keyToQuaternary(Directions quaternaryVector, int length) {
	auto temp = quaternaryVector;
	switch (Keyboard(_getch())) {
	case Keyboard::Right:
		temp = Directions::Right;
		break;
	case Keyboard::Up:
		temp = Directions::Up;
		break;
	case Keyboard::Left:
		temp = Directions::Left;
		break;
	case Keyboard::Down:
		temp = Directions::Down;
		break;
	}
	if (length > 1) //the Snake should not reverse its orientation when its length is bigger than 1
		if ((int(quaternaryVector) - int(temp)) % 2 == 0)
			return quaternaryVector;
	return temp;
}

void mapInput(int mapMacro) {
	const HRSRC hResource = FindResourceA(nullptr, MAKEINTRESOURCEA(mapMacro), "TEXT");
	const HGLOBAL hMemory = LoadResource(nullptr, hResource);
	char* mapElement = (char*)LockResource(hMemory);
	int str_size = SizeofResource(nullptr, hResource);
	if (!hResource) {
		std::cout << "Unable to load map file! " << mapMacro;
		exit(1);
	}
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			mapCurrent[i][j] = *mapElement - '0';
			mapElement++;
		}
		mapElement++;
		mapElement++;
	}
}

/* TODO
void eatSound() {
	//TODO find a proper sound fx
}
*/
