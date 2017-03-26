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
	vector<sf::Vector2i> horizontalNodes;
	vector<sf::Vector2i> verticalNodes;
	vector<GridRoom> rooms;
	int roomNodeCount;

	void CreateNodes();
	void GenerateRooms(int roomCount, int minRoomSize, int maxRoomSize);
	void GenerateDoors(int minDoors, int maxDoors);
	void GenerateCorridors();
	
	Grid* GenerateGrid(int nodeSize, int blockWidth, int blockHeight);
	void GenerateLadders(Grid* grid, int nodeSize);

	bool RoomOverlapsExistingRoom(sf::Vector2i roomPosition, sf::Vector2i roomSize);
	void PlaceRoomNodes(sf::Vector2i roomPosition, sf::Vector2i roomSize);

	GridNode* GetLeftNode(GridNode* node);
	GridNode* GetRightNode(GridNode* node);
	GridNode* GetUpNode(GridNode* node);
	GridNode* GetDownNode(GridNode* node);

	int NodeValueToGridValue(int index, int nodeSize);
	sf::Vector2i NodeIndexToGridIndex(sf::Vector2i index, int nodeSize);
};

#endif /* GridGenerator_hpp */
