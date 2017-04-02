//
//  BlockType.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef BlockType_hpp
#define BlockType_hpp

enum BlockType
{
	BlockType_None = 'x',
	BlockType_Empty = '0',
	BlockType_Solid = '1',
	BlockType_Liquid = '2',
	BlockType_LiquidTop = '3',
	BlockType_Ladder = '4',
	BlockType_LadderTop = '5',
	BlockType_LadderBottom = '6',
	BlockType_Corner = '7',
	BlockType_Platform = '8'
};

#endif /* BlockType_hpp */

