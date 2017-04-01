//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Particle.hpp"

Particle::Particle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration)
	:PhysicsObject(texture, position, size)
{
	this->duration = duration;

	velocity = sf::Vector2f(Random(-20, 20), Random(-50, -100));
	acceleration = sf::Vector2f();
}

////////////////////////////////////////////////////////////////////////

Particle::~Particle()
{
    
}

////////////////////////////////////////////////////////////////////////

void Particle::Update(float dt)
{
	PhysicsObject::Update(dt);

	duration -= dt;

	if (duration <= 0)
	{
		expired = true;
	}
}

////////////////////////////////////////////////////////////////////////
