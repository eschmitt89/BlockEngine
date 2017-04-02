//
//  ItemGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "ItemGenerator.hpp"

ItemGenerator::ItemGenerator()
{
	randomItemType = DropRateCollection<ItemType>();
	randomItemType.AddDropRate(ItemType_Equipment, 0.50);
	randomItemType.AddDropRate(ItemType_Potion, 0.17);
	randomItemType.AddDropRate(ItemType_Scroll, 0.17);
	randomItemType.AddDropRate(ItemType_Gem, 0.16);

	randomEquipmentType = DropRateCollection<EquipmentType>();
	randomEquipmentType.AddDropRate(EquipmentType_Armor, 0.75);
	randomEquipmentType.AddDropRate(EquipmentType_Weapon, 0.25);

	randomEquipmentRarity = DropRateCollection<EquipmentRarity>();
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Common, 0.489);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Good, 0.30);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Rare, 0.15);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Epic, 0.05);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Legendary, 0.01);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Artifact, 0.001);
}

////////////////////////////////////////////////////////////////////////

ItemGenerator::~ItemGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

Item * ItemGenerator::Generate(int level)
{
	ItemType itemType = randomItemType.Roll();

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

////////////////////////////////////////////////////////////////////////

Equipment * ItemGenerator::GenerateEquipment(int level)
{
	EquipmentType equipmentType = randomEquipmentType.Roll();
	EquipmentRarity equipmentRarity = randomEquipmentRarity.Roll();

	switch (equipmentType)
	{
	case EquipmentType_Armor:
		return new Armor(equipmentRarity, level);
	case EquipmentType_Weapon:
		return new Weapon(equipmentRarity, level);
	default:
		return new Armor(equipmentRarity, level);
	}
}

////////////////////////////////////////////////////////////////////////

EquipmentRarity ItemGenerator::GenerateEquipmentRarity(int level)
{
	EquipmentRarity equipmentRarity = randomEquipmentRarity.Roll();

	if (equipmentRarity == EquipmentRarity_Artifact && level < EquipmentRarity_Artifact)
	{
		equipmentRarity = EquipmentRarity_Legendary;
	}
	if (equipmentRarity == EquipmentRarity_Legendary && level < EquipmentRarity_Legendary)
	{
		equipmentRarity = EquipmentRarity_Epic;
	}
	if (equipmentRarity == EquipmentRarity_Epic && level < EquipmentRarity_Epic)
	{
		equipmentRarity = EquipmentRarity_Rare;
	}
	if (equipmentRarity == EquipmentRarity_Rare && level < EquipmentRarity_Rare)
	{
		equipmentRarity = EquipmentRarity_Good;
	}
	if (equipmentRarity == EquipmentRarity_Good && level < EquipmentRarity_Good)
	{
		equipmentRarity = EquipmentRarity_Common;
	}

	return equipmentRarity;
}
