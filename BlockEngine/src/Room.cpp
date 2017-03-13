//
//  Room.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Room.hpp"

Room::Room(sf::Vector2i position, sf::Vector2i size)
{
	Position = position;
	Size = size;
}

////////////////////////////////////////////////////////////////////////

Room::~Room()
{

}
