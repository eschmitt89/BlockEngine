//
//  Cell.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

using namespace std;

class Cell
{
public:
	Cell();
	~Cell();

	bool Visited;

	bool CorridorUp;
	bool CorridorDown;
	bool CorridorLeft;
	bool CorridorRight;

};

#endif /* Cell_hpp */
