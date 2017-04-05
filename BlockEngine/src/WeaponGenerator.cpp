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
	WeaponType type = GetRandomWeaponType(level);
	WeaponSlot slot = GenerateWeaponSlot(type);
	WeaponSpeed speed = GenerateWeaponSpeed(type, slot);
	EquipmentRarity rarity = GenerateEquipmentRarity(level);
	EquipmentStats stats = GenerateEquipmentStats(level, rarity);
	int damage = GenerateWeaponDamage(level, speed, rarity);
	
	return new Weapon(type, slot, speed, rarity, stats, level, damage, nullptr);
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