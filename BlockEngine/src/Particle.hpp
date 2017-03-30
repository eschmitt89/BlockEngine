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

	void AddColorKeyframe(float durationPercent, sf::Color color);

	sf::Color ComputeColor(float durationPercent);
};

#endif /* Particle_hpp */
