//
//  GridRoom.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridRoom.hpp"

GridRoom::GridRoom(sf::Vector2i position, sf::Vector2i size)
{
	this->position = position;
	this->size = size;
}

////////////////////////////////////////////////////////////////////////

GridRoom::~GridRoom()
{

}

////////////////////////////////////////////////////////////////////////

