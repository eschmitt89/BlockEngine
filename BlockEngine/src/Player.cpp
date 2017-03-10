//
//  Player.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Player.hpp"
#include "ResourceManager.hpp"
#include "EventManager.hpp"
#include <sstream>

Player::Player(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(texture, position, size)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	climbSpeed = 150;
	xMovementAxis = XMovementNone;
	yMovementAxis = YMovementNone;
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

	velocity.x = xMovementAxis * movementSpeed;

	if (playerState == OnLadder)
	{
		velocity.y = yMovementAxis * movementSpeed;
	}

	UpdateDebugText();
}

////////////////////////////////////////////////////////////////////////

void Player::HandleInput(const sf::RenderWindow & window)
{
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::A))
	{
		if (playerState != OnLadder)
		{
			xMovementAxis = XMovementLeft;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::D))
	{
		if (playerState != OnLadder)
		{
			xMovementAxis = XMovementRight;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::A) && EventManager::GetInstance().IsKeyPressed(sf::Keyboard::D))
	{
		xMovementAxis = XMovementNone;
	}
	if (!EventManager::GetInstance().IsKeyPressed(sf::Keyboard::A) && !EventManager::GetInstance().IsKeyPressed(sf::Keyboard::D))
	{
		if (yAxisState == OnGround)
		{
			xMovementAxis = XMovementNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::W))
	{
		if (yAxisState == InAir && playerState != OnLadder)
		{
			playerState = TryGrab;
		}
		if (playerState == OnLadder)
		{
			yMovementAxis = YMovementUp;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::W))
	{
		if (playerState == TryGrab)
		{
			playerState = Idle;
		}
		if (playerState == OnLadder)
		{
			yMovementAxis = YMovementNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::S))
	{
		if (playerState == OnLadder)
		{
			yMovementAxis = YMovementDown;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::S))
	{
		if (playerState == OnLadder)
		{
			yMovementAxis = YMovementNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::Space))
	{
		if (yAxisState == OnGround)
		{
			Impulse(sf::Vector2f(0, -jumpPower));
		}
		if (playerState == OnLadder)
		{
			playerState = Idle;
			velocity = sf::Vector2f();
			acceleration = sf::Vector2f(0, gravity);
			Impulse(sf::Vector2f(0, -jumpPower));
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
			velocity = sf::Vector2f();
			acceleration = sf::Vector2f();
			xMovementAxis = XMovementNone;
		}
		if (playerState == OnLadder)
		{
			position.x = block.GetPosition().x;
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
