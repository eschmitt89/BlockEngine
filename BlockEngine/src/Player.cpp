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
	movementState = MovementStateNone;

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

	if (movementState == OnLadder || movementState == InLiquid)
	{
		velocity.y = movementAxis.y * movementSpeed;
	}

	if (movementState == TryGrabLedge && verticalState != InAir)
	{
		movementState = MovementStateNone;
	}

	UpdateDebugText();
}

////////////////////////////////////////////////////////////////////////

void Player::HandleInput(const sf::RenderWindow & window)
{
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft))
	{
		if (movementState != OnLadder && movementState != OnLedge)
		{
			movementAxis.x = XAxisLeft;
		}
		if (movementState == MovementStateNone && verticalState == InAir)
		{
			movementState = TryGrabLedge;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		if (movementState != OnLadder && movementState != OnLedge)
		{
			movementAxis.x = XAxisRight;
		}
		if (movementState == MovementStateNone && verticalState == InAir)
		{
			movementState = TryGrabLedge;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxisNone;

		if (movementState == TryGrabLedge)
		{
			movementState = MovementStateNone;
		}
	}
	if (!EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && !EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxisNone;

		if (movementState == TryGrabLedge)
		{
			movementState = MovementStateNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveUp))
	{
		if (movementState == MovementStateNone || movementState == TryGrabLedge)
		{
			movementState = TryGrabLadder;
		}
		if (movementState == OnLadder || movementState == InLiquid)
		{
			movementAxis.y = YAxisUp;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveUp))
	{
		if (movementState == TryGrabLadder)
		{
			movementState = MovementStateNone;
		}
		if (movementState == OnLadder || movementState == InLiquid)
		{
			movementAxis.y = YAxisNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveDown))
	{
		if (movementState == OnLadder || movementState == InLiquid)
		{
			movementAxis.y = YAxisDown;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveDown))
	{
		if (movementState == OnLadder || movementState == InLiquid)
		{
			movementAxis.y = YAxisNone;
		}
		if (movementState == TryDrop || movementState == Dropped)
		{
			movementState = MovementStateNone;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::Jump))
	{
		if (verticalState == OnGround)
		{
			if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveDown))
			{
				if (movementState != Dropped)
				{
					movementState = TryDrop;
				}
			}
			else
			{
				Jump();
			}
		}
		else if (movementState == OnLedge || movementState == InLiquid || (movementState == OnLadder && !jumpKeyHeld))
		{
			movementState = MovementStateNone;
			velocity.y = 0;
			GravityOn();
			Jump();
		}
		jumpKeyHeld = true;
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::Jump))
	{
		jumpKeyHeld = false;

		if (movementState == TryDrop || movementState == Dropped)
		{
			movementState = MovementStateNone;
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
	if (block.GetType() == BlockType::Solid || block.GetType() == BlockType::Corner)
	{
		PhysicsObject::ResolveBlockCollisionX(block, dt);
	}
    if (block.GetType() == Corner)
	{
		if (movementState == TryGrabLedge && velocity.y >= 0)
		{
			if (abs(position.y - block.GetPosition().y) < 8)
			{
				GravityOff();
				movementState = OnLedge;
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
		if (movementState == TryGrabLadder && velocity.y >= 0)
		{
			if (abs(GetCenter().x - block.GetCenter().x) < 8)
			{
				if (block.GetType() != BlockType::LadderTop || (block.GetType() == BlockType::LadderTop && abs(GetCenter().y - block.GetCenter().y) < 8))
				{
					GravityOff();
					movementState = OnLadder;
					velocity = sf::Vector2f();
				}
			}
		}
		if (movementState == OnLadder)
		{
			position.x = block.GetPosition().x;

			if (block.GetType() == BlockType::LadderTop)
			{
				if (position.y + (size.y / 2) < block.GetPosition().y)
				{
					position.y = block.GetPosition().y - (size.y / 2);
				}
			}
			else if (block.GetType() == BlockType::LadderBottom)
			{
				if (position.y - (size.y / 2) > block.GetPosition().y)
				{
					position.y = block.GetPosition().y +(size.y / 2);
				}
			}
		}
	}
	else if (block.GetType() == BlockType::Platform)
	{
		if (movementState == TryDrop)
		{
			if (GetCenter().y > block.GetCenter().y)
			{
				movementState = Dropped;
			}
		}
		else 
		{
			if (velocity.y > 0 && (position.y + size.y) - block.GetPosition().y < 4 )
			{
				PhysicsObject::ResolveBlockCollisionY(block, dt);
			}
		}
	}
	else if (block.GetType() == BlockType::Liquid)
	{
		movementState = InLiquid;
		GravityOff();
	}
	else if (block.GetType() == BlockType::LiquidTop)
	{
		if (position.y < block.GetPosition().y && velocity.y < 0 && acceleration.y == 0)
		{
			position.y = block.GetPosition().y;
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

	switch (movementState)
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
		case TryDrop:
			ss << "try drop \n";
			break;
		case Dropped:
			ss << "dropped \n";
			break;
		case InLiquid:
			ss << "in liquid \n";
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
