//
//  LayoutRoom.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef LayoutRoom_hpp
#define LayoutRoom_hpp

#include <SFML/System.hpp>

using namespace std;

class LayoutRoom
{
public:
	LayoutRoom(sf::Vector2i position, sf::Vector2i size);
	~LayoutRoom();

	sf::Vector2i Position;
	sf::Vector2i Size;
};

#endif /* LayoutRoom_hpp */
