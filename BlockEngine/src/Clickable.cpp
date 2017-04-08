#include "Clickable.hpp"
#include "EventManager.hpp"
#include "Utilities.hpp"


Clickable::Clickable(sf::Vector2f position, sf::Vector2f size)
{
	mouseState = MouseState_Default;
	hitBox.setPosition(position);
	hitBox.setSize(size);

	mouseHover = false;
	mouseLeftPressedInside = false;
	mouseRightPressedInside = false;
}

////////////////////////////////////////////////////////////////////////

Clickable::~Clickable()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::Update(float dt)
{
	//mouseState = MouseState_Default;

	//if (mouseHover)
	//{
	//	mouseState = MouseState_Hover;

	//	if (mouseLeftPressedInside || mouseRightPressedInside)
	//	{
	//		mouseState = MouseState_Pressed;
	//	}
	//}

	if (mouseState == MouseState_Default)
	{
		hitBox.setFillColor(sf::Color::Red);
	}
	if (mouseState == MouseState_Hover)
	{
		hitBox.setFillColor(sf::Color::Blue);
	}
	if (mouseState == MouseState_Pressed)
	{
		hitBox.setFillColor(sf::Color::Green);
	}
	if (mouseState == MouseState_Released)
	{
		hitBox.setFillColor(sf::Color::Magenta);
	}
}

////////////////////////////////////////////////////////////////////////

void Clickable::HandleInput(const sf::RenderWindow & window)
{
	mouseHover = Intersect(GetMousePosition(window), sf::Vector2f(1, 1), hitBox.getPosition(), hitBox.getSize());

	mouseState = mouseHover ? MouseState_Hover : MouseState_Default;

	if (EventManager::GetInstance().IsMouseButtonPressed(sf::Mouse::Left))
	{
		if (mouseHover)
		{
			mouseLeftPressedInside = true;
		}
	}
	if (EventManager::GetInstance().IsMouseButtonReleased(sf::Mouse::Left))
	{
		if (mouseHover && mouseLeftPressedInside)
		{
			LeftClick();
			mouseState = MouseState_Released;
		}
		mouseLeftPressedInside = false;
	}

	if (EventManager::GetInstance().IsMouseButtonPressed(sf::Mouse::Right))
	{
		if (mouseHover)
		{
			mouseRightPressedInside = true;
		}
	}
	if (EventManager::GetInstance().IsMouseButtonReleased(sf::Mouse::Right))
	{
		if (mouseHover && mouseRightPressedInside)
		{
			RightClick();
			mouseState = MouseState_Released;
		}
		mouseRightPressedInside = false;
	}

	if (mouseLeftPressedInside || mouseRightPressedInside)
	{
		mouseState = MouseState_Pressed;
	}
}

////////////////////////////////////////////////////////////////////////

void Clickable::Draw(sf::RenderWindow & window)
{
	window.draw(hitBox);
}

////////////////////////////////////////////////////////////////////////

void Clickable::LeftClick()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::RightClick()
{

}