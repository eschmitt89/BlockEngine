//
//  Armor.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Armor.hpp"

Armor::Armor(ArmorType armorType, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level)
	:Equipment(EquipmentType_Armor, equipmentRarity, equipmentStats, level)
{
	this->armorType = armorType;
}

////////////////////////////////////////////////////////////////////////

Armor::~Armor()
{

}

////////////////////////////////////////////////////////////////////////

