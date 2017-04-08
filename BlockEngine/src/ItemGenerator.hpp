#ifndef ItemGenerator_hpp
#define ItemGenerator_hpp

#include "ArmorGenerator.hpp"
#include "WeaponGenerator.hpp"
#include "PotionGenerator.hpp"
#include "ScrollGenerator.hpp"
#include "GemGenerator.hpp"
#include "CoinGenerator.hpp"
#include "ItemPhysicsObject.hpp"

class ItemGenerator
{
public:
	ItemGenerator();
    virtual ~ItemGenerator();

	Item* Generate(int level);
	Armor* GenerateArmor(int level);
	Weapon* GenerateWeapon(int level);
	Potion* GeneratePotion(int level);
	Scroll* GenerateScroll(int level);
	Gem* GenerateGem(int level);
	Coin* GenerateCoin(int value);

	PhysicsObject* Generate(int level, sf::Vector2f position);
	vector<PhysicsObject*> GenerateLoot(int level, sf::Vector2f position);

private:
	DropRateCollection<ItemType> randomItemType;
	DropRateCollection<EquipmentType> randomEquipmentType;

	ArmorGenerator armorGenerator;
	WeaponGenerator weaponGenerator;
	PotionGenerator potionGenerator;
	ScrollGenerator scrollGenerator;
	GemGenerator gemGenerator;
	CoinGenerator coinGenerator;

	Equipment* GenerateEquipment(int level);
};

#endif /* ItemGenerator_hpp */
