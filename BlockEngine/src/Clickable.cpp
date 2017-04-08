#include "Clickable.hpp"
#include "Utilities.hpp"

Clickable::Clickable(sf::Vector2f position, sf::Vector2f size)
{
	mouseState = MouseState_Default;
	hitBox.setPosition(position);
	hitBox.setSize(size);
}

////////////////////////////////////////////////////////////////////////

Clickable::~Clickable()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::Update(float dt)
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::HandleInput(const sf::RenderWindow & window)
{
	if (Intersect(GetMousePosition(window), sf::Vector2f(1, 1), hitBox.getPosition(), hitBox.getSize()))
	{
		mouseState = MouseState_Hover;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mouseState = MouseState_PressedLeft;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			mouseState = MouseState_PressedRight;
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Clickable::Draw(sf::RenderWindow & window)
{
	window.draw(hitBox);
}
