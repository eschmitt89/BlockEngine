#include "Player.hpp"
#include "Coin.hpp"
#include "EventManager.hpp"
#include "ResourceManager.hpp"
#include "ItemPhysicsObject.hpp"
#include "Utilities.hpp"
#include <sstream>

Player::Player(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:Character(texture, position, size, 1, 100)
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

	coins = 0;

	inventory = new ItemCollection(50);
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
	if (EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveLeft))
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
	if (EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveRight))
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
	if (EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveLeft) && EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxis_None;

		if (movementState == MovementState_TryGrabLedge)
		{
			movementState = MovementState_None;
		}
	}
	if (!EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveLeft) && !EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveRight))
	{
		movementAxis.x = XAxis_None;

		if (movementState == MovementState_TryGrabLedge)
		{
			movementState = MovementState_None;
		}
	}
	if (EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveUp))
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
	if (EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveDown))
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
	if (EventManager::GetInstance().IsKeyHeld(KeyBindings::Jump))
	{
		if (yState == OnGround)
		{
			if (EventManager::GetInstance().IsKeyHeld(KeyBindings::MoveDown))
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
	if (EventManager::GetInstance().IsKeyReleased(KeyBindings::Attack))
	{
		Spawn(new Attack(ResourceManager::GetInstance().GetTexture("redX"), sf::Vector2f(position.x + size.x + 5, position.y), size, 50));
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
	Character::CollideWith(physicsObject);

	if (physicsObject->GetObjectType() == ObjectType_Item)
	{
		if (inventory->GetAvailableSpace() > 0)
		{
			inventory->Insert(new Item(*((ItemPhysicsObject*)physicsObject)->GetItem()));
			physicsObject->SetExpired(true);
		}
	}
	else if (physicsObject->GetObjectType() == ObjectType_Coin)
	{
		Coin* coin = (Coin*)physicsObject;
		coins += coin->GetValue();
		physicsObject->SetExpired(true);
	}
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

	//switch (xState)
	//{
	//case OnWallLeft:
	//	ss << "wall left \n";
	//	break;
	//case NotOnWall:
	//	ss << "no wall \n";
	//	break;
	//case OnWallRight:
	//	ss << "wall right \n";
	//	break;
	//default:
	//	break;
	//}

	//switch(yState)
	//{
	//	case OnCeiling:
	//		ss << "on ceiling \n";
	//		break;
	//	case InAir:
	//		ss << "in air \n";
	//		break;
	//	case OnGround:
	//		ss << "on ground \n";
	//		break;
	//	default:
	//		break;
	//}

	//switch (movementState)
	//{
	//	case MovementState_TryGrabLadder:
	//		ss << "grabbing ladder \n";
	//		break;
	//	case MovementState_OnLadder:
	//		ss << "on ladder \n";
	//		break;
	//	case MovementState_TryGrabLedge:
	//		ss << "grabbing ledge \n";
	//		break;
	//	case MovementState_OnLedge:
	//		ss << "on ledge \n";
	//		break;
	//	case MovementState_TryDrop:
	//		ss << "try drop \n";
	//		break;
	//	case MovementState_Dropped:
	//		ss << "dropped \n";
	//		break;
	//	case MovementState_InLiquid:
	//		ss << "in liquid \n";
	//		break;
	//	default:
	//		break;
	//}

	//if (jumpKeyHeld)
	//{
	//	ss << "jump pressed \n";
	//}
	EquipmentStats stats = equipment.GetEquipmentStats();

	ss << "Health: " << stats.health + health << "\n";
	ss << "Armor: " << stats.armor << "\n";
	ss << "Crit: " << stats.crit / 100.f << "\n";
	ss << "Dodge: " << stats.dodge / 100.f << "\n";
	ss << "Power: " << stats.power << "\n";
	ss << "Gold: " << coins << "\n";
	ss << "AvailableSpace: " << inventory->GetAvailableSpace() << "\n";

	if (EventManager::GetInstance().IsKeyPressed(sf::Keyboard::B))
	{
		ss << "pressed\n";
	}
	else if (EventManager::GetInstance().IsKeyHeld(sf::Keyboard::B))
	{
		ss << "Held\n";
	}
	if (EventManager::GetInstance().IsKeyReleased(sf::Keyboard::B))
	{
		ss << "Released\n";
	}

	

	debugText.setString(ss.str());
	debugText.setPosition(position);
}
