#ifndef Clickable_hpp
#define Clickable_hpp

#include <SFML/Graphics.hpp>
#include "MouseState.hpp"

using namespace std;

class Clickable
{
public:
	Clickable(sf::Vector2f position, sf::Vector2f size);
	~Clickable();

	void Update(float dt);
	void HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	virtual void LeftClick();
	virtual void RightClick();

private:
	sf::RectangleShape hitBox;
	MouseState mouseState;

	bool mouseHover;
	bool mouseLeftPressedInside;
	bool mouseRightPressedInside;

};

#endif /* Clickable_hpp */