//
//  Player.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Player.hpp"

Player::Player(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(texture, position, size)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 175;
	climbSpeed = 150;
	movementAxis = MovementNone;
	playerState = Standing;
}

////////////////////////////////////////////////////////////////////////

Player::~Player()
{
    
}

////////////////////////////////////////////////////////////////////////

void Player::Update(float dt)
{
	PhysicsObject::Update(dt);

	velocity.x = movementAxis * movementSpeed;

	if (playerState == OnLadder)
	{
		acceleration = sf::Vector2f();
	}
	else
	{
		acceleration = sf::Vector2f(0, gravity);
	}
}

////////////////////////////////////////////////////////////////////////

void Player::HandleInput(const sf::RenderWindow & window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementAxis = MovementLeft;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementAxis = MovementRight;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementAxis = MovementNone;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (yAxisState == OnGround)
		{
			Impulse(sf::Vector2f(0, -jumpPower));
		}
	    if (yAxisState == InAir && velocity.y > 0)
		{
			playerState = TryGrab;
		}
		if (playerState == OnLadder)
		{
			velocity.y = -climbSpeed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (playerState == OnLadder)
		{
			velocity.y = climbSpeed;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (playerState == OnLadder)
		{
			velocity.y = 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Player::ResolveBlockCollisionX(Block block, float dt)
{
	if (block.GetType() == BlockType::Solid)
	{
		PhysicsObject::ResolveBlockCollisionX(block, dt);
	}
}

////////////////////////////////////////////////////////////////////////

void Player::ResolveBlockCollisionY(Block block, float dt)
{
	if (block.GetType() == BlockType::Solid)
	{
		PhysicsObject::ResolveBlockCollisionY(block, dt);
	}
	else if (block.GetType() == BlockType::Ladder)
	{
		if (playerState == TryGrab)
		{
			playerState = OnLadder;
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Player::CollideWith(PhysicsObject * physicsObject)
{

}
