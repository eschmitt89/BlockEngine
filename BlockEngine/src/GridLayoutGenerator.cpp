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

GridLayout GridLayoutGenerator::Generate()
{
	vector<LayoutRoom> rooms;
	vector<vector<LayoutCell>> cells;
	vector<vector<bool>> visitedCells;
	vector<sf::Vector2i> visitedCellIndicies;

	int columns = 20;
	int rows = 20;
	int numberOfRoomCells = 0;
	int numberOfCells = columns * rows;

	// Init cells + visitedCells
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

	// Generate rooms
	int maxRooms = 20;
	int maxRoomPlacementAttemps = maxRooms * 10;
	int minRoomWidth = 2;
	int minRoomHeight = 2;
	int maxRoomWidth = 6;
	int maxRoomHeight = 6;

	for (int i = 0; i < maxRoomPlacementAttemps; i++)
	{
		if (rooms.size() == maxRooms)
		{
			break;
		}

		sf::Vector2i roomSize = sf::Vector2i(Random(minRoomWidth, maxRoomWidth), Random(minRoomHeight, maxRoomHeight));
		sf::Vector2i roomPosition = sf::Vector2i(Random(0, columns - roomSize.x - 1), Random(0, rows - roomSize.y - 1));

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

	sf::Vector2i currentCell = sf::Vector2i(Random(0, columns - 1), Random(0, rows - 1));

	while (visitedCells[currentCell.x][currentCell.y])
	{
		currentCell = sf::Vector2i(Random(0, columns - 1), Random(0, rows - 1));
	}

	while (visitedCellIndicies.size() < numberOfCells - numberOfRoomCells)
	{
		bool validDirectionFound = false;
		vector<int> validDirections = { 0, 1, 2, 3 };

		while (!validDirectionFound)
		{
			sf::Vector2i nextCell = currentCell;

			int direction = validDirections[Random(0, validDirections.size() - 1)];

			switch (direction)
			{
			case 0: // Left
				nextCell.x -= 1;
				validDirectionFound = (nextCell.x >= 0 && !visitedCells[nextCell.x][nextCell.y]);
				if (validDirectionFound)
				{
					cells[currentCell.x][currentCell.y].CorridorLeft = true;
				}
				else
				{
					validDirections.erase(remove(validDirections.begin(), validDirections.end(), 0));
				}
				break;
			case 1: // Right
				nextCell.x += 1;
				validDirectionFound = (nextCell.x < columns && !visitedCells[nextCell.x][nextCell.y]);
				if (validDirectionFound)
				{
					cells[currentCell.x][currentCell.y].CorridorRight = true;
				}
				else
				{
					validDirections.erase(remove(validDirections.begin(), validDirections.end(), 1));
				}
				break;
			case 2: // Up
				nextCell.y -= 1;
				validDirectionFound = (nextCell.y >= 0 && !visitedCells[nextCell.x][nextCell.y]);
				if (validDirectionFound)
				{
					cells[currentCell.x][currentCell.y].CorridorUp = true;
				}
				else
				{
					validDirections.erase(remove(validDirections.begin(), validDirections.end(), 2));
				}
				break;
			case 3: // Down
				nextCell.y += 1;
				validDirectionFound = (nextCell.y < rows && !visitedCells[nextCell.x][nextCell.y]);
				if (validDirectionFound)
				{
					cells[currentCell.x][currentCell.y].CorridorDown = true;
				}
				else
				{
					validDirections.erase(remove(validDirections.begin(), validDirections.end(), 3));
				}
			}

			if (validDirectionFound)
			{
				currentCell = nextCell;
				visitedCells[currentCell.x][currentCell.y] = true;
				visitedCellIndicies.push_back(currentCell);
			}
			if (validDirections.size() == 0)
			{
				currentCell = visitedCellIndicies[Random(0, visitedCellIndicies.size() - 1)];
				break;
			}
		}
	}


	return GridLayout(cells, rooms, sf::Vector2i(columns, rows));


	//int columns = 50;
	//int rows = 50;
	//int numberOfCells = columns * rows;

	//vector<vector<Cell>> cells = CreateCells(columns, rows);
	//vector<sf::Vector2i> visitedCells;

	//sf::Vector2i currentCell = sf::Vector2i(Random(0, columns - 1), Random(0, rows - 1));
	//cells[currentCell.x][currentCell.y].Visited = true;
	//visitedCells.push_back(currentCell);

	//while (visitedCells.size() < numberOfCells)
	//{
	//	bool validDirectionFound = false;
	//	vector<int> validDirections = { 0, 1, 2, 3 };

	//	while (!validDirectionFound)
	//	{
	//		sf::Vector2i nextCell = currentCell;

	//		int direction = validDirections[Random(0, validDirections.size() - 1)];

	//		switch (direction)
	//		{
	//		case 0: // Left
	//			nextCell.x -= 1;
	//			validDirectionFound = (nextCell.x >= 0 && !cells[nextCell.x][nextCell.y].Visited);
	//			if (validDirectionFound)
	//			{
	//				cells[currentCell.x][currentCell.y].CorridorLeft = true;
	//			}
	//			else
	//			{
	//				validDirections.erase(remove(validDirections.begin(), validDirections.end(), 0));
	//			}
	//			break;
	//		case 1: // Right
	//			nextCell.x += 1;
	//			validDirectionFound = (nextCell.x < columns && !cells[nextCell.x][nextCell.y].Visited);
	//			if (validDirectionFound)
	//			{
	//				cells[currentCell.x][currentCell.y].CorridorRight = true;
	//			}
	//			else
	//			{
	//				validDirections.erase(remove(validDirections.begin(), validDirections.end(), 1));
	//			}
	//			break;
	//		case 2: // Up
	//			nextCell.y -= 1;
	//			validDirectionFound = (nextCell.y >= 0 && !cells[nextCell.x][nextCell.y].Visited);
	//			if (validDirectionFound)
	//			{
	//				cells[currentCell.x][currentCell.y].CorridorUp = true;
	//			}
	//			else
	//			{
	//				validDirections.erase(remove(validDirections.begin(), validDirections.end(), 2));
	//			}
	//			break;
	//		case 3: // Down
	//			nextCell.y += 1;
	//			validDirectionFound = (nextCell.y < rows && !cells[nextCell.x][nextCell.y].Visited);
	//			if (validDirectionFound)
	//			{
	//				cells[currentCell.x][currentCell.y].CorridorDown = true;
	//			}
	//			else
	//			{
	//				validDirections.erase(remove(validDirections.begin(), validDirections.end(), 3));
	//			}
	//		}

	//		if (validDirectionFound)
	//		{
	//			currentCell = nextCell;
	//			cells[currentCell.x][currentCell.y].Visited = true;
	//			visitedCells.push_back(currentCell);
	//		}
	//		if (validDirections.size() == 0)
	//		{
	//			currentCell = visitedCells[Random(0, visitedCells.size() - 1)];
	//			break;
	//		}
	//	}
	//}

	//return cells;
}

//void GridLayoutGenerator::InitializeCorridors(int columns, int rows)
//{
//	for (int x = 0; x < columns; x++)
//	{
//		vector<LayoutCell> column;
//
//		for (int y = 0; y < rows; y++)
//		{
//			column.push_back(LayoutCell());
//		}
//
//		gridLayout.Corridors.push_back(column);
//	}
//}
//
//
//void GridLayoutGenerator::GenerateRooms(int maxNumberOfRooms, int minRoomSize, int maxRoomSize)
//{
//	int roomPlacementAttemps = maxNumberOfRooms * 3;
//
//	for (int i = 0; i < roomPlacementAttemps; i++)
//	{
//		if (gridLayout.Rooms.size() == maxNumberOfRooms)
//		{
//			return;
//		}
//
//		sf::Vector2i roomSize = sf::Vector2i(Random(minRoomSize, maxRoomSize), Random(minRoomSize, maxRoomSize));
//
//		sf::Vector2i roomPosition = sf::Vector2i(Random(0, gridLayout.Dimensions.x - roomSize.x - 1), Random(0, gridLayout.Dimensions.y - roomSize.y - 1));
//
//		if (roomPosition.x < 0 || roomPosition.y < 0)
//		{
//			continue;
//		}
//
//		LayoutRoom room = LayoutRoom(roomPosition, roomSize);
//
//		for (int j = 0; j < gridLayout.Rooms.size(); j++)
//		{
//			if (Intersect(room.Position, room.Size, gridLayout.Rooms[j].Position, gridLayout.Rooms[j].Size))
//			{
//				continue;
//			}
//		}
//
//		gridLayout.Rooms.push_back(room);
//	}
//}
//
//void GridLayoutGenerator::GenerateCorridors()
//{
//
//}
//
//bool GridLayoutGenerator::RoomOverlapsExistingRoom(int column, int row, int width, int height)
//{
//	return false;
//}



