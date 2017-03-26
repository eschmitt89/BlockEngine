//
//  GridNode.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridNode.hpp"

GridNode::GridNode(int x , int y, sf::Vector2i dimensions)
{
	index = sf::Vector2i(x, y);

	visited = false;

	leftInvalid = (x == 0);
	rightInvalid = (x == dimensions.x - 1);
	upInvalid = (y == 0);
	downInvalid = (y == dimensions.y - 1);

	leftNode = nullptr;
	rightNode = nullptr;
	upNode = nullptr;
	downNode = nullptr;
}

////////////////////////////////////////////////////////////////////////

GridNode::~GridNode()
{

}

////////////////////////////////////////////////////////////////////////

bool GridNode::AllDirectionsInvalid()
{
	return leftInvalid && rightInvalid && upInvalid && downInvalid;
}

////////////////////////////////////////////////////////////////////////

