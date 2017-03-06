//
//  PhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size)
	: Object(texture, position, size)
{

}

////////////////////////////////////////////////////////////////////////

PhysicsObject::~PhysicsObject()
{
    
}