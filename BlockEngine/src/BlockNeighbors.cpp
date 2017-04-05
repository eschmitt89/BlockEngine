#include "BlockNeighbors.hpp"

BlockNeighbors::BlockNeighbors()
{
	TopLeft = BlockType::BlockType_None;
	Top = BlockType::BlockType_None;
	TopRight = BlockType::BlockType_None;
	Left = BlockType::BlockType_None;
	Right = BlockType::BlockType_None;
	BottomLeft = BlockType::BlockType_None;
	Bottom = BlockType::BlockType_None;
	BottomRight = BlockType::BlockType_None;
}

////////////////////////////////////////////////////////////////////////

BlockNeighbors::~BlockNeighbors()
{
    
}