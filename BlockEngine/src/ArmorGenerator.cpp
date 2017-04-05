//
//  ArmorGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

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

	const sf::Texture* texture = GetArmorTexture(armorType, equipmentRarity);

	return new Armor(armorType, equipmentRarity, equipmentStats, level, texture);
}

////////////////////////////////////////////////////////////////////////

const sf::Texture * ArmorGenerator::GetArmorTexture(ArmorType armorType, EquipmentRarity equipmentRarity)
{
	if (textureNames[armorType][equipmentRarity].size() > 0)
	{
		return ResourceManager::GetInstance().GetTexture(textureNames[armorType][equipmentRarity][Random(0, textureNames[armorType][equipmentRarity].size() - 1)]);
	}
	return nullptr;
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

void ArmorGenerator::InitializeEquipmentRarityNames()
{
	equipmentRarityNames[EquipmentRarity_Common] = "common";
	equipmentRarityNames[EquipmentRarity_Good] = "good";
	equipmentRarityNames[EquipmentRarity_Rare] = "rare";
	equipmentRarityNames[EquipmentRarity_Epic] = "epic";
	equipmentRarityNames[EquipmentRarity_Legendary] = "legendary";
	equipmentRarityNames[EquipmentRarity_Artifact] = "artifact";
}

////////////////////////////////////////////////////////////////////////

void ArmorGenerator::InitializeTextureNames()
{
	InitializeArmorTypeNames();
	InitializeEquipmentRarityNames();

	ArmorType armorType;
	EquipmentRarity equipmentRarity;

	vector<string> textures = ResourceManager::GetInstance().GetTextureNames("armor");

	for (int i = 0; i < textures.size(); i++)
	{
		for (map<ArmorType, string>::iterator armorTypeItor = armorTypeNames.begin(); armorTypeItor != armorTypeNames.end(); armorTypeItor++)
		{
			if (StringContains(textures[i], armorTypeItor->second))
			{
				armorType = armorTypeItor->first;
				break;
			}
		}

		for (map<EquipmentRarity, string>::iterator equipmentRarityItor = equipmentRarityNames.begin(); equipmentRarityItor != equipmentRarityNames.end(); equipmentRarityItor++)
		{
			if (StringContains(textures[i], equipmentRarityItor->second))
			{
				equipmentRarity = equipmentRarityItor->first;
				break;
			}
		}

		textureNames[armorType][equipmentRarity].push_back(textures[i]);
	}
}

////////////////////////////////////////////////////////////////////////
