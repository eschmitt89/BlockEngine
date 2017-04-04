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

class ArmorGenerator : public EquipmentGenerator
{
public:
	ArmorGenerator();
    ~ArmorGenerator();

	Armor* Generate(int level);
	
private:

};

#endif /* ArmorGenerator_hpp */
