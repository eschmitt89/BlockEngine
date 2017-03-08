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

	void Impulse(sf::Vector2f vector);

	sf::Vector2f GetVelocity();
	float GetElasticity();
	float GetMass();

	virtual void ResolveBlockCollisionX(Block block, float dt);
	virtual void ResolveBlockCollisionY(Block block, float dt);
	virtual void CollideWith(PhysicsObject* physicsObject);

	typedef void(*ResolveBlockCollision)(PhysicsObject* physicsObject, Block block, float dt);

	static void ResolveBlockCollisionXFunction(PhysicsObject* physicsObject, Block block, float dt);
	static void ResolveBlockCollisionYFunction(PhysicsObject* physicsObject, Block block, float dt);

protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float elasticity;
	float friction;
	float mass;
};

#endif /* PhysicsObject_hpp */
