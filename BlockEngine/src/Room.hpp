//
//  Room.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Room_hpp
#define Room_hpp

#include <SFML/Window.hpp>

using namespace std;

class Room
{
public:
	Room(sf::Vector2i position, sf::Vector2i size);
	~Room();

	sf::Vector2i Position;
	sf::Vector2i Size;
};

#endif /* Room_hpp */
