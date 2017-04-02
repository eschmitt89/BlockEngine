//
//  ItemGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "ItemGenerator.hpp"

#define MAX_ROLL 1000
#define ITEM_TYPES 4
#define EQUIPMENT_TYPES 2
#define EQUIPMENT_STATS 5
#define EQUIPMENT_SLOTS 8
#define ARMOR_TYPES 6

#define MAX_STATS 5
#define MAX_LEVEL 100
#define MAX_HEALTH 10000
#define MAX_ARMOR 10000
#define MAX_CRIT 10000
#define MAX_DODGE 10000
#define MAX_POWER 10000


ItemGenerator::ItemGenerator()
{
	ItemDropRates = DropRateCollection<ItemType>();
	ItemDropRates.AddDropRate(ItemType_Equipment, 0.50);
	ItemDropRates.AddDropRate(ItemType_Potion, 0.17);
	ItemDropRates.AddDropRate(ItemType_Scroll, 0.17);
	ItemDropRates.AddDropRate(ItemType_Gem, 0.16);

	EquipmentDropRates = DropRateCollection<EquipmentType>();
	EquipmentDropRates.AddDropRate(EquipmentType_Armor, 0.75);
	EquipmentDropRates.AddDropRate(EquipmentType_Weapon, 0.25);
}

////////////////////////////////////////////////////////////////////////

ItemGenerator::~ItemGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

Item * ItemGenerator::Generate(int level = 0)
{
	ItemType itemType = ItemDropRates.Roll();

	switch (itemType)
	{
	case ItemType_Equipment:
		return GenerateEquipment(level);
	case ItemType_Potion:
		return GenerateEquipment(level);
	case ItemType_Scroll:
		return GenerateEquipment(level);
	case ItemType_Gem:
		return GenerateEquipment(level);
	default:
		return GenerateEquipment(level);
	}
}

Equipment * ItemGenerator::GenerateEquipment(int level)
{
	EquipmentType equipmentType = EquipmentDropRates.Roll();

	switch (equipmentType)
	{
	case EquipmentType_Armor:
		return GenerateArmor(level);
	case EquipmentType_Weapon:
		return GenerateWeapon();
	default:
		return GenerateArmor(level);
	}
}

////////////////////////////////////////////////////////////////////////

Armor * ItemGenerator::GenerateArmor(int level)
{
	// Generate Armor Type
	int roll = Random(1, ARMOR_TYPES);

	// Generate Rarity
	ArmorType armorType = static_cast<ArmorType>(roll);
	EquipmentRarity equipmentRarity;

	roll = Random(1, 1000);
	
	if (roll < 500) // Common - 50%
	{
		equipmentRarity = EquipmentRarity_Common;
	}
	else if (roll < 800) // Good - 30%
	{
		equipmentRarity = EquipmentRarity_Good;
	}
	else if (roll < 950) // Rare - 15%
	{
		equipmentRarity = EquipmentRarity_Rare;
	}
	else if (roll < 990) // Epic - 5%
	{
		equipmentRarity = EquipmentRarity_Epic;
	}
	else if (roll < 999) // Legendary - 1%
	{
		equipmentRarity = EquipmentRarity_Legendary;
	}
	else // Artifact - 0.1%
	{
		equipmentRarity = EquipmentRarity_Artifact;
	}

	// Generate Stats
	int statPoints = equipmentRarity;
	int health = 0;
	int armor = 0;
	int crit = 0;
	int dodge = 0;
	int power = 0;

	for (int i = 0; i < statPoints; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(1, EQUIPMENT_STATS));

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

	return new Armor(armorType, equipmentRarity, level, health, armor, crit, dodge, power);
}

////////////////////////////////////////////////////////////////////////

Weapon * ItemGenerator::GenerateWeapon()
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////

int ItemGenerator::GetStatValue(int maxValue, int level)
{
	return ((float)level / MAX_LEVEL) * (maxValue / EQUIPMENT_SLOTS / MAX_STATS);
}