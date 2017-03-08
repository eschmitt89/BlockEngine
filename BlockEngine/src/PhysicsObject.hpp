//
//  PhysicsObject.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef PhysicsObject_hpp
#define PhysicsObject_hpp

#include "Object.hpp"
#include "Block.hpp"

class PhysicsObject : public Object
{
public:
	PhysicsObject(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
    ~PhysicsObject();

	virtual void Update(float dt);

	void UpdateX(float dt);
	void UpdateY(float dt);

	virtual void ResolveBlockCollisionX(Block block);
	virtual void ResolveBlockCollisionY(Block block);
	virtual void ResolvePhysicsObjectCollision(PhysicsObject* physicsObject);

	typedef void(*ResolveBlockCollision)(PhysicsObject* physicsObject, Block block);

	static void ResolveBlockCollisionXFunction(PhysicsObject* physicsObject, Block block);
	static void ResolveBlockCollisionYFunction(PhysicsObject* physicsObject, Block block);

protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f friction;

};

#endif /* PhysicsObject_hpp */
