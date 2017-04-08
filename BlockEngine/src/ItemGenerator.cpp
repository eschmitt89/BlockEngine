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
		//return GeneratePotion(level);
	case ItemType_Scroll:
		//return GenerateScroll(level);
	case ItemType_Gem:
		//return GenerateGem(level);
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
		//return GenerateWeapon(level);
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

Potion * ItemGenerator::GeneratePotion(int level)
{
	return potionGenerator.Generate(level);
}

////////////////////////////////////////////////////////////////////////

Scroll * ItemGenerator::GenerateScroll(int level)
{
	return scrollGenerator.Generate(level);
}

////////////////////////////////////////////////////////////////////////

Gem * ItemGenerator::GenerateGem(int level)
{
	return gemGenerator.Generate(level);
}

////////////////////////////////////////////////////////////////////////

Coin * ItemGenerator::GenerateCoin(int value)
{
	return coinGenerator.Generate(value);
}

////////////////////////////////////////////////////////////////////////

PhysicsObject * ItemGenerator::Generate(int level, sf::Vector2f position)
{
	return new ItemPhysicsObject(Generate(level), position);
}

////////////////////////////////////////////////////////////////////////

vector<PhysicsObject*> ItemGenerator::GenerateLoot(int level, sf::Vector2f position)
{
	vector<PhysicsObject*> loot;

	int numberOfCoins = Random(1, ((level / (float)EQUIPMENT_MAX_LEVEL) * MAX_COINS) + 1);

	for (int i = 0; i < numberOfCoins; i++)
	{
		//loot.push_back(new ItemPhysicsObject(GenerateCoin(COIN_VALUE), position));
	}

	int numberOfItems = Random(2, 4);

	for (int i = 0; i < numberOfItems; i++)
	{
		loot.push_back(Generate(level, position));
	}

	return loot;
}

////////////////////////////////////////////////////////////////////////
