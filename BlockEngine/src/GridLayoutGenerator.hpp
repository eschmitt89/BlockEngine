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

#define RoomMinSize 4
#define RoomMaxSize 16

using namespace std;

class GridLayoutGenerator
{
public:
	GridLayoutGenerator();
    ~GridLayoutGenerator();
    
	//Grid* Generate(int columns, int rows, int blockWidth, int blockHeight, int numberOfRooms);
	//vector<Vector4i> Generate2();

	GridLayout Generate();
	//vector<vector<GridLayout>> CreateCells(int columns, int rows);

private:
	//vector<Room> rooms;

	//void SpawnRooms(Grid* grid, int numberOfRooms, int maxAttempts);
	//Room GenerateRoom(Grid* grid);
	//bool RoomCollision(Room room);

	//void InitializeCorridors(int columns, int rows);
	//void GenerateRooms(int maxNumberOfRooms, int minRoomSize, int maxRoomSize);
	//void GenerateCorridors();

	//bool RoomOverlapsExistingRoom(int column, int row, int width, int height);

};

#endif /* GridLayoutGenerator_hpp */
