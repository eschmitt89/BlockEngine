#ifndef Equipment_hpp
#define Equipment_hpp

#include "Item.hpp"
#include "EquipmentStat.hpp"
#include "EquipmentStats.hpp"
#include "EquipmentType.hpp"
#include "EquipmentQuality.hpp"

class Equipment : public Item
{
public:
	Equipment(EquipmentType equipmentType, EquipmentQuality equipmentQuality, EquipmentStats equipmentStats, int level, const sf::Texture* texture);
	Equipment(const Equipment& equipment);
    virtual ~Equipment();

	EquipmentType GetEquipmentType();
	EquipmentQuality GetEquipmentQuality();
	EquipmentStats GetEquipmentStats();

	int GetLevel();

protected:
	EquipmentType equipmentType;
	EquipmentQuality equipmentQuality;
	EquipmentStats equipmentStats;
	
	int level;
};

#endif /* Equipment_hpp */
