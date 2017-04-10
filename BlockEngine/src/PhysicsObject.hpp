#ifndef PhysicsObject_hpp
#define PhysicsObject_hpp

#include "Object.hpp"
#include "Block.hpp"
#include "XState.hpp"
#include "YState.hpp"

class PhysicsObject : public Object
{
public:
	PhysicsObject(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	PhysicsObject(sf::Vector2f position, sf::Vector2f size) : PhysicsObject(nullptr, position, size) { }
	PhysicsObject(const sf::Texture* texture, sf::Vector2f position) : PhysicsObject(texture, position, (sf::Vector2f)texture->getSize()) { }
    virtual ~PhysicsObject();
	virtual ObjectType GetObjectType() { return ObjectType_PhysicsObject; }

	virtual void Update(float dt);

	void UpdateX(float dt);
	void UpdateY(float dt);

	void Impulse(sf::Vector2f vector);

	sf::Vector2f GetVelocity();
	float GetElasticity();
	float GetMass();
	bool GetCollidesWithPhysicsObjects();
	bool GetExpired();

	void SetExpired(bool expired);

	virtual void ResolveBlockCollisionX(vector<vector<Block>> blocks, float dt);
	virtual void ResolveBlockCollisionY(vector<vector<Block>> blocks, float dt);

	virtual void ResolveBlockCollisionX(Block block, float dt);
	virtual void ResolveBlockCollisionY(Block block, float dt);
	virtual void CollideWith(PhysicsObject* physicsObject);

	typedef void(*ResolveBlockCollision)(PhysicsObject* physicsObject, Block block, float dt);

	static void ResolveBlockCollisionXFunction(PhysicsObject* physicsObject, Block block, float dt);
	static void ResolveBlockCollisionYFunction(PhysicsObject* physicsObject, Block block, float dt);

	void SpawnPhysicsObjects(vector<PhysicsObject*>& physicsManagerObjects);

protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f friction;
	float elasticity;
	float mass;
	float gravity;

	XState xState;
	YState yState;

	bool collidesWithPhysicsObjects;
	bool expired;

	vector<PhysicsObject*> spawnedPhysicsObjects;

	void Spawn(PhysicsObject* physicsObject);
};

#endif /* PhysicsObject_hpp */
