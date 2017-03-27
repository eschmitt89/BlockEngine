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

class Particle : public PhysicsObject
{
public:
	Particle(sf::Vector2f position, sf::Vector2f size);
	Particle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
    virtual ~Particle();
    
protected:
	sf::RectangleShape sprite;
	sf::Vector2f position;
	sf::Vector2f size;
};

#endif /* Particle_hpp */
