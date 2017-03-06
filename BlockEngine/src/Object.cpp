//
//  Object.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Object.hpp"

Object::Object(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
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

void Object::SetSize(sf::Vector2f size)
{
	this->size = size;

	sf::Vector2u textureSize = sprite.getTexture()->getSize();

	sf::Vector2f scale = sf::Vector2f(size.x / textureSize.x, size.y / textureSize.y);

	sprite.setScale(scale);
}

////////////////////////////////////////////////////////////////////////
