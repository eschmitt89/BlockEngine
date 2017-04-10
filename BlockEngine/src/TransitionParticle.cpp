#include "TransitionParticle.hpp"

TransitionParticle::TransitionParticle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration)
	:Particle(texture, position, size, duration)
{
	this->totalDuration = duration;

	velocity = sf::Vector2f(Random(-20, 20), Random(-20, 20));
	acceleration = sf::Vector2f();
	
	AddColorKeyframe(0.0, sf::Color::White);
	AddColorKeyframe(0.25, sf::Color(255, 255, 0, 255)); // Yellow
	AddColorKeyframe(0.5, sf::Color(255, 127, 0, 255)); // Orange
	AddColorKeyframe(0.75, sf::Color(255, 0, 0, 255)); // Red
	AddColorKeyframe(1.0, sf::Color(0, 0, 0, 0)); // Black

	
	//
	//AddColorKeyframe(0.0, sf::Color(0, 255, 64, 255));
	//AddColorKeyframe(0.5, sf::Color(64, 0, 128, 255));
	//AddColorKeyframe(1.0, sf::Color(64, 0, 128, 0));
}

////////////////////////////////////////////////////////////////////////

TransitionParticle::~TransitionParticle()
{
    
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::Update(float dt)
{
	Particle::Update(dt);

	float durationPercent = 1 - (remainingDuration / totalDuration);

	UpdateColor(durationPercent);
	UpdateSize(durationPercent);
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::AddColorKeyframe(float durationPercent, sf::Color color)
{
	colorKeyframes.push_back(TypeValue<sf::Color>(color, durationPercent));
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::AddSizeKeyframe(float durationPercent, sf::Vector2f size)
{
	sizeKeyframes.push_back(TypeValue<sf::Vector2f>(size, durationPercent));
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::UpdateColor(float durationPercent)
{
	if (colorKeyframes.size() == 0)
	{
		return;
	}

	TypeTransition<sf::Color> transition = FindTransitionPoints(colorKeyframes, durationPercent);

	int red = transition.start.type.r + (transition.percent * (transition.end.type.r - transition.start.type.r));
	int green = transition.start.type.g + (transition.percent * (transition.end.type.g - transition.start.type.g));
	int blue = transition.start.type.b + (transition.percent * (transition.end.type.b - transition.start.type.b));
	int alpha = transition.start.type.a + (transition.percent * (transition.end.type.a - transition.start.type.a));

	sprite.setFillColor(sf::Color(red, green, blue, alpha));
}

////////////////////////////////////////////////////////////////////////

void TransitionParticle::UpdateSize(float durationPercent)
{
	if (sizeKeyframes.size() == 0)
	{
		return;
	}

	TypeTransition<sf::Vector2f> transition = FindTransitionPoints(sizeKeyframes, durationPercent);

	float x = transition.start.type.x + (transition.percent * (transition.end.type.x - transition.start.type.x));
	float y = transition.start.type.y + (transition.percent * (transition.end.type.y - transition.start.type.y));

	SetSize(sf::Vector2f(x, y));
}
