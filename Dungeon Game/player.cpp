#include "player.h"
//#include <iostream>

Player::Player(std::string _name, int _health, int _damage) : GameCharacter(_name, _health, _damage) {
    armor = 0;
    criticalChance = 0;
    currentRoom = nullptr;
    previousRoom = nullptr;
}

void Player::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth)
        currentHealth = maxHealth;
}

void Player::takeDamage(int amount) {
    currentHealth -= amount;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

void Player::moveToRoom(room* newRoom) {
    if (newRoom != nullptr) {
        previousRoom = currentRoom;
        currentRoom = newRoom;
    }
    else {
        //std::cout << "Attempted to move to a null room.\n";
    }
}

void Player::retreat() {
    if (currentRoom == nullptr || previousRoom == nullptr) {
        //std::cout << "Retreat not possible: invalid room pointers.\n";
        return;
    }

    //std::cout << "Attempting to retreat from room "
    //    << (currentRoom ? std::to_string(currentRoom->row) + " " + std::to_string(currentRoom->col) : "NULL")
    //    << " to previous room "
    //    << (previousRoom ? std::to_string(previousRoom->row) + " " + std::to_string(previousRoom->col) : "NULL")
    //    << "\n";

    std::swap(currentRoom, previousRoom);
}

void Player::pickUpItem(Item* item) {
    if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {  // Dyanmic cast to see if the item is of Weapon class
        //std::cout << "\nWEAPON TYPE\n";
        damage = baseDamage + weapon->damage;  // Set the weapon damage to player
        criticalChance = weapon->criticalChance;  // Set the critical chance
    }
    else if (Armor* armor = dynamic_cast<Armor*>(item)) {  // Dyanmic cast to see if the item is of Armor class
        //std::cout << "\nARMOR TYPE\n";
        this->armor += armor->armor;  // Add armor to player's armor
        maxHealth += armor->bonusHealth;
        heal(armor->bonusHealth);
    }
    else if (Potion* potion = dynamic_cast<Potion*>(item)) {  // Dyanmic cast to see if the item is of Potion class
        //std::cout << "\nPOTION TYPE\n";
        heal(potion->healing);  // Heal player using potion
    }
    else {
        //std::cout << "\nNON-ITEM TYPE\n";  // If it's none of the expected types
    }
}

int Player::getArmor() {
    return armor;
}

int Player::getCriticalChance() {
    return criticalChance;
}
