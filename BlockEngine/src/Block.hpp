//
//  Block.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <SFML/Graphics.hpp>
#include "BlockType.hpp"

using namespace std;

class Block
{
public:
	Block(BlockType type, sf::Vector2f position, sf::Vector2f size);
    ~Block();

	BlockType GetType();
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	sf::FloatRect GetGlobalBounds();

private:
	BlockType type;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::FloatRect globalBounds;
};

#endif /* Block_hpp */
