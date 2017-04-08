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

	bool IsKeyPressed(sf::Keyboard::Key key);
	bool IsKeyHeld(sf::Keyboard::Key key);
	bool IsKeyReleased(sf::Keyboard::Key key);

	bool IsMouseButtonPressed(sf::Mouse::Button button);
	bool IsMouseButtonHeld(sf::Mouse::Button button);
	bool IsMouseButtonReleased(sf::Mouse::Button button);
    
private:
	EventManager() {};
	EventManager(EventManager const &);
	void operator = (EventManager const &) { }


	set<sf::Keyboard::Key> keysPressed;
	set<sf::Keyboard::Key> keysHeld;
	set<sf::Keyboard::Key> keysReleased;

	set<sf::Mouse::Button> buttonsPressed;
	set<sf::Mouse::Button> buttonsHeld;
	set<sf::Mouse::Button> buttonsReleased;
};

#endif /* EventManager_hpp */
