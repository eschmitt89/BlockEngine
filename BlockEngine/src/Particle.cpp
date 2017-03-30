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
	
	AddColorKeyframe(0.0, sf::Color::White);
	AddColorKeyframe(0.25, sf::Color::Red);
	AddColorKeyframe(0.5, sf::Color::Green);
	AddColorKeyframe(0.75, sf::Color::Blue);
	AddColorKeyframe(1.0, sf::Color::Black);
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

	sprite.setFillColor(ComputeColor(durationPercent));

	if (currentDuration >= totalDuration)
	{
		expired = true;
	}
}

////////////////////////////////////////////////////////////////////////

void Particle::AddColorKeyframe(float durationPercent, sf::Color color)
{
	colorKeyframes.push_back(Keyframe<sf::Color>(durationPercent, color));
}

////////////////////////////////////////////////////////////////////////

sf::Color Particle::ComputeColor(float durationPercent)
{
	Keyframe<sf::Color> startColor = Keyframe<sf::Color>(0, sf::Color::White);
	Keyframe<sf::Color> endColor = Keyframe<sf::Color>(1, sf::Color::White);

	for (int i = colorKeyframes.size() - 1; i >= 0; i--)
	{
		if (colorKeyframes[i].key <= durationPercent)
		{
			startColor = colorKeyframes[i];
			if (i < colorKeyframes.size() - 1)
			{
				endColor = colorKeyframes[i + 1];
			}
			break;
		}
	}

	float transitionPercent = (durationPercent - startColor.key) / (endColor.key - startColor.key);

	int red = startColor.value.r + (transitionPercent * (endColor.value.r - startColor.value.r));
	int green = startColor.value.g + (transitionPercent * (endColor.value.g - startColor.value.g));
	int blue = startColor.value.b + (transitionPercent * (endColor.value.b - startColor.value.b));
	int alpha = startColor.value.a + (transitionPercent * (endColor.value.a - startColor.value.a));

	return sf::Color(red, green, blue, alpha);
}
