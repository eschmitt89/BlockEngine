//
//  EventManager.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <SFML/Window.hpp>
#include <set>

using namespace std;

class EventManager
{
public:
	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}
    ~EventManager();

	void HandleEvent(sf::Event event);
	void ClearEvents();

	bool IsKeyJustPressed(sf::Keyboard::Key key);
	bool IsKeyPressed(sf::Keyboard::Key key);
	bool IsKeyReleased(sf::Keyboard::Key key);

	bool IsMouseButtonPressed(sf::Mouse::Button button);
	bool IsMouseButtonReleased(sf::Mouse::Button button);
    
private:
	EventManager() {};
	EventManager(EventManager const &);
	void operator = (EventManager const &);

	set<sf::Keyboard::Key> keysPressed;
	set<sf::Keyboard::Key> keysReleased;
	set<sf::Mouse::Button> buttonsReleased;
};

#endif /* EventManager_hpp */
