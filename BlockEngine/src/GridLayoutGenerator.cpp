//
//  GridLayoutGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridLayoutGenerator.hpp"
#include "Utilities.hpp"

GridLayoutGenerator::GridLayoutGenerator()
{

}

////////////////////////////////////////////////////////////////////////

GridLayoutGenerator::~GridLayoutGenerator()
{

}

////////////////////////////////////////////////////////////////////////

GridLayout GridLayoutGenerator::Generate(int columns, int rows, int maxRooms, int minRoomSize, int maxRoomSize)
{
	dimensions = sf::Vector2i(columns, rows);

	InitializeCells(columns, rows);

	GenerateRooms(maxRooms, minRoomSize, maxRoomSize);
	
	GenerateCorridors();

	return GridLayout(cells, rooms, dimensions);
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::InitializeCells(int columns, int rows)
{
	for (int x = 0; x < columns; x++)
	{
		vector<LayoutCell> cellColumn;
		vector<bool> visitedCellColumn;

		for (int y = 0; y < rows; y++)
		{
			cellColumn.push_back(LayoutCell());
			visitedCellColumn.push_back(false);
		}

		cells.push_back(cellColumn);
		visitedCells.push_back(visitedCellColumn);
	}
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::GenerateRooms(int maxNumberOfRooms, int minRoomSize, int maxRoomSize)
{
	numberOfRoomCells = 0;
	int maxRoomPlacementAttemps = maxNumberOfRooms * 10;

	for (int i = 0; i < maxRoomPlacementAttemps; i++)
	{
		if (rooms.size() == maxNumberOfRooms)
		{
			return;
		}

		sf::Vector2i roomSize = sf::Vector2i(Random(minRoomSize, maxRoomSize), Random(minRoomSize, maxRoomSize));
		sf::Vector2i roomPosition = sf::Vector2i(Random(0, dimensions.x - roomSize.x - 1), Random(0, dimensions.y - roomSize.y - 1));

		LayoutRoom room = LayoutRoom(roomPosition, roomSize);

		bool roomOverlapsExistingRoom = false;

		for (int j = 0; j < rooms.size(); j++)
		{
			if (Intersect(room.Position, room.Size, rooms[j].Position, rooms[j].Size))
			{
				roomOverlapsExistingRoom = true;
				break;
			}
		}

		if (!roomOverlapsExistingRoom)
		{
			rooms.push_back(room);

			for (int x = room.Position.x; x < room.Position.x + room.Size.x; x++)
			{
				for (int y = room.Position.y; y < room.Position.y + room.Size.y; y++)
				{
					visitedCells[x][y] = true;
					numberOfRoomCells++;
				}
			}
		}
	}
}

void GridLayoutGenerator::GenerateCorridors()
{
	sf::Vector2i currentCell = sf::Vector2i(Random(0, dimensions.x - 1), Random(0, dimensions.y - 1));

	while (visitedCells[currentCell.x][currentCell.y])
	{
		currentCell = sf::Vector2i(Random(0, dimensions.x - 1), Random(0, dimensions.y - 1));
	}

	int numberOfCells = dimensions.x * dimensions.y;

	while (visitedCellIndicies.size() < numberOfCells - numberOfRoomCells)
	{
		bool moved = false;
		bool leftInvalid = false;
		bool rightInvalid = false;
		bool upInvalid = false;
		bool downInvalid = false;

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
					leftInvalid = (nextCell.x < 0 || visitedCells[nextCell.x][nextCell.y]);
					if (!leftInvalid)
					{
						moved = true;
						cells[currentCell.x][currentCell.y].CorridorLeft = true;
					}
				}
				break;
			case 1: // Right
				if (!rightInvalid)
				{
					nextCell.x += 1;
					rightInvalid = (nextCell.x >= dimensions.x || visitedCells[nextCell.x][nextCell.y]);
					if (!rightInvalid)
					{
						moved = true;
						cells[currentCell.x][currentCell.y].CorridorRight = true;
					}
				}
				break;
			case 2: // Up
				if (!upInvalid)
				{
					nextCell.y -= 1;
					upInvalid = (nextCell.y < 0 || visitedCells[nextCell.x][nextCell.y]);
					if (!upInvalid)
					{
						moved = true;
						cells[currentCell.x][currentCell.y].CorridorUp = true;
					}
				}
				break;
			case 3: // Down
				if (!downInvalid)
				{
					nextCell.y += 1;
					downInvalid = (nextCell.y >= dimensions.y || visitedCells[nextCell.x][nextCell.y]);
					if (!downInvalid)
					{
						moved = true;
						cells[currentCell.x][currentCell.y].CorridorDown = true;
					}
				}
			}

			if (moved)
			{
				currentCell = nextCell;
				visitedCells[currentCell.x][currentCell.y] = true;
				visitedCellIndicies.push_back(currentCell);
			}
			if (leftInvalid && rightInvalid && upInvalid && downInvalid)
			{
				// TODO this can hang
				currentCell = visitedCellIndicies[Random(0, visitedCellIndicies.size() - 1)];
				break;
			}
		}
	}
}


