//
//  Grid.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Grid.hpp"


Grid::Grid(int rows, int columns, int blockWidth, int blockHeight)
{
	this->dimensions = sf::Vector2i(columns, rows);
	this->blockSize = sf::Vector2f(blockWidth, blockHeight);

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
    block.setSize(blockSize);
	block.setOutlineColor(sf::Color::Red);
	block.setOutlineThickness(1);
    
    for (int column = 0; column < blocks.size(); column++)
    {
        for (int row = 0; row < blocks[column].size(); row++)
        {
			if (blocks[column][row] != BlockType::Empty)
			{
				block.setPosition(GetBlockPosition(column, row));
				window.draw(block);
			}
        }
    }
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f Grid::GetBlockPosition(int column, int row)
{
	return sf::Vector2f(column * blockSize.x, row * blockSize.y);
}

////////////////////////////////////////////////////////////////////////

sf::Vector2i Grid::GetBlockIndex(sf::Vector2f position)
{
	return sf::Vector2i(position.x / blockSize.x, position.y / blockSize.y);
}

////////////////////////////////////////////////////////////////////////

Vector4i Grid::GetBlockIndicies(sf::Vector2f position, sf::Vector2f size)
{
	return Vector4i(GetBlockIndex(position), GetBlockIndex(position + size));
}

////////////////////////////////////////////////////////////////////////

sf::FloatRect Grid::GetBlockGlobalBounds(int column, int row)
{
	return sf::FloatRect(GetBlockPosition(column, row), blockSize);
}

////////////////////////////////////////////////////////////////////////

int Grid::GetBlockKey(int column, int row)
{
	return (column * dimensions.x) + row;
}

////////////////////////////////////////////////////////////////////////

BlockType Grid::GetBlockType(sf::Vector2f position)
{
	sf::Vector2i blockIndex = GetBlockIndex(position);

	if (IsValidBlockIndex(blockIndex))
	{
		return blocks[blockIndex.x][blockIndex.y];
	}
}

////////////////////////////////////////////////////////////////////////

void Grid::SetBlockType(sf::Vector2f position, BlockType blockType)
{
	sf::Vector2i blockIndex = GetBlockIndex(position);

	if (IsValidBlockIndex(blockIndex))
	{
		blocks[blockIndex.x][blockIndex.y] = blockType;
	}
}

////////////////////////////////////////////////////////////////////////

bool Grid::IsValidBlockIndex(int x, int y)
{
	return x >= 0 && y >= 0 && x < dimensions.x && y < dimensions.y;
}

////////////////////////////////////////////////////////////////////////

bool Grid::IsValidBlockIndex(sf::Vector2i blockIndex)
{
	return IsValidBlockIndex(blockIndex.x, blockIndex.y);
}

////////////////////////////////////////////////////////////////////////

bool Grid::IsValidNonEmptyBlockIndex(int x, int y)
{
	return IsValidBlockIndex(x, y) && blocks[x][y] != BlockType::Empty;
}

