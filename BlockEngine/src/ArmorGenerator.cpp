//
//  ArmorGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "ArmorGenerator.hpp"

ArmorGenerator::ArmorGenerator()
{

}

////////////////////////////////////////////////////////////////////////

ArmorGenerator::~ArmorGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

Armor * ArmorGenerator::Generate(int level)
{
	ArmorType armorType = static_cast<ArmorType>(Random(1, ARMOR_TYPE_COUNT));

	EquipmentRarity equipmentRarity = GenerateEquipmentRarity(level);

	int health = 0;
	int armor = 0;
	int crit = 0;
	int dodge = 0;
	int power = 0;

	for (int i = 0; i < equipmentRarity; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(1, EQUIPMENT_STAT_COUNT));

		switch (stat)
		{
		case EquipmentStat_Health:
			health += GenerateEquipmentStatValue(level, MAX_HEALTH);
			break;
		case EquipmentStat_Armor:
			armor += GenerateEquipmentStatValue(level, MAX_ARMOR);
			break;
		case EquipmentStat_Crit:
			crit += GenerateEquipmentStatValue(level, MAX_CRIT);
			break;
		case EquipmentStat_Dodge:
			dodge += GenerateEquipmentStatValue(level, MAX_DODGE);
			break;
		case EquipmentStat_Power:
			power += GenerateEquipmentStatValue(level, MAX_POWER);
			break;
		default:
			break;
		}
	}

	return new Armor(armorType, equipmentRarity, level, health, armor, crit, dodge, power);
}

////////////////////////////////////////////////////////////////////////