//
//  Grid.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Grid.hpp"
#include <iostream>


Grid::Grid(int rows, int columns, int blockWidth, int blockHeight)
{
	this->gridDimensions = sf::Vector2i(columns, rows);
	this->blockSize = sf::Vector2i(blockWidth, blockHeight);

    for (int column = 0; column < columns; column++)
    {
        vector<BlockType> blockColumn;
        
        for (int row = 0; row < rows; row++)
        {
            blockColumn.push_back(BlockType::Solid);
        }
        
        blocks.push_back(blockColumn);
    }
}

////////////////////////////////////////////////////////////////////////

Grid::~Grid()
{
    
}

////////////////////////////////////////////////////////////////////////

void Grid::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(20,20));
	block.setOutlineColor(sf::Color::Red);
	block.setOutlineThickness(1);
    
    for (int column = 0; column < blocks.size(); column++)
    {
        for (int row = 0; row < blocks[column].size(); row++)
        {
			if (blocks[column][row] != BlockType::Empty)
			{
				block.setPosition(GetBlockPosition(row, column));
				window.draw(block);
			}
        }
    }
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f Grid::GetBlockPosition(int row, int column)
{
	return sf::Vector2f(row * blockSize.y, column * blockSize.x);
}

////////////////////////////////////////////////////////////////////////

sf::Vector2i Grid::GetBlockIndex(sf::Vector2f position)
{
	cout << "position: " << position.y << ", " << position.x << endl;
	cout << "index: " << position.y / blockSize.y << ", " << position.x / blockSize.x << endl;
	return sf::Vector2i(position.y / blockSize.y, position.x / blockSize.x);
}
