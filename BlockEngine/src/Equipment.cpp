//
//  Equipment.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Equipment.hpp"

Equipment::Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, int level, int health, int armor, int crit, int dodge, int power)
	:Item(ItemType_Equipment)
{
	this->equipmentType = equipmentType;
	this->equipmentRarity = equipmentRarity;

	this->level = level;

	this->health = health;
	this->armor = armor;
	this->crit = crit;
	this->dodge = dodge;
	this->power = power;
}

////////////////////////////////////////////////////////////////////////

Equipment::~Equipment()
{
    
}

////////////////////////////////////////////////////////////////////////

