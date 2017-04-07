#include "ArmorGenerator.hpp"

ArmorGenerator::ArmorGenerator()
{
	InitializeTextureNames();
}

////////////////////////////////////////////////////////////////////////

ArmorGenerator::~ArmorGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

Armor * ArmorGenerator::Generate(int level)
{
	ArmorType armorType = static_cast<ArmorType>(Random(1, ARMOR_TYPE_COUNT));

	EquipmentQuality equipmentQuality = GenerateEquipmentQuality(level);

	EquipmentStats equipmentStats = GenerateEquipmentStats(level, equipmentQuality);

	const sf::Texture* texture = GenerateArmorTexture(armorType, equipmentQuality);

	return new Armor(armorType, equipmentQuality, equipmentStats, level, texture);
}

////////////////////////////////////////////////////////////////////////

void ArmorGenerator::InitializeArmorTypeNames()
{
	armorTypeNames[ArmorType_Head] = "head";
	armorTypeNames[ArmorType_Chest] = "chest";
	armorTypeNames[ArmorType_Hands] = "hands";
	armorTypeNames[ArmorType_Waist] = "waist";
	armorTypeNames[ArmorType_Legs] = "legs";
	armorTypeNames[ArmorType_Feet] = "feet";
}

////////////////////////////////////////////////////////////////////////

void ArmorGenerator::InitializeTextureNames()
{
	InitializeArmorTypeNames();
	InitializeEquipmentQualityNames();

	ArmorType armorType;
	EquipmentQuality equipmentQuality;

	vector<string> textureNames = ResourceManager::GetInstance().GetTextureNames("armor");

	for (int i = 0; i < textureNames.size(); i++)
	{
		armorType = GetTypeFromString<ArmorType>(armorTypeNames, textureNames[i]);

		equipmentQuality = GetTypeFromString<EquipmentQuality>(equipmentQualityNames, textureNames[i]);

		armorTextureNames[armorType][equipmentQuality].push_back(textureNames[i]);
	}
}

////////////////////////////////////////////////////////////////////////

const sf::Texture * ArmorGenerator::GenerateArmorTexture(ArmorType armorType, EquipmentQuality equipmentQuality)
{
	if (armorTextureNames[armorType][equipmentQuality].size() == 0)
	{
		return nullptr;
	}

	return ResourceManager::GetInstance().GetTexture(armorTextureNames[armorType][equipmentQuality][Random(0, armorTextureNames[armorType][equipmentQuality].size() - 1)]);
}

////////////////////////////////////////////////////////////////////////
