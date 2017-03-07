//
//  Object.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Object.hpp"

Object::Object(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
{
	sprite.setTexture(*texture);
	SetPosition(position);
	SetSize(size);
}

////////////////////////////////////////////////////////////////////////

Object::~Object()
{
    
}

////////////////////////////////////////////////////////////////////////

void Object::Update(float dt)
{

}

////////////////////////////////////////////////////////////////////////

void Object::Draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}

////////////////////////////////////////////////////////////////////////

sf::FloatRect Object::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f Object::GetPosition()
{
	return position;
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f Object::GetSize()
{
	return size;
}

////////////////////////////////////////////////////////////////////////

void Object::SetPosition(sf::Vector2f position)
{
	this->position = position;
	sprite.setPosition(position);
}

////////////////////////////////////////////////////////////////////////

void Object::SetSize(sf::Vector2f size)
{
	this->size = size;
	sprite.setScale(sf::Vector2f(size.x / sprite.getTexture()->getSize().x, size.y / sprite.getTexture()->getSize().y));
}