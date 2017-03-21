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
#include "LayoutNode.hpp"
#include "LayoutRoom.hpp"
#include <vector>


using namespace std;

class GridLayout
{
public:
	GridLayout(sf::Vector2i dimensions, vector<LayoutRoom> rooms, vector<sf::Vector2i> doors, vector<sf::Vector2i> ladders, vector<vector<LayoutNode>> corridors);
    ~GridLayout();

	sf::Vector2i Dimensions;
	vector<LayoutRoom> Rooms;
	vector<sf::Vector2i> Doors;
	vector<sf::Vector2i> Ladders;
	vector<vector<LayoutNode>> Corridors;
	
	

private:
	
};

#endif /* GridLayout_hpp */
