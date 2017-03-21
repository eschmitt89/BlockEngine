//
//  GridLayout.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridLayout.hpp"


GridLayout::GridLayout(sf::Vector2i dimensions, vector<LayoutRoom> rooms, vector<sf::Vector2i> doors, vector<sf::Vector2i> ladders, vector<vector<LayoutNode>> corridors)
{
	this->Dimensions = dimensions;
	this->Rooms = rooms;
	this->Doors = doors;
	this->Ladders = ladders;
	this->Corridors = corridors;
}

////////////////////////////////////////////////////////////////////////

GridLayout::~GridLayout()
{

}

////////////////////////////////////////////////////////////////////////



