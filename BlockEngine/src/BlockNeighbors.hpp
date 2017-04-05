#ifndef BlockNeighbors_hpp
#define BlockNeighbors_hpp

#include "BlockType.hpp"

using namespace std;

class BlockNeighbors
{
public:
	BlockNeighbors();
    ~BlockNeighbors();

	BlockType TopLeft;
	BlockType Top;
	BlockType TopRight;
	BlockType Left;
	BlockType Right;
	BlockType BottomLeft;
	BlockType Bottom;
	BlockType BottomRight;

private:

};

#endif /* BlockNeighbors_hpp */
