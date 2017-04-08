#include "Character.hpp"
#include "Coin.hpp"
#include "EventManager.hpp"
#include "ItemPhysicsObject.hpp"
#include "Utilities.hpp"
#include <sstream>

Character::Character(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, int level, int health)
	:PhysicsObject(texture, position, size)
{
	this->level = level;
	this->health = health;

	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	movementState = MovementState_None;
}

////////////////////////////////////////////////////////////////////////

Character::~Character()
{
    
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
	health -= damage;

	if (health <= 0)
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

