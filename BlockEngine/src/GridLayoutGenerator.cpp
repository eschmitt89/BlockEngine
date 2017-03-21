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

	InitializeNodes(columns, rows);

	GenerateRooms(columns, rows, maxRooms, minRoomSize, maxRoomSize);

	GenerateDoors(columns, rows);
	
	GenerateCorridors(columns, rows);

	return GridLayout(dimensions, rooms, doors, ladders, nodes);
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::InitializeNodes(int columns, int rows)
{
	for (int x = 0; x < columns; x++)
	{
		vector<LayoutNode> nodeColumn;

		for (int y = 0; y < rows; y++)
		{
			nodeColumn.push_back(LayoutNode());
		}

		nodes.push_back(nodeColumn);
	}
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::GenerateRooms(int columns, int rows, int maxNumberOfRooms, int minRoomSize, int maxRoomSize)
{
	numberOfRoomNodes = 0;
	int maxRoomPlacementAttemps = maxNumberOfRooms * 10;

	for (int i = 0; i < maxRoomPlacementAttemps; i++)
	{
		if (rooms.size() == maxNumberOfRooms)
		{
			return;
		}

		sf::Vector2i roomSize = sf::Vector2i(Random(minRoomSize, maxRoomSize), Random(minRoomSize, maxRoomSize));
		sf::Vector2i roomPosition = sf::Vector2i(Random(0, columns - roomSize.x - 1), Random(0, rows - roomSize.y - 1));

		LayoutRoom room = LayoutRoom(roomPosition, roomSize);

		bool roomOverlapsExistingRoom = false;

		for (int j = 0; j < rooms.size(); j++)
		{
			if (Intersect(room.Position + sf::Vector2i(-1, -1), room.Size + sf::Vector2i(2, 2), rooms[j].Position, rooms[j].Size))
			{
				roomOverlapsExistingRoom = true;
				break;
			}
		}

		if (!roomOverlapsExistingRoom)
		{
			ladders.push_back(roomPosition);

			for (int x = room.Position.x; x < room.Position.x + room.Size.x; x++)
			{
				for (int y = room.Position.y; y < room.Position.y + room.Size.y; y++)
				{
					nodes[x][y].Visited = true;
					numberOfRoomNodes++;
				}
			}

			rooms.push_back(room);
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::GenerateDoors(int columns, int rows)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		if (rooms[i].Position.x > 0)
		{
			doors.push_back(sf::Vector2i(rooms[i].Position.x, Random(rooms[i].Position.y, rooms[i].Position.y + rooms[i].Size.y - 1)));
		}
		if (rooms[i].Position.x + rooms[i].Size.x - 1 < columns)
		{
			doors.push_back(sf::Vector2i(rooms[i].Position.x + rooms[i].Size.x, Random(rooms[i].Position.y, rooms[i].Position.y + rooms[i].Size.y - 1)));
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::GenerateCorridors(int columns, int rows)
{
	sf::Vector2i currentNodeIndex = sf::Vector2i(Random(0, columns - 1), Random(0, rows - 1));

	while (nodes[currentNodeIndex.x][currentNodeIndex.y].Visited)
	{
		currentNodeIndex = sf::Vector2i(Random(0, columns - 1), Random(0, rows - 1));
	}

	nodes[currentNodeIndex.x][currentNodeIndex.y].Visited = true;
	visitedNodeIndicies.push_back(currentNodeIndex);

	int visitedNodeCount = 1;
	int numberOfNodes = columns * rows;

	while (visitedNodeCount < numberOfNodes - numberOfRoomNodes)
	{
		LayoutNode currentNode = nodes[currentNodeIndex.x][currentNodeIndex.y];

		bool moved = false;

		while (!moved)
		{
			sf::Vector2i nextNodeIndex = currentNodeIndex;

			int direction = Random(0, 3);

			switch (direction)
			{
			case 0: // Left
				if (!currentNode.LeftInvalid)
				{
					nextNodeIndex.x -= 1;
					currentNode.LeftInvalid = (nextNodeIndex.x < 0 || nodes[nextNodeIndex.x][nextNodeIndex.y].Visited);
					if (!currentNode.LeftInvalid)
					{
						moved = true;
						currentNode.CorridorLeft = true;
					}
				}
				break;
			case 1: // Right
				if (!currentNode.RightInvalid)
				{
					nextNodeIndex.x += 1;
					currentNode.RightInvalid = (nextNodeIndex.x >= columns || nodes[nextNodeIndex.x][nextNodeIndex.y].Visited);
					if (!currentNode.RightInvalid)
					{
						moved = true;
						currentNode.CorridorRight = true;
					}
				}
				break;
			case 2: // Up
				if (!currentNode.UpInvalid)
				{
					nextNodeIndex.y -= 1;
					currentNode.UpInvalid = (nextNodeIndex.y < 0 || nodes[nextNodeIndex.x][nextNodeIndex.y].Visited);
					if (!currentNode.UpInvalid)
					{
						moved = true;
						currentNode.CorridorUp = true;
						ladders.push_back(currentNodeIndex);
					}
				}
				break;
			case 3: // Down
				if (!currentNode.DownInvalid)
				{
					nextNodeIndex.y += 1;
					currentNode.DownInvalid = (nextNodeIndex.y >= rows || nodes[nextNodeIndex.x][nextNodeIndex.y].Visited);
					if (!currentNode.DownInvalid)
					{
						moved = true;
						currentNode.CorridorDown = true;
						ladders.push_back(currentNodeIndex);
					}
				}
			}

			nodes[currentNodeIndex.x][currentNodeIndex.y] = currentNode;

			if (moved)
			{
				currentNodeIndex = nextNodeIndex;
				nodes[currentNodeIndex.x][currentNodeIndex.y].Visited = true;
				visitedNodeIndicies.push_back(currentNodeIndex);
				visitedNodeCount++;
			}
			if (currentNode.LeftInvalid && currentNode.RightInvalid && currentNode.UpInvalid && currentNode.DownInvalid)
			{
				visitedNodeIndicies.erase(remove(visitedNodeIndicies.begin(), visitedNodeIndicies.end(), currentNodeIndex), visitedNodeIndicies.end());
				currentNodeIndex = visitedNodeIndicies[Random(0, visitedNodeIndicies.size() - 1)];
 				
				break;
			}
		}
	}
}


