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

Equipment * ItemGenerator::GenerateEquipment(int level)
{
	EquipmentType equipmentType = randomEquipmentType.Roll();

	switch (equipmentType)
	{
	case EquipmentType_Armor:
		return new Armor(level);
	case EquipmentType_Weapon:
		return new Weapon(level);
	default:
		return new Armor(level);
	}
}