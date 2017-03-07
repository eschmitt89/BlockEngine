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

inline sf::Vector2f ConvertToVector2f(sf::Vector2i vector2i)
{
	return sf::Vector2f(vector2i.x, vector2i.y);

}

////////////////////////////////////////////////////////////////////////

inline sf::Vector2f GetMousePosition(const sf::RenderWindow& window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
		x2 = vector1.x;
		y2 = vector2.y;
	}
};

#endif /* Utilties_hpp */
