//
//  Particle.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "PhysicsObject.hpp"
#include "Keyframe.hpp"

class Particle : public PhysicsObject
{
public:
	Particle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration);
	Particle(sf::Vector2f position, sf::Vector2f size, float duration) : Particle(nullptr, position, size, duration) { }
    virtual ~Particle();
    
	virtual void Update(float dt);

protected:
	float totalDuration;
	float currentDuration;

	vector<Keyframe<sf::Color>> colorKeyframes;
	vector<Keyframe<sf::Vector2f>> sizeKeyframes;

	void AddColorKeyframe(float durationPercent, sf::Color color);
	void AddSizeKeyframe(float durationPercent, sf::Vector2f size);

	sf::Color ComputeColor(float durationPercent);
	sf::Vector2f ComputeSize(float durationPercent);
};

#endif /* Particle_hpp */
