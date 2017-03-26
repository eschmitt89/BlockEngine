//
//  GridGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef GridGenerator_hpp
#define GridGenerator_hpp

#include "Grid.hpp"
#include "GridNode.hpp"
#include "GridRoom.hpp"
#include <vector>

using namespace std;

class GridGenerator
{
public:
	GridGenerator();
    ~GridGenerator();

	Grid * Generate(int columns, int rows, int rooms, int minRoomSize, int maxRoomSize, int minDoorCount, int maxDoorCount, int nodeSize, int blockWidth, int blockHeight);

private:
	sf::Vector2i dimensions;
	vector<vector<GridNode*>> nodes;
	vector<Vector4i> horizontalAreas;
	vector<Vector4i> verticalAreas;
	vector<GridRoom> rooms;
	int roomNodeCount;

	void CreateNodes();

	void GenerateRooms(int roomCount, int minRoomSize, int maxRoomSize, int minDoors, int maxDoors);
	void GenerateDoors(GridRoom room, int minDoors, int maxDoors);
	void GenerateCorridors();

	void FillRooms(Grid* grid, int nodeSize, int blockWidth, int blockHeight);
	void FillCorridors(Grid* grid, int nodeSize);

	void FindHorizontalAreas(Grid* grid, int nodeSize);
	void FindVerticalAreas(Grid* grid, int nodeSize);

	void FillHorizontalAreas(Grid* grid, int nodeSize);
	void FillVerticalAreas(Grid* grid, int nodeSize);

	void GenerateLadder(sf::Vector2i& currentIndex, sf::Vector2i minIndex, sf::Vector2i maxIndex, Grid* grid, int minLadderHeight, int maxLadderHeight);
	void GeneratePlatform(sf::Vector2i& currentIndex, sf::Vector2i minIndex, sf::Vector2i maxIndex, Grid* grid, int minPlatformLength, int maxPlatformLength);
	void GenerateSolidPlatform(sf::Vector2i& currentIndex, sf::Vector2i minIndex, sf::Vector2i maxIndex, Grid* grid, int minPlatformLength, int maxPlatformLength);

	void FindAndSetCornerBlocks(Grid* grid);
	void FindAndSetLadderEnds(Grid* grid);

	bool RoomOverlapsExistingRoom(sf::Vector2i roomPosition, sf::Vector2i roomSize);
	void PlaceRoomNodes(sf::Vector2i roomPosition, sf::Vector2i roomSize);

	GridNode* GetLeftNode(GridNode* node);
	GridNode* GetRightNode(GridNode* node);
	GridNode* GetUpNode(GridNode* node);
	GridNode* GetDownNode(GridNode* node);

	int NodeValueToGridValue(int index, int nodeSize);
	sf::Vector2i NodeIndexToGridIndex(sf::Vector2i index, int nodeSize);
	sf::Vector2f NodeIndexToGridPosition(sf::Vector2i index, int nodeSize, int blockWidth, int blockHeight);
};

#endif /* GridGenerator_hpp */
