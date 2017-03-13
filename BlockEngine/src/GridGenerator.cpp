//
//  GridGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridGenerator.hpp"
#include "Utilities.hpp"

GridGenerator::GridGenerator()
{

}

////////////////////////////////////////////////////////////////////////

GridGenerator::~GridGenerator()
{

}

////////////////////////////////////////////////////////////////////////

Grid * GridGenerator::Generate(int columns, int rows, int blockWidth, int blockHeight, int numberOfRooms)
{
	Grid* grid = new Grid(columns, rows, blockWidth, blockHeight);

	SpawnRooms(grid, 10, 20);

	return grid;
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::SpawnRooms(Grid * grid, int numberOfRooms, int maxAttempts)
{
	for (int attempt = 0; attempt < maxAttempts; attempt++)
	{
		if (rooms.size() == numberOfRooms)
		{
			return;
		}

		Room room = GenerateRoom(grid);

		if (!RoomCollision(room))
		{
			rooms.push_back(room);
		}
	}

	for (int i = 0; i < rooms.size(); i++)
	{
		sf::Vector2f position = sf::Vector2f(grid->GetBlockPosition(rooms[i].Position.x, rooms[i].Position.y));
		sf::Vector2f size = sf::Vector2f(rooms[i].Size.x * 32, rooms[i].Size.y * 32);
		grid->SetBlockType(position, size, BlockType::Empty);
	}
}

Room GridGenerator::GenerateRoom(Grid* grid)
{
	sf::Vector2i size = sf::Vector2i(Random(RoomMinSize, RoomMaxSize), Random(RoomMinSize, RoomMaxSize));
	sf::Vector2i position = sf::Vector2i(Random(1, grid->GetDimensions().x - size.x - 1), Random(1, grid->GetDimensions().y - size.y - 1));
	
	return Room(position, size);
}

bool GridGenerator::RoomCollision(Room room)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		if (Intersect((sf::Vector2f)room.Position, (sf::Vector2f)room.Size, (sf::Vector2f)rooms[i].Position, (sf::Vector2f)rooms[i].Size))
		{
			return true;
		}
	}
	return false;
}


