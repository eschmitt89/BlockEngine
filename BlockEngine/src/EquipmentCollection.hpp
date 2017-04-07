#ifndef EquipmentCollection_hpp
#define EquipmentCollection_hpp

#include "Armor.hpp"
#include "Weapon.hpp"

class EquipmentCollection
{
public:
	EquipmentCollection();
    ~EquipmentCollection();

	void Equip(Equipment* equipment);

	EquipmentStats GetEquipmentStats();

private:
	map<ArmorType, Armor*> armor;

	Weapon* mainHandWeapon;
	Weapon* offHandWeapon;
};

#endif /* EquipmentCollection_hpp */
