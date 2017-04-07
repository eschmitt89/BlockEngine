#ifndef Character_hpp
#define Character_hpp

#include "PhysicsObject.hpp"
#include "MovementAxis.hpp"
#include "MovementState.hpp"
#include "ResourceManager.hpp"


using namespace std;

class Character : public PhysicsObject
{
public:
	Character(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
    virtual ~Character();

protected:
	int level;

	int health;

	float jumpPower;
	float movementSpeed;
	MovementAxis movementAxis;
	MovementState movementState;

	

	void Jump();

	sf::Text debugText;
	void UpdateDebugText();

};

#endif /* Character_hpp */
