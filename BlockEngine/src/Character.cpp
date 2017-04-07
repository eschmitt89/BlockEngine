#include "Character.hpp"
#include "GoldCoin.hpp"
#include "EventManager.hpp"
#include "ItemPhysicsObject.hpp"
#include "Utilities.hpp"
#include <sstream>

Character::Character(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
	:PhysicsObject(texture, position, size)
{
	friction = sf::Vector2f(1, 0);
	elasticity = 0;

	jumpPower = 450;
	movementSpeed = 150;
	movementState = MovementState_None;

	debugText = sf::Text("debug", *ResourceManager::GetInstance().GetFont("font"));
	debugText.setFillColor(sf::Color::Red);
	debugText.setOrigin(sf::Vector2f(-30, 30));

}

////////////////////////////////////////////////////////////////////////

Character::~Character()
{
    
}

////////////////////////////////////////////////////////////////////////

void Character::Jump()
{
	Impulse(sf::Vector2f(0, -jumpPower));
}

////////////////////////////////////////////////////////////////////////

void Character::UpdateDebugText()
{
	stringstream ss;

	debugText.setString(ss.str());
	debugText.setPosition(position);
}
