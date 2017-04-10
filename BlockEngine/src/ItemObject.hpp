#ifndef ItemObject_hpp
#define ItemObject_hpp

#include "Item.hpp"
#include "Object.hpp"

using namespace std;

class ItemObject : public Object
{
public:
	ItemObject(Item* item, sf::Vector2f position, sf::Vector2f size);
	~ItemObject();

	void SetItem(Item* item);
	void SetPosition(sf::Vector2f position);

protected:
	Item* item;
};

#endif /* ItemObject_hpp */