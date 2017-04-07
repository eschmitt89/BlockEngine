#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"

using namespace std;

class Enemy : public Character
{
public:
	Enemy(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
    virtual ~Enemy();
    
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual void ResolveBlockCollisionX(Block block, float dt) = 0;
	virtual void ResolveBlockCollisionY(Block block, float dt) = 0;
	virtual void CollideWith(PhysicsObject* physicsObject) = 0;

private:
	float jumpPower;
	float movementSpeed;
	MovementAxis movementAxis;
	MovementState movementState;

	void Jump();

	sf::Text debugText;
	void UpdateDebugText();

};

#endif /* Enemy_hpp */
