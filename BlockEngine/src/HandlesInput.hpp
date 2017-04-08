#ifndef HandlesInput_hpp
#define HandlesInput_hpp

#include <SFML/Graphics.hpp>

class HandlesInput
{
public:
	virtual void HandleInput(const sf::RenderWindow& window) = 0;
	
private:
};

#endif /* HandlesInput_hpp */