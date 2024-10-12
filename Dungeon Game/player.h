#include "gameCharacter.h"
#include "room.cpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameCharacter {
    private:
        room* previousRoom;
    protected:
        int armor;
        int criticalChance;
    public:
        room* currentRoom;
        Player(std::string, int, int);
        void heal(int);
        void takeDamage(int);
        void moveToRoom(room*);
        void retreat();
        void pickUpItem(Item*);
        int getArmor();
        int getCriticalChance();
};

#endif