//
//  ItemGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "ItemGenerator.hpp"

#define ITEM_TYPES 4

ItemGenerator::ItemGenerator()
{

}

////////////////////////////////////////////////////////////////////////

ItemGenerator::~ItemGenerator()
{
    
}

Item * ItemGenerator::Generate()
{
	int roll = Random(1, 100);

	if (roll < 50) // Equipment - 50%
	{
		
	}
	else if (roll < 66) // Potion - 16%
	{

	}
	else if (roll < 83) // Scroll - 16%
	{

	}
	else // Gem - 16%
	{

	}

	return nullptr;
}

////////////////////////////////////////////////////////////////////////

