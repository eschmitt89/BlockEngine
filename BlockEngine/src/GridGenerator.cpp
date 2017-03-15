//
//  GridGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridGenerator.hpp"
#include "Utilities.hpp"
#include <set>

GridGenerator::GridGenerator()
{

}

////////////////////////////////////////////////////////////////////////

GridGenerator::~GridGenerator()
{

}

////////////////////////////////////////////////////////////////////////

//Grid * GridGenerator::Generate(int columns, int rows, int blockWidth, int blockHeight, int numberOfRooms)
//{
//	Grid* grid = new Grid(columns, rows, blockWidth, blockHeight);
//
//	SpawnRooms(grid, 10, 20);
//
//	return grid;
//}
//
//////////////////////////////////////////////////////////////////////////
//
//void GridGenerator::SpawnRooms(Grid * grid, int numberOfRooms, int maxAttempts)
//{
//	for (int attempt = 0; attempt < maxAttempts; attempt++)
//	{
//		if (rooms.size() == numberOfRooms)
//		{
//			return;
//		}
//
//		Room room = GenerateRoom(grid);
//
//		if (!RoomCollision(room))
//		{
//			rooms.push_back(room);
//		}
//	}
//
//	for (int i = 0; i < rooms.size(); i++)
//	{
//		sf::Vector2f position = sf::Vector2f(grid->GetBlockPosition(rooms[i].Position.x, rooms[i].Position.y));
//		sf::Vector2f size = sf::Vector2f(rooms[i].Size.x * 32, rooms[i].Size.y * 32);
//		grid->SetBlockType(position, size, BlockType::Empty);
//	}
//}
//
//Room GridGenerator::GenerateRoom(Grid* grid)
//{
//	sf::Vector2i size = sf::Vector2i(Random(RoomMinSize, RoomMaxSize), Random(RoomMinSize, RoomMaxSize));
//	sf::Vector2i position = sf::Vector2i(Random(1, grid->GetDimensions().x - size.x - 1), Random(1, grid->GetDimensions().y - size.y - 1));
//	
//	return Room(position, size);
//}
//
//bool GridGenerator::RoomCollision(Room room)
//{
//	for (int i = 0; i < rooms.size(); i++)
//	{
//		if (Intersect((sf::Vector2f)room.Position, (sf::Vector2f)room.Size, (sf::Vector2f)rooms[i].Position, (sf::Vector2f)rooms[i].Size))
//		{
//			return true;
//		}
//	}
//	return false;
//}

//vector<Vector4i> GridGenerator::Generate2()
//{
//	int width = 100;
//	int height = 100;
//
//	vector<Vector4i> corridors;
//	vector<vector<bool>> cells;
//	vector<sf::Vector2i> visitedCells;
//
//	for (int x = 0; x < width; x++)
//	{
//		vector<bool> column;
//		for (int y = 0; y < height; y++)
//		{
//			column.push_back(false);
//		}
//		cells.push_back(column);
//	}
//
//	sf::Vector2i currentCell = sf::Vector2i(Random(0, width - 1), Random(0, height - 1));
//
//	cells[currentCell.x][currentCell.y] = true;
//
//	visitedCells.push_back(currentCell);
//
//	while (visitedCells.size() < width * height)
//	{
//		bool leftInvalid = false;
//		bool rightInvalid = false;
//		bool upInvalid = false;
//		bool downInvalid = false;
//		bool moved = false;
//
//		while (!moved)
//		{
//			sf::Vector2i nextCell = currentCell;
//
//			int direction = Random(0, 3);
//
//			switch (direction)
//			{
//			case 0: // left
//				if (!leftInvalid)
//				{
//					nextCell.x -= 1;
//					if (nextCell.x >= 0 && !cells[nextCell.x][nextCell.y])
//					{
//						moved = true;
//					}
//					else
//					{
//						leftInvalid = true;
//					}
//				}
//				break;
//			case 1: // right
//				if (!rightInvalid)
//				{
//					nextCell.x += 1;
//					if (nextCell.x < width && !cells[nextCell.x][nextCell.y])
//					{
//						moved = true;
//					}
//					else
//					{
//						rightInvalid = true;
//					}
//				}
//				break;
//			case 2: // up
//				if (!upInvalid)
//				{
//					nextCell.y -= 1;
//					if (nextCell.y >= 0 && !cells[nextCell.x][nextCell.y])
//					{
//						moved = true;
//					}
//					else
//					{
//						upInvalid = true;
//					}
//				}
//				break;
//			case 3: // down
//				if (!downInvalid)
//				{
//					nextCell.y += 1;
//					if (nextCell.y < height && !cells[nextCell.x][nextCell.y])
//					{
//						moved = true;
//					}
//					else
//					{
//						downInvalid = true;
//					}
//				}
//				break;
//			}
//
//			if (moved)
//			{
//				corridors.push_back(Vector4i(currentCell, nextCell));
//				currentCell = nextCell;
//				cells[currentCell.x][currentCell.y] = true;
//				visitedCells.push_back(currentCell);
//			}
//			if ((leftInvalid && rightInvalid && upInvalid && downInvalid) || visitedCells.size() == width * height)
//			{
//				corridors.push_back(Vector4i(currentCell, currentCell));
//				currentCell = visitedCells[Random(0, visitedCells.size() - 1)];
//				moved = true;
//			}
//		}
//	}
//
//	return corridors;
//}

vector<vector<Cell>> GridGenerator::Generate()
{
	int columns = 10;
	int rows = 10;
	int numberOfCells = columns * rows;

	vector<vector<Cell>> cells = CreateCells(columns, rows);
	vector<sf::Vector2i> visitedCells;

	sf::Vector2i currentCell = sf::Vector2i(Random(0, columns - 1), Random(0, rows - 1));
	cells[currentCell.x][currentCell.y].Visited = true;
	visitedCells.push_back(currentCell);

	while (visitedCells.size() < numberOfCells)
	{
		bool moved = false;
		bool leftInvalid = false;
		bool rightInvalid = false;
		bool upInvalid = false;
		bool downInvalid = false;
		//set<int> validDirections = { 0, 1, 2, 3 };

		//validDirections.erase(validDirections.find(0));

		while (!moved)
		{
			sf::Vector2i nextCell = currentCell;

			int direction = Random(0, 3);

			switch (direction)
			{
			case 0: // Left
				if (!leftInvalid)
				{
					nextCell.x -= 1;
					leftInvalid = (nextCell.x < 0 || cells[nextCell.x][nextCell.y].Visited);
					moved = !leftInvalid;
					if (moved)
					{
						cells[currentCell.x][currentCell.y].CorridorLeft = true;
					}
				}
				break;
			case 1: // Right
				if (!rightInvalid)
				{
					nextCell.x += 1;
					rightInvalid = (nextCell.x >= columns || cells[nextCell.x][nextCell.y].Visited);
					moved = !rightInvalid;
					if (moved)
					{
						cells[currentCell.x][currentCell.y].CorridorRight = moved;
					}
				}
				break;
			case 2: // Up
				if (!upInvalid)
				{
					nextCell.y -= 1;
					upInvalid = (nextCell.y < 0 || cells[nextCell.x][nextCell.y].Visited);
					moved = !upInvalid;
					if (moved)
					{
						cells[currentCell.x][currentCell.y].CorridorUp = moved;
					}
				}
				break;
			case 3: // Down
				if (!downInvalid)
				{
					nextCell.y += 1;
					downInvalid = (nextCell.y >= rows || cells[nextCell.x][nextCell.y].Visited);
					moved = !downInvalid;
					if (moved)
					{
						cells[currentCell.x][currentCell.y].CorridorDown = moved;
					}
				}
				break;
			}

			if (moved)
			{
				currentCell = nextCell;
				cells[currentCell.x][currentCell.y].Visited = true;
				visitedCells.push_back(currentCell);
			}
			if (leftInvalid && rightInvalid && upInvalid && downInvalid)
			{
				currentCell = visitedCells[Random(0, visitedCells.size() - 1)];
				moved = true;
			}
		}
	}

	return cells;
}

vector<vector<Cell>> GridGenerator::CreateCells(int columns, int rows)
{
	vector<vector<Cell>> cells;

	for (int x = 0; x < columns; x++)
	{
		vector<Cell> column;

		for (int y = 0; y < columns; y++)
		{
			column.push_back(Cell());
		}

		cells.push_back(column);
	}

	return cells;
}


