//
//  Weapon.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Weapon.hpp"

Weapon::Weapon(WeaponType weaponType, EquipmentRarity rarity, int level)
	:Equipment(EquipmentType_Weapon, rarity, level)
{
	this->weaponType = weaponType;
}

////////////////////////////////////////////////////////////////////////

Weapon::~Weapon()
{
    
}

////////////////////////////////////////////////////////////////////////

void Weapon::GenerateStats(EquipmentRarity rarity, int level)
{

}

////////////////////////////////////////////////////////////////////////

