#include "Coin.hpp"
#include "ResourceManager.hpp"

Coin::Coin(int value)
	:Item(ItemType_Coin, ResourceManager::GetInstance().GetTexture("coin"))
{
	this->value = value;
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

