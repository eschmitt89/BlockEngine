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

class Item
{
public:
	Item(ItemType itemType, const sf::Texture* texture);
    virtual ~Item();

	ItemType GetItemType();
	const sf::Texture* GetTexture();

protected:
	ItemType itemType;
	const sf::Texture* texture;
};

#endif /* Item_hpp */
