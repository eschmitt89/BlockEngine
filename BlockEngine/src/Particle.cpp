//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Particle.hpp"
#include "Utilities.hpp"

Particle::Particle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration)
	:PhysicsObject(texture, position, size)
{
	this->currentDuration = 0;
	this->totalDuration = duration;

	velocity = sf::Vector2f(Random(-20, 20), Random(-10, -50));
	acceleration = sf::Vector2f();
	
	AddColorKeyframe(0.0, sf::Color::White);
	AddColorKeyframe(0.25, sf::Color(255, 255, 0, 255)); // Yellow
	AddColorKeyframe(0.5, sf::Color(255, 127, 0, 255)); // Orange
	AddColorKeyframe(0.75, sf::Color(255, 0, 0, 255)); // Red
	AddColorKeyframe(1.0, sf::Color(0, 0, 0, 0)); // Black
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
	SetSize(ComputeSize(durationPercent));

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

void Particle::AddSizeKeyframe(float durationPercent, sf::Vector2f size)
{
	sizeKeyframes.push_back(Keyframe<sf::Vector2f>(durationPercent, size));
}

////////////////////////////////////////////////////////////////////////

sf::Color Particle::ComputeColor(float durationPercent)
{
	Keyframe<sf::Color> startColor = Keyframe<sf::Color>(0, sf::Color::White);
	Keyframe<sf::Color> endColor = Keyframe<sf::Color>(1, sf::Color::White);

	for (int i = 0 ; i < colorKeyframes.size(); i++)
	{
		if (colorKeyframes[i].key >= durationPercent)
		{
			endColor = colorKeyframes[i];
			if (i > 0)
			{
				startColor = colorKeyframes[i - 1];
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

////////////////////////////////////////////////////////////////////////

sf::Vector2f Particle::ComputeSize(float durationPercent)
{
	Keyframe<sf::Vector2f> startSize = Keyframe<sf::Vector2f>(0, size);
	Keyframe<sf::Vector2f> endSize = Keyframe<sf::Vector2f>(1, size);

	for (int i = 0; i < sizeKeyframes.size(); i++)
	{
		if (sizeKeyframes[i].key >= durationPercent)
		{
			endSize = sizeKeyframes[i];
			if (i > 0)
			{
				startSize = sizeKeyframes[i - 1];
			}
			break;
		}
	}

	float transitionPercent = (durationPercent - startSize.key) / (endSize.key - startSize.key);

	float x = startSize.value.x + (transitionPercent * (endSize.value.x - startSize.value.x));
	float y = startSize.value.y + (transitionPercent * (endSize.value.y - startSize.value.y));

	return sf::Vector2f(x, y);
}
