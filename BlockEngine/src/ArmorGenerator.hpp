#ifndef ArmorGenerator_hpp
#define ArmorGenerator_hpp

#include "EquipmentGenerator.hpp"
#include "Armor.hpp"

class ArmorGenerator : public EquipmentGenerator
{
public:
	ArmorGenerator();
    ~ArmorGenerator();

	Armor* Generate(int level);
	
private:
	map<ArmorType, string> armorTypeNames;
	map<ArmorType, map<EquipmentRarity, vector<string>>> armorTextureNames;

	void InitializeArmorTypeNames();
	void InitializeTextureNames();

	const sf::Texture* GenerateArmorTexture(ArmorType armorType, EquipmentRarity equipmentRarity);
};

#endif /* ArmorGenerator_hpp */