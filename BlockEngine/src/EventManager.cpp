//
//  EventManager.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "EventManager.hpp"

EventManager::~EventManager()
{

}

////////////////////////////////////////////////////////////////////////

void EventManager::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyReleased:
			keysReleased.insert(event.key.code);
			break;
		case sf::Event::MouseButtonReleased:
			buttonsReleased.insert(event.mouseButton.button);
		break;
		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////

void EventManager::ClearEvents()
{
	keysReleased.clear();
	buttonsReleased.clear();
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsKeyReleased(sf::Keyboard::Key key)
{
	return keysReleased.find(key) != keysReleased.end();
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsMouseButtonPressed(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsMouseButtonReleased(sf::Mouse::Button button)
{
	return buttonsReleased.find(button) != buttonsReleased.end();
}
