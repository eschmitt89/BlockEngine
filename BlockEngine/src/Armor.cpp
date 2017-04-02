//
//  Armor.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Armor.hpp"

Armor::Armor(ArmorType armorType, EquipmentRarity rarity, int level, int health, int armor, int crit, int dodge, int power)
	:Equipment(EquipmentType_Armor, rarity, level, health, armor, crit, dodge, power)
{
	this->armorType = armorType;
}

////////////////////////////////////////////////////////////////////////

Armor::Armor(int level)
	:Equipment(EquipmentType_Armor, EquipmentRarity_Common, level, 0, 0, 0, 0, 0)
{
	GenerateStats(level);
}

////////////////////////////////////////////////////////////////////////

Armor::~Armor()
{
    
}

////////////////////////////////////////////////////////////////////////

void Armor::GenerateStats(int level)
{
	armorType = static_cast<ArmorType>(Random(1, ARMOR_TYPE_COUNT));

	equipmentRarity = rarityDropRates.Roll();

	for (int i = 0; i < equipmentRarity; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(1, EQUIPMENT_STAT_COUNT));

		switch (stat)
		{
		case EquipmentStat_Health:
			health += GetStatValue(level, MAX_HEALTH);
			break;
		case EquipmentStat_Armor:
			armor += GetStatValue(level, MAX_ARMOR);
			break;
		case EquipmentStat_Crit:
			crit += GetStatValue(level, MAX_CRIT);
			break;
		case EquipmentStat_Dodge:
			dodge += GetStatValue(level, MAX_DODGE);
			break;
		case EquipmentStat_Power:
			power += GetStatValue(level, MAX_POWER);
			break;
		default:
			break;
		}
	}
}

