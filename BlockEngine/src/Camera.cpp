//
//  Camera.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(sf::Vector2f center, sf::Vector2f size)
{
	this->view = sf::View(center, size);
	this->moveSpeed = 1;
}

////////////////////////////////////////////////////////////////////////

Camera::~Camera()
{
    
}

////////////////////////////////////////////////////////////////////////

void Camera::HandleInput(const sf::RenderWindow & window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Move(-moveSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Move(moveSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Move(0, -moveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Move(0, moveSpeed);
	}
}

////////////////////////////////////////////////////////////////////////

void Camera::Move(float offsetX, float offsetY)
{
	view.move(offsetX, offsetY);
}

////////////////////////////////////////////////////////////////////////

sf::View Camera::GetView()
{
	return view;
}