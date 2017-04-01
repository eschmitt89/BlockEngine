//
//  Emitter.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Emitter_hpp
#define Emitter_hpp

#include "Particle.hpp"

class Emitter : public Particle
{
public:
	Emitter(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration);
	Emitter(sf::Vector2f position, sf::Vector2f size, float duration) : Emitter(nullptr, position, size, duration) { }
    virtual ~Emitter();
    
	virtual void Update(float dt);

protected:
	vector<Particle> particles;
};

#endif /* Emitter_hpp */
