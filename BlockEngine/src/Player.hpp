//
//  Player.hpp
#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"
#include "KeyBindings.hpp"
#include "MovementAxis.hpp"
#include "MovementState.hpp"
#include "ItemCollection.hpp"
#include "EquipmentCollection.hpp"

using namespace std;

class Player : public Character
{
public:
	Player(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
    ~Player();
    
	void Update(float dt);
	void HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	void ResolveBlockCollisionX(Block block, float dt);
	void ResolveBlockCollisionY(Block block, float dt);
	void CollideWith(PhysicsObject* physicsObject);

private:
	float climbSpeed;

	bool jumpKeyHeld;

	void GravityOn();
	void GravityOff();

	sf::Text debugText;
	void UpdateDebugText();

	int coins;
	ItemCollection* inventory;
	EquipmentCollection equipment;
};

#endif /* Player_hpp */
