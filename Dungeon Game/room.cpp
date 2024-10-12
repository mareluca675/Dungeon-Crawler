#include <deque>

#include "gameCharacter.h"
#include "item.h"

#ifndef ROOM_CPP
#define ROOM_CPP

struct room {
	int row;
	int col;
	std::deque<GameCharacter> enemies;
	std::deque<Item*> items;
};

#endif