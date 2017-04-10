//
//  HomeScreen.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef HomeScreen_hpp
#define HomeScreen_hpp

#include "AbstractScreen.hpp"
#include "Grid.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "PhysicsManager.hpp"
#include "ItemGenerator.hpp"
#include "Clickable.hpp"
#include "InventoryView.hpp"
#include "EnemyManager.hpp"

class HomeScreen : public AbstractScreen
{
public:
    HomeScreen();
    ~HomeScreen();
    bool DoesHandleInput();
    void HandleInput(const sf::RenderWindow& window);
    bool DoesUpdate();
    void Update(float dt);
    bool DoesDraw();
    void Draw(sf::RenderWindow& window);
    
private:
	Grid* grid;
	Camera* camera;
	Player* player;
	PhysicsManager* physicsManager;
	ItemGenerator* itemGenerator;

	sf::Text fpsText;

	int currentItemLevel;

	string GetFpsString(float dt);

	Clickable * clickable;
	InventoryView* inventoryView;

	EnemyManager enemyManager;
};

#endif /* HomeScreen_hpp */
