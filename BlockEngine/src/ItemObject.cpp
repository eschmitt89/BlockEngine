#include "ItemObject.hpp"

ItemObject::ItemObject(Item * item, sf::Vector2f position, sf::Vector2f size)
	:Object(item->GetTexture(), position, size)
{
	this->item = item;
}

////////////////////////////////////////////////////////////////////////

ItemObject::~ItemObject()
{
}

////////////////////////////////////////////////////////////////////////

void ItemObject::SetItem(Item * item)
{
	this->item = item;
	sprite.setTexture(item->GetTexture());
	SetSize((sf::Vector2f)item->GetTexture()->getSize());
}

////////////////////////////////////////////////////////////////////////

void ItemObject::SetPosition(sf::Vector2f position)
{
	SetPosition(position);
}

////////////////////////////////////////////////////////////////////////

