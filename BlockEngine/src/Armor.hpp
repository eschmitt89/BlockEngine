#ifndef Armor_hpp
#define Armor_hpp

#include "Equipment.hpp"
#include "ArmorType.hpp"

class Armor : public Equipment
{
public:
	Armor(ArmorType armorType, EquipmentQuality quality, EquipmentStats equipmentStats, int level, const sf::Texture* texture);
	Armor(const Armor& armor);
    virtual ~Armor();

	ArmorType GetArmorType();

protected:
	ArmorType armorType;
};

#endif /* Armor_hpp */
