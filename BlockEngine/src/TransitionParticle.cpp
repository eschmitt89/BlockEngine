//
//  Particle.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "TransitionParticle.hpp"

TransitionParticle::TransitionParticle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration)
	:Particle(texture, position, size, duration)
{
	this->totalDuration = duration;

	velocity = sf::Vector2f(Random(-20, 20), Random(-50, -100));
	acceleration = sf::Vector2f();
	
	AddColorKeyframe(0.0, sf::Color::White);
	AddColorKeyframe(0.25, sf::Color(255, 255, 0, 255)); // Yellow
	AddColorKeyframe(0.5, sf::Color(255, 127, 0, 255)); // Orange
	AddColorKeyframe(0.75, sf::Color(255, 0, 0, 255)); // Red
	AddColorKeyframe(1.0, sf::Color(0, 0, 0, 0)); // Black
}

////////////////////////////////////////////////////////////////////////

TransitionParticle::~TransitionParticle()
{
    
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::Update(float dt)
{
	Particle::Update(dt);

	float durationPercent = 1 - (duration / totalDuration);

	UpdateColor(durationPercent);
	UpdateSize(durationPercent);
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::AddColorKeyframe(float durationPercent, sf::Color color)
{
	colorKeyframes.push_back(Keyframe<sf::Color>(durationPercent, color));
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::AddSizeKeyframe(float durationPercent, sf::Vector2f size)
{
	sizeKeyframes.push_back(Keyframe<sf::Vector2f>(durationPercent, size));
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::UpdateColor(float durationPercent)
{
	if (colorKeyframes.size() == 0)
	{
		return;

	}

	KeyFrameTransition<sf::Color> transition = FindTransitionPoints(colorKeyframes, durationPercent);

	int red = transition.start.value.r + (transition.percent * (transition.end.value.r - transition.start.value.r));
	int green = transition.start.value.g + (transition.percent * (transition.end.value.g - transition.start.value.g));
	int blue = transition.start.value.b + (transition.percent * (transition.end.value.b - transition.start.value.b));
	int alpha = transition.start.value.a + (transition.percent * (transition.end.value.a - transition.start.value.a));

	sprite.setFillColor(sf::Color(red, green, blue, alpha));
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::UpdateSize(float durationPercent)
{
	if (sizeKeyframes.size() == 0)
	{
		return;
	}

	KeyFrameTransition<sf::Vector2f> transition = FindTransitionPoints(sizeKeyframes, durationPercent);

	float x = transition.start.value.x + (transition.percent * (transition.end.value.x - transition.start.value.x));
	float y = transition.start.value.y + (transition.percent * (transition.end.value.y - transition.start.value.y));

	SetSize(sf::Vector2f(x, y));
}
