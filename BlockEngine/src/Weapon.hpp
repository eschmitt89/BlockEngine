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
#include "WeaponSlot.hpp"
#include "WeaponSpeed.hpp"

#define SPEED_NONE 0.0
#define SPEED_FAST 1.0
#define SPEED_MEDIUM 2.0
#define SPEED_SLOW 3.0

class Weapon : public Equipment
{
public:
	Weapon(WeaponType weaponType, WeaponSlot weaponSlot, WeaponSpeed speed, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level, int damage);
    virtual ~Weapon();

protected:
	WeaponType weaponType;
	WeaponSlot weaponSlot;
	WeaponSpeed speed;
	int damage;
};

#endif /* Weapon_hpp */
