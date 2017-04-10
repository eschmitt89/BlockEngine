#ifndef Emitter_hpp
#define Emitter_hpp

#include "Particle.hpp"

class Emitter : public Particle
{
public:
	Emitter(Particle* particle, sf::Vector2f position, sf::Vector2f size, float duration);
    virtual ~Emitter();
    
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

protected:
	Particle* particle;
	int particlesPerMinute;
	float spawnTimer;
};

#endif /* Emitter_hpp */
