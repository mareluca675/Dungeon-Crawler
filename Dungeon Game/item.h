#include <string>

#ifndef ITEM_H
#define ITEM_H

class Item {
	public:
		std::string name;
		virtual ~Item() {} // Destructor to ensure polymorphic behaviour
};

class Armor : public Item {
	public:
		int armor;
		int bonusHealth;
		Armor(std::string, int, int);
};

class Weapon : public Item {
	public:
		int damage;
		int criticalChance;
		Weapon(std::string, int, int);
};

class Potion : public Item {
	public:
		int healing;
		Potion(std::string, int);
};

#endif