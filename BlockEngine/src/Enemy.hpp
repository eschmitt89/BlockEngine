#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"
#include "EnemyState.hpp"

using namespace std;

class Enemy : public Character
{
public:
	Enemy(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size, Character* target);
	virtual ~Enemy();
    
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual void ResolveBlockCollisionX(Block block, float dt);
	virtual void ResolveBlockCollisionY(Block block, float dt);
	virtual void CollideWith(PhysicsObject* physicsObject);

private:
	EnemyState state;
	Character* target;

	float fleeHealthPercent;
	float aggroRange;
};

#endif /* Enemy_hpp */
