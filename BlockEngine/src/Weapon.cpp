//
//  Weapon.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Weapon.hpp"

Weapon::Weapon(WeaponType weaponType, WeaponSlot weaponSlot, EquipmentRarity rarity, int level, int health, int armor, int crit, int dodge, int power)
	:Equipment(EquipmentType_Weapon, rarity, level, health, armor, crit, dodge, power)
{
	this->weaponType = weaponType;
	this->weaponSlot = weaponSlot;
}

////////////////////////////////////////////////////////////////////////

Weapon::~Weapon()
{
    
}

////////////////////////////////////////////////////////////////////////

