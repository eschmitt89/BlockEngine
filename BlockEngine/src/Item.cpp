//
//  Item.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Item.hpp"

Item::Item(ItemType itemType, const sf::Texture* texture)
{
	this->itemType = itemType;
	this->texture = texture;
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

const sf::Texture * Item::GetTexture()
{
	return texture;
}

////////////////////////////////////////////////////////////////////////

