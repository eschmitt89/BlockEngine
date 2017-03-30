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
	this->currentDuration = 0;
	this->totalDuration = duration;

	ColorKeyframes[0] = sf::Color::White;
	ColorKeyframes[1] = sf::Color::Red;
}

////////////////////////////////////////////////////////////////////////

Particle::~Particle()
{
    
}

////////////////////////////////////////////////////////////////////////

void Particle::Update(float dt)
{
	PhysicsObject::Update(dt);

	currentDuration += dt;

	float durationPercent = currentDuration / totalDuration;

	sprite.setFillColor(GetCurrentColor(durationPercent));
	sprite.setSize(GetCurrentSize(durationPercent));

	if (currentDuration >= totalDuration)
	{
		expired = true;
	}
}

sf::Color Particle::GetCurrentColor(float durationPercent)
{
	//for (int i = 0; i < )
	return sf::Color();
}

sf::Vector2f Particle::GetCurrentSize(float durationPercent)
{
	return sf::Vector2f();
}
