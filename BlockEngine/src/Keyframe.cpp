//
//  Keyframe.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "SFML/Graphics.hpp"
#include "Keyframe.hpp"

template<typename T>
Keyframe<T>::Keyframe(float key, const T & value)
{
	this->key = key;
	this->value = value;
}

////////////////////////////////////////////////////////////////////////

template<typename T>
Keyframe<T>::~Keyframe()
{

}

////////////////////////////////////////////////////////////////////////

template class Keyframe<sf::Vector2f>;
template class Keyframe<sf::Color>;