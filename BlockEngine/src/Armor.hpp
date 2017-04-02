//
//  Armor.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Armor_hpp
#define Armor_hpp

#include "Equipment.hpp"
#include "ArmorType.hpp"

class Armor : public Equipment
{
public:
	Armor(ArmorType armorType, EquipmentRarity rarity, int level);
    virtual ~Armor();

protected:
	ArmorType armorType;

private:
	void GenerateStats(EquipmentRarity rarity, int level);
};

#endif /* Armor_hpp */
