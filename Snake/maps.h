#pragma once

struct maps {
	maps(int macro) {
		this->mapMacro = macro;
	}
	struct {
		int spawnX;
		int spawnY;
		int quaternaryVector;
	} spawn[4] = { {1, 1, 0}, {1, 12, 1}, {12, 12, 2}, {12, 1, 3} };
	int mapMacro;
};
