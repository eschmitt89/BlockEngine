//
//  Item.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include "SFML/Window.hpp"
#include "ItemType.hpp"
#include "Utilities.hpp"
#include "ResourceManager.hpp"

class Item
{
public:
	Item(ItemType itemType);
    virtual ~Item();

	ItemType GetItemType();

protected:
	ItemType itemType;
	sf::RectangleShape sprite;
};

#endif /* Item_hpp */
