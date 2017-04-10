#include "Emitter.hpp"
#include "TransitionParticle.hpp"

Emitter::Emitter(Particle* particle, sf::Vector2f position, sf::Vector2f size, float duration)
	:Particle(nullptr, position, size, duration)
{
	velocity = sf::Vector2f(500, 0);
	this->particle = particle;
	particlesPerMinute = 10000;
	spawnTimer = 0;
	mass = 100;
}

////////////////////////////////////////////////////////////////////////

Emitter::~Emitter()
{
	delete particle;
}

////////////////////////////////////////////////////////////////////////

void Emitter::Update(float dt)
{
	Particle::Update(dt);

	spawnTimer -= dt;

	if (spawnTimer <= 0)
	{
		Spawn(new TransitionParticle(position, size, 0.6));

		spawnTimer = 60 / (float)particlesPerMinute;
	}
}

////////////////////////////////////////////////////////////////////////

void Emitter::Draw(sf::RenderWindow & window)
{
	
}

////////////////////////////////////////////////////////////////////////
