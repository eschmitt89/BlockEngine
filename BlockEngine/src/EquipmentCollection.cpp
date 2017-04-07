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
	}
}

////////////////////////////////////////////////////////////////////////
