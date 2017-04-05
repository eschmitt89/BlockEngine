//
//  ArmorGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef ArmorGenerator_hpp
#define ArmorGenerator_hpp

#include "EquipmentGenerator.hpp"
#include "Armor.hpp"
#include <map>

class ArmorGenerator : public EquipmentGenerator
{
public:
	ArmorGenerator();
    ~ArmorGenerator();

	Armor* Generate(int level);
	
private:
	map<ArmorType, string> armorTypeNames;
	map<EquipmentRarity, string> equipmentRarityNames;
	map<ArmorType, map<EquipmentRarity, vector<string>>> textureNames;

	void InitializeArmorTypeNames();
	void InitializeEquipmentRarityNames();
	void InitializeTextureNames();

	const sf::Texture* GetArmorTexture(ArmorType armorType, EquipmentRarity equipmentRarity);
};

#endif /* ArmorGenerator_hpp */
