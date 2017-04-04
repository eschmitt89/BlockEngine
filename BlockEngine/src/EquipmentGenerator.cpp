//
//  EquipmentGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "EquipmentGenerator.hpp"

EquipmentGenerator::EquipmentGenerator()
{
	randomEquipmentRarity = DropRateCollection<EquipmentRarity>();
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Common, 0.489);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Good, 0.30);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Rare, 0.15);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Epic, 0.05);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Legendary, 0.01);
	randomEquipmentRarity.AddDropRate(EquipmentRarity_Artifact, 0.001);
}

////////////////////////////////////////////////////////////////////////

EquipmentGenerator::~EquipmentGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

EquipmentRarity EquipmentGenerator::GenerateEquipmentRarity(int level)
{
	EquipmentRarity equipmentRarity = randomEquipmentRarity.Roll();

	if (equipmentRarity == EquipmentRarity_Artifact && level < MIN_ARTIFACT_LEVEL)
	{
		equipmentRarity = EquipmentRarity_Legendary;
	}
	if (equipmentRarity == EquipmentRarity_Legendary && level < MIN_LEGENDARY_LEVEL)
	{
		equipmentRarity = EquipmentRarity_Epic;
	}
	if (equipmentRarity == EquipmentRarity_Epic && level < MIN_EPIC_LEVEL)
	{
		equipmentRarity = EquipmentRarity_Rare;
	}
	if (equipmentRarity == EquipmentRarity_Rare && level < MIN_RARE_LEVEL)
	{
		equipmentRarity = EquipmentRarity_Good;
	}
	if (equipmentRarity == EquipmentRarity_Good && level < MIN_GOOD_LEVEL)
	{
		equipmentRarity = EquipmentRarity_Common;
	}

	return equipmentRarity;
}

////////////////////////////////////////////////////////////////////////

int EquipmentGenerator::GenerateEquipmentStatValue(int level, int maxValue)
{
	return ((float)level / EQUIPMENT_MAX_LEVEL) * (maxValue / EQUIPMENT_SLOTS / EQUIPMENT_MAX_STAT_COUNT);
}

////////////////////////////////////////////////////////////////////////
