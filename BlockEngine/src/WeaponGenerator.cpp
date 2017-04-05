#include "WeaponGenerator.hpp"

WeaponGenerator::WeaponGenerator()
{

}

////////////////////////////////////////////////////////////////////////

WeaponGenerator::~WeaponGenerator()
{
    
}

////////////////////////////////////////////////////////////////////////

Weapon * WeaponGenerator::Generate(int level)
{
	WeaponType type = GetRandomWeaponType(level);
	WeaponSlot slot = GenerateWeaponSlot(type);
	WeaponSpeed speed = GenerateWeaponSpeed(type, slot);
	EquipmentRarity rarity = GenerateEquipmentRarity(level);
	EquipmentStats stats = GenerateEquipmentStats(level, rarity);
	int damage = GenerateWeaponDamage(level, speed, rarity);
	const sf::Texture* texture = GenerateWeaponTexture(type, slot, rarity);
	
	return new Weapon(type, slot, speed, rarity, stats, level, damage, texture);
}

////////////////////////////////////////////////////////////////////////

WeaponType WeaponGenerator::GetRandomWeaponType(int level)
{
	return static_cast<WeaponType>(Random(1, WEAPON_TYPE_COUNT));
}

////////////////////////////////////////////////////////////////////////

WeaponSlot WeaponGenerator::GenerateWeaponSlot(WeaponType weaponType)
{
	if (weaponType == WeaponType_Dagger || weaponType == WeaponType_Wand)
	{
		return WeaponSlot_OneHand;
	}
	else if (weaponType == WeaponType_Sword || weaponType == WeaponType_Axe || weaponType == WeaponType_Mace)
	{
		return (Random(1, 3) > 1) ? WeaponSlot_OneHand : WeaponSlot_TwoHand;
	}
	else if (weaponType == WeaponType_Staff)
	{
		return WeaponSlot_TwoHand;
	}
	else if (weaponType == WeaponType_Orb || weaponType == WeaponType_Shield)
	{
		return WeaponSlot_OffHand;
	}
	else
	{
		return WeaponSlot_OneHand;
	}
}

////////////////////////////////////////////////////////////////////////

WeaponSpeed WeaponGenerator::GenerateWeaponSpeed(WeaponType weaponType, WeaponSlot weaponSlot)
{
	switch (weaponSlot)
	{
	case WeaponSlot_OneHand:
		if (weaponType == WeaponType_Dagger || weaponType == WeaponType_Wand)
		{
			return WeaponSpeed_Fast;
		}
		else
		{
			return WeaponSpeed_Medium;
		}
	case WeaponSlot_TwoHand:
		return WeaponSpeed_Slow;
	case WeaponSlot_OffHand:
		return WeaponSpeed_None;
	default:
		return WeaponSpeed_None;
	}
}

////////////////////////////////////////////////////////////////////////

int WeaponGenerator::GenerateWeaponDamage(int level, WeaponSpeed speed, EquipmentRarity equipmentRarity)
{
	switch (speed)
	{
	case WeaponSpeed_None:
		return 0;
	case WeaponSpeed_Fast:
		return level;
	case WeaponSpeed_Medium:
		return level * 2;
	case WeaponSpeed_Slow:
		return level * 3;
	default:
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////

void WeaponGenerator::InitializeWeaponTypeNames()
{
	weaponTypeNames[WeaponType_Dagger] = "dagger";
	weaponTypeNames[WeaponType_Sword] = "sword";
	weaponTypeNames[WeaponType_Axe] = "axe";
	weaponTypeNames[WeaponType_Mace] = "mace";
	weaponTypeNames[WeaponType_Wand] = "wand";
	weaponTypeNames[WeaponType_Staff] = "staff";
	weaponTypeNames[WeaponType_Orb] = "orb";
	weaponTypeNames[WeaponType_Shield] = "shield";
}

////////////////////////////////////////////////////////////////////////

void WeaponGenerator::InitializeWeaponSlotNames()
{
	weaponSlotNames[WeaponSlot_OneHand] = "1H";
	weaponSlotNames[WeaponSlot_TwoHand] = "2H";
	weaponSlotNames[WeaponSlot_OffHand] = "oH";
}

////////////////////////////////////////////////////////////////////////

void WeaponGenerator::InitializeTextureNames()
{
	InitializeWeaponTypeNames();
	InitializeWeaponSlotNames();

	WeaponType weaponType;
	WeaponSlot weaponSlot;
	EquipmentRarity equipmentRarity;

	vector<string> textureNames = ResourceManager::GetInstance().GetTextureNames("weapon");

	for (int i = 0; i < textureNames.size(); i++)
	{
		weaponType = GetTypeFromString<WeaponType>(weaponTypeNames, textureNames[i]);

		weaponSlot = GetTypeFromString<WeaponSlot>(weaponSlotNames, textureNames[i]);

		equipmentRarity = GetTypeFromString<EquipmentRarity>(equipmentRarityNames, textureNames[i]);

		weaponTextureNames[weaponType][weaponSlot][equipmentRarity].push_back(textureNames[i]);
	}
}

////////////////////////////////////////////////////////////////////////

const sf::Texture * WeaponGenerator::GenerateWeaponTexture(WeaponType weaponType, WeaponSlot weaponSlot, EquipmentRarity equipmentRarity)
{
	if (weaponTextureNames[weaponType][weaponSlot][equipmentRarity].size() == 0)
	{
		return nullptr;
	}

	return ResourceManager::GetInstance().GetTexture(weaponTextureNames[weaponType][weaponSlot][equipmentRarity][Random(0, weaponTextureNames[weaponType][weaponSlot][equipmentRarity].size() - 1)]);
}

////////////////////////////////////////////////////////////////////////