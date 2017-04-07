#include "Armor.hpp"

Armor::Armor(ArmorType armorType, EquipmentQuality equipmentQuality, EquipmentStats equipmentStats, int level, const sf::Texture* texture)
	:Equipment(EquipmentType_Armor, equipmentQuality, equipmentStats, level, texture)
{
	this->armorType = armorType;
}

////////////////////////////////////////////////////////////////////////

Armor::Armor(const Armor & armor)
	: Equipment(armor.equipmentType, armor.equipmentQuality, armor.equipmentStats, armor.level, armor.texture)
{
	this->armorType = armor.armorType;
}

////////////////////////////////////////////////////////////////////////

Armor::~Armor()
{

}

ArmorType Armor::GetArmorType()
{
	return armorType;
}

////////////////////////////////////////////////////////////////////////

