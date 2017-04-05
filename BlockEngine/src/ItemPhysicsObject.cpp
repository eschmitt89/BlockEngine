//
//  ItemPhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "ItemPhysicsObject.hpp"

ItemPhysicsObject::ItemPhysicsObject(Item* item, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(item->GetTexture(), position, size)
{
	velocity = sf::Vector2f(Random(-100, 100), Random(-100, 100));
}

////////////////////////////////////////////////////////////////////////

ItemPhysicsObject::~ItemPhysicsObject()
{
    
}

