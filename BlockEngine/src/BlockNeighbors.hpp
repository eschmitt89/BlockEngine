//
//  BlockNeighbors.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef BlockNeighbors_hpp
#define BlockNeighbors_hpp

#include "BlockType.hpp"

using namespace std;

struct BlockNeighbors
{
	BlockNeighbors()
	{
		TopLeft = Top = TopRight = Left = Right = BottomLeft = Bottom = BottomRight = BlockType::NoBlock;
	}

	BlockType TopLeft;
	BlockType Top;
	BlockType TopRight;
	BlockType Left;
	BlockType Right;
	BlockType BottomLeft;
	BlockType Bottom;
	BlockType BottomRight;
};

#endif /* BlockNeighbors_hpp */
