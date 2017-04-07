#include "EquipmentCollection.hpp"

EquipmentCollection::EquipmentCollection()
{

}

////////////////////////////////////////////////////////////////////////

EquipmentCollection::~EquipmentCollection()
{
    
}

////////////////////////////////////////////////////////////////////////

void EquipmentCollection::Equip(Equipment * equipment)
{
	if (equipment->GetEquipmentType() == EquipmentType_Armor)
	{
		Armor* armor = (Armor*)equipment;
		this->armor[armor->GetArmorType()] = armor;
	}
	else if (equipment->GetEquipmentType() == EquipmentType_Weapon)
	{
		Weapon* weapon = (Weapon*)equipment;
		if (weapon->GetWeaponSlot() == WeaponSlot_TwoHand)
		{
			mainHandWeapon = weapon;
		}
		else if(weapon->GetWeaponSlot() == WeaponSlot_OffHand)
		{
			offHandWeapon = weapon;
		}
		else if (weapon->GetWeaponSlot() == WeaponSlot_OneHand)
		{
			if (!mainHandWeapon || (mainHandWeapon && offHandWeapon))
			{
				mainHandWeapon = weapon;
			}
			else if (!offHandWeapon)
			{
				offHandWeapon = weapon;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

EquipmentStats EquipmentCollection::GetEquipmentStats()
{
	EquipmentStats equipmentStats;

	for (map<ArmorType, Armor*>::iterator itor = armor.begin(); itor != armor.end(); itor++)
	{
		equipmentStats += itor->second->GetEquipmentStats();
	}

	return equipmentStats;
}

////////////////////////////////////////////////////////////////////////
