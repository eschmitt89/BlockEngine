//
//  ItemGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef ItemGenerator_hpp
#define ItemGenerator_hpp

#include "Armor.hpp"
#include "Weapon.hpp"

class ItemGenerator
{
public:
	ItemGenerator();
    virtual ~ItemGenerator();

	Item* Generate(int level);
	Equipment* GenerateEquipment(int level);
	Armor* GenerateArmor(int level);
	Weapon* GenerateWeapon();

private:
	DropRateCollection<ItemType> ItemDropRates;
	DropRateCollection<EquipmentType> EquipmentDropRates;

	int GetStatValue(int maxValue, int level);

};

#endif /* ItemGenerator_hpp */
