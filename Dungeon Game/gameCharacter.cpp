#include "gameCharacter.h"

GameCharacter::GameCharacter(std::string _name, int _health, int _damage) {
	name = _name;
	maxHealth = _health;
	currentHealth = _health;
	damage = _damage;
	baseDamage = _damage;
}

void GameCharacter::takeDamage(int amount) {
	currentHealth -= amount;
}

bool GameCharacter::checkIfAlive() {
	return (currentHealth > 0);
}

std::string GameCharacter::getName() {
	return name;
}

int GameCharacter::getHealth() {
	return currentHealth;
}

int GameCharacter::getDamage() {
	return damage;
}