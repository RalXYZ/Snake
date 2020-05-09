#pragma once

#include "macros.h"
#include "resource.h"
#include <vector>

class Map {
public:
	unsigned int number;
	unsigned int spawnNumber;

	std::vector<int> resource = { IDR_MAP00, IDR_MAP01, IDR_MAP02, IDR_MAP03, IDR_MAP04, IDR_MAP05, IDR_MAP06 };

	struct spawn {
		int x;
		int y;
		Directions headDirection;
	} spawnProperties[4] = { {1, 1, Directions::Right}, {1, 12, Directions::Up},
		{12, 12, Directions::Left}, {12, 1, Directions::Down} };

	Map();
};
