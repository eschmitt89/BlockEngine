//
//  Player.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Player.hpp"
#include "ResourceManager.hpp"
#include <sstream>

Player::Player(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(texture, position, size)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	climbSpeed = 150;
	movementAxis = MovementNone;
	playerState = Idle;

	debugText = sf::Text("debug", *ResourceManager::GetInstance().GetFont("font"));
	debugText.setFillColor(sf::Color::Red);
	debugText.setOrigin(sf::Vector2f(-30, 30));
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

	UpdateDebugText();
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
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && yAxisState == OnGround)
	{
		movementAxis = MovementNone;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (yAxisState == OnGround)
		{
			Impulse(sf::Vector2f(0, -jumpPower));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (yAxisState == InAir && playerState != OnLadder)
		{
			playerState = TryGrab;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (playerState == TryGrab)
		{
			playerState = Idle;
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Player::Draw(sf::RenderWindow & window)
{
	Object::Draw(window);
	window.draw(debugText);
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

////////////////////////////////////////////////////////////////////////

void Player::UpdateDebugText()
{
	stringstream ss;

	switch (xAxisState)
	{
	case OnWallLeft:
		ss << "wall left \n";
		break;
	case NotOnWall:
		ss << "no wall \n";
		break;
	case OnWallRight:
		ss << "wall right \n";
		break;
	default:
		break;
	}

	switch(yAxisState)
	{
		case OnCeiling:
			ss << "on ceiling \n";
			break;
		case InAir:
			ss << "in air \n";
			break;
		case OnGround:
			ss << "on ground \n";
			break;
		default:
			break;
	}

	switch (playerState)
	{
		case TryGrab:
			ss << "grabbing \n";
			break;
		case OnLadder:
			ss << "on ladder \n";
			break;
		default:
			break;
	}

	debugText.setString(ss.str());
	debugText.setPosition(position);
}
