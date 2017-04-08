#include "Equipment.hpp"

Equipment::Equipment(EquipmentType equipmentType, EquipmentQuality equipmentQuality, EquipmentStats equipmentStats, int level, const sf::Texture* texture)
	:Item(ItemType_Equipment, texture)
{
	this->equipmentType = equipmentType;
	this->equipmentQuality = equipmentQuality;
	this->equipmentStats = equipmentStats;
	this->level = level;
}

////////////////////////////////////////////////////////////////////////

Equipment::Equipment(const Equipment & equipment)
	:Item(equipment.itemType, equipment.texture)
{
	this->equipmentType = equipment.equipmentType;
	this->equipmentQuality = equipment.equipmentQuality;
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

EquipmentQuality Equipment::GetEquipmentQuality()
{
	return equipmentQuality;
}

////////////////////////////////////////////////////////////////////////

EquipmentStats Equipment::GetEquipmentStats()
{
	return equipmentStats;
}

int Equipment::GetLevel()
{
	return level;
}

////////////////////////////////////////////////////////////////////////