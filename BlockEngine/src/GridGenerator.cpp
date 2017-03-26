//
//  GridGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridGenerator.hpp"

GridGenerator::GridGenerator()
{

}

////////////////////////////////////////////////////////////////////////

GridGenerator::~GridGenerator()
{
	// Delete nodes
	for (int x = 0; x < nodes.size(); x++)
	{
		for (int y = 0; y < nodes[x].size(); y++)
		{
			delete nodes[x][y];
		}
		nodes[x].clear();
	}
	nodes.clear();
}

////////////////////////////////////////////////////////////////////////

Grid * GridGenerator::Generate(int columns, int rows, int rooms, int minRoomSize, int maxRoomSize, int nodeSize, int blockWidth, int blockHeight)
{
	dimensions = sf::Vector2i(columns, rows);

	InitializeNodes();

	GenerateRooms(rooms, minRoomSize, maxRoomSize);

	GenerateDoors(1, 4);

	GenerateCorridors();

	return GenerateGrid(nodeSize, blockWidth, blockHeight);
}

////////////////////////////////////////////////////////////////////////


void GridGenerator::InitializeNodes()
{
	for (int x = 0; x < dimensions.x; x++)
	{
		vector<GridNode*> nodeColumn;

		for (int y = 0; y < dimensions.y; y++)
		{
			nodeColumn.push_back(new GridNode(x, y, dimensions));
		}

		nodes.push_back(nodeColumn);
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::GenerateRooms(int roomCount, int minRoomSize, int maxRoomSize)
{
	int roomPlacementAttemps = roomCount * 10;

	// Attempt to place rooms
	for (int i = 0; i < roomPlacementAttemps; i++)
	{
		// Done when enough rooms have been placed
		if (rooms.size() == roomCount)
		{
			return;
		}

		// Choose a random room position and size
		sf::Vector2i roomSize = sf::Vector2i(Random(minRoomSize, maxRoomSize), Random(minRoomSize, maxRoomSize));
		sf::Vector2i roomPosition = sf::Vector2i(Random(0, dimensions.x - roomSize.x - 1), Random(0, dimensions.y - roomSize.y - 1));

		// If the new rooms does not overlap existing rooms, place it
		if (!RoomOverlapsExistingRoom(roomPosition, roomSize))
		{
			PlaceRoomNodes(roomPosition, roomSize);
			rooms.push_back(GridRoom(roomPosition, roomSize));
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::GenerateDoors(int minDoors, int maxDoors)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		vector<GridNode*> validDoorNodes;
		GridRoom room = rooms[i];
		int doorsPlaced = 0;
		int doorsToPlace = Random(minDoors, maxDoors);
		
		// Find the room's border nodes that could be doors

		while (doorsPlaced < doorsToPlace)
		{
			int x = Random(0, 1) == 0 ? room.position.x : room.position.x + room.size.x - 1;
			int y = Random(0, 1) == 0 ? room.position.y : room.position.y + room.size.y - 1;

			GridNode* node = nodes[x][y];

			if (x == room.position.x && !nodes[x][y]->leftInvalid)
			{
				nodes[x][y]->leftNode = nodes[x - 1][y];
				doorsPlaced++;
			}
			else if (x == (room.position.x + room.size.x - 1) && !nodes[x][y]->rightInvalid)
			{
				nodes[x][y]->rightNode = nodes[x + 1][y];
				doorsPlaced++;
			}

			if (y == room.position.y && !nodes[x][y]->upInvalid)
			{
				nodes[x][y]->upNode = nodes[x][y - 1];
				doorsPlaced++;
			}
			else if (y == (room.position.y + room.size.y - 1) && !nodes[x][y]->downInvalid)
			{
				nodes[x][y]->downNode = nodes[x][y + 1];
				doorsPlaced++;
			}
		}

		//for (int x = room.position.x; x < room.position.x + room.size.x; x++)
		//{
		//	for (int y = room.position.y; y < room.position.y + room.size.y; y++)
		//	{
		//		if (x == room.position.x || x == (room.position.x + room.size.x - 1) || y == room.position.y || y == (room.position.y + room.size.y - 1))
		//		{
		//			validDoorNodes.push_back(nodes[x][y]);
		//		}
		//		if (x == room.position.x)
		//		{
		//			// door on left

		//		}
		//	}
		//}

		//// Place a random number of doors in each room
		//while (validDoorNodes.size() > 0 && doorsPlaced < doorsToPlace)
		//{
		//	GridNode* doorNode = validDoorNodes[Random(0, validDoorNodes.size() - 1)];

		//	bool doorPlaced = false;

		//	while (!doorPlaced)
		//	{
		//		int direction = Random(0, 3);

		//		switch (direction)
		//		{
		//		case 0: // Left
		//			if (!doorNode->leftInvalid)
		//			{
		//				doorNode->leftNode = nodes[doorNode->index.x - 1][doorNode->index.y];
		//				doorPlaced = true;
		//				doorsPlaced++;
		//			}
		//			break;
		//		case 1: // Right
		//			if (!doorNode->rightInvalid)
		//			{
		//				doorNode->rightNode = nodes[doorNode->index.x + 1][doorNode->index.y];
		//				doorPlaced = true;
		//				doorsPlaced++;
		//			}
		//			break;
		//		case 2: // Up
		//			if (!doorNode->upInvalid)
		//			{
		//				doorNode->upNode = nodes[doorNode->index.x][doorNode->index.y - 1];
		//				doorPlaced = true;
		//				doorsPlaced++;
		//			}
		//			break;
		//		case 3: // Down
		//			if (!doorNode->downInvalid)
		//			{
		//				doorNode->downNode = nodes[doorNode->index.x][doorNode->index.y + 1];
		//				doorPlaced = true;
		//				doorsPlaced++;
		//			}
		//			break;
		//		}
		//	}
		//}
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::GenerateCorridors()
{
	// Keep track of the valid nodes
	vector<GridNode*> validNodes;

	// Choose a random node index as the current node index
	GridNode* currentNode = nodes[Random(0, dimensions.x - 1)][Random(0, dimensions.y - 1)];

	// If the current node index is visited, choose another node index
	while (currentNode->visited)
	{
		currentNode = nodes[Random(0, dimensions.x - 1)][Random(0, dimensions.y - 1)];
	}

	// Set the current node to visisted and add it to the set of valid nodes
	currentNode->visited = true;
	validNodes.push_back(currentNode);

	int visitedNodes = validNodes.size();
	int totalNodes = dimensions.x * dimensions.y;

	// Continue generating corridors until every node is visisted
	while (visitedNodes < totalNodes - roomNodeCount)
	{
		bool moved = false;
		vector<int> directions = { 0, 1, 2, 3 };

		while (!moved)
		{
			GridNode* nextNode = currentNode;

			// Try to move in a random untried direction
			int direction = Random(0, 3);//directions[Random(0, directions.size() - 1)];

			switch (direction)
			{
			case 0: // Left
				if (!currentNode->leftInvalid)
				{
					nextNode = nodes[currentNode->index.x - 1][currentNode->index.y];
					currentNode->leftInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->leftNode = nextNode;
						moved = true;
					}
				}
				else
				{
					VectorEraseElement(directions, 0);
				}
				break;
			case 1: // Right
				if (!currentNode->rightInvalid)
				{
					nextNode = nodes[currentNode->index.x + 1][currentNode->index.y];
					currentNode->rightInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->rightNode = nextNode;
						moved = true;
					}
				}
				else
				{
					VectorEraseElement(directions, 1);
				}
				break;
			case 2: // Up
				if (!currentNode->upInvalid)
				{
					nextNode = nodes[currentNode->index.x][currentNode->index.y - 1];
					currentNode->upInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->upNode = nextNode;
						moved = true;
					}
				}
				else
				{
					VectorEraseElement(directions, 2);
				}
				break;
			case 3: // Down
				if (!currentNode->downInvalid)
				{
					nextNode = nodes[currentNode->index.x][currentNode->index.y + 1];
					currentNode->downInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->downNode = nextNode;
						moved = true;
					}
				}
				else
				{
					VectorEraseElement(directions, 3);
				}
				break;
			}

			// If a valid direction was found move to the node in that direction
			if (moved)
			{
				visitedNodes++;
				currentNode = nextNode;
				currentNode->visited = true;
				validNodes.push_back(currentNode);
			}

			// If no valid directions were found choose a random valid node and start over
			if (currentNode->AllDirectionsInvalid())
			{
				VectorEraseElement(validNodes, currentNode);
				currentNode = validNodes[Random(0, validNodes.size() - 1)];
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

Grid * GridGenerator::GenerateGrid(int nodeSize, int blockWidth, int blockHeight)
{
	Grid* grid = new Grid(NodeValueToGridValue(dimensions.x, nodeSize), NodeValueToGridValue(dimensions.y, nodeSize), blockWidth, blockHeight);

	for (int x = 0; x < nodes.size(); x++)
	{
		for (int y = 0; y < nodes[x].size(); y++)
		{
			GridNode* node = nodes[x][y];

			sf::Vector2i gridIndex = NodeIndexToGridIndex(node->index, nodeSize);

			for (int i = 0; i < nodeSize; i++)
			{
				for (int j = 0; j < nodeSize; j++)
				{
					grid->SetBlockType(gridIndex.x + i, gridIndex.y + j, BlockType::Empty);

					if (node->leftNode)
					{
						grid->SetBlockType(gridIndex.x - (i + 1), gridIndex.y + j, BlockType::Empty);
					}
					if (node->rightNode)
					{
						grid->SetBlockType(gridIndex.x + (i + 1), gridIndex.y + j, BlockType::Empty);
					}
					if (node->upNode)
					{
						grid->SetBlockType(gridIndex.x + j, gridIndex.y - (i + 1), BlockType::Empty);
					}
					if (node->downNode)
					{
						grid->SetBlockType(gridIndex.x + j, gridIndex.y + (i + 1), BlockType::Empty);
					}
				}
			}
		}
	}

	return grid;
}

////////////////////////////////////////////////////////////////////////

bool GridGenerator::RoomOverlapsExistingRoom(sf::Vector2i roomPosition, sf::Vector2i roomSize)
{
	for (int i  = 0; i < rooms.size(); i++)
	{
		// Add a 1 node buffer around the existing room to prevent adjacent room placement
		if (Intersect(roomPosition, roomSize, rooms[i].position - sf::Vector2i(1, 1), rooms[i].size + sf::Vector2i(2, 2)))
		{
			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::PlaceRoomNodes(sf::Vector2i roomPosition, sf::Vector2i roomSize)
{
	for (int x = roomPosition.x; x < roomPosition.x + roomSize.x; x++)
	{
		for (int y = roomPosition.y; y < roomPosition.y + roomSize.y; y++)
		{
			// Set each node that the room occupies to visisted
			nodes[x][y]->visited = true;

			// Keep track of the number of room nodes
			roomNodeCount++;

			//// Connect all the interior nodes of the room
			//if (x < roomPosition.x + roomSize.x - 1)
			//{
			//	nodes[x][y]->rightNode = nodes[x + 1][y];
			//}
			//if (y < roomPosition.y + roomSize.y - 1)
			//{
			//	nodes[x][y]->downNode = nodes[x][y + 1];
			//}
		}
	}
}

////////////////////////////////////////////////////////////////////////

int GridGenerator::NodeValueToGridValue(int index, int nodeSize)
{
	return (index * (nodeSize + 1)) + 1;
}

////////////////////////////////////////////////////////////////////////


sf::Vector2i GridGenerator::NodeIndexToGridIndex(sf::Vector2i index, int nodeSize)
{
	return sf::Vector2i(NodeValueToGridValue(index.x, nodeSize), NodeValueToGridValue(index.y, nodeSize));
}

////////////////////////////////////////////////////////////////////////

