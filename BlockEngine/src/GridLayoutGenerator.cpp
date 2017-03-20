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

	InitializeNodes();

	GenerateRooms(maxRooms, minRoomSize, maxRoomSize);
	
	GenerateCorridors();

	return GridLayout(nodes, rooms, dimensions);
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::InitializeNodes()
{
	for (int x = 0; x < dimensions.x; x++)
	{
		vector<LayoutNode> nodeColumn;
		vector<bool> visitedNodeColumn;

		for (int y = 0; y < dimensions.y; y++)
		{
			nodeColumn.push_back(LayoutNode());
			visitedNodeColumn.push_back(false);
		}

		nodes.push_back(nodeColumn);
		visitedNodes.push_back(visitedNodeColumn);
	}
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::GenerateRooms(int maxNumberOfRooms, int minRoomSize, int maxRoomSize)
{
	numberOfRoomNodes = 0;
	int maxRoomPlacementAttemps = maxNumberOfRooms * 10;
	int minDoors = 1;
	int maxDoors = 4;

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
			if (Intersect(room.Position + sf::Vector2i(-1, -1), room.Size + sf::Vector2i(2, 2), rooms[j].Position, rooms[j].Size))
			{
				roomOverlapsExistingRoom = true;
				break;
			}
		}

		int doors = 0;
		int numberOfDoors = Random(minDoors, maxDoors);

		if (!roomOverlapsExistingRoom)
		{
			for (int x = room.Position.x; x < room.Position.x + room.Size.x; x++)
			{
				for (int y = room.Position.y; y < room.Position.y + room.Size.y; y++)
				{
					if (doors < numberOfDoors && (x == room.Position.x || x == room.Position.x + room.Size.x - 1))
					{
						if (Random() < 0.3)
						{
							room.Doors.push_back(sf::Vector2i(x, y));
							doors++;
						}
					}

					visitedNodes[x][y] = true;
					numberOfRoomNodes++;
				}
			}

			rooms.push_back(room);
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridLayoutGenerator::GenerateCorridors()
{
	sf::Vector2i currentNode = sf::Vector2i(Random(0, dimensions.x - 1), Random(0, dimensions.y - 1));

	while (visitedNodes[currentNode.x][currentNode.y])
	{
		currentNode = sf::Vector2i(Random(0, dimensions.x - 1), Random(0, dimensions.y - 1));
	}

	int visitedNodeCount = 0;
	int numberOfNodes = dimensions.x * dimensions.y;

	while (visitedNodeCount < numberOfNodes - numberOfRoomNodes)
	{
		bool moved = false;
		bool leftInvalid = false;
		bool rightInvalid = false;
		bool upInvalid = false;
		bool downInvalid = false;

		while (!moved)
		{
			sf::Vector2i nextNode = currentNode;

			int direction = Random(0, 3);

			switch (direction)
			{
			case 0: // Left
				if (!leftInvalid)
				{
					nextNode.x -= 1;
					leftInvalid = (nextNode.x < 0 || visitedNodes[nextNode.x][nextNode.y]);
					if (!leftInvalid)
					{
						moved = true;
						nodes[currentNode.x][currentNode.y].CorridorLeft = true;
					}
				}
				break;
			case 1: // Right
				if (!rightInvalid)
				{
					nextNode.x += 1;
					rightInvalid = (nextNode.x >= dimensions.x || visitedNodes[nextNode.x][nextNode.y]);
					if (!rightInvalid)
					{
						moved = true;
						nodes[currentNode.x][currentNode.y].CorridorRight = true;
					}
				}
				break;
			case 2: // Up
				if (!upInvalid)
				{
					nextNode.y -= 1;
					upInvalid = (nextNode.y < 0 || visitedNodes[nextNode.x][nextNode.y]);
					if (!upInvalid)
					{
						moved = true;
						nodes[currentNode.x][currentNode.y].CorridorUp = true;
					}
				}
				break;
			case 3: // Down
				if (!downInvalid)
				{
					nextNode.y += 1;
					downInvalid = (nextNode.y >= dimensions.y || visitedNodes[nextNode.x][nextNode.y]);
					if (!downInvalid)
					{
						moved = true;
						nodes[currentNode.x][currentNode.y].CorridorDown = true;
					}
				}
			}

			if (moved)
			{
				currentNode = nextNode;
				visitedNodes[currentNode.x][currentNode.y] = true;
				visitedNodeIndicies.push_back(currentNode);
				visitedNodeCount++;
			}
			if (leftInvalid && rightInvalid && upInvalid && downInvalid)
			{
				visitedNodeIndicies.erase(remove(visitedNodeIndicies.begin(), visitedNodeIndicies.end(), currentNode), visitedNodeIndicies.end());
				currentNode = visitedNodeIndicies[Random(0, visitedNodeIndicies.size() - 1)];
				break;
			}
		}
	}
}


