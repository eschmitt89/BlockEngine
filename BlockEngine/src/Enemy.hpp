#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"

using namespace std;

class Enemy : public Character
{
public:
	Enemy(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	virtual ~Enemy();
    
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual void ResolveBlockCollisionX(Block block, float dt);
	virtual void ResolveBlockCollisionY(Block block, float dt);
	virtual void CollideWith(PhysicsObject* physicsObject);

private:

};

#endif /* Enemy_hpp */
