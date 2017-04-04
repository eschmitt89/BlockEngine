//
//  WeaponGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef WeaponGenerator_hpp
#define WeaponGenerator_hpp

#include "EquipmentGenerator.hpp"
#include "Weapon.hpp"

class WeaponGenerator : public EquipmentGenerator
{
public:
	WeaponGenerator();
    ~WeaponGenerator();

	Weapon* Generate(int level);
	
private:
	WeaponType GetRandomWeaponType(int level);
	WeaponSlot GenerateWeaponSlot(WeaponType weaponType);
	WeaponSpeed GenerateWeaponSpeed(WeaponType weaponType, WeaponSlot weaponSlot);
	int GenerateWeaponDamage(int level, WeaponSpeed speed, EquipmentRarity equipmentRarity);
};

#endif /* WeaponGenerator_hpp */
