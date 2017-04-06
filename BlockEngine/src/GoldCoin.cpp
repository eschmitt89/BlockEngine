#include "GoldCoin.hpp"
#include "ResourceManager.hpp"

GoldCoin::GoldCoin(sf::Vector2f position, int value)
	:PhysicsObject(ResourceManager::GetInstance().GetTexture("goldCoin"), position, size)
{
	this->value = value;
	SetSize((sf::Vector2f)sprite.getTexture()->getSize());
}

////////////////////////////////////////////////////////////////////////

GoldCoin::~GoldCoin()
{
    
}

////////////////////////////////////////////////////////////////////////

int GoldCoin::GetValue()
{
	return value;
}

