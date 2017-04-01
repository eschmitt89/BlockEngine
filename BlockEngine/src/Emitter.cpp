//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Emitter.hpp"

Emitter::Emitter(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration)
	:Particle(texture, position, size, duration)
{

}

////////////////////////////////////////////////////////////////////////

Emitter::~Emitter()
{
    
}

////////////////////////////////////////////////////////////////////////

void Emitter::Update(float dt)
{
	PhysicsObject::Update(dt);

	duration -= dt;

	if (duration <= 0)
	{
		expired = true;
	}
}

////////////////////////////////////////////////////////////////////////
