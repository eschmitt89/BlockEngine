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
	void Update(float dt);

	void Move(float offsetX, float offsetY);
	void SetCenter(sf::Vector2f center);
	void Zoom(float factor);

	sf::View GetView();
    
private:
	sf::View view;
	float moveSpeed;
	float zoomSpeed;
	sf::Vector2i moveAxis;
};

#endif /* Camera_hpp */
