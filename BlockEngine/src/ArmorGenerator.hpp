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
	map<ArmorType, map<EquipmentQuality, vector<string>>> armorTextureNames;

	void InitializeArmorTypeNames();
	void InitializeTextureNames();

	const sf::Texture* GenerateArmorTexture(ArmorType armorType, EquipmentQuality equipmentQuality);
};

#endif /* ArmorGenerator_hpp */