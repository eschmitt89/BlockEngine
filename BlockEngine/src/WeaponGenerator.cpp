//
//  WeaponGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "WeaponGenerator.hpp"

WeaponGenerator::WeaponGenerator()
{

}

////////////////////////////////////////////////////////////////////////

WeaponGenerator::~WeaponGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

Weapon * WeaponGenerator::Generate(int level)
{
	WeaponType weaponType = GetRandomWeaponType(level);
	WeaponSlot weaponSlot = GenerateWeaponSlot(weaponType);
	WeaponSpeed speed = GenerateWeaponSpeed(weaponType, weaponSlot);
	EquipmentRarity equipmentRarity = GenerateEquipmentRarity(level);
	int damage = GenerateWeaponDamage(level, speed, equipmentRarity);
	
	int health = 0;
	int armor = 0;
	int crit = 0;
	int dodge = 0;
	int power = 0;

	for (int i = 0; i < equipmentRarity; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(1, EQUIPMENT_STAT_COUNT));
		
		switch (stat)
		{
		case EquipmentStat_Health:
			health += GenerateEquipmentStatValue(level, MAX_HEALTH);
			break;
		case EquipmentStat_Armor:
			armor += GenerateEquipmentStatValue(level, MAX_ARMOR);
			break;
		case EquipmentStat_Crit:
			crit += GenerateEquipmentStatValue(level, MAX_CRIT);
			break;
		case EquipmentStat_Dodge:
			dodge += GenerateEquipmentStatValue(level, MAX_DODGE);
			break;
		case EquipmentStat_Power:
			power += GenerateEquipmentStatValue(level, MAX_POWER);
			break;
		default:
			break;
		}
	}

	return new Weapon(weaponType, weaponSlot, speed, equipmentRarity, level, health, armor, crit, dodge, power, damage);
}

////////////////////////////////////////////////////////////////////////

WeaponType WeaponGenerator::GetRandomWeaponType(int level)
{
	return static_cast<WeaponType>(Random(1, WEAPON_TYPE_COUNT));
}

////////////////////////////////////////////////////////////////////////

WeaponSlot WeaponGenerator::GenerateWeaponSlot(WeaponType weaponType)
{
	if (weaponType == WeaponType_Dagger || weaponType == WeaponType_Wand)
	{
		return WeaponSlot_OneHand;
	}
	else if (weaponType == WeaponType_Sword || weaponType == WeaponType_Axe || weaponType == WeaponType_Mace)
	{
		return (Random(1, 3) > 1) ? WeaponSlot_OneHand : WeaponSlot_TwoHand;
	}
	else if (weaponType == WeaponType_Staff)
	{
		return WeaponSlot_TwoHand;
	}
	else if (weaponType == WeaponType_Orb || weaponType == WeaponType_Shield)
	{
		return WeaponSlot_OffHand;
	}
	else
	{
		return WeaponSlot_OneHand;
	}
}

////////////////////////////////////////////////////////////////////////

WeaponSpeed WeaponGenerator::GenerateWeaponSpeed(WeaponType weaponType, WeaponSlot weaponSlot)
{
	switch (weaponSlot)
	{
	case WeaponSlot_OneHand:
		if (weaponType == WeaponType_Dagger || weaponType == WeaponType_Wand)
		{
			return WeaponSpeed_Fast;
		}
		else
		{
			return WeaponSpeed_Medium;
		}
	case WeaponSlot_TwoHand:
		return WeaponSpeed_Slow;
	case WeaponSlot_OffHand:
		return WeaponSpeed_None;
	default:
		return WeaponSpeed_None;
	}
}

////////////////////////////////////////////////////////////////////////

int WeaponGenerator::GenerateWeaponDamage(int level, WeaponSpeed speed, EquipmentRarity equipmentRarity)
{
	switch (speed)
	{
	case WeaponSpeed_None:
		return 0;
	case WeaponSpeed_Fast:
		return level;
	case WeaponSpeed_Medium:
		return level * 2;
	case WeaponSpeed_Slow:
		return level * 3;
	default:
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////