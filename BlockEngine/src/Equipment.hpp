#ifndef Equipment_hpp
#define Equipment_hpp

#include "Item.hpp"
#include "EquipmentStat.hpp"
#include "EquipmentStats.hpp"
#include "EquipmentType.hpp"
#include "EquipmentRarity.hpp"

class Equipment : public Item
{
public:
	Equipment(EquipmentType equipmentType, EquipmentRarity equipmentRarity, EquipmentStats equipmentStats, int level, const sf::Texture* texture);
	Equipment(const Equipment& equipment);
    virtual ~Equipment();

	EquipmentType GetEquipmentType();
	EquipmentRarity GetEquipmentRarity();
	EquipmentStats GetEquipmentStats();

protected:
	EquipmentType equipmentType;
	EquipmentRarity equipmentRarity;
	EquipmentStats equipmentStats;
	
	int level;
};

#endif /* Equipment_hpp */
