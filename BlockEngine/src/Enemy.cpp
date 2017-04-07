#include "Enemy.hpp"
#include <sstream>

Enemy::Enemy(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:Character(texture, position, size)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	movementState = MovementState_None;

	debugText = sf::Text("debug", *ResourceManager::GetInstance().GetFont("font"));
	debugText.setFillColor(sf::Color::Red);
	debugText.setOrigin(sf::Vector2f(-30, 30));

}

////////////////////////////////////////////////////////////////////////

Enemy::~Enemy()
{
    
}

////////////////////////////////////////////////////////////////////////

void Enemy::Update(float dt)
{
	PhysicsObject::Update(dt);

	velocity.x = movementAxis.x * movementSpeed;

	UpdateDebugText();
}

////////////////////////////////////////////////////////////////////////

void Enemy::Draw(sf::RenderWindow & window)
{
	Object::Draw(window);
	window.draw(debugText);
}

////////////////////////////////////////////////////////////////////////

void Enemy::ResolveBlockCollisionX(Block block, float dt)
{
	PhysicsObject::ResolveBlockCollisionX(block, dt);
}

////////////////////////////////////////////////////////////////////////

void Enemy::ResolveBlockCollisionY(Block block, float dt)
{
	PhysicsObject::ResolveBlockCollisionY(block, dt);
}

////////////////////////////////////////////////////////////////////////

void Enemy::CollideWith(PhysicsObject * physicsObject)
{

}

////////////////////////////////////////////////////////////////////////

void Enemy::Jump()
{
	Impulse(sf::Vector2f(0, -jumpPower));
}

////////////////////////////////////////////////////////////////////////

void Enemy::UpdateDebugText()
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

	debugText.setString(ss.str());
	debugText.setPosition(position);
}
