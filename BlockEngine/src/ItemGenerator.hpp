//
//  ItemGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef ItemGenerator_hpp
#define ItemGenerator_hpp

#include "ArmorGenerator.hpp"
#include "WeaponGenerator.hpp"
#include "PotionGenerator.hpp"
#include "ScrollGenerator.hpp"
#include "GemGenerator.hpp"

class ItemGenerator
{
public:
	ItemGenerator();
    virtual ~ItemGenerator();

	Item* Generate(int level);
	Armor* GenerateArmor(int level);
	Weapon* GenerateWeapon(int level);
	Item* GeneratePotion(int level);
	Item* GenerateScroll(int level);
	Item* GenerateGem(int level);

private:
	DropRateCollection<ItemType> randomItemType;
	DropRateCollection<EquipmentType> randomEquipmentType;

	ArmorGenerator armorGenerator;
	WeaponGenerator weaponGenerator;
	PotionGenerator potionGenerator;
	ScrollGenerator scrollGenerator;
	GemGenerator gemGenerator;

	Equipment* GenerateEquipment(int level);
};

#endif /* ItemGenerator_hpp */
