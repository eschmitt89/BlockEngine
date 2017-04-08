#include "Clickable.hpp"

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
	mouseState = MouseState_Default;

	if (mouseHover)
	{
		mouseState = MouseState_Hover;

		if (mouseLeftPressedInside || mouseRightPressedInside || mouseMiddlePressedInside)
		{
			mouseState = MouseState_Pressed;
		}
	}

	switch (mouseState)
	{
	case MouseState_Default:
		hitBox.setFillColor(sf::Color::Red);
		break;
	case MouseState_Hover:
		hitBox.setFillColor(sf::Color::Blue);
		break;
	case MouseState_Pressed:
		hitBox.setFillColor(sf::Color::Green);
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////

void Clickable::HandleInput(const sf::RenderWindow & window)
{
	mouseHover = Intersect(GetMousePosition(window), sf::Vector2f(1, 1), hitBox.getPosition(), hitBox.getSize());

	if (EventManager::GetInstance().IsMouseButtonPressed(sf::Mouse::Left))
	{
		if (mouseHover && !mouseRightPressedInside && !mouseMiddlePressedInside)
		{
			LeftPressed();
			mouseLeftPressedInside = true;
		}
	}
	if (EventManager::GetInstance().IsMouseButtonReleased(sf::Mouse::Left))
	{
		if (mouseHover && mouseLeftPressedInside)
		{
			LeftClick();
		}
		mouseLeftPressedInside = false;
	}

	if (EventManager::GetInstance().IsMouseButtonPressed(sf::Mouse::Right))
	{
		if (mouseHover && !mouseLeftPressedInside && !mouseMiddlePressedInside)
		{
			RightPressed();
			mouseRightPressedInside = true;
		}
	}
	if (EventManager::GetInstance().IsMouseButtonReleased(sf::Mouse::Right))
	{
		if (mouseHover && mouseRightPressedInside)
		{
			RightClick();
		}
		mouseRightPressedInside = false;
	}

	if (EventManager::GetInstance().IsMouseButtonPressed(sf::Mouse::Middle))
	{
		if (mouseHover && !mouseLeftPressedInside && !mouseRightPressedInside)
		{
			MiddlePressed();
			mouseMiddlePressedInside = true;
		}
	}
	if (EventManager::GetInstance().IsMouseButtonReleased(sf::Mouse::Middle))
	{
		if (mouseHover && mouseMiddlePressedInside)
		{
			MiddleClick();
		}
		mouseMiddlePressedInside = false;
	}
}

////////////////////////////////////////////////////////////////////////

void Clickable::Draw(sf::RenderWindow & window)
{
	window.draw(hitBox);
}

////////////////////////////////////////////////////////////////////////

void Clickable::LeftPressed()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::RightPressed()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::MiddlePressed()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::LeftClick()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::RightClick()
{

}

////////////////////////////////////////////////////////////////////////

void Clickable::MiddleClick()
{

}
