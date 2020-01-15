#pragma once

void upRightRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 18);
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void upLeftRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 18);
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void downRightRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 24);
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void downLeftRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 24);
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void downRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 24);
}

void upRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 18);
}

void rightRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void leftRectangle(int y, int x) {
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void verticalRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 0, y * 20 + 18, x * 20 + 24);
}

void horizontalRectangle(int y, int x) {
	fillrectangle(y * 20 + 0, x * 20 + 6, y * 20 + 24, x * 20 + 18);
}

void dotRectangle(int y, int x) {
	fillrectangle(y * 20 + 6, x * 20 + 6, y * 20 + 18, x * 20 + 18);
}

void fruitRectangle(int y, int x) {
	fillrectangle(y * 20 + 9, x * 20 + 9, y * 20 + 15, x * 20 + 15);
}
