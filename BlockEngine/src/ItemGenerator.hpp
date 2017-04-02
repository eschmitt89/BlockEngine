//
//  ItemGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef ItemGenerator_hpp
#define ItemGenerator_hpp

#include "Armor.hpp"

class ItemGenerator
{
public:
	ItemGenerator();
    virtual ~ItemGenerator();

	static Item* Generate();

};

#endif /* ItemGenerator_hpp */
