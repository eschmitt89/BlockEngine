//
//  GridLayoutGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef GridLayoutGenerator_hpp
#define GridLayoutGenerator_hpp

#include "GridLayout.hpp"

using namespace std;

class GridLayoutGenerator
{
public:
	GridLayoutGenerator();
    ~GridLayoutGenerator();

	GridLayout Generate(int columns, int rows, int maxRooms, int minRoomSize, int maxRoomSize);

private:
	sf::Vector2i dimensions;
	vector<LayoutRoom> rooms;
	vector<vector<LayoutNode>> nodes;
	vector<vector<bool>> visitedNodes;
	vector<sf::Vector2i> visitedNodeIndicies;
	int numberOfRoomNodes;

	void InitializeNodes();

	void GenerateRooms(int maxNumberOfRooms, int minRoomSize, int maxRoomSize);

	void GenerateCorridors();

};

#endif /* GridLayoutGenerator_hpp */
