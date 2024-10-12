#include "dungeon.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void Dungeon::spawnEnemies(GameCharacter enemy, int number_of_enemies) {
    for (int t = 0; t < number_of_enemies; ++t) {
        int random_row = std::rand() % 5, random_col = (std::rand() % 5); // Generating a random number from 0 to 4
        while ((random_row == 0 and random_col == 0) || (random_row == 4 and random_col == 4))
            random_row = std::rand() % 5, random_col = (std::rand() % 5);
        rooms[random_row][random_col].enemies.push_back(enemy);
    }
}

void Dungeon::spawnItems(Item* item, int number_of_items) {
    for (int t = 0; t < number_of_items; ++t) {
        int random_row = std::rand() % 5, random_col = (std::rand() % 5); // Generating a random number from 0 to 4
        while ((random_row == 0 and random_col == 0) || (random_row == 4 and random_col == 4))
            random_row = std::rand() % 5, random_col = (std::rand() % 5);
        rooms[random_row][random_col].items.push_back(item);
    }
}

void Dungeon::setUpDungeon() {
    // Setting up the dungeon, giving each room it's coords
    for (int row = 0; row < ROWS; ++ row)
        for (int col = 0; col < COLS; ++ col)
            rooms[row][col] = { row, col };

    // Setting the seed of the number generator to the current time
    std::srand(static_cast<unsigned int>(time(0))); // This is so as we get different numbers each time we play

    // Spawning each enemy in random positions

    // Bat
    GameCharacter bat = GameCharacter("Bat", 20, 5);
    constexpr int number_of_bats = 2;
    spawnEnemies(bat, number_of_bats);

    // Rat
    GameCharacter rat = GameCharacter("Rat", 20, 10);
    constexpr int number_of_rats = 2;
    spawnEnemies(rat, number_of_rats);

    // Slime
    GameCharacter slime = GameCharacter("Slime", 10, 10);
    constexpr int number_of_slimes = 3;
    spawnEnemies(slime, number_of_slimes);

    // Goblin
    GameCharacter goblin = GameCharacter("Goblin", 50, 8);
    constexpr int number_of_goblins = 1;
    spawnEnemies(goblin, number_of_goblins);

    // Troll
    GameCharacter troll = GameCharacter("Troll", 500, 100);
    rooms[0][0].enemies.push_back(troll); // This will be the final boss, so it will be in the last room

    // List of items in the dungeon

    // Dynamically allocating every item so it has a larger lifetime
    Weapon* commonSword = new Weapon("Common Sword", 25, 15);
    Weapon* rareSword = new Weapon("Rare Sword", 50, 30);
    Weapon* epicSword = new Weapon("Epic Sword", 80, 50);
    spawnItems(commonSword, 1);
    spawnItems(rareSword, 1);
    spawnItems(epicSword, 1);

    Armor* helmet = new Armor("Helmet", 15, 15);
    Armor* chestplate = new Armor("Chestplate", 30, 50);
    Armor* leggings = new Armor("a pair of Leggings", 20, 25);
    Armor* boots = new Armor("a pair of Boots", 15, 20);
    spawnItems(helmet, 1);
    spawnItems(chestplate, 1);
    spawnItems(leggings, 1);
    spawnItems(boots, 1);

    for (int i = 0; i < 4; ++i) {
        Potion* healingPotion = new Potion("Healing Potion", 50);
        spawnItems(healingPotion, 1);
    }
}
