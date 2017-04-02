//
//  PhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	: Object(texture, position, size)
{
	gravity = 1200;
	velocity = sf::Vector2f(10, 20);
	acceleration = sf::Vector2f(0, gravity);
	friction = sf::Vector2f(0.5, 0.5);
	elasticity = 0.5;
	mass = 1;

	xState = NotOnWall;
	yState = InAir;

	expired = false;
}

////////////////////////////////////////////////////////////////////////

PhysicsObject::~PhysicsObject()
{
    
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::Update(float dt)
{
	SetPosition(position);
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::UpdateX(float dt)
{
	xState = NotOnWall;

	velocity.x += acceleration.x * dt;
	position.x += velocity.x * dt;
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::UpdateY(float dt)
{
	yState = InAir;

	velocity.y += acceleration.y * dt;
	position.y += velocity.y * dt;
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::Impulse(sf::Vector2f vector)
{
	velocity += vector;
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f PhysicsObject::GetVelocity()
{
	return velocity;
}

////////////////////////////////////////////////////////////////////////

float PhysicsObject::GetElasticity()
{
	return elasticity;
}

////////////////////////////////////////////////////////////////////////

float PhysicsObject::GetMass()
{
	return mass;
}

////////////////////////////////////////////////////////////////////////

bool PhysicsObject::GetExpired()
{
	return expired;
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::ResolveBlockCollisionX(Block block, float dt)
{
	if (velocity.x < 0)
	{
		xState = OnWallLeft;
		position.x = block.GetPosition().x + block.GetSize().x;
	}
	else
	{
		xState = OnWallRight;
		position.x = block.GetPosition().x - size.x;
	}

	velocity.x *= -elasticity;
	velocity.y *= pow(1 - friction.y, dt);
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::ResolveBlockCollisionY(Block block, float dt)
{
	if (velocity.y < 0)
	{
		yState = OnCeiling;
		position.y = block.GetPosition().y + block.GetSize().y;
	}
	else
	{
		yState = OnGround;
		position.y = block.GetPosition().y - size.y;
	}

	velocity.x *= pow(1 - friction.x, dt);
	velocity.y *= -elasticity;
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::CollideWith(PhysicsObject * physicsObject)
{

}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::ResolveBlockCollisionXFunction(PhysicsObject* physicsObject, Block block, float dt)
{
	physicsObject->ResolveBlockCollisionX(block, dt);
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::ResolveBlockCollisionYFunction(PhysicsObject* physicsObject, Block block, float dt)
{
	physicsObject->ResolveBlockCollisionY(block, dt);
}

////////////////////////////////////////////////////////////////////////

