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
#include "Utilities.hpp"
#include <sstream>

Player::Player(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(texture, position, size)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	climbSpeed = 150;
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

	velocity.x = movementAxis.x * movementSpeed;

	if (playerState == OnLadder)
	{
		velocity.y = movementAxis.y * movementSpeed;
	}

	UpdateDebugText();
}

////////////////////////////////////////////////////////////////////////

void Player::HandleInput(const sf::RenderWindow & window)
{
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft))
	{
		if (playerState == Idle)
		{
			movementAxis.x = XAxisLeft;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		if (playerState == Idle)
		{
			movementAxis.x = XAxisRight;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxisNone;
	}
	if (!EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && !EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxisNone;
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveUp))
	{
		if (playerState == Idle)
		{
			playerState = TryGrab;
		}
		if (playerState == OnLadder)
		{
			movementAxis.y = YAxisUp;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveUp))
	{
		if (playerState == TryGrab)
		{
			playerState = Idle;
		}
		if (playerState == OnLadder)
		{
			movementAxis.y = YAxisNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveDown))
	{
		if (playerState == OnLadder)
		{
			movementAxis.y = YAxisDown;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveDown))
	{
		if (playerState == OnLadder)
		{
			movementAxis.y = YAxisNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::Jump))
	{
		if (verticalState == OnGround)
		{
			Jump();
		}
		if (playerState == OnLadder)
		{
			playerState = Idle;
			velocity.y = 0;
			GravityOn();
			Jump();
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
	else if (block.GetType() == BlockType::Ladder || block.GetType() == BlockType::LadderTop || block.GetType() == BlockType::LadderBottom)
	{
		if (playerState == TryGrab)
		{
			if (abs(GetCenter().x - block.GetCenter().x) < 16)
			{
				GravityOff();
				playerState = OnLadder;
				velocity = sf::Vector2f();
			}
		}
		if (playerState == OnLadder)
		{
			position.x = block.GetPosition().x;

			if (block.GetType() == BlockType::LadderTop)
			{
				if (position.y < block.GetPosition().y)
				{
					position.y = block.GetPosition().y;
				}
			}
			else if (block.GetType() == BlockType::LadderBottom)
			{
				if (position.y > block.GetPosition().y)
				{
					position.y = block.GetPosition().y;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Player::CollideWith(PhysicsObject * physicsObject)
{

}

////////////////////////////////////////////////////////////////////////

void Player::Jump()
{
	Impulse(sf::Vector2f(0, -jumpPower));
}

////////////////////////////////////////////////////////////////////////

void Player::GravityOn()
{
	acceleration = sf::Vector2f(0, gravity);
}

////////////////////////////////////////////////////////////////////////

void Player::GravityOff()
{
	acceleration = sf::Vector2f();
}

////////////////////////////////////////////////////////////////////////

void Player::UpdateDebugText()
{
	stringstream ss;

	switch (horizontalState)
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

	switch(verticalState)
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
