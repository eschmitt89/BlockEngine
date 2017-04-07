#include "Equipment.hpp"

Equipment::Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level, const sf::Texture* texture)
	:Item(ItemType_Equipment, texture)
{
	this->equipmentType = equipmentType;
	this->equipmentRarity = equipmentRarity;
	this->equipmentStats = equipmentStats;
	this->level = level;
}

Equipment::Equipment(const Equipment & equipment)
	:Item(equipment.itemType, equipment.texture)
{
	this->equipmentType = equipment.equipmentType;
	this->equipmentRarity = equipment.equipmentRarity;
	this->equipmentStats = equipment.equipmentStats;
	this->level = equipment.level;
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