#include "Weapon.hpp"

Weapon::Weapon(WeaponType weaponType, WeaponSlot weaponSlot, WeaponSpeed speed, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level, int damage, const sf::Texture* texture)
	:Equipment(EquipmentType_Weapon, equipmentRarity, equipmentStats, level, texture)
{
	this->weaponType = weaponType;
	this->weaponSlot = weaponSlot;
	this->speed = speed;
	this->damage = damage;
}

////////////////////////////////////////////////////////////////////////

Weapon::Weapon(const Weapon & weapon)
	:Equipment(weapon.equipmentType, weapon.equipmentRarity, weapon.equipmentStats, weapon.level, weapon.texture)
{
	this->weaponType = weapon.weaponType;
	this->weaponSlot = weapon.weaponSlot;
	this->speed = weapon.speed;
	this->damage = weapon.damage;
}

////////////////////////////////////////////////////////////////////////

Weapon::~Weapon()
{

}

//////////////////////////////////////////////////////////////////////////

