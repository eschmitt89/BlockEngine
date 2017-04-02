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
#include "EquipmentType.hpp"
#include "EquipmentRarity.hpp"
#include "Utilities.hpp"

class Equipment : public Item
{
public:
	Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, int level);
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

	virtual void GenerateStats(EquipmentRarity equipmentRarity, int level);

private:
	int GetStatValue(int maxValue, int level);

};

#endif /* Equipment_hpp */
