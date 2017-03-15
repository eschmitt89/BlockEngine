//
//  GridGenerator.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef GridGenerator_hpp
#define GridGenerator_hpp

#include "Cell.hpp"
#include <vector>

#define RoomMinSize 4
#define RoomMaxSize 16

using namespace std;

class GridGenerator
{
public:
	GridGenerator();
    ~GridGenerator();
    
	//Grid* Generate(int columns, int rows, int blockWidth, int blockHeight, int numberOfRooms);
	//vector<Vector4i> Generate2();

	vector<vector<Cell>> Generate();
	vector<vector<Cell>> CreateCells(int columns, int rows);

private:
	//vector<Room> rooms;

	//void SpawnRooms(Grid* grid, int numberOfRooms, int maxAttempts);
	//Room GenerateRoom(Grid* grid);
	//bool RoomCollision(Room room);

	

	

};

#endif /* GridGenerator_hpp */
