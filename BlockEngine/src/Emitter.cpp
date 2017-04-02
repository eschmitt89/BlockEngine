//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Emitter.hpp"
#include "TransitionParticle.hpp"

Emitter::Emitter(Particle* particle, sf::Vector2f position, sf::Vector2f size, float duration)
	:Particle(nullptr, position, size, duration)
{
	velocity = sf::Vector2f(500, 0);
	this->particle = particle;
	particlesPerMinute = 10000;
	spawnTimer = 0;
}

////////////////////////////////////////////////////////////////////////

Emitter::~Emitter()
{
	delete particle;
}

////////////////////////////////////////////////////////////////////////

void Emitter::Update(float dt)
{
	Particle::Update(dt);

	spawnTimer -= dt;

	if (spawnTimer <= 0)
	{
		spawnedPhysicsObjects.push_back(new TransitionParticle(position, size, 0.6));
		spawnTimer = 60 / (float)particlesPerMinute;
	}
}

////////////////////////////////////////////////////////////////////////

void Emitter::Draw(sf::RenderWindow & window)
{
	
}

////////////////////////////////////////////////////////////////////////
