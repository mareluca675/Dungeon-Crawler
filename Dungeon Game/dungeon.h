#include "room.cpp" 

#ifndef DUNGEON_H
#define DUNGEON_H

// Defining constants for the dungeon's size
#define ROWS 5
#define COLS 5

// Dungeon class
class Dungeon {
    public:
        static constexpr int rows = ROWS, cols = COLS;
        room rooms[ROWS][COLS];
        void setUpDungeon(); // Function for setting up the dungeon 
        void spawnEnemies(GameCharacter, int); // Function for spawning enemies into the dungeon
        void spawnItems(Item*, int);
};

#endif