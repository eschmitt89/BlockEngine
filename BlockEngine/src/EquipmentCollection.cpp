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
		this->armor[armor->GetArmorType()] = new Armor(*armor);
	}
	else if (equipment->GetEquipmentType() == EquipmentType_Weapon)
	{
		Weapon* weapon = (Weapon*)equipment;
		if (weapon->GetWeaponSlot() == WeaponSlot_TwoHand)
		{
			mainHandWeapon = new Weapon(*weapon);
		}
		else if(weapon->GetWeaponSlot() == WeaponSlot_OffHand)
		{
			offHandWeapon = new Weapon(*weapon);
		}
		else if (weapon->GetWeaponSlot() == WeaponSlot_OneHand)
		{
			if (!mainHandWeapon || (mainHandWeapon && offHandWeapon))
			{
				mainHandWeapon = new Weapon(*weapon);
			}
			else if (!offHandWeapon)
			{
				offHandWeapon = new Weapon(*weapon);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

EquipmentStats EquipmentCollection::GetEquipmentStats()
{
	EquipmentStats equipmentStats = EquipmentStats();

	for (map<ArmorType, Armor*>::iterator itor = armor.begin(); itor != armor.end(); itor++)
	{
		equipmentStats += (*itor).second->GetEquipmentStats();
	}

	if (mainHandWeapon)
	{
		equipmentStats += mainHandWeapon->GetEquipmentStats();
	}
	if (offHandWeapon)
	{
		equipmentStats += offHandWeapon->GetEquipmentStats();
	}

	return equipmentStats;
}

////////////////////////////////////////////////////////////////////////
