#ifndef EquipmentGenerator_hpp
#define EquipmentGenerator_hpp

#define EQUIPMENT_MAX_LEVEL 100
#define EQUIPMENT_SLOTS 8
#define EQUIPMENT_MAX_STAT_COUNT 5

#define MIN_GOOD_LEVEL 0
#define MIN_RARE_LEVEL 5
#define MIN_EPIC_LEVEL 10
#define MIN_LEGENDARY_LEVEL 15
#define MIN_ARTIFACT_LEVEL 20

#define MAX_HEALTH 10000
#define MAX_ARMOR 10000
#define MAX_CRIT 10000
#define MAX_DODGE 10000
#define MAX_POWER 10000

#include "Equipment.hpp"
#include "ResourceManager.hpp"

class EquipmentGenerator
{
public:
	EquipmentGenerator();
    virtual ~EquipmentGenerator();

protected:
	map<EquipmentRarity, string> equipmentRarityNames;
	DropRateCollection<EquipmentRarity> randomEquipmentRarity;

	virtual EquipmentStats GenerateEquipmentStats(int level, EquipmentRarity equipmentRarity);
	int GenerateEquipmentStatValue(int level, int maxValue);
	EquipmentRarity GenerateEquipmentRarity(int level);
	void InitializeEquipmentRarityNames();
};

#endif /* EquipmentGenerator_hpp */
