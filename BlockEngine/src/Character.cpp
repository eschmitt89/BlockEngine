#include "Character.hpp"
#include "Coin.hpp"
#include "EventManager.hpp"
#include "ItemPhysicsObject.hpp"
#include "Utilities.hpp"

Character::Character(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, int level, int health)
	:PhysicsObject(texture, position, size)
{
	this->level = level;
	this->currentHealth = health;
	this->totalHealth = health;

	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	movementState = MovementState_None;

	attacking = false;
	attackSpeed = 1;
	attackTimer = attackSpeed;
}

////////////////////////////////////////////////////////////////////////

Character::~Character()
{
    
}

////////////////////////////////////////////////////////////////////////

void Character::Update(float dt)
{
	PhysicsObject::Update(dt);

	if (attacking)
	{
		attackTimer -= dt;

		if (attackTimer <= 0)
		{
			Spawn(new Attack(ResourceManager::GetInstance().GetTexture("redX"), sf::Vector2f(position.x + size.x + 5, position.y), size, 50));
			attackTimer = attackSpeed;
		}
	}

	velocity.x = movementAxis.x * movementSpeed;
}

////////////////////////////////////////////////////////////////////////

void Character::CollideWith(PhysicsObject * physicsObject)
{
	if (physicsObject->GetObjectType() == ObjectType_Attack)
	{
		Attack* attack = (Attack*)physicsObject;
		RecieveDamage(attack->GetDamage());
	}
}

////////////////////////////////////////////////////////////////////////

void Character::RecieveDamage(int damage)
{
	currentHealth -= damage;

	if (currentHealth <= 0)
	{
		Die();
	}
}

////////////////////////////////////////////////////////////////////////

void Character::Jump()
{
	Impulse(sf::Vector2f(0, -jumpPower));
}

////////////////////////////////////////////////////////////////////////

void Character::Die()
{
	expired = true;
}

float Character::GetHealthPercent()
{
	return currentHealth / totalHealth;
}

