#include "maps.h"
#include <random>

//int mapNumber = 0;
//int spawnNumber = 0;

Map::Map() {
	this->number = rand() % (this->resource.size());
	this->spawnNumber = rand() % 4;
}
