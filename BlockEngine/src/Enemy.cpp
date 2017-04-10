#include "Enemy.hpp"
#include "Utilities.hpp"

Enemy::Enemy(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, Character* target)
	:Character(texture, position, size, 1, 200)
{
	this->target = target;
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 100;
	movementState = MovementState_None;
	movementAxis.x = XAxis_Left;

	state = EnemyState_Patrol;

	fleeHealthPercent = 0.2;
	aggroRange = 300;

}

////////////////////////////////////////////////////////////////////////

Enemy::~Enemy()
{
    
}

////////////////////////////////////////////////////////////////////////

void Enemy::Update(float dt)
{
	Character::Update(dt);

	if (state == EnemyState_Patrol)
	{
		float distanceToTarget = Distance(GetCenter(), target->GetCenter());

		if (distanceToTarget <= aggroRange)
		{
			state = EnemyState_Chase;
		}
	}
	else if (state == EnemyState_Chase)
	{
		if (target->GetPosition().x + target->GetSize().x < position.x)
		{
			movementAxis.x = XAxis_Left;
		}
		else if (target->GetPosition().x > position.x + size.x)
		{
			movementAxis.x = XAxis_Right;
		}
		else
		{
			movementAxis.x = XAxis_None;
		}

		if (target->GetPosition().y < position.y - 64 && yState == OnGround)
		{
			Jump();
		}

		if (GetHealthPercent() <= fleeHealthPercent)
		{
			state = EnemyState_Flee;
		}
	}
	else if (state == EnemyState_Flee)
	{
		if (target->GetCenter().x < GetCenter().x)
		{
			movementAxis.x = XAxis_Right;
		}
		else
		{
			movementAxis.x = XAxis_Left;
		}
	}

	if ((xState == OnWallLeft || xState == OnWallRight) && yState == OnGround)
	{
		Jump();
	}
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
