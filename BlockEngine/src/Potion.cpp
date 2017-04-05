//
//  Potion.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Potion.hpp"

Potion::Potion(const sf::Texture* texture)
	:Item(ItemType_Potion, texture)
{

}

////////////////////////////////////////////////////////////////////////

Potion::~Potion()
{
    
}

////////////////////////////////////////////////////////////////////////