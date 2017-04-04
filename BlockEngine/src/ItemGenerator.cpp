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
		return GeneratePotion(level);
	case ItemType_Scroll:
		return GenerateScroll(level);
	case ItemType_Gem:
		return GenerateGem(level);
	default:
		return GenerateEquipment(level);
	}
}

////////////////////////////////////////////////////////////////////////

Equipment * ItemGenerator::GenerateEquipment(int level)
{
	EquipmentType equipmentType = randomEquipmentType.Roll();

	switch (equipmentType)
	{
	case EquipmentType_Armor:
		return GenerateArmor(level);
	case EquipmentType_Weapon:
		return GenerateWeapon(level);
	default:
		return GenerateArmor(level);
	}
}

////////////////////////////////////////////////////////////////////////

Armor * ItemGenerator::GenerateArmor(int level)
{
	return armorGenerator.Generate(level);
}

////////////////////////////////////////////////////////////////////////

Weapon * ItemGenerator::GenerateWeapon(int level)
{
	return weaponGenerator.Generate(level);
}

////////////////////////////////////////////////////////////////////////

Item * ItemGenerator::GeneratePotion(int level)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////

Item * ItemGenerator::GenerateScroll(int level)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////

Item * ItemGenerator::GenerateGem(int level)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////
