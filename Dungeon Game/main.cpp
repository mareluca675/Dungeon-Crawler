#include <iostream>
#include "time_utils.h"
#include "game.h"

void TimeSleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
    std::string name;
    std::cout << "Welcome to the dungeon! What is your name?\n";
    std::cin >> name;

    Player player = Player(name, 100, 10);
    Dungeon dungeon;
    Game game = Game(&player, &dungeon);

    std::cout << "Good luck, " << name << "! Beware, there are many creatures down there..\n";

    TimeSleep(2000);
    while (!game.isGameOver)
        game.initiateRoomSequence();
}