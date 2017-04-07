#include "Enemy.hpp"
#include <sstream>

Enemy::Enemy(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:Character(texture, position, size, 1, 100)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	movementState = MovementState_None;
	movementAxis.x = XAxis_Left;

}

////////////////////////////////////////////////////////////////////////

Enemy::~Enemy()
{
    
}

////////////////////////////////////////////////////////////////////////

void Enemy::Update(float dt)
{
	PhysicsObject::Update(dt);

	if ((xState == OnWallLeft || xState == OnWallRight) && yState == OnGround)
	{
		Jump();
	}

	velocity.x = movementAxis.x * movementSpeed;
}

////////////////////////////////////////////////////////////////////////

void Enemy::Draw(sf::RenderWindow & window)
{
	Object::Draw(window);
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
	Character::CollideWith(physicsObject);
}

////////////////////////////////////////////////////////////////////////