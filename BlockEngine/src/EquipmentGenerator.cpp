#include "EquipmentGenerator.hpp"

EquipmentGenerator::EquipmentGenerator()
{
	randomEquipmentQuality = DropRateCollection<EquipmentQuality>();
	randomEquipmentQuality.AddDropRate(EquipmentQuality_Common, 0.489);
	randomEquipmentQuality.AddDropRate(EquipmentQuality_Good, 0.30);
	randomEquipmentQuality.AddDropRate(EquipmentQuality_Rare, 0.15);
	randomEquipmentQuality.AddDropRate(EquipmentQuality_Epic, 0.05);
	randomEquipmentQuality.AddDropRate(EquipmentQuality_Legendary, 0.01);
	randomEquipmentQuality.AddDropRate(EquipmentQuality_Artifact, 0.001);
}

////////////////////////////////////////////////////////////////////////

EquipmentGenerator::~EquipmentGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

EquipmentStats EquipmentGenerator::GenerateEquipmentStats(int level, EquipmentQuality equipmentQuality)
{
	EquipmentStats equipmentStats = EquipmentStats(0, 0, 0, 0, 0);

	for (int i = 0; i < equipmentQuality; i++)
	{
		EquipmentStat stat = static_cast<EquipmentStat>(Random(1, EQUIPMENT_STAT_COUNT));

		switch (stat)
		{
		case EquipmentStat_Health:
			equipmentStats.health += GenerateEquipmentStatValue(level, MAX_HEALTH);
			break;
		case EquipmentStat_Armor:
			equipmentStats.armor += GenerateEquipmentStatValue(level, MAX_ARMOR);
			break;
		case EquipmentStat_Crit:
			equipmentStats.crit += GenerateEquipmentStatValue(level, MAX_CRIT);
			break;
		case EquipmentStat_Dodge:
			equipmentStats.dodge += GenerateEquipmentStatValue(level, MAX_DODGE);
			break;
		case EquipmentStat_Power:
			equipmentStats.power += GenerateEquipmentStatValue(level, MAX_POWER);
			break;
		default:
			break;
		}
	}

	return equipmentStats;
}

////////////////////////////////////////////////////////////////////////

int EquipmentGenerator::GenerateEquipmentStatValue(int level, int maxValue)
{
	return ((float)level / EQUIPMENT_MAX_LEVEL) * (maxValue / EQUIPMENT_SLOTS / EQUIPMENT_MAX_STAT_COUNT);
}

////////////////////////////////////////////////////////////////////////

EquipmentQuality EquipmentGenerator::GenerateEquipmentQuality(int level)
{
	EquipmentQuality equipmentQuality = randomEquipmentQuality.Roll();

	if (equipmentQuality == EquipmentQuality_Artifact && level < MIN_ARTIFACT_LEVEL)
	{
		equipmentQuality = EquipmentQuality_Legendary;
	}
	if (equipmentQuality == EquipmentQuality_Legendary && level < MIN_LEGENDARY_LEVEL)
	{
		equipmentQuality = EquipmentQuality_Epic;
	}
	if (equipmentQuality == EquipmentQuality_Epic && level < MIN_EPIC_LEVEL)
	{
		equipmentQuality = EquipmentQuality_Rare;
	}
	if (equipmentQuality == EquipmentQuality_Rare && level < MIN_RARE_LEVEL)
	{
		equipmentQuality = EquipmentQuality_Good;
	}
	if (equipmentQuality == EquipmentQuality_Good && level < MIN_GOOD_LEVEL)
	{
		equipmentQuality = EquipmentQuality_Common;
	}

	return equipmentQuality;
}

////////////////////////////////////////////////////////////////////////

void EquipmentGenerator::InitializeEquipmentQualityNames()
{
	equipmentQualityNames[EquipmentQuality_Common] = "common";
	equipmentQualityNames[EquipmentQuality_Good] = "good";
	equipmentQualityNames[EquipmentQuality_Rare] = "rare";
	equipmentQualityNames[EquipmentQuality_Epic] = "epic";
	equipmentQualityNames[EquipmentQuality_Legendary] = "legendary";
	equipmentQualityNames[EquipmentQuality_Artifact] = "artifact";
}

////////////////////////////////////////////////////////////////////////
