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

	GenerateDoors(1, 3);

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
		GridRoom room = rooms[i];
		int doorsPlaced = 0;
		int doorsToPlace = Random(minDoors, maxDoors);

		while (doorsPlaced < doorsToPlace)
		{
			GridNode* node = nullptr;

			int direction = Random(0, 3);

			switch (direction)
			{
			case 0: // Left
				node = nodes[room.position.x][Random(room.position.y, room.position.y + room.size.y - 1)];
				if (!node->leftInvalid)
				{
					node->leftNode = GetLeftNode(node);
					doorsPlaced++;
				}
				break;
			case 1: // Right
				node = nodes[room.position.x + room.size.x - 1][Random(room.position.y, room.position.y + room.size.y - 1)];
				if (!node->rightInvalid)
				{
					node->rightNode = GetRightNode(node);
					doorsPlaced++;
				}
				break;
			case 2: // Up
				node = nodes[Random(room.position.x, room.position.x + room.size.x - 1)][room.position.y];
				if (!node->upInvalid)
				{
					node->upNode = GetUpNode(node);
					doorsPlaced++;
				}
				break;
			case 3: // Down
				node = nodes[Random(room.position.x, room.position.x + room.size.x - 1)][room.position.y + room.size.y - 1];
				if (!node->downInvalid)
				{
					node->downNode = GetDownNode(node);
					doorsPlaced++;
				}
				break;
			}
		}
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

		while (!moved)
		{
			GridNode* nextNode = currentNode;

			// Try to move in a random direction
			int direction = Random(0, 3);

			switch (direction)
			{
			case 0: // Left
				if (!currentNode->leftInvalid)
				{
					nextNode = GetLeftNode(currentNode);
					currentNode->leftInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->leftNode = nextNode;
						moved = true;
					}
				}
				break;
			case 1: // Right
				if (!currentNode->rightInvalid)
				{
					nextNode = GetRightNode(currentNode);
					currentNode->rightInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->rightNode = nextNode;
						moved = true;
					}
				}
				break;
			case 2: // Up
				if (!currentNode->upInvalid)
				{
					nextNode = GetUpNode(currentNode);
					currentNode->upInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->upNode = nextNode;
						moved = true;
					}
				}
				break;
			case 3: // Down
				if (!currentNode->downInvalid)
				{
					nextNode = GetDownNode(currentNode);
					currentNode->downInvalid = nextNode->visited;
					if (!nextNode->visited)
					{
						currentNode->downNode = nextNode;
						moved = true;
					}
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
		// Add a 1 node buffer around existing rooms to prevent adjacent room placement
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

			// Connect all the interior nodes of the room
			if (x < roomPosition.x + roomSize.x - 1)
			{
				nodes[x][y]->rightNode = nodes[x + 1][y];
			}
			if (y < roomPosition.y + roomSize.y - 1)
			{
				nodes[x][y]->downNode = nodes[x][y + 1];
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

GridNode * GridGenerator::GetLeftNode(GridNode * node)
{
	return nodes[node->index.x - 1][node->index.y];
}

////////////////////////////////////////////////////////////////////////

GridNode * GridGenerator::GetRightNode(GridNode * node)
{
	return nodes[node->index.x + 1][node->index.y];
}

////////////////////////////////////////////////////////////////////////

GridNode * GridGenerator::GetUpNode(GridNode * node)
{
	return nodes[node->index.x][node->index.y - 1];
}

////////////////////////////////////////////////////////////////////////

GridNode * GridGenerator::GetDownNode(GridNode * node)
{
	return nodes[node->index.x][node->index.y + 1];
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

