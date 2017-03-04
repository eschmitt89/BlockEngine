//
//  Grid.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <SFML/Graphics.hpp>
#include "BlockType.hpp"
#include "Utilities.hpp"
#include <vector>

using namespace std;

class Grid
{
public:
    Grid(int rows, int columns, int blockWidth, int blockHeight);
    ~Grid();
    
    void Draw(sf::RenderWindow& window);
    
	sf::Vector2f GetBlockPosition(int row, int column);
	sf::Vector2i GetBlockIndex(sf::Vector2f position);

	BlockType GetBlockType(sf::Vector2f position);
	void SetBlockType(sf::Vector2f position, BlockType blockType);

private:
    vector<vector<BlockType>> blocks;
	sf::Vector2i gridDimensions;
	sf::Vector2i blockSize;

	bool IsValidBlockIndex(sf::Vector2i blockIndex);


};

#endif /* Grid_hpp */
