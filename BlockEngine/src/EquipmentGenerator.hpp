//
//  EquipmentGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef EquipmentGenerator_hpp
#define EquipmentGenerator_hpp

#include "Equipment.hpp"

#define EQUIPMENT_MAX_LEVEL 100
#define EQUIPMENT_SLOTS 8
#define EQUIPMENT_MAX_STAT_COUNT 5

#define MIN_GOOD_LEVEL 1
#define MIN_RARE_LEVEL 5
#define MIN_EPIC_LEVEL 10
#define MIN_LEGENDARY_LEVEL 15
#define MIN_ARTIFACT_LEVEL 20

#define MAX_HEALTH 10000
#define MAX_ARMOR 10000
#define MAX_CRIT 10000
#define MAX_DODGE 10000
#define MAX_POWER 10000

class EquipmentGenerator
{
public:
	EquipmentGenerator();
    virtual ~EquipmentGenerator();

protected:
	DropRateCollection<EquipmentRarity> randomEquipmentRarity;

	EquipmentRarity GenerateEquipmentRarity(int level);
	int GenerateEquipmentStatValue(int level, int maxValue);

};

#endif /* EquipmentGenerator_hpp */
