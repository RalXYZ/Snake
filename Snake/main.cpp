#include <ctime>
#include <cstdlib>
#include <easyx.h>
#include <windows.h>
#include <conio.h>
#include <thread>
#include "resource.h"
#include "utilities.h"
#include "graphic.h"
#include "maps.h"

extern int themeNumber;
extern int mapNumber;
extern int spawnNumber;

bool windowCreated = false;
int mapCurrent[LENGTH + 2][LENGTH + 2];
int numberOfRow = 12, numberOfColumn = 12;
int fruitRow, fruitColumn;
DWORD timePerFrame;

int main() {

	/*create the seed for randoming*/
	srand((unsigned)time(NULL));

	/*data initialization*/
	themeNumber = rand() % ThemeSize;
	mapNumber = rand() % MapResourceSize;
	spawnNumber = rand() % 4;
	auto spawnCurrent = MapResource[mapNumber].spawn[spawnNumber];
	Directions headDirection = spawnCurrent.headDirection;
	int currentRow = spawnCurrent.spawnX,
		currentColumn = spawnCurrent.spawnY;
	int length = 1;
	bool fruitExists = false;
	bool hitBody = false;
	bool hitWall = false;
	bool firstLoop = true;

	/*linked list initialization*/
	Snake* oldBody = new Snake;
	oldBody->x = spawnCurrent.spawnX;
	oldBody->y = spawnCurrent.spawnY;
	oldBody->next = nullptr;
	Snake* head = oldBody;
	Snake* tail = oldBody;

	/*window initialization*/
	if (windowCreated == false) {
		initgraph(HORIZENTAL, VERTICAL);
		windowCreated = true;
	}
	setlinestyle(PS_NULL);

	mapInput(MapResource[mapNumber].mapMacro);

	Complex::welcome(head);

	while (true) {
		bool fruitEaten = false;

		/*detect user keyboard input, pause or go, and judge the next location of the Snake's head based on it*/
		char key = '\0';
		if (_kbhit()) {
			key = _getch();
			if (key == ' ') {
				Word::paused();
				_getch();
				Word::statistics(length);
			}
			else if (key == -32)
				headDirection = keyToQuaternary(headDirection, length);
		}

		quaternaryToVector(headDirection, currentRow, currentColumn);

		/*place food randomly until the food is not located on the Snake's body*/
		Complex::placeFruit(fruitExists, head);

		/*detect what exists at the next position where the Snake's head locates*/
		if (currentRow == fruitRow && currentColumn == fruitColumn) {
			++length;
			fruitExists = false;
			fruitEaten = true;
			std::thread sound(eatSound);
			sound.detach();
		}
		else if (mapCurrent[currentColumn][currentRow] == 1) {
			setfillcolor(Theme[themeNumber].accent.front());
			switch (headDirection) {
			case Directions::Right:
				drawRectangle::right(head->x, head->y);
				break;
			case Directions::Up:
				drawRectangle::up(head->x, head->y);
				break;
			case Directions::Left:
				drawRectangle::left(head->x, head->y);
				break;
			case Directions::Down:
				drawRectangle::down(head->x, head->y);
				break;
			}
			hitWall = true;
			break;
		}
		else {
			for (Snake* tempBody = head; tempBody != tail; tempBody = tempBody->next)
				if (tempBody->x == currentRow && tempBody->y == currentColumn)
					hitBody = true;
		}

		/*the movement of Snake*/
		Snake* newBody = new Snake;
		newBody->x = currentRow;
		newBody->y = currentColumn;
		newBody->previous = nullptr;
		newBody->next = oldBody;
		head = newBody;
		oldBody->previous = newBody;
		if (fruitEaten == false) {
			Snake* temp = tail->previous;
			clearrectangle(tail->x * CUBE, tail->y * CUBE, tail->x * CUBE + CUBE, tail->y * CUBE + CUBE);
			if (tail->previous != nullptr)
				clearrectangle(tail->previous->x * CUBE, tail->previous->y * CUBE, tail->previous->x * CUBE + CUBE, tail->previous->y * CUBE + CUBE);
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
		oldBody = newBody;

		/*place food randomly until the food is not located on the Snake's body*/
		Complex::placeFruit(fruitExists, head);

		/*output*/
		Complex::visualSnake(head);
		if (fruitEaten || firstLoop)
			Word::statistics(length);

		/*judge game over*/
		if (hitBody)
			break;

		timePerFrame = accelerate(length);
		Sleep(timePerFrame);

		firstLoop = false;
	}

	/*prevent memory leak, delete the linked list of Snake*/
	for (Snake* i = head; i != nullptr; ) {
		Snake* temp = i->next;
		delete i;
		i = temp;
	}

	/*judge win or loss after ending*/
	if (length != numberOfRow * numberOfColumn) {
		char key = '\0';
		Word::gameOver(length);
		while (key = _getch())
			if (key == ' ')
				main();
	}
	else
		Word::youWin();
	return 0;
}
