//
//  Weapon.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include "Equipment.hpp"
#include "WeaponType.hpp"

class Weapon : public Equipment
{
public:
	Weapon(WeaponType weaponType, EquipmentRarity rarity, int level);
    virtual ~Weapon();

protected:
	WeaponType weaponType;

private:
	void GenerateStats(EquipmentRarity rarity, int level);
};

#endif /* Weapon_hpp */
