//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Particle.hpp"

Particle::Particle(const sf::Texture* texture, sf::Color color, sf::Vector2f position, sf::Vector2f size, float duration)
	:PhysicsObject(texture, position, size)
{
	sprite.setFillColor(color);

	this->remainingDuration = duration;

	velocity = sf::Vector2f(Random(-100, 100), Random(-100, 100));
}

////////////////////////////////////////////////////////////////////////

Particle::~Particle()
{
    
}

////////////////////////////////////////////////////////////////////////

void Particle::Update(float dt)
{
	PhysicsObject::Update(dt);

	remainingDuration -= dt;

	if (remainingDuration <= 0)
	{
		expired = true;
	}
}

////////////////////////////////////////////////////////////////////////
