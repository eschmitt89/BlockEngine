#include "EventManager.hpp"

EventManager::~EventManager()
{

}

////////////////////////////////////////////////////////////////////////

void EventManager::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			if (keysHeld.find(event.key.code) == keysHeld.end())
			{
				keysPressed.insert(event.key.code);
			}
			keysHeld.insert(event.key.code);
			break;
		case sf::Event::KeyReleased:
			keysReleased.insert(event.key.code);
			keysHeld.erase(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			if (keysHeld.find(event.key.code) == keysHeld.end())
			{
				buttonsPressed.insert(event.mouseButton.button);
			}
			buttonsHeld.insert(event.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased:
			buttonsReleased.insert(event.mouseButton.button);
			buttonsHeld.erase(event.mouseButton.button);
		break;
		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////

void EventManager::ClearEvents()
{
	keysPressed.clear();
	keysReleased.clear();
	buttonsReleased.clear();
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsKeyPressed(sf::Keyboard::Key key)
{
	return keysPressed.find(key) != keysPressed.end();
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsKeyHeld(sf::Keyboard::Key key)
{
	return keysHeld.find(key) != keysHeld.end();
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

bool EventManager::IsMouseButtonHeld(sf::Mouse::Button button)
{
	return false;
}

////////////////////////////////////////////////////////////////////////

bool EventManager::IsMouseButtonReleased(sf::Mouse::Button button)
{
	return buttonsReleased.find(button) != buttonsReleased.end();
}
