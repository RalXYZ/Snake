#pragma once

#include "macros.h"
#include <vector>

struct map {
	map(int macro) {
		this->mapMacro = macro;
	}
	struct {
		int spawnX;
		int spawnY;
		Directions headDirection;
	} spawn[4] = { {1, 1, Right}, {1, 12, Up}, {12, 12, Left}, {12, 1, Down} };
	int mapMacro;
};
