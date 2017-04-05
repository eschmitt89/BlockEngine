//
//  Weapon.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Weapon.hpp"

Weapon::Weapon(WeaponType weaponType, WeaponSlot weaponSlot, WeaponSpeed speed, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level, int damage, const sf::Texture* texture)
	:Equipment(EquipmentType_Weapon, equipmentRarity, equipmentStats, level, texture)
{
	this->weaponType = weaponType;
	this->weaponSlot = weaponSlot;
	this->speed = speed;
	this->damage = damage;
}

////////////////////////////////////////////////////////////////////////

Weapon::~Weapon()
{

}

//////////////////////////////////////////////////////////////////////////

