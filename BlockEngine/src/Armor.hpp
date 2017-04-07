#ifndef Armor_hpp
#define Armor_hpp

#include "Equipment.hpp"
#include "ArmorType.hpp"

class Armor : public Equipment
{
public:
	Armor(ArmorType armorType, EquipmentRarity rarity, EquipmentStats equipmentStats, int level, const sf::Texture* texture);
	Armor(const Armor& armor);
    virtual ~Armor();

protected:
	ArmorType armorType;
};

#endif /* Armor_hpp */
