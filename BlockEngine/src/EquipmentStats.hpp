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

	int health;
	int armor;
	int crit;
	int dodge;
	int power;
};

#endif /* EquipmentStat_hpp */
