#include "game.h"
#include "time_utils.h"

#include <vector>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <conio.h>  // For _getch()

#define ClearScreen() system("cls")
#define IS_VOWEL(c) (tolower(c) == 'a' || tolower(c) == 'e' || tolower(c) == 'i' || tolower(c) == 'o' || tolower(c) == 'u')

std::unordered_map<Item*, bool> ignored; // Map for ignored items

Game::Game(Player* _player, Dungeon* _dungeon) {
    player = _player;
    dungeon = _dungeon;
    isGameOver = false;
    dungeon->setUpDungeon();
    player->currentRoom = &dungeon->rooms[dungeon->rows - 1][dungeon->cols - 1];
}

void Game::initiateRoomSequence() {
    ClearScreen();
    room* room = player->currentRoom;
    if (room->row == 0 && room->col == 0 && room->enemies.empty()) {
        std::cout << "Congratulations, you have reached the exit and are free of the dungeon! Farwell " << player->getName() << "!\n";
        isGameOver = true;
        return;
    }

    if (!room->enemies.empty()) {
        handleEnemyActions();
    }
    else if (!room->items.empty() and !ignored[player->currentRoom->items.front()]) {
        handleItemActions();
    }
    else {
        handleMovementActions();
        ignored.clear(); // Clear the list of ignored items
    }
}

void Game::printActions(std::vector<std::string> actions) {
    for (int index = 0; index < actions.size(); ++ index)
        std::cout << index + 1 << ". " << actions[index] << '\n';
}

std::vector<std::string> Game::getMovementActions() {
    std::vector<std::string> actions;
    room* currentRoom = player->currentRoom;
    if (currentRoom->col > 0)
        actions.push_back("Move left");
    if (currentRoom->row > 0)
        actions.push_back("Move up");
    if (currentRoom->col < (dungeon->cols - 1))
        actions.push_back("Move right");
    if (currentRoom->row < (dungeon->rows - 1))
        actions.push_back("Move down");
    return actions;
}

void Game::handleMovementActions() {
    printDungeon();
    std::cout << "You are now in room " << player->currentRoom->row << " " << player->currentRoom->col << '\n';
    std::cout << "Where do you want to go next?\n";
    std::vector<std::string> actions = getMovementActions();
    printActions(actions);

    int input;
    std::cin >> input;
    std::string chosenAction = actions[input - 1];

    int horizontalMovement = 0, verticalMovement = 0;
    if (chosenAction == "Move left")
        horizontalMovement = -1;
    else if (chosenAction == "Move up")
        verticalMovement = -1;
    else if (chosenAction == "Move right")
        horizontalMovement = 1;
    else if (chosenAction == "Move down")
        verticalMovement = 1;
    room* newRoom = &dungeon->rooms[player->currentRoom->row + verticalMovement][player->currentRoom->col + horizontalMovement];
    player->moveToRoom(newRoom);
    TimeSleep(250);
}

void Game::handleEnemyActions() {
    std::cout << "There is an enemy " << player->currentRoom->enemies.front().getName() << " in this room! What would you like to do?\n";
    std::vector<std::string> actions;
    actions.push_back("Engage enemy");
    actions.push_back("Retreat");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input == 1) {
        engageInCombat();
        return;
    }
    else {
        player->retreat();
        return;
    }
}

void Game::engageInCombat() {
    GameCharacter* enemy = &player->currentRoom->enemies.front();

    while (true) {
        bool isCriticalHit = std::rand() % 100 + 1 <= player->getCriticalChance(); // Boolean to verify if the hit was a criticall strike
        enemy->takeDamage(player->getDamage() * (1 + isCriticalHit));
        
        if(isCriticalHit)
            std::cout << "You critically strike the " << enemy->getName() << ", dealing " << player->getDamage() * 2 << " damage.\n";
        else
            std::cout << "You strike the " << enemy->getName() << ", dealing " << player->getDamage() << " damage.\n";

        if (!enemy->checkIfAlive()) {
            std::cout << "You have defeated the " << enemy->getName() << "!\n";
            player->currentRoom->enemies.pop_front();
            TimeSleep(1500);
            return;
        }

        int damageTaken = enemy->getDamage() - (enemy->getDamage() * player->getArmor() / 100);
        player->takeDamage(damageTaken);
        std::cout << "You take " << damageTaken << " damage. You now have " << player->getHealth() << " health.\n";
        
        if (!player->checkIfAlive()) {
            isGameOver = true;
            std::cout << "You have been defeated! Better luck next time!\n";
            TimeSleep(1500);
            return;
        }

        std::cout << "Would you like to keep fighting or retreat?\n";
        std::vector<std::string> actions;
        actions.push_back("Keep fighting");
        actions.push_back("Retreat");
        printActions(actions);

        int input;
        std::cin >> input;
        if (input != 1) {
            player->retreat();
            return;
        }
    }
}

void Game::handleItemActions() {
    Item* item = player->currentRoom->items.front();
    if (IS_VOWEL(player->currentRoom->items.front()->name[0]))
        std::cout << "You find an " << item->name << " in this room! What would you like to do?\n";
    else
        std::cout << "You find a " << item->name << " in this room! What would you like to do?\n";
    std::vector<std::string> actions;
    actions.push_back("Pick up item");
    actions.push_back("Ignore item");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input == 1) {
        player->pickUpItem(player->currentRoom->items.front());
        std::cout << "You equipped the " << player->currentRoom->items.front()->name << ".\n";
        std::cout << "Your stats are now: \n";
        std::cout << "Health: " << player->getHealth() << ".\n";
        std::cout << "Armor: " << player->getArmor() << ".\n";
        std::cout << "Damage: " << player->getDamage() << ".\n";
        std::cout << "Critical chance: " << player->getCriticalChance() << ".\n";
        delete player->currentRoom->items.front();
        player->currentRoom->items.pop_front();
        std::cout << "Press any button to continue.\n";
        while (true)
            if (_getch()) // Check if Enter is pressed (ASCII code 13)
                break;
        return;
    }
    else {
        ignored[player->currentRoom->items.front()] = true;
        player->currentRoom->items.push_back(player->currentRoom->items.front());
        player->currentRoom->items.pop_front();
        // Removing the first element so as all of them move left and thus another element is at front
        std::cout << "You chose to ignore the " << item->name << ".\n";
        TimeSleep(1000);
        return;
    }
}

void Game::printDungeon() {
    int currentRow = player->currentRoom->row, currentCol = player->currentRoom->col;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (row == currentRow && col == currentCol) {
                std::cout << "[ X ] ";
                continue;
            }
            
            std::cout << "[   ] ";
        }
        
        std::cout << '\n';
    }
}