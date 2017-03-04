//
//  Camera.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(sf::Vector2f center, sf::Vector2f size);
    ~Camera();

	void HandleInput(const sf::RenderWindow& window);

	void Move(float offsetX, float offsetY);

	sf::View GetView();
    
private:
	sf::View view;
	float moveSpeed;
};

#endif /* Camera_hpp */
