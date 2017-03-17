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
	this->moveSpeed = 200;
}

////////////////////////////////////////////////////////////////////////

Camera::~Camera()
{
    
}

////////////////////////////////////////////////////////////////////////

void Camera::HandleInput(const sf::RenderWindow & window)
{
	moveAxis = sf::Vector2i();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moveAxis.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moveAxis.x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moveAxis.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveAxis.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveAxis.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveAxis.y = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
	{
		Zoom(1.01f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		Zoom(0.99f);
	}
}

void Camera::Update(float dt)
{
	Move(moveAxis.x * moveSpeed * dt, moveAxis.y * moveSpeed * dt);
}

////////////////////////////////////////////////////////////////////////

void Camera::Move(float offsetX, float offsetY)
{
	view.move(offsetX, offsetY);
}

////////////////////////////////////////////////////////////////////////

void Camera::SetCenter(sf::Vector2f center)
{
	view.setCenter(center);
}

////////////////////////////////////////////////////////////////////////

void Camera::Zoom(float factor)
{
	view.zoom(factor);
}

////////////////////////////////////////////////////////////////////////

sf::View Camera::GetView()
{
	return view;
}