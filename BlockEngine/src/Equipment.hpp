//
//  Equipment.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Equipment_hpp
#define Equipment_hpp

#include "Item.hpp"
#include "EquipmentStat.hpp"
#include "EquipmentType.hpp"
#include "EquipmentRarity.hpp"

#define EQUIPMENT_SLOT_COUNT 8
#define EQUIPMENT_MAX_STATS 5

#define MAX_LEVEL 100

#define MAX_HEALTH 10000
#define MAX_ARMOR 10000
#define MAX_CRIT 10000
#define MAX_DODGE 10000
#define MAX_POWER 10000

class Equipment : public Item
{
public:
	Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, int level, int health, int armor, int crit, int dodge, int power);
    virtual ~Equipment();

protected:
	EquipmentType equipmentType;
	EquipmentRarity equipmentRarity;
	
	int level;

	int health;
	int armor;
	int crit;
	int dodge;
	int power;

	int GetStatValue(int level, int maxValue);

};

#endif /* Equipment_hpp */
