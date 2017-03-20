//
//  GridLayout.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridLayout.hpp"


GridLayout::GridLayout(vector<vector<LayoutNode>> corridors, vector<LayoutRoom> rooms, sf::Vector2i dimensions)
{
	this->Corridors = corridors;
	this->Rooms = rooms;
	this->Dimensions = dimensions;
}

////////////////////////////////////////////////////////////////////////

GridLayout::~GridLayout()
{

}

////////////////////////////////////////////////////////////////////////



