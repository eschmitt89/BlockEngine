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

	jumpKeyHeld = false;

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
		if (playerState != OnLadder && playerState != OnLedge)
		{
			movementAxis.x = XAxisLeft;
		}
		if (playerState == Idle && verticalState == InAir)
		{
			playerState = TryGrabLedge;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		if (playerState != OnLadder && playerState != OnLedge)
		{
			movementAxis.x = XAxisRight;
		}
		if (playerState == Idle && verticalState == InAir)
		{
			playerState = TryGrabLedge;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxisNone;
		if (playerState == TryGrabLedge)
		{
			playerState = Idle;
		}
	}
	if (!EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && !EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxisNone;
		if (playerState == TryGrabLedge)
		{
			playerState = Idle;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveUp))
	{
		if (playerState == Idle)
		{
			playerState = TryGrabLadder;
		}
		if (playerState == OnLadder)
		{
			movementAxis.y = YAxisUp;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveUp))
	{
		if (playerState == TryGrabLadder)
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
		else if (playerState == OnLedge)
		{
			playerState = Idle;
			velocity.y = 0;
			GravityOn();
			Jump();
		}
		else if (playerState == OnLadder && !jumpKeyHeld)
		{
			playerState = Idle;
			velocity.y = 0;
			GravityOn();
			Jump();
		}
		jumpKeyHeld = true;
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::Jump))
	{
		jumpKeyHeld = false;
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
	if (block.GetType() == BlockType::Solid || block.GetType() == BlockType::Corner)
	{
		PhysicsObject::ResolveBlockCollisionX(block, dt);
	}
    if (block.GetType() == Corner)
	{
		if (playerState == TryGrabLedge && velocity.y >= 0)
		{
			if (abs(position.y - block.GetPosition().y) < 8)
			{
				GravityOff();
				playerState = OnLedge;
				velocity = sf::Vector2f();
				position.y = block.GetPosition().y;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Player::ResolveBlockCollisionY(Block block, float dt)
{
	if (block.GetType() == BlockType::Solid || block.GetType() == BlockType::Corner)
	{
		PhysicsObject::ResolveBlockCollisionY(block, dt);
	}
	else if (block.GetType() == BlockType::Ladder || block.GetType() == BlockType::LadderTop || block.GetType() == BlockType::LadderBottom)
	{
		if (playerState == TryGrabLadder && velocity.y >= 0)
		{
			if (abs(GetCenter().x - block.GetCenter().x) < 8)
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
		case TryGrabLadder:
			ss << "grabbing ladder \n";
			break;
		case OnLadder:
			ss << "on ladder \n";
			break;
		case TryGrabLedge:
			ss << "grabbing ledge \n";
			break;
		case OnLedge:
			ss << "on ledge \n";
			break;
		default:
			break;
	}

	if (jumpKeyHeld)
	{
		ss << "jump pressed \n";
	}

	debugText.setString(ss.str());
	debugText.setPosition(position);
}
