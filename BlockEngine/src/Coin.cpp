#include "Coin.hpp"
#include "Utilities.hpp"
#include "ResourceManager.hpp"

Coin::Coin(sf::Vector2f position, int value)
	:PhysicsObject(ResourceManager::GetInstance().GetTexture("coin"), position)
{
	this->value = value;
	velocity = sf::Vector2f(Random(-100, 100), Random(-500, -50));
}

////////////////////////////////////////////////////////////////////////

Coin::~Coin()
{
    
}

////////////////////////////////////////////////////////////////////////

int Coin::GetValue()
{
	return value;
}

