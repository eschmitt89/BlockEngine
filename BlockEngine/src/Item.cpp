//
//  Item.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Item.hpp"

Item::Item(ItemType itemType)
{
	this->itemType = itemType;
}

////////////////////////////////////////////////////////////////////////

Item::~Item()
{
    
}

////////////////////////////////////////////////////////////////////////

ItemType Item::GetItemType()
{
	return itemType;
}

////////////////////////////////////////////////////////////////////////

