#pragma once

#include <vector>

using std::vector;
struct color {
	int background;
	int foreground;
	vector<int> accent;
};

const color nightClub{ 0x3a2528, 0x4f17c3, {0x8d83b5} };

/*Designed by Sunflower*/
const color cangSong{ 0x273220, 0x6d7b63, {0xadc29c} };
const color hoopoe{ 0x4d95ff, 0x1e2f48, {0xd8e6ff} };
const color redBean{ 0xb4b2b9, 0x1f121b, {0x0e0b7a} };
const color bluebird{ 0xd9d1c9, 0xba8047, {0x5552ba} };
const color rose{ 0x312e31, 0xb9b6ff, {0x7f5fff} };
const color halloween{ 0x2b161c, 0x0a4eb9, {0x1281c3} };
const color panda{ 0x222222, 0x828282, {0xeaeaea} };
const color raven{ 0x201c19, 0x9d9893, { 0x030067, 0x376fff, 0x37c0ff, 0x2ac264, 0x86c216, 0xd17524, 0x931941 } };
const color nightRain{ 0x201c19, 0x705f52, {0xd9baa2} };
const color plumage{ 0xffefdd, 0x00bdd4, {0xc0ac6e} };

const vector<color> theme{ nightClub, cangSong, hoopoe, redBean, bluebird, rose, halloween, panda, raven, nightRain };
