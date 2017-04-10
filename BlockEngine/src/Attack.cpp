#include "Attack.hpp"

Attack::Attack(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, int damage)
	:PhysicsObject(texture, position, size)
{
	this->damage = damage;
	this->velocity = sf::Vector2f();
	this->acceleration = sf::Vector2f();
	expired = true;
}

////////////////////////////////////////////////////////////////////////

Attack::~Attack()
{
    
}

////////////////////////////////////////////////////////////////////////

int Attack::GetDamage()
{
	return damage;;
}


////////////////////////////////////////////////////////////////////////