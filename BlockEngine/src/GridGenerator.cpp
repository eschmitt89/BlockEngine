//
//  GridGenerator.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "GridGenerator.hpp"
#include <set>

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

Grid * GridGenerator::Generate(int columns, int rows, int rooms, int minRoomSize, int maxRoomSize, int minDoorCount, int maxDoorCount, int nodeSize, int blockWidth, int blockHeight)
{
	dimensions = sf::Vector2i(columns, rows);

	CreateNodes();

	GenerateRooms(rooms, minRoomSize, maxRoomSize, minDoorCount, maxDoorCount);

	GenerateCorridors();

	Grid* grid = new Grid(NodeValueToGridValue(dimensions.x, nodeSize), NodeValueToGridValue(dimensions.y, nodeSize), blockWidth, blockHeight);

	FillRooms(grid, nodeSize, blockWidth, blockHeight);
	
	FillCorridors(grid, nodeSize);

	FindHorizontalAreas(grid, nodeSize);
	FillHorizontalAreas(grid, nodeSize);

	FindVerticalAreas(grid, nodeSize);
	FillVerticalAreas(grid, nodeSize);

	FindAndSetCornerBlocks(grid);
	FindAndSetLadderEnds(grid);

	return grid;
}

////////////////////////////////////////////////////////////////////////


void GridGenerator::CreateNodes()
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

void GridGenerator::GenerateRooms(int roomCount, int minRoomSize, int maxRoomSize, int minDoors, int maxDoors)
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
			GridRoom room = GridRoom(roomPosition, roomSize);
			GenerateDoors(room, minDoors, maxDoors);
			rooms.push_back(room);
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::GenerateDoors(GridRoom room, int minDoors, int maxDoors)
{
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

void GridGenerator::FillRooms(Grid * grid, int nodeSize, int blockWidth, int blockHeight)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		sf::Vector2f roomPosition = NodeIndexToGridPosition(rooms[i].position, nodeSize, blockWidth, blockHeight);
		sf::Vector2f roomSize = sf::Vector2f(NodeValueToGridValue(rooms[i].size.x - 1, nodeSize) * blockWidth, NodeValueToGridValue(rooms[i].size.y - 1, nodeSize) * blockHeight);

		grid->SetBlockType(roomPosition, roomSize, BlockType::Empty);
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FillCorridors(Grid * grid, int nodeSize)
{
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
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FindHorizontalAreas(Grid * grid, int nodeSize)
{
	// Go through each node and look for horizontal sections
	for (int x = 0; x < nodes.size(); x++)
	{
		for (int y = 0; y < nodes[x].size(); y++)
		{
			GridNode* node = nodes[x][y];
			sf::Vector2i minGridIndex = NodeIndexToGridIndex(node->index, nodeSize);
			sf::Vector2i maxGridIndex = sf::Vector2i(minGridIndex.x, minGridIndex.y + nodeSize - 1);
			
			// If the node is a horizontal section find its minimum (left) and maximum (right) indicies
			if (node->leftNode || node->rightNode)
			{
				while (grid->GetBlockType(minGridIndex.x - 1, minGridIndex.y) != BlockType::Solid)
				{
					minGridIndex.x--;
				}
				while (grid->GetBlockType(maxGridIndex.x + 1, maxGridIndex.y) != BlockType::Solid)
				{
					maxGridIndex.x++;
				}

				// Add the horizontal node if it is new
				if (find(horizontalAreas.begin(), horizontalAreas.end(), Vector4i(minGridIndex, maxGridIndex)) == horizontalAreas.end())
				{
					horizontalAreas.push_back(Vector4i(minGridIndex, maxGridIndex));
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FindVerticalAreas(Grid * grid, int nodeSize)
{
	// Go through each node and look for horizontal and vertical sections
	for (int x = 0; x < nodes.size(); x++)
	{
		for (int y = 0; y < nodes[x].size(); y++)
		{
			GridNode* node = nodes[x][y];
			sf::Vector2i minGridIndex = NodeIndexToGridIndex(node->index, nodeSize);
			sf::Vector2i maxGridIndex = sf::Vector2i(minGridIndex.x + nodeSize - 1, minGridIndex.y);

			// If the node is a vertical section find its minimum (top) and maximum (bottom) indicies
			if (node->upNode || node->downNode)
			{
				while (grid->GetBlockType(minGridIndex.x, minGridIndex.y - 1) != BlockType::Solid)
				{
					minGridIndex.y--;
				}
				while (grid->GetBlockType(maxGridIndex.x, maxGridIndex.y + 1) != BlockType::Solid)
				{
					maxGridIndex.y++;
				}

				// Add the vertical node if it is new
				if (find(verticalAreas.begin(), verticalAreas.end(), Vector4i(minGridIndex, maxGridIndex)) == verticalAreas.end())
				{
					verticalAreas.push_back(Vector4i(minGridIndex, maxGridIndex));
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FillHorizontalAreas(Grid * grid, int nodeSize)
{

}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FillVerticalAreas(Grid * grid, int nodeSize)
{
	for (int i = 0; i < verticalAreas.size(); i++)
	{
		// Get the minimum and maximim indicies for the vertical section
		sf::Vector2i minIndex = sf::Vector2i(verticalAreas[i].x1, verticalAreas[i].y1);
		sf::Vector2i maxIndex = sf::Vector2i(verticalAreas[i].x2, verticalAreas[i].y2);

		// Set the current indicies x position to a random position within the section and its y position to the bottom of the section
		sf::Vector2i currentIndex = sf::Vector2i(Random(minIndex.x, maxIndex.x), maxIndex.y + 1);

		// Continue building up until the top of the section is reached
		while (currentIndex.y > minIndex.y)
		{
			// Choose a random vertical build type (ladder, platform, or solid platform)
			int buildType = Random(0, 2);

			switch (buildType)
			{
			case 0: // Ladder
			{
				GenerateLadder(currentIndex, minIndex, maxIndex, grid, 2, 5);
				break;
			}
			case 1: // Platform
			{
				GeneratePlatform(currentIndex, minIndex, maxIndex, grid, 2, nodeSize);
				break;
			}
			case 2: // Solid platform
			{
				GenerateSolidPlatform(currentIndex, minIndex, maxIndex, grid, 2, nodeSize / 2);
				break;
			}
			}
		}
	}
}

void GridGenerator::GenerateLadder(sf::Vector2i & currentIndex, sf::Vector2i minIndex, sf::Vector2i maxIndex, Grid * grid, int minLadderHeight, int maxLadderHeight)
{
	// Determine the length of the ladder and how far the player will have to jump to reach it
	int verticalJumpDistance = Random(0, 3);
	int horizontalJumpDistance = verticalJumpDistance == 3 ? Random(0, 2) : Random(0, 3);
	int horizontalJumpDirection = Random(0, 1) == 0 ? -1 : 1;
	int ladderHeight = Random(minLadderHeight, maxLadderHeight);

	// Move the ladder's start position horizontally in the jump direction by the jump distance amount
	if (currentIndex.x + (horizontalJumpDirection * horizontalJumpDistance) >= minIndex.x && currentIndex.x + (horizontalJumpDirection * horizontalJumpDistance) <= maxIndex.x)
	{
		currentIndex.x += (horizontalJumpDirection * horizontalJumpDistance);
	}

	// Move the ladder's start position vertically by the jump distance amount
	if (currentIndex.y - verticalJumpDistance > minIndex.y)
	{
		currentIndex.y -= verticalJumpDistance;
	}

	// Build the ladder its specified height
	for (int i = 0; i < ladderHeight; i++)
	{
		if (currentIndex.y - 1 > minIndex.y)
		{
			currentIndex.y--;
			grid->SetBlockType(currentIndex, BlockType::Ladder);
		}
		else
		{
			// Stop if the ladder's intended position is above the top of the section
			currentIndex.y = minIndex.y;
		}
	}
}

void GridGenerator::GeneratePlatform(sf::Vector2i & currentIndex, sf::Vector2i minIndex, sf::Vector2i maxIndex, Grid * grid, int minPlatformLength, int maxPlatformLength)
{
	// Determine the length of the platform and how far the player will have to jump to reach it
	int verticalJumpDistance = 2;
	int horizontalJumpDistance = Random(0, 3);
	int horizontalJumpDirection = Random(0, 1) == 0 ? -1 : 1;
	int platformLength = Random(minPlatformLength, maxPlatformLength);
	int platformDirection = Random(0, 1) == 0 ? -1 : 1;

	// Move the platform's start position horizontally in the jump direction by the jump distance amount
	if (currentIndex.x + (horizontalJumpDirection * horizontalJumpDistance) >= minIndex.x && currentIndex.x + (horizontalJumpDirection * horizontalJumpDistance) <= maxIndex.x)
	{
		currentIndex.x += (horizontalJumpDirection * horizontalJumpDistance);
	}

	// If the corner's position is on an edge of the section make its direction move away from the edge
	if (currentIndex.x == minIndex.x)
	{
		platformDirection = 1;
	}
	else if (currentIndex.x == maxIndex.x)
	{
		platformDirection = -1;
	}

	// Move the platform's start position vertically by the jump distance amount
	if (currentIndex.y - verticalJumpDistance > minIndex.y)
	{
		// Place the platform's start block
		int actualPlatformLength = 1;
		currentIndex.y -= verticalJumpDistance;
		grid->SetBlockType(currentIndex, BlockType::Platform);

		// Build out the platform's length
		for (int i = 0; i < platformLength; i++)
		{
			if (currentIndex.x + platformDirection >= minIndex.x && currentIndex.x + platformDirection <= maxIndex.x)
			{
				actualPlatformLength++;
				currentIndex.x += platformDirection;
				grid->SetBlockType(currentIndex, BlockType::Platform);
			}
		}

		// Set the currentIndex's horizontal value to a random location on the platform
		currentIndex.x -= (platformDirection * Random(0, actualPlatformLength - 1));
	}
	else
	{
		// Stop if the platform's intended position is above the top of the section
		currentIndex.y = minIndex.y;
	}
}

void GridGenerator::GenerateSolidPlatform(sf::Vector2i & currentIndex, sf::Vector2i minIndex, sf::Vector2i maxIndex, Grid * grid, int minPlatformLength, int maxPlatformLength)
{
	// Determine the length of the corner's platform and how far the player will have to jump to reach it
	int verticalJumpDistance = 3;
	int horizontalJumpDistance = Random(1, 3);
	int horizontalJumpDirection = Random(0, 1) == 0 ? -1 : 1;
	int platformLength = Random(minPlatformLength, maxPlatformLength);

	// If the corner's position is on an edge of the section make its direction move away from the edge
	if (currentIndex.x == minIndex.x)
	{
		horizontalJumpDirection = 1;
	}
	else if (currentIndex.x == maxIndex.x)
	{
		horizontalJumpDirection = -1;
	}

	// Move the corner's start position horizontally in the jump direction by the jump distance amount
	for (int i = 0; i < horizontalJumpDistance; i++)
	{
		if (currentIndex.x + horizontalJumpDirection >= minIndex.x && currentIndex.x + horizontalJumpDirection <= maxIndex.x)
		{
			currentIndex.x += horizontalJumpDirection;
		}
	}

	// Move the corner's start position vertically by the jump distance amount
	if (currentIndex.y - verticalJumpDistance > minIndex.y)
	{
		// Place the corner's start block
		int actualPlatformLength = 1;
		int platformDirection = horizontalJumpDirection;
		currentIndex.y -= verticalJumpDistance;
		grid->SetBlockType(currentIndex, BlockType::Solid);

		// Build out the corner's platform length
		for (int i = 1; i < platformLength; i++)
		{
			if (currentIndex.x + platformDirection >= minIndex.x && currentIndex.x + platformDirection <= maxIndex.x)
			{
				actualPlatformLength++;
				currentIndex.x += platformDirection;
				grid->SetBlockType(currentIndex, BlockType::Solid);
			}
		}

		// Set the currentIndex's horizontal value to a random location on the platform
		currentIndex.x -= (platformDirection * Random(0, actualPlatformLength - 1));
	}
	else
	{
		// Stop if the corner's intended position is above the top of the section
		currentIndex.y = minIndex.y;
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FindAndSetCornerBlocks(Grid * grid)
{
	// Find all the corner blocks and set their type to corner
	for (int x = 0; x < grid->GetDimensions().x; x++)
	{
		for (int y = 0; y < grid->GetDimensions().y; y++)
		{
			if (grid->GetBlockType(x, y) == BlockType::Solid)
			{
				BlockNeighbors blockNeighbors = grid->GetBlockNeighbors(x, y);

				if ((blockNeighbors.Left == BlockType::Empty && blockNeighbors.TopLeft == BlockType::Empty && blockNeighbors.Top == BlockType::Empty) ||
					(blockNeighbors.Right == BlockType::Empty && blockNeighbors.TopRight == BlockType::Empty && blockNeighbors.Top == BlockType::Empty))
				{
					grid->SetBlockType(sf::Vector2i(x, y), BlockType::Corner);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void GridGenerator::FindAndSetLadderEnds(Grid * grid)
{
	// Find all the corner blocks and set their type to corner
	for (int x = 0; x < grid->GetDimensions().x; x++)
	{
		for (int y = 0; y < grid->GetDimensions().y; y++)
		{
			if (grid->GetBlockType(x, y) == BlockType::Ladder)
			{
				BlockNeighbors blockNeighbors = grid->GetBlockNeighbors(x, y);

				if (blockNeighbors.Top != BlockType::Ladder && blockNeighbors.Top != BlockType::LadderTop)
				{
					grid->SetBlockType(sf::Vector2i(x, y), BlockType::LadderTop);
				}
				if (blockNeighbors.Bottom != BlockType::Ladder)
				{
					grid->SetBlockType(sf::Vector2i(x, y), BlockType::LadderBottom);
				}
			}
		}
	}
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

sf::Vector2f GridGenerator::NodeIndexToGridPosition(sf::Vector2i index, int nodeSize, int blockWidth, int blockHeight)
{
	return sf::Vector2f(NodeValueToGridValue(index.x, nodeSize) * blockWidth, NodeValueToGridValue(index.y, nodeSize) * blockHeight);
}

////////////////////////////////////////////////////////////////////////

