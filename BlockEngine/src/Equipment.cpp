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

	rarityDropRates = DropRateCollection<EquipmentRarity>();
	rarityDropRates.AddDropRate(EquipmentRarity_Common, 0.489);
	rarityDropRates.AddDropRate(EquipmentRarity_Good, 0.30);
	rarityDropRates.AddDropRate(EquipmentRarity_Rare, 0.15);
	rarityDropRates.AddDropRate(EquipmentRarity_Epic, 0.05);
	rarityDropRates.AddDropRate(EquipmentRarity_Legendary, 0.01);
	rarityDropRates.AddDropRate(EquipmentRarity_Artifact, 0.001);
}

////////////////////////////////////////////////////////////////////////

Equipment::~Equipment()
{
    
}

////////////////////////////////////////////////////////////////////////

void Equipment::GenerateStats(int level)
{

}

////////////////////////////////////////////////////////////////////////

int Equipment::GetStatValue(int level, int maxValue)
{
	return ((float)level / MAX_LEVEL) * (maxValue / EQUIPMENT_SLOT_COUNT / MAX_STATS);
}

////////////////////////////////////////////////////////////////////////

