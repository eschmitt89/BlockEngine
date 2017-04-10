#ifndef TransitionParticle_hpp
#define TransitionParticle_hpp

#include "Particle.hpp"

class TransitionParticle : public Particle
{
public:
	TransitionParticle(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, float duration);
	TransitionParticle(sf::Vector2f position, sf::Vector2f size, float duration) : TransitionParticle(nullptr, position, size, duration) { }
    virtual ~TransitionParticle();
    
	virtual void Update(float dt);

protected:
	float totalDuration;

	vector<TypeValue<sf::Color>> colorKeyframes;
	vector<TypeValue<sf::Vector2f>> sizeKeyframes;

	void AddColorKeyframe(float durationPercent, sf::Color color);
	void AddSizeKeyframe(float durationPercent, sf::Vector2f size);

	void UpdateColor(float durationPercent);
	void UpdateSize(float durationPercent);
};

#endif /* TransitionParticle_hpp */




