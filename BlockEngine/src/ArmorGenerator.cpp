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

	EquipmentStats equipmentStats = GenerateEquipmentStats(level, equipmentRarity);

	return new Armor(armorType, equipmentRarity, equipmentStats, level);
}

////////////////////////////////////////////////////////////////////////
