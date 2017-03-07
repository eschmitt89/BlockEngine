//
//  PhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "PhysicsObject.hpp"

#define GRAVITY 10

PhysicsObject::PhysicsObject(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	: Object(texture, position, size)
{
	velocity = sf::Vector2f(10, 20);
	acceleration = sf::Vector2f(0, GRAVITY);
	friction = sf::Vector2f();
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
	velocity.x += acceleration.x * dt;
	position.x += velocity.x * dt;
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::UpdateY(float dt)
{
	velocity.y += acceleration.y * dt;
	position.y += velocity.y * dt;
	
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::HandleBlockCollision(Block block)
{
}

////////////////////////////////////////////////////////////////////////

void PhysicsObject::HandleObjectCollision(PhysicsObject * physicsObject)
{
}
