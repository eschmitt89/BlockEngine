#ifndef Character_hpp
#define Character_hpp

#include "PhysicsObject.hpp"
#include "MovementAxis.hpp"
#include "MovementState.hpp"
#include "ResourceManager.hpp"
#include "Attack.hpp"

using namespace std;

class Character : public PhysicsObject
{
public:
	Character(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, int level, int health);
    virtual ~Character();
	virtual ObjectType GetObjectType() { return ObjectType_Character; }

	virtual void CollideWith(PhysicsObject* physicsObject);

protected:
	int level;
	int health;

	float jumpPower;
	float movementSpeed;
	MovementAxis movementAxis;
	MovementState movementState;

	virtual void RecieveDamage(int damage);
	virtual void Jump();
	virtual void Die();

};

#endif /* Character_hpp */
