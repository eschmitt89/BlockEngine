//
//  Player.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "PhysicsObject.hpp"
#include "XMovementAxis.hpp"
#include "YMovementAxis.hpp"
#include "PlayerState.hpp"

using namespace std;

class Player : public PhysicsObject
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
	float jumpPower;
	float movementSpeed;
	float climbSpeed;
	XMovementAxis xMovementAxis;
	YMovementAxis yMovementAxis;
	PlayerState playerState;

	sf::Text debugText;
	void UpdateDebugText();
};

#endif /* Player_hpp */
