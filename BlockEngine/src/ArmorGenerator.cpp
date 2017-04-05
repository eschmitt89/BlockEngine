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

	EquipmentRarity equipmentRarity = GenerateEquipmentRarity(level);

	EquipmentStats equipmentStats = GenerateEquipmentStats(level, equipmentRarity);

	const sf::Texture* texture = GenerateArmorTexture(armorType, equipmentRarity);

	return new Armor(armorType, equipmentRarity, equipmentStats, level, texture);
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
	InitializeEquipmentRarityNames();

	ArmorType armorType;
	EquipmentRarity equipmentRarity;

	vector<string> textureNames = ResourceManager::GetInstance().GetTextureNames("armor");

	for (int i = 0; i < textureNames.size(); i++)
	{
		armorType = GetTypeFromString<ArmorType>(armorTypeNames, textureNames[i]);

		equipmentRarity = GetTypeFromString<EquipmentRarity>(equipmentRarityNames, textureNames[i]);

		armorTextureNames[armorType][equipmentRarity].push_back(textureNames[i]);
	}
}

////////////////////////////////////////////////////////////////////////

const sf::Texture * ArmorGenerator::GenerateArmorTexture(ArmorType armorType, EquipmentRarity equipmentRarity)
{
	if (armorTextureNames[armorType][equipmentRarity].size() == 0)
	{
		return nullptr;
	}

	return ResourceManager::GetInstance().GetTexture(armorTextureNames[armorType][equipmentRarity][Random(0, armorTextureNames[armorType][equipmentRarity].size() - 1)]);
}

////////////////////////////////////////////////////////////////////////
