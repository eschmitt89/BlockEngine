//
//  Equipment.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Equipment.hpp"
#include "EquipmentStat.hpp"


#define STAT_COUNT 5
#define EQUIPMENT_SLOTS 8

#define MAX_STATS 5
#define MAX_LEVEL 100
#define MAX_HEALTH 10000
#define MAX_ARMOR 10000
#define MAX_CRIT 10000
#define MAX_DODGE 10000
#define MAX_POWER 10000

Equipment::Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, int level)
	:Item(ItemType_Equipment)
{
	this->equipmentType = equipmentType;
	this->equipmentRarity = equipmentRarity;
	this->level = level;

	health = 0;
	armor = 0;
	crit = 0;
	dodge = 0;
	power = 0;

	GenerateStats(equipmentRarity, level);
}

////////////////////////////////////////////////////////////////////////

Equipment::~Equipment()
{
    
}

////////////////////////////////////////////////////////////////////////

void Equipment::GenerateStats(EquipmentRarity equipmentRarity, int level)
{
	int statPoints = equipmentRarity;

	for (int i = 0; i < statPoints; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(0, STAT_COUNT - 1));

		switch (stat)
		{
		case EquipmentStat_Health:
			health += GetStatValue(MAX_HEALTH, level);
			break;
		case EquipmentStat_Armor:
			armor += GetStatValue(MAX_ARMOR, level);
			break;
		case EquipmentStat_Crit:
			crit += GetStatValue(MAX_CRIT, level);
			break;
		case EquipmentStat_Dodge:
			dodge += GetStatValue(MAX_DODGE, level);
			break;
		case EquipmentStat_Power:
			power += GetStatValue(MAX_POWER, level);
			break;
		}
	}
}

int Equipment::GetStatValue(int maxValue, int level)
{
	return ((float)level / MAX_LEVEL) * (maxValue / EQUIPMENT_SLOTS / MAX_STATS);
}

////////////////////////////////////////////////////////////////////////

