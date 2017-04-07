//
//  EquipmentStats.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef EquipmentStats_hpp
#define EquipmentStats_hpp

struct EquipmentStats
{
	EquipmentStats() { EquipmentStats(0, 0, 0, 0, 0); }
	EquipmentStats(int health, int armor, int crit, int dodge, int power)
	{
		this->health = health;
		this->armor = armor;
		this->crit = crit;
		this->dodge = dodge;
		this->power = power;
	}
	void operator += (const EquipmentStats & equipmentStats)
	{
		this->health = equipmentStats.health;
		this->armor = equipmentStats.armor;
		this->crit = equipmentStats.crit;
		this->dodge = equipmentStats.dodge;
		this->power = equipmentStats.power;
	}

	int health;
	int armor;
	int crit;
	int dodge;
	int power;
};

#endif /* EquipmentStat_hpp */
