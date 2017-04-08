#ifndef Clickable_hpp
#define Clickable_hpp

#include <SFML/Graphics.hpp>
#include "EventManager.hpp"
#include "MouseState.hpp"
#include "Utilities.hpp"

using namespace std;

class Clickable
{
public:
	Clickable(sf::Vector2f position, sf::Vector2f size);
	~Clickable();

	void Update(float dt);
	void HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

protected:
	virtual void LeftPressed();
	virtual void RightPressed();
	virtual void MiddlePressed();

	virtual void LeftClick();
	virtual void RightClick();
	virtual void MiddleClick();

private:
	sf::RectangleShape hitBox;
	MouseState mouseState;

	bool mouseHover;
	bool mouseLeftPressedInside;
	bool mouseRightPressedInside;
	bool mouseMiddlePressedInside;
};

#endif /* Clickable_hpp */