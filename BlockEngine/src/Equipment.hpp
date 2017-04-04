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

class Equipment : public Item
{
public:
	Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, int level, int health, int armor, int crit, int dodge, int power);
    virtual ~Equipment();

	EquipmentType GetEquipmentType();
	EquipmentRarity GetEquipmentRarity();
	

protected:
	EquipmentType equipmentType;
	EquipmentRarity equipmentRarity;
	
	int level;

	int health;
	int armor;
	int crit;
	int dodge;
	int power;

};

#endif /* Equipment_hpp */
