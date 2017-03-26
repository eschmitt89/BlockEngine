//
//  Grid.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "Grid.hpp"
#include "ResourcePath.hpp"
#include "ResourceManager.hpp"

Grid::Grid(int columns, int rows, int blockWidth, int blockHeight)
{
	LoadBlockSprites();

	InitializeBlocks(columns, rows, blockWidth, blockHeight, BlockType::Solid);
}

////////////////////////////////////////////////////////////////////////

Grid::Grid(string fileName, int blockWidth, int blockHeight)
{
	LoadBlockSprites();

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

Grid::Grid(GridLayout gridLayout, int nodeSize, int blockWidth, int blockHeight)
{
	LoadBlockSprites();

	int columns = (gridLayout.Dimensions.x * (nodeSize + 1)) + 1;
	int rows = (gridLayout.Dimensions.y * (nodeSize + 1)) + 1;

	// Initialize Blocks
	InitializeBlocks(columns, rows, blockWidth, blockHeight, BlockType::Solid);

	// Place corridors
	for (int column = 0; column < gridLayout.Corridors.size(); column++)
	{
		for (int row = 0; row < gridLayout.Corridors[column].size(); row++)
		{
			LayoutNode currentNode = gridLayout.Corridors[column][row];

			int blockColumn = LayoutNodeIndexToBlockIndex(column, nodeSize);
			int blockRow = LayoutNodeIndexToBlockIndex(row, nodeSize);;

			for (int i = 0; i < nodeSize; i++)
			{
				for (int j = 0; j < nodeSize; j++)
				{
					blocks[blockColumn + i][blockRow + j] = BlockType::Empty;

					if (currentNode.CorridorLeft)
					{
						blocks[blockColumn - (i + 1)][blockRow + j] = BlockType::Empty;
					}
					if (currentNode.CorridorRight)
					{
						blocks[blockColumn + (i + 1)][blockRow + j] = BlockType::Empty;
					}
					if (currentNode.CorridorUp)
					{
						blocks[blockColumn + j][blockRow - (i + 1)] = BlockType::Empty;
					}
					if (currentNode.CorridorDown)
					{
						blocks[blockColumn + j][blockRow + (i + 1)] = BlockType::Empty;
					}
				}
			}
		}
	}

	// Place rooms
	for (int i = 0; i < gridLayout.Rooms.size(); i++)
	{
		sf::Vector2f roomPosition = LayoutNodePositionToBlockPosition(gridLayout.Rooms[i].Position, nodeSize);
		sf::Vector2f roomSize = LayoutNodeSizeToGridSize(gridLayout.Rooms[i].Size, nodeSize);

		SetBlockType(roomPosition, roomSize, BlockType::Empty);

		sf::Vector2f currentPosition = sf::Vector2f(Random(roomPosition.x, roomPosition.x + roomSize.x), roomPosition.y + roomSize.y + blockSize.y);

		

		//while (currentPosition.y > roomPosition.y)
		//{
		//	int action = Random(0, 3);

		//	if (action == 0) // climb
		//	{
		//		int ladderHeight = Random(2, (roomSize.y / blockSize.y) / 4);
		//		for (int i = 0; i < ladderHeight; i++)
		//		{
		//			currentPosition.y -= blockSize.y;
		//			if (currentPosition.y > roomPosition.y) 
		//			{
		//				SetBlockType(currentPosition, BlockType::Ladder);
		//			}
		//		}
		//		if (currentPosition.y - blockSize.y > roomPosition.y)
		//		{
		//			currentPosition.y -= blockSize.y;
		//			SetBlockType(currentPosition, BlockType::Platform);
		//		}
		//	}
		//	else if (action == 1) // jump vertical
		//	{
		//		currentPosition.y -= (blockSize.y * 2);
		//		if (currentPosition.y > roomPosition.y)
		//		{
		//			SetBlockType(currentPosition, BlockType::Platform);
		//		}
		//	}
		//	else if (action == 2) // jump horizontal
		//	{
		//		int jumpDistance = (blockSize.x * 3);
		//		int direction = Random(0, 1);
		//		if (direction == 0)
		//		{
		//			if (currentPosition.x + jumpDistance < roomPosition.x + roomSize.x)
		//			{
		//				currentPosition.x += jumpDistance;
		//			}
		//		}
		//		else if (direction == 1)
		//		{
		//			if (currentPosition.x - jumpDistance > roomPosition.x)
		//			{
		//				currentPosition.x -= jumpDistance;
		//			}
		//		}

		//		if (currentPosition.y < roomPosition.y + roomSize.y && currentPosition.y > roomPosition.y)
		//		{
		//			SetBlockType(currentPosition, BlockType::Platform);
		//		}
		//	}
		//	else if (action == 3) // drop
		//	{
		//		if (currentPosition.y + (blockSize.y * 2) < roomPosition.y + roomSize.y)
		//		{
		//			currentPosition.y += (blockSize.y * 2);
		//			SetBlockType(currentPosition, BlockType::Platform);
		//		}
		//	}

		//	int direction = Random(0, 1);
		//	int moveDistance = Random(2, roomSize.y / blockSize.y / 4);
		//	if (direction == 0) // right
		//	{
		//		for (int i = 0; i < moveDistance; i++)
		//		{
		//			if (currentPosition.x + blockSize.x < roomPosition.x + roomSize.x && currentPosition.y < roomPosition.y + roomSize.y && currentPosition.y > roomPosition.y)
		//			{
		//				currentPosition.x += blockSize.x;
		//				SetBlockType(currentPosition, BlockType::Platform);
		//			}
		//		}
		//	}
		//	else if (direction == 1) // left
		//	{
		//		for (int i = 0; i < moveDistance; i++)
		//		{
		//			if (currentPosition.x - blockSize.x > roomPosition.x && currentPosition.y < roomPosition.y + roomSize.y && currentPosition.y > roomPosition.y)
		//			{
		//				currentPosition.x -= blockSize.x;
		//				SetBlockType(currentPosition, BlockType::Platform);
		//			}
		//		}
		//	}
		//}
		

		// Place platforms
		/*for (int j = 1; j < roomSize.y / blockSize.y / 2; j++)
		{
			sf::Vector2f platformPosition = roomPosition + sf::Vector2f(0, blockSize.y * 2 * j);
			sf::Vector2f platformSize = sf::Vector2f(roomSize.x, 1);

			SetBlockType(platformPosition, platformSize, BlockType::Platform);
		}*/
	}

	// Place doors
	for (int i = 0; i < gridLayout.Doors.size(); i++)
	{
		sf::Vector2f doorPosition = LayoutNodePositionToBlockPosition(gridLayout.Doors[i], nodeSize) -sf::Vector2f(blockSize.x, 0);
		sf::Vector2f doorSize = sf::Vector2f(1, blockSize.y * (nodeSize - 1));

		//SetBlockType(doorPosition, doorSize, BlockType::Empty);
	}

	// Place ladders
	for (int i = 0; i < gridLayout.Ladders.size(); i++)
	{
		int column = LayoutNodeIndexToBlockIndex(gridLayout.Ladders[i].x, nodeSize) + nodeSize/2;
		int row = LayoutNodeIndexToBlockIndex(gridLayout.Ladders[i].y, nodeSize);

		while (blocks[column][row - 1] == BlockType::Empty)
		{
			row--;
		}

		while (blocks[column][row] == BlockType::Empty)
		{
			//blocks[column][row] = BlockType::Ladder;
			row++;
		}
	}

	// Place corners
	for (int x = 0; x < blocks.size(); x++)
	{
		for (int y = 0; y < blocks[x].size(); y++)
		{
			if (blocks[x][y] == BlockType::Solid)
			{
				BlockNeighbors neighbors = GetBlockNeighbors(x, y);

				if ((neighbors.Left == BlockType::Empty && neighbors.TopLeft == BlockType::Empty && neighbors.Top == BlockType::Empty) 
					|| (neighbors.Right == BlockType::Empty && neighbors.TopRight == BlockType::Empty && neighbors.Top == BlockType::Empty))
				{
					blocks[x][y] = BlockType::Corner;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

Grid::~Grid()
{
	Save("gridSave.png");
}

////////////////////////////////////////////////////////////////////////

void Grid::InitializeBlocks(int columns, int rows, int blockWidth, int blockHeight, BlockType blockType)
{
	dimensions = sf::Vector2i(columns, rows);
	blockSize = sf::Vector2f(blockWidth, blockHeight);

	for (int column = 0; column < dimensions.x; column++)
	{
		vector<BlockType> blockColumn;

		for (int row = 0; row < dimensions.y; row++)
		{
			blockColumn.push_back(blockType);
		}

		blocks.push_back(blockColumn);
	}
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
				blockSprites[blocks[column][row]].setPosition(GetBlockPosition(column, row));

				window.draw(blockSprites[blocks[column][row]]);
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

BlockType Grid::GetBlockType(int column, int row)
{
	return IsValidBlockIndex(column, row) ? blocks[column][row] : BlockType::NoBlock;
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
	return IsValidBlockIndex(column, row) && blocks[column][row] != BlockType::Empty;
}

////////////////////////////////////////////////////////////////////////

void Grid::LoadBlockSprites()
{
	blockSprites[BlockType::Solid] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("whiteBlock"));
	blockSprites[BlockType::Corner] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("whiteBlock"));
	blockSprites[BlockType::Platform] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("platformBlock"));
	blockSprites[BlockType::Ladder] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("ladderBlock"));
	blockSprites[BlockType::LadderBottom] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("ladderBlock"));
	blockSprites[BlockType::LadderTop] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("ladderBlock"));
	blockSprites[BlockType::Liquid] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("waterBlock"));
	blockSprites[BlockType::LiquidTop] = sf::Sprite(*ResourceManager::GetInstance().GetTexture("waterBlock"));
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
		return sf::Color::White;
	case Solid:
		return sf::Color::Black;
	case Liquid:
		return sf::Color::Blue;
	case LiquidTop:
		return sf::Color(123, 12, 67, 255);
	case Ladder:
		return sf::Color(185, 122, 87, 255);
	case LadderTop:
		return sf::Color(90, 56, 37, 255);
	case LadderBottom:
		return sf::Color(213, 174, 153, 255);
	case Corner:
		return sf::Color(128, 128, 128, 255);
	case Platform:
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
		return BlockType::Empty;
	}
	else if (color == sf::Color::Black)
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


