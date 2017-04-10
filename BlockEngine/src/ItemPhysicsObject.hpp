#ifndef ItemPhysicsObject_hpp
#define ItemPhysicsObject_hpp

#include "Item.hpp"
#include "PhysicsObject.hpp"

class ItemPhysicsObject : public PhysicsObject
{
public:
	ItemPhysicsObject(Item* item, sf::Vector2f position);
    virtual ~ItemPhysicsObject();
	virtual ObjectType GetObjectType() { return ObjectType_Item; }

	ItemType GetItemType();
    
	Item* GetItem();

protected:
	Item* item;
};

#endif /* ItemPhysicsObject_hpp */
