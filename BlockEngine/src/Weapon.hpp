#ifndef Weapon_hpp
#define Weapon_hpp

#define SPEED_NONE 0.0
#define SPEED_FAST 1.0
#define SPEED_MEDIUM 2.0
#define SPEED_SLOW 3.0

#include "Equipment.hpp"
#include "WeaponType.hpp"
#include "WeaponSlot.hpp"
#include "WeaponSpeed.hpp"

class Weapon : public Equipment
{
public:
	Weapon(WeaponType weaponType, WeaponSlot weaponSlot, WeaponSpeed speed, EquipmentQuality equipmentQuality, EquipmentStats equipmentStats, int level, int damage, const sf::Texture* texture);
	Weapon(const Weapon& weapon);
    virtual ~Weapon();

	WeaponSlot GetWeaponSlot();

protected:
	WeaponType weaponType;
	WeaponSlot weaponSlot;
	WeaponSpeed speed;
	int damage;
};

#endif /* Weapon_hpp */
