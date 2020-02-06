#pragma once

#include "macros.h"
#include "resource.h"

struct map {
	map(int macro) {
		this->mapMacro = macro;
	}
	struct {
		int spawnX;
		int spawnY;
		Directions headDirection;
	} spawn[4] = { {1, 1, Directions::Right}, {1, 12, Directions::Up}, {12, 12, Directions::Left}, {12, 1, Directions::Down} };
	int mapMacro;
};

const map MapResource[]{ (IDR_MAP00), (IDR_MAP01), (IDR_MAP02), (IDR_MAP03), (IDR_MAP04), (IDR_MAP05), (IDR_MAP06) };
const int MapResourceSize = sizeof(MapResource) / sizeof(*MapResource);
