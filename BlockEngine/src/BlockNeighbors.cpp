//
//  BlockNeighbors.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "BlockNeighbors.hpp"

BlockNeighbors::BlockNeighbors()
{
	TopLeft = BlockType::NoBlock;
	Top = BlockType::NoBlock;
	TopRight = BlockType::NoBlock;
	Left = BlockType::NoBlock;
	Right = BlockType::NoBlock;
	BottomLeft = BlockType::NoBlock;
	Bottom = BlockType::NoBlock;
	BottomRight = BlockType::NoBlock;
}

////////////////////////////////////////////////////////////////////////

BlockNeighbors::~BlockNeighbors()
{
    
}