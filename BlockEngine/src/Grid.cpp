//
//  Grid.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Grid.hpp"
#include "ResourcePath.hpp"

Grid::Grid(int columns, int rows, int blockWidth, int blockHeight)
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

Grid::Grid(string fileName, int blockWidth, int blockHeight)
{
	sf::Image gridImage;
	gridImage.loadFromFile(resourcePath() + fileName);

	this->dimensions = (sf::Vector2i)gridImage.getSize();
	this->blockSize = sf::Vector2f(blockWidth, blockHeight);

	for (int column = 0; column < dimensions.x; column++)
	{
		vector<BlockType> blockColumn;

		for (int row = 0; row < dimensions.y; row++)
		{
			blockColumn.push_back(ColorToBlockType(gridImage.getPixel(column, row)));
		}

		blocks.push_back(blockColumn);
	}
}

////////////////////////////////////////////////////////////////////////

Grid::~Grid()
{
	Save("gridSave.png");
}

////////////////////////////////////////////////////////////////////////

void Grid::Draw(sf::RenderWindow &window, Camera* camera)
{
    sf::RectangleShape block;
    block.setSize(blockSize);
	block.setOutlineThickness(1);

	Vector4i visibleBlocks = GetBlockIndicies(camera->GetView().getCenter() - (camera->GetView().getSize() * 0.5f), camera->GetView().getSize());
    
    for (int column = visibleBlocks.x1; column <= visibleBlocks.x2; column++)
    {
        for (int row = visibleBlocks.y1; row <= visibleBlocks.y2; row++)
        {
			if (IsValidNonEmptyBlockIndex(column, row))
			{
				block.setPosition(GetBlockPosition(column, row));
				block.setFillColor(sf::Color::White);
				block.setOutlineColor(sf::Color::Red);

				switch (blocks[column][row])
				{
					case Solid:
						block.setOutlineColor(sf::Color::Red);
						break;
					case Ladder:
						block.setOutlineColor(sf::Color::Blue);
						break;
					case LadderTop:
						block.setOutlineColor(sf::Color::Green);
						break;
					case LadderBottom:
						block.setOutlineColor(sf::Color::Yellow);
						break;
					case Corner:
						block.setOutlineColor(sf::Color::Magenta);
						break;
					case Platform:
						block.setFillColor(sf::Color::Magenta);
						break;
					case Liquid:
						block.setFillColor(sf::Color::Blue);
						break;
					case LiquidTop:
						block.setFillColor(sf::Color::Blue);
						block.setOutlineColor(sf::Color::Yellow);
						break;
				}

				window.draw(block);
			}
        }
    }
}

////////////////////////////////////////////////////////////////////////

Block Grid::GetBlock(int column, int row)
{
	if (IsValidBlockIndex(column, row))
	{
		return Block(blocks[column][row], GetBlockPosition(column, row), blockSize);
	}
}

////////////////////////////////////////////////////////////////////////

int Grid::GetBlockKey(int column, int row)
{
	return (column * dimensions.x) + row;
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

void Grid::SetBlockType(sf::Vector2f position, BlockType blockType)
{
	sf::Vector2i blockIndex = GetBlockIndex(position);

	if (IsValidBlockIndex(blockIndex))
	{
		blocks[blockIndex.x][blockIndex.y] = blockType;
	}
}

////////////////////////////////////////////////////////////////////////

bool Grid::IsValidBlockIndex(int column, int row)
{
	return column >= 0 && row >= 0 && column < dimensions.x && row < dimensions.y;
}

////////////////////////////////////////////////////////////////////////

bool Grid::IsValidBlockIndex(sf::Vector2i blockIndex)
{
	return IsValidBlockIndex(blockIndex.x, blockIndex.y);
}

////////////////////////////////////////////////////////////////////////

bool Grid::IsValidNonEmptyBlockIndex(int column, int row)
{
	return IsValidBlockIndex(column, row) && blocks[column][row] != BlockType::Empty;
}

////////////////////////////////////////////////////////////////////////

void Grid::Save(string fileName)
{
	sf::Image gridImage;
	gridImage.create(dimensions.x, dimensions.y, sf::Color::White);

	for (int column = 0; column < dimensions.x; column++)
	{
		for (int row = 0; row < dimensions.y; row++)
		{
			gridImage.setPixel(column, row, BlockTypeToColor(blocks[column][row]));
		}
	}                                 

	gridImage.saveToFile(resourcePath() + fileName);
}

////////////////////////////////////////////////////////////////////////

sf::Color Grid::BlockTypeToColor(BlockType blockType)
{
	switch (blockType)
	{
	case Empty:
		return sf::Color::Black;
		break;
	case Solid:
		return sf::Color::White;
		break;
	case Liquid:
		return sf::Color::Blue;
		break;
	case LiquidTop:
		return sf::Color(123, 12, 67, 255);
		break;
	case Ladder:
		return sf::Color(185, 122, 87, 255);
		break;
	case LadderTop:
		return sf::Color(90, 56, 37, 255);
		break;
	case LadderBottom:
		return sf::Color(213, 174, 153, 255);
		break;
	case Corner:
		return sf::Color(128, 128, 128, 255);
		break;
	case Platform:
		return sf::Color::Red;
		break;
	default:
		return sf::Color::White;
		break;
	}
}

////////////////////////////////////////////////////////////////////////

BlockType Grid::ColorToBlockType(sf::Color color)
{
	if (color == sf::Color::Black)
	{
		return BlockType::Empty;
	}
	else if (color == sf::Color::White)
	{
		return BlockType::Solid;
	}
	else if (color == sf::Color::Blue)
	{
		return BlockType::Liquid;
	}
	else if (color == sf::Color(123, 12, 67, 255))
	{
		return BlockType::LiquidTop;
	}
	else if (color == sf::Color(185, 122, 87, 255))
	{
		return BlockType::Ladder;
	}
	else if (color == sf::Color(90, 56, 37, 255))
	{
		return BlockType::LadderTop;
	}
	else if (color == sf::Color(213, 174, 153, 255))
	{
		return BlockType::LadderBottom;
	}
	else if (color == sf::Color(128, 128, 128, 255))
	{
		return BlockType::Corner;
	}
	else if (color == sf::Color::Red)
	{
		return BlockType::Platform;
	}

	return BlockType::Empty;
}


