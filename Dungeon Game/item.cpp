#include "item.h"

Armor::Armor(std::string _name, int _armor, int _bonusHealth){
	name = _name;
	armor = _armor;
	bonusHealth = _bonusHealth;
};

Weapon::Weapon(std::string _name, int _damage, int _criticalChance) {
	name = _name;
	damage = _damage;
	criticalChance = _criticalChance;
};

Potion::Potion(std::string _name, int _healing) {
	name = _name;
	healing = _healing;
};

