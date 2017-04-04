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
#include "Utilities.hpp"

class Particle : public PhysicsObject
{
public:
	Particle(const sf::Texture* texture, sf::Color color, sf::Vector2f position, sf::Vector2f size, float duration);
	Particle(sf::Vector2f position, sf::Vector2f size, float duration) : Particle(nullptr, sf::Color::White, position, size, duration) { }
	Particle(sf::Color color, sf::Vector2f position, sf::Vector2f size, float duration) : Particle(nullptr, color, position, size, duration) { }
	Particle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration) : Particle(texture, sf::Color::White, position, size, duration) { }
    virtual ~Particle();
    
	virtual void Update(float dt);

protected:
	float remainingDuration;
};

#endif /* Particle_hpp */
