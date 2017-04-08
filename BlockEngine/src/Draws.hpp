#ifndef Draws_hpp
#define Draws_hpp

#include <SFML/Graphics.hpp>

class Draws
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;

};

#endif /* Draws_hpp */