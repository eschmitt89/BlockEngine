//
//  Armor.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Armor.hpp"

Armor::Armor(ArmorType armorType, EquipmentRarity equipmentRarity, int level, int health, int armor, int crit, int dodge, int power)
	:Equipment(EquipmentType_Armor, equipmentRarity, level, health, armor, crit, dodge, power)
{
	this->armorType = armorType;
}

////////////////////////////////////////////////////////////////////////

Armor::~Armor()
{

}

////////////////////////////////////////////////////////////////////////

