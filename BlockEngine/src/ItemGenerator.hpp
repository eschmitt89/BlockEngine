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
	Armor* GenerateArmor(int level);
	Weapon* GenerateWeapon(int level);
	EquipmentRarity GenerateEquipmentRarity(int level);

private:
	DropRateCollection<ItemType> randomItemType;
	DropRateCollection<EquipmentType> randomEquipmentType;
	DropRateCollection<EquipmentRarity> randomEquipmentRarity;

	Equipment* GenerateEquipment(int level);

};

#endif /* ItemGenerator_hpp */
