//
//  Block.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include "Object.hpp"
#include "BlockType.hpp"

using namespace std;

class Block : public Object
{
public:
	Block(BlockType type, sf::Vector2f position, sf::Vector2f size);
    ~Block();

	BlockType GetType();

private:
	BlockType type;

};

#endif /* Block_hpp */
