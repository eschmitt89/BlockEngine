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
#include "PhysicsManager.hpp"

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
	PhysicsManager* physicsManager;

	sf::Text fpsText;

	string GetFpsString(float dt);
};

#endif /* HomeScreen_hpp */
