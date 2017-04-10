#include "ItemPhysicsObject.hpp"

ItemPhysicsObject::ItemPhysicsObject(Item* item, sf::Vector2f position)
	:PhysicsObject(item->GetTexture(), position, sf::Vector2f())
{
	this->item = item;
	if (item->GetTexture())
	{
		SetSize((sf::Vector2f)item->GetTexture()->getSize());
	}

	velocity = sf::Vector2f(Random(-100, 100), Random(-200, -100));
}

////////////////////////////////////////////////////////////////////////

ItemPhysicsObject::~ItemPhysicsObject()
{
	delete item;
}

////////////////////////////////////////////////////////////////////////

ItemType ItemPhysicsObject::GetItemType()
{
	return item->GetItemType();
}

////////////////////////////////////////////////////////////////////////

Item * ItemPhysicsObject::GetItem()
{
	return item;
}

