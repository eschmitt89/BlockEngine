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
    
	sf::Vector2f GetBlockPosition(int column, int row);
	sf::Vector2i GetBlockIndex(sf::Vector2f position);
	Vector4i GetBlockIndicies(sf::Vector2f position, sf::Vector2f size);
	sf::FloatRect GetBlockGlobalBounds(int column, int row);
	int GetBlockKey(int column, int row);

	BlockType GetBlockType(sf::Vector2f position);
	void SetBlockType(sf::Vector2f position, BlockType blockType);

	bool IsValidBlockIndex(int x, int y);
	bool IsValidBlockIndex(sf::Vector2i blockIndex);
	bool IsValidNonEmptyBlockIndex(int x, int y);
	

private:
    vector<vector<BlockType>> blocks;
	sf::Vector2i dimensions;
	sf::Vector2f blockSize;

	


};

#endif /* Grid_hpp */
