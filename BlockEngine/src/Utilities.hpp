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
#include <Windows.h>

using namespace std;

inline sf::Vector2f ConvertToVector2f(sf::Vector2i vector2i)
{
	return sf::Vector2f(vector2i.x, vector2i.y);

}
inline sf::Vector2f GetMousePosition(const sf::RenderWindow& window)
{
	return ConvertToVector2f(sf::Mouse::getPosition(window));
}

inline void WriteLine(string line)
{
	line += "\r\n";
	wstring stemp = wstring(line.begin(), line.end());
	LPCWSTR sw = stemp.c_str();
	OutputDebugString(sw);
}




#endif /* Utilties_hpp */
