#pragma once

#include <vector>

using std::vector;
struct color {
	int background;
	int foreground;
	vector<int> accent;
};

static const color NightClub{ 0x3a2528, 0x4f17c3, {0x8d83b5} };

/*Designed by Sunflower*/
static const color CangSong{ 0x273220, 0x6d7b63, {0xadc29c} };
static const color Hoopoe{ 0x4d95ff, 0x1e2f48, {0xd8e6ff} };
static const color RedBean{ 0xb4b2b9, 0x1f121b, {0x0e0b7a} };
static const color Bluebird{ 0xd9d1c9, 0xba8047, {0x5552ba} };
static const color Rose{ 0x312e31, 0xb9b6ff, {0x7f5fff} };
static const color Halloween{ 0x2b161c, 0x0a4eb9, {0x1281c3} };
static const color Panda{ 0x222222, 0x828282, {0xeaeaea} };
static const color Raven{ 0x201c19, 0x9d9893, { 0x030067, 0x376fff, 0x37c0ff, 0x2ac264, 0x86c216, 0xd17524, 0x931941 } };
static const color NightRain{ 0x201c19, 0x705f52, {0xd9baa2} };
static const color Plumage{ 0xffefdd, 0x00bdd4, {0xc0ac6e} };

const color Theme[]{ NightClub, CangSong, Hoopoe, RedBean, Bluebird, Rose, Halloween, Panda, Raven, NightRain };
const int ThemeSize = sizeof(Theme) / sizeof(*Theme);
