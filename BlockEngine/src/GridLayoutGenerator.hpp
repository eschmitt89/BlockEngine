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
	vector<sf::Vector2i> doors;
	vector<sf::Vector2i> ladders;
	vector<vector<LayoutNode>> nodes;
	vector<sf::Vector2i> visitedNodeIndicies;
	int numberOfRoomNodes;

	void InitializeNodes(int columns, int rows);

	void GenerateRooms(int columns, int rows, int maxNumberOfRooms, int minRoomSize, int maxRoomSize);

	void GenerateDoors(int columns, int rows);

	void GenerateCorridors(int columns, int rows);

};

#endif /* GridLayoutGenerator_hpp */
