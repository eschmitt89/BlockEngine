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
#include "Block.hpp"
#include "Camera.hpp"
#include "Utilities.hpp"
#include <vector>

using namespace std;

class Grid
{
public:
    Grid(int columns, int rows, int blockWidth, int blockHeight);
	Grid(string fileName, int blockWidth, int blockHeight);
    ~Grid();
    
    void Draw(sf::RenderWindow& window, Camera* camera);
    
	Block GetBlock(int column, int row);
	int GetBlockKey(int column, int row);
	sf::Vector2f GetBlockPosition(int column, int row);
	sf::Vector2i GetBlockIndex(sf::Vector2f position);
	Vector4i GetBlockIndicies(sf::Vector2f position, sf::Vector2f size);

	void SetBlockType(sf::Vector2f position, BlockType blockType);

	bool IsValidBlockIndex(int column, int row);
	bool IsValidBlockIndex(sf::Vector2i blockIndex);
	bool IsValidNonEmptyBlockIndex(int column, int row);

private:
    vector<vector<BlockType>> blocks;
	sf::Vector2i dimensions;
	sf::Vector2f blockSize;

	void Save(string fileName);

	sf::Color BlockTypeToColor(BlockType blockType);
	BlockType ColorToBlockType(sf::Color color);

};

#endif /* Grid_hpp */
