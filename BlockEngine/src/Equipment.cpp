//
//  Equipment.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Equipment.hpp"

Equipment::Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level)
	:Item(ItemType_Equipment)
{
	this->equipmentType = equipmentType;
	this->equipmentRarity = equipmentRarity;
	this->equipmentStats = equipmentStats;
	this->level = level;
}

////////////////////////////////////////////////////////////////////////

Equipment::~Equipment()
{
    
}

////////////////////////////////////////////////////////////////////////

EquipmentType Equipment::GetEquipmentType()
{
	return equipmentType;
}

////////////////////////////////////////////////////////////////////////

EquipmentRarity Equipment::GetEquipmentRarity()
{
	return equipmentRarity;
}

////////////////////////////////////////////////////////////////////////

EquipmentStats Equipment::GetEquipmentStats()
{
	return equipmentStats;
}

////////////////////////////////////////////////////////////////////////