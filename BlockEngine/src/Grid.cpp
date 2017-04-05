#include "Grid.hpp"
#include "ResourcePath.hpp"
#include "ResourceManager.hpp"

Grid::Grid(int columns, int rows, int blockWidth, int blockHeight)
{
	dimensions = sf::Vector2i(columns, rows);
	blockSize = sf::Vector2f(blockWidth, blockHeight);

	for (int column = 0; column < dimensions.x; column++)
	{
		vector<BlockType> blockColumn;

		for (int row = 0; row < dimensions.y; row++)
		{
			blockColumn.push_back(BlockType::BlockType_Solid);
		}

		blocks.push_back(blockColumn);
	}

	LoadBlockTextures();
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

	LoadBlockTextures();
}

////////////////////////////////////////////////////////////////////////

Grid::~Grid()
{
	Save("gridSave.png");
}

////////////////////////////////////////////////////////////////////////

void Grid::Draw(sf::RenderWindow &window, Camera* camera)
{
	Vector4i visibleBlocks = GetBlockIndicies(camera->GetView().getCenter() - (camera->GetView().getSize() * 0.5f), camera->GetView().getSize());
    
    for (int column = visibleBlocks.x1; column <= visibleBlocks.x2; column++)
    {
        for (int row = visibleBlocks.y1; row <= visibleBlocks.y2; row++)
        {
			if (IsValidNonEmptyBlockIndex(column, row))
			{
				blockTextures[blocks[column][row]].setPosition(GetBlockPosition(column, row));

				window.draw(blockTextures[blocks[column][row]]);
			}
        }
    }
}

////////////////////////////////////////////////////////////////////////

sf::Vector2i Grid::GetDimensions()
{
	return dimensions;
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

BlockType Grid::GetBlockType(int column, int row)
{
	return IsValidBlockIndex(column, row) ? blocks[column][row] : BlockType::BlockType_None;
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

BlockNeighbors Grid::GetBlockNeighbors(int column, int row)
{
	BlockNeighbors neighbors;

	if (IsValidBlockIndex(column - 1, row - 1))
	{
		neighbors.TopLeft = blocks[column - 1][row - 1];
	}
	if (IsValidBlockIndex(column, row - 1))
	{
		neighbors.Top = blocks[column][row - 1];
	}
	if (IsValidBlockIndex(column + 1, row - 1))
	{
		neighbors.TopRight = blocks[column + 1][row - 1];
	}
	if (IsValidBlockIndex(column - 1, row))
	{
		neighbors.Left = blocks[column - 1][row];
	}
	if (IsValidBlockIndex(column + 1, row))
	{
		neighbors.Right = blocks[column + 1][row];
	}
	if (IsValidBlockIndex(column - 1, row + 1))
	{
		neighbors.BottomLeft = blocks[column - 1][row + 1];
	}
	if (IsValidBlockIndex(column, row + 1))
	{
		neighbors.Bottom = blocks[column][row + 1];
	}
	if (IsValidBlockIndex(column + 1, row + 1))
	{
		neighbors.BottomRight = blocks[column + 1][row + 1];
	}

	return neighbors;
}

////////////////////////////////////////////////////////////////////////

void Grid::SetBlockType(int column, int row, BlockType blockType)
{
	if (IsValidBlockIndex(column, row))
	{
		blocks[column][row] = blockType;
	}
}

////////////////////////////////////////////////////////////////////////

void Grid::SetBlockType(sf::Vector2i blockIndex, BlockType blockType)
{
	if (IsValidBlockIndex(blockIndex))
	{
		blocks[blockIndex.x][blockIndex.y] = blockType;
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

void Grid::SetBlockType(sf::Vector2f position, sf::Vector2f size, BlockType blockType)
{
	Vector4i collidedBlocks = GetBlockIndicies(position, size);

	for (int column = collidedBlocks.x1; column <= collidedBlocks.x2; column++)
	{
		for (int row = collidedBlocks.y1; row <= collidedBlocks.y2; row++)
		{
			if (IsValidBlockIndex(column, row))
			{
				blocks[column][row] = blockType;
			}
		}
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
	return IsValidBlockIndex(column, row) && blocks[column][row] != BlockType::BlockType_Empty;
}

////////////////////////////////////////////////////////////////////////

void Grid::LoadBlockTextures()
{
	blockTextures[BlockType::BlockType_Solid] = LoadBlockTexture("whiteBlock");
	blockTextures[BlockType::BlockType_Corner] = LoadBlockTexture("whiteBlock");
	blockTextures[BlockType::BlockType_Platform] = LoadBlockTexture("platformBlock");
	blockTextures[BlockType::BlockType_Ladder] = LoadBlockTexture("ladderBlock");
	blockTextures[BlockType::BlockType_LadderBottom] = LoadBlockTexture("ladderBlock");
	blockTextures[BlockType::BlockType_LadderTop] = LoadBlockTexture("ladderBlock");
	blockTextures[BlockType::BlockType_Liquid] = LoadBlockTexture("waterBlock");
	blockTextures[BlockType::BlockType_LiquidTop] = LoadBlockTexture("waterBlock");
}

////////////////////////////////////////////////////////////////////////

sf::RectangleShape Grid::LoadBlockTexture(string textureName)
{
	sf::RectangleShape block(blockSize);
	block.setTexture(ResourceManager::GetInstance().GetTexture(textureName));
	return block;
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
	case BlockType_Empty:
		return sf::Color::White;
	case BlockType_Solid:
		return sf::Color::Black;
	case BlockType_Liquid:
		return sf::Color::Blue;
	case BlockType_LiquidTop:
		return sf::Color(123, 12, 67, 255);
	case BlockType_Ladder:
		return sf::Color(185, 122, 87, 255);
	case BlockType_LadderTop:
		return sf::Color(90, 56, 37, 255);
	case BlockType_LadderBottom:
		return sf::Color(213, 174, 153, 255);
	case BlockType_Corner:
		return sf::Color(128, 128, 128, 255);
	case BlockType_Platform:
		return sf::Color::Red;
	default:
		return sf::Color::White;
	}
}

////////////////////////////////////////////////////////////////////////

BlockType Grid::ColorToBlockType(sf::Color color)
{
	if (color == sf::Color::White)
	{
		return BlockType::BlockType_Empty;
	}
	else if (color == sf::Color::Black)
	{
		return BlockType::BlockType_Solid;
	}
	else if (color == sf::Color::Blue)
	{
		return BlockType::BlockType_Liquid;
	}
	else if (color == sf::Color(123, 12, 67, 255))
	{
		return BlockType::BlockType_LiquidTop;
	}
	else if (color == sf::Color(185, 122, 87, 255))
	{
		return BlockType::BlockType_Ladder;
	}
	else if (color == sf::Color(90, 56, 37, 255))
	{
		return BlockType::BlockType_LadderTop;
	}
	else if (color == sf::Color(213, 174, 153, 255))
	{
		return BlockType::BlockType_LadderBottom;
	}
	else if (color == sf::Color(128, 128, 128, 255))
	{
		return BlockType::BlockType_Corner;
	}
	else if (color == sf::Color::Red)
	{
		return BlockType::BlockType_Platform;
	}

	return BlockType::BlockType_Empty;
}

////////////////////////////////////////////////////////////////////////

int Grid::LayoutNodeIndexToBlockIndex(int index, int nodeSize)
{
	return (index * (nodeSize + 1)) + 1;
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f Grid::LayoutNodePositionToBlockPosition(sf::Vector2i position, int nodeSize)
{
	sf::Vector2i gridIndex = sf::Vector2i(LayoutNodeIndexToBlockIndex(position.x, nodeSize), LayoutNodeIndexToBlockIndex(position.y, nodeSize));
	return GetBlockPosition(gridIndex.x, gridIndex.y);
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f Grid::LayoutNodeSizeToGridSize(sf::Vector2i size, int nodeSize)
{
	return sf::Vector2f(((size.x * (nodeSize + 1) - 1) * blockSize.x) - 1, ((size.y * (nodeSize + 1) - 1) * blockSize.y) - 1);
}


