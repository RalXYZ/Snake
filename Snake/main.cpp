#include <ctime>
#include <cmath>
#include <cstdlib>
#include <easyx.h>
#include <conio.h>
#include <thread>
#include "resource.h"
#include "utilities.h"
#include "display.h"
#include "maps.h"
#include "theme.h"

extern int themeNumber;
//extern int mapNumber;
//extern int spawnNumber;

bool windowCreated = false;
int mapCurrent[LENGTH + 2][LENGTH + 2];
int numberOfRow = 12, numberOfColumn = 12;
int fruitRow, fruitColumn;
DWORD timePerFrame;

int main() {
	/*create the seed for random*/
	srand(unsigned(time(nullptr)));

	Map Map;

	/*data initialization*/
	themeNumber = rand() % ThemeSize;
	//mapNumber = rand() % MapResourceSize;
	//spawnNumber = rand() % 4;
	//auto spawnCurrent = MapResource[mapNumber].spawn[spawnNumber];
	auto headDirection = Map.spawnProperties[Map.spawnNumber].headDirection;
	auto currentRow = Map.spawnProperties[Map.spawnNumber].x,
		currentColumn = Map.spawnProperties[Map.spawnNumber].y;
	auto length = 1;
	auto fruitExists = false;
	auto hitBody = false;
	auto hitWall = false; //Currently unused
	auto firstLoop = true;

	/*linked list initialization*/
	auto oldBody = new Snake;
	oldBody->x = Map.spawnProperties[Map.spawnNumber].x;
	oldBody->y = Map.spawnProperties[Map.spawnNumber].y;
	oldBody->next = nullptr;
	auto head = oldBody;
	auto tail = oldBody;

	/*window initialization*/
	if (windowCreated == false) {
		initgraph(HORIZONTAL, VERTICAL);
		windowCreated = true;
	}
	setlinestyle(PS_NULL);

	mapInput(Map.resource.at(Map.number));

	DisplayComplex::welcome(head, Map);

	while (true) {
		auto fruitEaten = false;

		/*detect user keyboard input, pause or go, and judge the next location of the Snake's head based on it*/
		auto key = '\0';
		if (_kbhit()) {
			key = char(_getch());
			if (key == ' ') {
				DisplayWord::paused();
				_getch();
				DisplayWord::statistics(length);
			}
			else if (key == -32)
				headDirection = keyToQuaternary(headDirection, length);
		}

		quaternaryToVector(headDirection, currentRow, currentColumn);

		/*place food randomly until the food is not located on the Snake's body*/
		DisplayComplex::placeFruit(fruitExists, head);

		/*detect what exists at the next position where the Snake's head locates*/
		if (currentRow == fruitRow && currentColumn == fruitColumn) {
			++length;
			fruitExists = false;
			fruitEaten = true;
			/* TODO
			std::thread sound(eatSound);
			sound.detach();
			*/
		}
		else if (mapCurrent[currentColumn][currentRow] == 1) {
			DisplayComplex::headStuck(head, headDirection);
			hitWall = true;
			break;
		}
		else {
			for (auto tempBody = head; tempBody != tail; tempBody = tempBody->next)
				if (tempBody->x == currentRow && tempBody->y == currentColumn)
					hitBody = true;
		}

		/*the movement of Snake*/
		const auto newBody = new Snake;
		newBody->x = currentRow;
		newBody->y = currentColumn;
		newBody->previous = nullptr;
		newBody->next = oldBody;
		head = newBody;
		oldBody->previous = newBody;
		if (fruitEaten == false) {
			const auto temp = tail->previous;
			clearrectangle(tail->x * CUBE, tail->y * CUBE, tail->x * CUBE + CUBE, tail->y * CUBE + CUBE);
			if (tail->previous != nullptr)
				clearrectangle(tail->previous->x * CUBE, tail->previous->y * CUBE, tail->previous->x * CUBE + CUBE, tail->previous->y * CUBE + CUBE);
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
		oldBody = newBody;

		/*place food randomly until the food is not located on the Snake's body*/
		DisplayComplex::placeFruit(fruitExists, head);

		/*output*/
		DisplayComplex::visualSnake(head);
		if (fruitEaten || firstLoop)
			DisplayWord::statistics(length);

		/*judge game over*/
		if (hitBody)
			break;

		timePerFrame = accelerate(length);
		Sleep(timePerFrame);

		firstLoop = false;
	}

	/*prevent memory leak, delete the linked list of Snake*/
	for (auto i = head; i != nullptr; ) {
		const auto temp = i->next;
		delete i;
		i = temp;
	}

	/*judge win or loss after ending*/
	if (length != numberOfRow * numberOfColumn) {
		auto key = '\0';
		DisplayWord::gameOver(length);
		while (key = char(_getch()))
			if (key == ' ')
				main();
	}
	else
		DisplayWord::youWin();
	return 0;
}
