#ifndef LootGenerator_hpp
#define LootGenerator_hpp

#include "ItemGenerator.hpp"
#include "GoldCoin.hpp"

class LootGenerator
{
public:
	LootGenerator();
    virtual ~LootGenerator();

	/*Item* Generate(int level);
	Armor* GenerateArmor(int levelWeapon
	* GenerateWeapon(int level);
	Item* GeneratePotion(int level);
	Item* GenerateScroll(int level);
	Item* GenerateGem(int level);*/

private:
	//DropRateCollection<ItemType> randomItemType;
	//DropRateCollection<EquipmentType> randomEquipmentType;

	//ArmorGenerator armorGenerator;
	//WeaponGenerator weaponGenerator;
	//PotionGenerator potionGenerator;
	//ScrollGenerator scrollGenerator;
	//GemGenerator gemGenerator;

	//Equipment* GenerateEquipment(int level);
};

#endif /* LootGenerator_hpp */
