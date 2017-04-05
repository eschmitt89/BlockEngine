//
//  ItemPhysicsObject.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef ItemPhysicsObject_hpp
#define ItemPhysicsObject_hpp

#include "Item.hpp"
#include "PhysicsObject.hpp"

class ItemPhysicsObject : public PhysicsObject
{
public:
	ItemPhysicsObject(Item* item, sf::Vector2f position, sf::Vector2f size);
    virtual ~ItemPhysicsObject();
	virtual ObjectType GetObjectType() { return ObjectType_Item; }
    
protected:
	Item* item;
};

#endif /* ItemPhysicsObject_hpp */