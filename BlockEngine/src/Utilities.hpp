//
//  Utilties.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Utilties_hpp
#define Utilties_hpp

#include <SFML/Graphics.hpp>

using namespace std;

inline sf::Vector2f GetMousePosition(const sf::RenderWindow& window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

////////////////////////////////////////////////////////////////////////

inline bool Intersect(const sf::Vector2f& position1, const sf::Vector2f& size1, const sf::Vector2f& position2, const sf::Vector2f& size2)
{
	return (position1.x + size1.x > position2.x && position1.x < position2.x + size2.x && position1.y + size1.y > position2.y && position1.y < position2.y + size2.y);
}

////////////////////////////////////////////////////////////////////////

inline bool Intersect(const sf::Vector2i& position1, const sf::Vector2i& size1, const sf::Vector2i& position2, const sf::Vector2i& size2)
{
	return (position1.x + size1.x > position2.x && position1.x < position2.x + size2.x && position1.y + size1.y > position2.y && position1.y < position2.y + size2.y);
}

////////////////////////////////////////////////////////////////////////

float inline VectorLength(const sf::Vector2f vector)
{
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f inline NormalizeVector(const sf::Vector2f& vector)
{
	float vectorLength = VectorLength(vector);
	if (!vectorLength) return sf::Vector2f();
	return vector / vectorLength;
}

////////////////////////////////////////////////////////////////////////

float inline DotProduct(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

////////////////////////////////////////////////////////////////////////

float inline Distance(sf::Vector2f position1, sf::Vector2f position2)
{
	return sqrt(((position2.x - position1.x)*(position2.x - position1.x)) + ((position2.y - position1.y)*(position2.y - position1.y)));
}

////////////////////////////////////////////////////////////////////////

float inline AbsoluteDistance(sf::Vector2f position1, sf::Vector2f position2)
{
	return abs(Distance(position1, position2));
}

////////////////////////////////////////////////////////////////////////

int inline Random(int min, int max)
{
	int diff = max - min + 1;

	return (rand() % diff) + min;
}


////////////////////////////////////////////////////////////////////////

float inline Random()
{
	return (float)rand() / INT_MAX;
}

////////////////////////////////////////////////////////////////////////
struct Vector4i 
{
	int x1;
	int y1;
	int x2;
	int y2;

	Vector4i(sf::Vector2i vector1, sf::Vector2i vector2)
	{
		x1 = vector1.x;
		y1 = vector1.y;
		x2 = vector2.x;
		y2 = vector2.y;
	}
};

#endif /* Utilties_hpp */
