#include "Player.hpp"
#include "GoldCoin.hpp"
#include "EventManager.hpp"
#include "ResourceManager.hpp"
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
	movementState = MovementState_None;

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

	if (movementState == MovementState_OnLadder || movementState == MovementState_InLiquid)
	{
		velocity.y = movementAxis.y * movementSpeed;
	}

	if (movementState == MovementState_TryGrabLedge && yState != InAir)
	{
		movementState = MovementState_None;
	}

	UpdateDebugText();
}

////////////////////////////////////////////////////////////////////////

void Player::HandleInput(const sf::RenderWindow & window)
{
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft))
	{
		if (movementState != MovementState_OnLadder && movementState != MovementState_OnLedge)
		{
			movementAxis.x = XAxis_Left;
		}
		if (movementState == MovementState_None && yState == InAir)
		{
			movementState = MovementState_TryGrabLedge;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		if (movementState != MovementState_OnLadder && movementState != MovementState_OnLedge)
		{
			movementAxis.x = XAxis_Right;
		}
		if (movementState == MovementState_None && yState == InAir)
		{
			movementState = MovementState_TryGrabLedge;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxis_None;

		if (movementState == MovementState_TryGrabLedge)
		{
			movementState = MovementState_None;
		}
	}
	if (!EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveLeft) && !EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxis_None;

		if (movementState == MovementState_TryGrabLedge)
		{
			movementState = MovementState_None;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveUp))
	{
		if (movementState == MovementState_None || movementState == MovementState_TryGrabLedge)
		{
			movementState = MovementState_TryGrabLadder;
		}
		if (movementState == MovementState_OnLadder || movementState == MovementState_InLiquid)
		{
			movementAxis.y = YAxis_Up;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveUp))
	{
		if (movementState == MovementState_TryGrabLadder)
		{
			movementState = MovementState_None;
		}
		if (movementState == MovementState_OnLadder || movementState == MovementState_InLiquid)
		{
			movementAxis.y = YAxis_None;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveDown))
	{
		if (movementState == MovementState_OnLadder || movementState == MovementState_InLiquid)
		{
			movementAxis.y = YAxis_Down;
		}
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::MoveDown))
	{
		if (movementState == MovementState_OnLadder || movementState == MovementState_InLiquid)
		{
			movementAxis.y = YAxis_None;
		}
		if (movementState == MovementState_TryDrop || movementState == MovementState_Dropped)
		{
			movementState = MovementState_None;
		}
	}
	if (EventManager::GetInstance().IsKeyPressed(KeyBindings::Jump))
	{
		if (yState == OnGround)
		{
			if (EventManager::GetInstance().IsKeyPressed(KeyBindings::MoveDown))
			{
				if (movementState != MovementState_Dropped)
				{
					movementState = MovementState_TryDrop;
				}
			}
			else if (!jumpKeyHeld)
			{
				Jump();
			}
		}
		else if (movementState == MovementState_OnLedge || movementState == MovementState_InLiquid || (movementState == MovementState_OnLadder && !jumpKeyHeld))
		{
			movementState = MovementState_None;
			velocity.y = 0;
			GravityOn();
			Jump();
		}
		jumpKeyHeld = true;
	}
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::Jump))
	{
		jumpKeyHeld = false;

		if (movementState == MovementState_TryDrop || movementState == MovementState_Dropped)
		{
			movementState = MovementState_None;
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
	if (block.GetType() == BlockType::BlockType_Solid || block.GetType() == BlockType::BlockType_Corner)
	{
		PhysicsObject::ResolveBlockCollisionX(block, dt);
	}
    if (block.GetType() == BlockType_Corner)
	{
		if (movementState == MovementState_TryGrabLedge && velocity.y >= 0)
		{
			if (abs(position.y - block.GetPosition().y) < 8)
			{
				GravityOff();
				movementState = MovementState_OnLedge;
				velocity = sf::Vector2f();
				position.y = block.GetPosition().y;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Player::ResolveBlockCollisionY(Block block, float dt)
{
	if (block.GetType() == BlockType::BlockType_Solid || block.GetType() == BlockType::BlockType_Corner)
	{
		PhysicsObject::ResolveBlockCollisionY(block, dt);
	}
	else if (block.GetType() == BlockType::BlockType_Ladder || block.GetType() == BlockType::BlockType_LadderTop || block.GetType() == BlockType::BlockType_LadderBottom)
	{
		if (movementState == MovementState_TryGrabLadder && velocity.y >= 0)
		{
			if (abs(GetCenter().x - block.GetCenter().x) < 8)
			{
				if (block.GetType() != BlockType::BlockType_LadderTop || (block.GetType() == BlockType::BlockType_LadderTop && abs(GetCenter().y - block.GetCenter().y) < 8))
				{
					GravityOff();
					movementState = MovementState_OnLadder;
					velocity = sf::Vector2f();
				}
			}
		}
		if (movementState == MovementState_OnLadder)
		{
			position.x = block.GetPosition().x;

			if (block.GetType() == BlockType::BlockType_LadderTop)
			{
				if (position.y + (size.y / 2) < block.GetPosition().y)
				{
					position.y = block.GetPosition().y - (size.y / 2);
				}
			}
			else if (block.GetType() == BlockType::BlockType_LadderBottom)
			{
				if (position.y - (size.y / 2) > block.GetPosition().y)
				{
					position.y = block.GetPosition().y +(size.y / 2);
				}
			}
		}
	}
	else if (block.GetType() == BlockType::BlockType_Platform)
	{
		if (movementState == MovementState_TryDrop)
		{
			if (GetCenter().y > block.GetCenter().y)
			{
				movementState = MovementState_Dropped;
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
	else if (block.GetType() == BlockType::BlockType_Liquid)
	{
		movementState = MovementState_InLiquid;
		GravityOff();
	}
	else if (block.GetType() == BlockType::BlockType_LiquidTop)
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
	if (physicsObject->GetObjectType() == ObjectType_Item)
	{
		//Item* item = (Item*)physicsObject;
	}
	else if (physicsObject->GetObjectType() == ObjectType_GoldCoin)
	{
		GoldCoin* goldCoin = (GoldCoin*)physicsObject;
		goldCoins += goldCoin->GetValue();
		goldCoin->SetExpired(true);
	}
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

	switch (xState)
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

	switch(yState)
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
		case MovementState_TryGrabLadder:
			ss << "grabbing ladder \n";
			break;
		case MovementState_OnLadder:
			ss << "on ladder \n";
			break;
		case MovementState_TryGrabLedge:
			ss << "grabbing ledge \n";
			break;
		case MovementState_OnLedge:
			ss << "on ledge \n";
			break;
		case MovementState_TryDrop:
			ss << "try drop \n";
			break;
		case MovementState_Dropped:
			ss << "dropped \n";
			break;
		case MovementState_InLiquid:
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
