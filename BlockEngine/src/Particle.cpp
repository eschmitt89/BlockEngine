//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Particle.hpp"

Particle::Particle(sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(position, size)
{

}

////////////////////////////////////////////////////////////////////////

Particle::Particle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(texture, position, size)
{

}

////////////////////////////////////////////////////////////////////////

Particle::~Particle()
{
    
}