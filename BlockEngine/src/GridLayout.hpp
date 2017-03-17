//
//  GridLayout.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef GridLayout_hpp
#define GridLayout_hpp

#include "SFML/System.hpp"
#include "LayoutCell.hpp"
#include "LayoutRoom.hpp"
#include <vector>

#define RoomMinSize 4
#define RoomMaxSize 16

using namespace std;

class GridLayout
{
public:
	GridLayout(vector<vector<LayoutCell>> corridors, vector<LayoutRoom> rooms, sf::Vector2i dimensions);
    ~GridLayout();

	vector<vector<LayoutCell>> Corridors;
	vector<LayoutRoom> Rooms;
	sf::Vector2i Dimensions;

private:
	
};

#endif /* GridLayout_hpp */
