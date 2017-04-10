#ifndef Attack_hpp
#define Attack_hpp

#include "PhysicsObject.hpp"

using namespace std;

class Attack : public PhysicsObject
{
public:
	Attack(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, int damage);
    virtual ~Attack();
	virtual ObjectType GetObjectType() { return ObjectType_Attack; }

	int GetDamage();

private:
	int damage;

};

#endif /* Attack_hpp */
