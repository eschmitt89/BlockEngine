//
//  Weapon.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Weapon.hpp"

Weapon::Weapon(WeaponType weaponType, WeaponSlot weaponSlot, WeaponSpeed speed, EquipmentRarity rarity, int level, int health, int armor, int crit, int dodge, int power, int damage)
	:Equipment(EquipmentType_Weapon, rarity, level, health, armor, crit, dodge, power)
{
	this->weaponType = weaponType;
	this->weaponSlot = weaponSlot;
	this->speed = speed;
	this->damage = damage;
}

////////////////////////////////////////////////////////////////////////

Weapon::Weapon(int level)
	:Equipment(EquipmentType_Weapon, EquipmentRarity_Common, level, 0, 0, 0, 0, 0)
{
	GenerateStats(level);
}

////////////////////////////////////////////////////////////////////////

Weapon::~Weapon()
{

}

////////////////////////////////////////////////////////////////////////

void Weapon::GenerateStats(int level)
{
	equipmentRarity = rarityDropRates.Roll();

	weaponType = GetRandomWeaponType(level);
	weaponSlot = GenerateWeaponSlot(weaponType);
	speed = GenerateWeaponSpeed(weaponType, weaponSlot);
	damage = GenerateWeaponDamage(level, speed, equipmentRarity);

	GenerateWeaponStats(level, weaponType, equipmentRarity);
}

WeaponType Weapon::GetRandomWeaponType(int level)
{
	return static_cast<WeaponType>(Random(1, WEAPON_TYPE_COUNT));
}

////////////////////////////////////////////////////////////////////////

WeaponSlot Weapon::GenerateWeaponSlot(WeaponType weaponType)
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

WeaponSpeed Weapon::GenerateWeaponSpeed(WeaponType weaponType, WeaponSlot weaponSlot)
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
		return WeaponSpeed_Medium;
	}
}

////////////////////////////////////////////////////////////////////////

int Weapon::GenerateWeaponDamage(int level, WeaponSpeed speed, EquipmentRarity equipmentRarity)
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

void Weapon::GenerateWeaponStats(int level, WeaponType weaponType, EquipmentRarity equipmentRarity)
{
	for (int i = 0; i < equipmentRarity; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(1, EQUIPMENT_STAT_COUNT));

		switch (stat)
		{
		case EquipmentStat_Health:
			health += GetStatValue(level, MAX_HEALTH);
			break;
		case EquipmentStat_Armor:
			armor += GetStatValue(level, MAX_ARMOR);
			break;
		case EquipmentStat_Crit:
			crit += GetStatValue(level, MAX_CRIT);
			break;
		case EquipmentStat_Dodge:
			dodge += GetStatValue(level, MAX_DODGE);
			break;
		case EquipmentStat_Power:
			power += GetStatValue(level, MAX_POWER);
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////

