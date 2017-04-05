#include "Equipment.hpp"

Equipment::Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level, const sf::Texture* texture)
	:Item(ItemType_Equipment, texture)
{
	this->equipmentType = equipmentType;
	this->equipmentRarity = equipmentRarity;
	this->equipmentStats = equipmentStats;
	this->level = level;
}

////////////////////////////////////////////////////////////////////////

Equipment::~Equipment()
{
    
}

////////////////////////////////////////////////////////////////////////

EquipmentType Equipment::GetEquipmentType()
{
	return equipmentType;
}

////////////////////////////////////////////////////////////////////////

EquipmentRarity Equipment::GetEquipmentRarity()
{
	return equipmentRarity;
}

////////////////////////////////////////////////////////////////////////

EquipmentStats Equipment::GetEquipmentStats()
{
	return equipmentStats;
}

////////////////////////////////////////////////////////////////////////